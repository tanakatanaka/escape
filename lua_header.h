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
 tolua_usertype(tolua_S,"Twod");
 tolua_usertype(tolua_S,"Player");
 tolua_usertype(tolua_S,"Sound");
 tolua_usertype(tolua_S,"Mess");
 tolua_usertype(tolua_S,"Room");
 tolua_usertype(tolua_S,"Console");
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

/* function: Sound_type */
static int tolua_lua_header_Sound_type00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Sound",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Sound* self = ((Sound*)  tolua_tousertype(tolua_S,1,0));
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  Sound_type(self,type);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Sound_type'.",&tolua_err);
 return 0;
#endif
}

/* function: Sound_se */
static int tolua_lua_header_Sound_se00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Sound",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Sound* self = ((Sound*)  tolua_tousertype(tolua_S,1,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  Sound_se(self,name);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Sound_se'.",&tolua_err);
 return 0;
#endif
}

/* get function: area of class  Room */
static int tolua_get_Room_Room_area(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'area'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->area);
 return 1;
}

/* set function: area of class  Room */
static int tolua_set_Room_Room_area(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'area'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->area = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: room of class  Room */
static int tolua_get_Room_Room_room(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'room'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->room);
 return 1;
}

/* set function: room of class  Room */
static int tolua_set_Room_Room_room(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'room'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->room = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: door of class  Room */
static int tolua_get_Room_Room_door(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'door'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->door);
 return 1;
}

/* set function: door of class  Room */
static int tolua_set_Room_Room_door(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'door'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->door = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: glass of class  Room */
static int tolua_get_Room_Room_glass(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'glass'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->glass);
 return 1;
}

