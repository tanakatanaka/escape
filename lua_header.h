/*
** Lua binding: lua_header
*/

#include "tolua.h"

#ifndef __cplusplus
#include <stdlib.h>
#endif
#ifdef __cplusplus
 extern "C" int tolua_bnd_takeownership (lua_State* L); // from tolua_map.c
#else
 int tolua_bnd_takeownership (lua_State* L); /* from tolua_map.c */
#endif
#include <string.h>

/* Exported function */
TOLUA_API int tolua_lua_header_open (lua_State* tolua_S);
LUALIB_API int luaopen_lua_header (lua_State* tolua_S);


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Mess");
 tolua_usertype(tolua_S,"Twod");
 tolua_usertype(tolua_S,"Room");
 tolua_usertype(tolua_S,"Console");
 tolua_usertype(tolua_S,"Player");
}

/* function: console_d_bag */
static int tolua_lua_header_console_d_bag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Console",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Console* self = ((Console*)  tolua_tousertype(tolua_S,1,0));
 {
  const char* tolua_ret = (const char*)  console_d_bag(self);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'console_d_bag'.",&tolua_err);
 return 0;
#endif
}

/* function: Player_get_area */
static int tolua_lua_header_Player_get_area00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Player* self = ((Player*)  tolua_tousertype(tolua_S,1,0));
 {
  int tolua_ret = (int)  Player_get_area(self);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Player_get_area'.",&tolua_err);
 return 0;
#endif
}

/* function: Player_get_hougaku */
static int tolua_lua_header_Player_get_hougaku00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Player* self = ((Player*)  tolua_tousertype(tolua_S,1,0));
 {
  int tolua_ret = (int)  Player_get_hougaku(self);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Player_get_hougaku'.",&tolua_err);
 return 0;
#endif
}

/* function: Player_act */
static int tolua_lua_header_Player_act00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Player* self = ((Player*)  tolua_tousertype(tolua_S,1,0));
  const char* action = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  Player_act(self,action);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Player_act'.",&tolua_err);
 return 0;
#endif
}

/* function: Twod_add_image */
static int tolua_lua_header_Twod_add_image00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Twod",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
 !tolua_isstring(tolua_S,4,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Twod* self = ((Twod*)  tolua_tousertype(tolua_S,1,0));
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,4,0));
 {
  Twod_add_image(self,x,y,name);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Twod_add_image'.",&tolua_err);
 return 0;
#endif
}

/* function: Twod_erase_image */
static int tolua_lua_header_Twod_erase_image00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Twod",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Twod* self = ((Twod*)  tolua_tousertype(tolua_S,1,0));
 {
  Twod_erase_image(self);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Twod_erase_image'.",&tolua_err);
 return 0;
#endif
}

/* function: Mess_add_word */
static int tolua_lua_header_Mess_add_word00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Mess",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
 !tolua_isstring(tolua_S,4,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Mess* self = ((Mess*)  tolua_tousertype(tolua_S,1,0));
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  const char* word = ((const char*)  tolua_tostring(tolua_S,4,0));
 {
  Mess_add_word(self,x,y,word);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Mess_add_word'.",&tolua_err);
 return 0;
#endif
}

/* function: Mess_erase_word */
static int tolua_lua_header_Mess_erase_word00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Mess",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Mess* self = ((Mess*)  tolua_tousertype(tolua_S,1,0));
 {
  Mess_erase_word(self);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Mess_erase_word'.",&tolua_err);
 return 0;
#endif
}

/* function: Room_act */
static int tolua_lua_header_Room_act00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Room",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Room* self = ((Room*)  tolua_tousertype(tolua_S,1,0));
  const char* act = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  Room_act(self,act);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Room_act'.",&tolua_err);
 return 0;
#endif
}

/* Open lib function */
LUALIB_API int luaopen_lua_header (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_function(tolua_S,"console_d_bag",tolua_lua_header_console_d_bag00);
 tolua_function(tolua_S,"Player_get_area",tolua_lua_header_Player_get_area00);
 tolua_function(tolua_S,"Player_get_hougaku",tolua_lua_header_Player_get_hougaku00);
 tolua_function(tolua_S,"Player_act",tolua_lua_header_Player_act00);
 tolua_function(tolua_S,"Twod_add_image",tolua_lua_header_Twod_add_image00);
 tolua_function(tolua_S,"Twod_erase_image",tolua_lua_header_Twod_erase_image00);
 tolua_function(tolua_S,"Mess_add_word",tolua_lua_header_Mess_add_word00);
 tolua_function(tolua_S,"Mess_erase_word",tolua_lua_header_Mess_erase_word00);
 tolua_function(tolua_S,"Room_act",tolua_lua_header_Room_act00);
 tolua_endmodule(tolua_S);
 return 1;
}
/* Open tolua function */
TOLUA_API int tolua_lua_header_open (lua_State* tolua_S)
{
 lua_pushcfunction(tolua_S, luaopen_lua_header);
 lua_pushstring(tolua_S, "lua_header");
 lua_call(tolua_S, 1, 0);
 return 1;
}
