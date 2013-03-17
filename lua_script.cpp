#include "lua_script.h"
#include "windows.h"
#include <memory>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "lua_header.h"

struct LuaScript
{
    lua_State *lua;
    const char *filename;
};

std::unique_ptr<WCHAR []> utf8_to_wstr(const char *ansi)
{
  const int length = strlen(ansi);
  const int unicode_length = MultiByteToWideChar(CP_UTF8, 0, ansi, length, NULL, 0);
  std::unique_ptr<WCHAR []> unicode(new WCHAR[unicode_length + 1]);
  MultiByteToWideChar(CP_UTF8, 0, ansi, length, unicode.get(), unicode_length);
  unicode[unicode_length] = 0;
  return unicode;
}

std::unique_ptr<char []> wstr_to_ansi(WCHAR *wstr)
{
  const int wstr_length = wcslen(wstr);
  const int ansi_length = WideCharToMultiByte(CP_ACP, 0, wstr, wstr_length, NULL, 0, " ", NULL);
  std::unique_ptr<char []> ansi(new char[ansi_length + 1]);
  WideCharToMultiByte(CP_ACP, 0, wstr, wstr_length, ansi.get(), ansi_length, " ", NULL);
  ansi[ansi_length] = 0;
  return ansi;
}

static void show_error(const char *msg)
{
    if (msg == NULL) { return; }
    
    /*
    LuaスクリプトはUTF8で統一しているので、日本語混じりのメッセージを
    printfで表示するにはANSI(Shift JIS)に変換する必要がある。
    Windows標準でUTF8からSJISに直接変換する方法がわからなかったので、一旦ワイド文字を挟んである。
    MessageBoxのほうは折角ワイド文字にしたのでそのままUnicode版を使った。
    
    LuaスクリプトをSJISで統一してもいいのだが、
    おそらく'ソ'とか'表'でバックスラッシュ問題が起こる。
    */
    std::unique_ptr<WCHAR []> msgw(utf8_to_wstr(msg));
    std::unique_ptr<char []> msga(wstr_to_ansi(msgw.get()));
    
    printf("lua error: %s\n", msga.get());
    MessageBoxW(NULL, msgw.get(), L"ゲームのエラー", 0);
}

extern "C" {

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
    const char *filename = (const char *)lua_touserdata(L, 1);
  	
  	if (dofile(L, filename) != LUA_OK)
    {
  		  return 0;
    }
    
    lua_pushboolean(L, 1);
    return 1;
}

/** UTF8からSJISにエンコード。Lua用 */
static int encode_to_c(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isstring(tolua_S,1,0,&tolua_err))
    goto tolua_lerror;
    else
#endif
    {
        const char *msg = tolua_tostring(tolua_S, 1, 0);

        std::unique_ptr<WCHAR []> msgw(utf8_to_wstr(msg));
        std::unique_ptr<char []> msga(wstr_to_ansi(msgw.get()));
        
        tolua_pushstring(tolua_S, msga.get());
    }
    return 1;
#ifndef TOLUA_RELEASE
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'encode_to_c'.",&tolua_err);
    return 0;
#endif
}

} /* extern "C" */

LuaScript *LuaScript_Initialize()
{
    LuaScript *self = new LuaScript();
    
    self->lua = luaL_newstate();
    
  	luaL_openlibs(self->lua);
	  tolua_lua_header_open(self->lua);
	  
    lua_pushcfunction(self->lua, &encode_to_c);
    lua_setglobal(self->lua, "encode_to_c");
	  
	  return self;
}

bool LuaScript_Load(LuaScript *self, const char *filename)
{
  	printf("loading \"%s\"\n", filename);
    lua_pushcfunction(self->lua, &load_lua_script);
    lua_pushlightuserdata(self->lua, const_cast<char *>(filename));
    
    int status = lua_pcall(self->lua, 1, 1, 0);
    int result = lua_toboolean(self->lua, -1);
    
    if (result && status == LUA_OK)
    {
      	printf("loaded successfully\n", filename);
        return true;
    }
    else
    {
      	printf("loading failed\n");
        const char *msg = (lua_type(self->lua, -1) == LUA_TSTRING) ? lua_tostring(self->lua, -1) : NULL;
        show_error(msg);
        lua_pop(self->lua, 1);
        return false;
    }
}

void LuaScript_Set(LuaScript *self, const char *type, const char *name, void *data)
{
    lua_State *L = self->lua;
    tolua_pushusertype(L, data, type);
    lua_setglobal(L, name);
}

void LuaScript_Call(LuaScript *self, const char *name)
{
    lua_State *L = self->lua;
    lua_getglobal(L, name);
    
    int status = report(L, lua_pcall(L, 0, 0, 0));
    
    if (status != LUA_OK)
    {
        printf("failed to call function \"%s\"\n", name);
    }
}

void LuaScript_Finalize(LuaScript *self)
{
    if (self->lua)
    {
        lua_close(self->lua);
    }
    
    delete self;
}