/* set function: glass of class  Room */
static int tolua_set_Room_Room_glass(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'glass'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->glass = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: hammer of class  Room */
static int tolua_get_Room_Room_hammer(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hammer'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->hammer);
 return 1;
}

/* set function: hammer of class  Room */
static int tolua_set_Room_Room_hammer(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hammer'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->hammer = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: pot of class  Room */
static int tolua_get_Room_Room_pot(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pot'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->pot);
 return 1;
}

/* set function: pot of class  Room */
static int tolua_set_Room_Room_pot(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pot'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->pot = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: paper0 of class  Room */
static int tolua_get_Room_Room_paper0(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'paper0'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->paper0);
 return 1;
}

/* set function: paper0 of class  Room */
static int tolua_set_Room_Room_paper0(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'paper0'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->paper0 = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: paper1 of class  Room */
static int tolua_get_Room_Room_paper1(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'paper1'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->paper1);
 return 1;
}

/* set function: paper1 of class  Room */
static int tolua_set_Room_Room_paper1(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'paper1'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->paper1 = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: rotY of class  Room */
static int tolua_get_Room_Room_rotY(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rotY'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->rotY);
 return 1;
}

/* set function: rotY of class  Room */
static int tolua_set_Room_Room_rotY(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rotY'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->rotY = ((double)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: swit of class  Room */
static int tolua_get_Room_Room_swit(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'swit'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->swit);
 return 1;
}

/* set function: swit of class  Room */
static int tolua_set_Room_Room_swit(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'swit'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->swit = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: count of class  Room */
static int tolua_get_Room_Room_count(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'count'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->count);
 return 1;
}

/* set function: count of class  Room */
static int tolua_set_Room_Room_count(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'count'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->count = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: s_swit of class  Room */
static int tolua_get_Room_Room_s_swit(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 's_swit'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->s_swit);
 return 1;
}

/* set function: s_swit of class  Room */
static int tolua_set_Room_Room_s_swit(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 's_swit'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->s_swit = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: s_count of class  Room */
static int tolua_get_Room_Room_s_count(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 's_count'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->s_count);
 return 1;
}

/* set function: s_count of class  Room */
static int tolua_set_Room_Room_s_count(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 's_count'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->s_count = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: slide of class  Room */
static int tolua_get_Room_Room_slide(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'slide'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->slide);
 return 1;
}

/* set function: slide of class  Room */
static int tolua_set_Room_Room_slide(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'slide'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->slide = ((double)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: role of class  Room */
static int tolua_get_Room_Room_role(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'role'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->role);
 return 1;
}

/* set function: role of class  Room */
static int tolua_set_Room_Room_role(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'role'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->role = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: slide_lock of class  Room */
static int tolua_get_Room_Room_slide_lock(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'slide_lock'",NULL);
#endif
 tolua_pushboolean(tolua_S,(bool)self->slide_lock);
 return 1;
}

/* set function: slide_lock of class  Room */
static int tolua_set_Room_Room_slide_lock(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'slide_lock'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->slide_lock = ((bool)  tolua_toboolean(tolua_S,2,0));
 return 0;
}

/* get function: get_hammer of class  Room */
static int tolua_get_Room_Room_get_hammer(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'get_hammer'",NULL);
#endif
 tolua_pushboolean(tolua_S,(bool)self->get_hammer);
 return 1;
}

/* set function: get_hammer of class  Room */
static int tolua_set_Room_Room_get_hammer(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'get_hammer'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->get_hammer = ((bool)  tolua_toboolean(tolua_S,2,0));
 return 0;
}

/* get function: break_pot of class  Room */
static int tolua_get_Room_Room_break_pot(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'break_pot'",NULL);
#endif
 tolua_pushboolean(tolua_S,(bool)self->break_pot);
 return 1;
}

/* set function: break_pot of class  Room */
static int tolua_set_Room_Room_break_pot(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'break_pot'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->break_pot = ((bool)  tolua_toboolean(tolua_S,2,0));
 return 0;
}

/* get function: get_paper0 of class  Room */
static int tolua_get_Room_Room_get_paper0(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'get_paper0'",NULL);
#endif
 tolua_pushboolean(tolua_S,(bool)self->get_paper0);
 return 1;
}

/* set function: get_paper0 of class  Room */
static int tolua_set_Room_Room_get_paper0(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'get_paper0'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->get_paper0 = ((bool)  tolua_toboolean(tolua_S,2,0));
 return 0;
}

/* get function: get_paper1 of class  Room */
static int tolua_get_Room_Room_get_paper1(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'get_paper1'",NULL);
#endif
 tolua_pushboolean(tolua_S,(bool)self->get_paper1);
 return 1;
}

/* set function: get_paper1 of class  Room */
static int tolua_set_Room_Room_get_paper1(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'get_paper1'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->get_paper1 = ((bool)  tolua_toboolean(tolua_S,2,0));
 return 0;
}

/* get function: x of class  Room */
static int tolua_get_Room_Room_x(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->x);
 return 1;
}

/* set function: x of class  Room */
static int tolua_set_Room_Room_x(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->x = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: y of class  Room */
static int tolua_get_Room_Room_y(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->y);
 return 1;
}

/* set function: y of class  Room */
static int tolua_set_Room_Room_y(lua_State* tolua_S)
{
  Room* self = (Room*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->y = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
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
 tolua_function(tolua_S,"Sound_type",tolua_lua_header_Sound_type00);
 tolua_function(tolua_S,"Sound_se",tolua_lua_header_Sound_se00);
 tolua_cclass(tolua_S,"Room","Room","",NULL);
 tolua_beginmodule(tolua_S,"Room");
 tolua_variable(tolua_S,"area",tolua_get_Room_Room_area,tolua_set_Room_Room_area);
 tolua_variable(tolua_S,"room",tolua_get_Room_Room_room,tolua_set_Room_Room_room);
 tolua_variable(tolua_S,"door",tolua_get_Room_Room_door,tolua_set_Room_Room_door);
 tolua_variable(tolua_S,"glass",tolua_get_Room_Room_glass,tolua_set_Room_Room_glass);
 tolua_variable(tolua_S,"hammer",tolua_get_Room_Room_hammer,tolua_set_Room_Room_hammer);
 tolua_variable(tolua_S,"pot",tolua_get_Room_Room_pot,tolua_set_Room_Room_pot);
 tolua_variable(tolua_S,"paper0",tolua_get_Room_Room_paper0,tolua_set_Room_Room_paper0);
 tolua_variable(tolua_S,"paper1",tolua_get_Room_Room_paper1,tolua_set_Room_Room_paper1);
 tolua_variable(tolua_S,"rotY",tolua_get_Room_Room_rotY,tolua_set_Room_Room_rotY);
 tolua_variable(tolua_S,"swit",tolua_get_Room_Room_swit,tolua_set_Room_Room_swit);
 tolua_variable(tolua_S,"count",tolua_get_Room_Room_count,tolua_set_Room_Room_count);
 tolua_variable(tolua_S,"s_swit",tolua_get_Room_Room_s_swit,tolua_set_Room_Room_s_swit);
 tolua_variable(tolua_S,"s_count",tolua_get_Room_Room_s_count,tolua_set_Room_Room_s_count);
 tolua_variable(tolua_S,"slide",tolua_get_Room_Room_slide,tolua_set_Room_Room_slide);
 tolua_variable(tolua_S,"role",tolua_get_Room_Room_role,tolua_set_Room_Room_role);
 tolua_variable(tolua_S,"slide_lock",tolua_get_Room_Room_slide_lock,tolua_set_Room_Room_slide_lock);
 tolua_variable(tolua_S,"get_hammer",tolua_get_Room_Room_get_hammer,tolua_set_Room_Room_get_hammer);
 tolua_variable(tolua_S,"break_pot",tolua_get_Room_Room_break_pot,tolua_set_Room_Room_break_pot);
 tolua_variable(tolua_S,"get_paper0",tolua_get_Room_Room_get_paper0,tolua_set_Room_Room_get_paper0);
 tolua_variable(tolua_S,"get_paper1",tolua_get_Room_Room_get_paper1,tolua_set_Room_Room_get_paper1);
 tolua_variable(tolua_S,"x",tolua_get_Room_Room_x,tolua_set_Room_Room_x);
 tolua_variable(tolua_S,"y",tolua_get_Room_Room_y,tolua_set_Room_Room_y);
 tolua_endmodule(tolua_S);
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
