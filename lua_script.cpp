#include "lua_script.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

struct LuaScript
{
    lua_State *lua;
    const char *filename;
};

extern "C" {

static void show_error(const char *msg)
{
    // MessageBox(NULL, msg, "ƒQ[ƒ€‚ÌƒGƒ‰[", 0);
    fprintf(stderr, "lua error: %s\n", msg);
}

static int traceback(lua_State *L)
{
    const char *msg = lua_tostring(L, 1);
    if (msg)
    {
        luaL_traceback(L, L, msg, 1);
    }
    else if (!lua_isnoneornil(L, 1) && !luaL_callmeta(L, 1, "__tostring"))
    {
        lua_pushliteral(L, "(no error message)");
    }
    
    return 1;
}

static int report(lua_State *L, int status) {
  if (status != LUA_OK && !lua_isnil(L, -1))
  {
    const char *msg = lua_tostring(L, -1);
    if (msg == NULL) { msg = "(error object is not a string)"; }
    show_error(msg);
    lua_pop(L, 1);
    lua_gc(L, LUA_GCCOLLECT, 0);
  }
  return status;
}

static int dofile(lua_State *L, const char *name)
{
  int status = luaL_loadfile(L, name);
  
  if (status == LUA_OK)
  {
      int base = lua_gettop(L);
      lua_pushcfunction(L, traceback);
      lua_insert(L, base);
      status = lua_pcall(L, 0, 0, base);
      lua_remove(L, base);
  }
  
  return report(L, status);
}

static int load_lua_script(lua_State *L)
{
    LuaScript *self = (LuaScript *)lua_touserdata(L, 1);
  	
  	luaL_openlibs(L);
  	
  	fprintf(stderr, "loading \"%s\"", self->filename);
  	
  	if (dofile(L, self->filename))
    {
  		  return 0;
    }
    
    lua_pushboolean(L, 1);
    return 1;
}

} /* extern "C" */

LuaScript *LuaScript_Load(const char *filename)
{
    LuaScript *self = new LuaScript();
    
    self->filename = filename;
    self->lua = luaL_newstate();

    lua_pushcfunction(self->lua, &load_lua_script);
    lua_pushlightuserdata(self->lua, self);
    
    int status = lua_pcall(self->lua, 1, 1, 0);
    int result = lua_toboolean(self->lua, -1);
    
    if (!result || status != LUA_OK)
    {
        const char *msg = (lua_type(self->lua, -1) == LUA_TSTRING) ? lua_tostring(self->lua, -1) : NULL;
        
        if (msg == NULL)
        {
            msg = "(error object is not a string)";
        }
        
        show_error(msg);
        
        lua_pop(self->lua, 1);
        
        LuaScript_Finalize(self);
        self = NULL;
    }
    
    return self;
}

void LuaScript_Finalize(LuaScript *self)
{
    lua_close(self->lua);
    delete self;
}
