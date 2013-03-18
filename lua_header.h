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

 namespace DxLib {
 typedef struct tagVECTOR VECTOR; 
 struct tagVECTOR
 {
 	float x, y, z;
 	VECTOR(float x, float y, float z) : x(x), y(y), z(z) {}
 	VECTOR operator +(const VECTOR &b) const { return VECTOR(x + b.x, y + b.y, z + b.z); }
 	VECTOR operator -(const VECTOR &b) const { return VECTOR(x - b.x, y - b.y, z - b.z); }
 	VECTOR operator *(float b) const { return VECTOR(x * b, y * b, z * b); }
 	VECTOR operator /(float b) const { return VECTOR(x / b, y / b, z / b); }
 };
  	extern  int         MV1SetPosition(int MHandle, VECTOR Position);
  	extern  VECTOR      MV1GetPosition(int MHandle);
  	extern  int         MV1SetScale(int MHandle, VECTOR Scale);
  	extern  VECTOR      MV1GetScale(int MHandle);
  	extern  int         MV1SetRotationXYZ(int MHandle, VECTOR Rotate);
  	extern  VECTOR      MV1GetRotationXYZ(int MHandle);
  	extern  int         MV1SetVisible(int MHandle, int VisibleFlag);
  	extern  int         MV1GetVisible(int MHandle);
 
 extern	int			MV1GetFrameNum( int MHandle ) ;
 extern	int			MV1SearchFrame( int MHandle, const char *FrameName ) ;
 extern	int			MV1SearchFrameChild( int MHandle, int FrameIndex = -1 , const char *ChildName = NULL ) ;
 extern	const char *MV1GetFrameName( int MHandle, int FrameIndex ) ;
 extern	int			MV1GetFrameParent( int MHandle, int FrameIndex ) ;
 extern	int			MV1GetFrameChildNum( int MHandle, int FrameIndex = -1 ) ;
 extern	int			MV1GetFrameChild( int MHandle, int FrameIndex = -1 , int ChildIndex = 0 ) ;
 extern	VECTOR		MV1GetFramePosition( int MHandle, int FrameIndex ) ;
 extern	int			MV1ResetFrameUserLocalMatrix( int MHandle, int FrameIndex ) ;
 extern	VECTOR		MV1GetFrameMaxVertexLocalPosition( int MHandle, int FrameIndex ) ;
 extern	VECTOR		MV1GetFrameMinVertexLocalPosition( int MHandle, int FrameIndex ) ;
 extern	VECTOR		MV1GetFrameAvgVertexLocalPosition( int MHandle, int FrameIndex ) ;
 extern	int			MV1GetFrameTriangleNum( int MHandle, int FrameIndex ) ;
 extern	int			MV1GetFrameMeshNum( int MHandle, int FrameIndex ) ;
 extern	int			MV1GetFrameMesh( int MHandle, int FrameIndex, int Index ) ;
 extern	int			MV1SetFrameVisible( int MHandle, int FrameIndex, int VisibleFlag ) ;
 extern	int			MV1GetFrameVisible( int MHandle, int FrameIndex ) ;
 extern	int			MV1GetFrameSemiTransState( int MHandle, int FrameIndex ) ;
 extern	int			MV1SetFrameOpacityRate( int MHandle, int FrameIndex, float Rate ) ;
 extern	float		MV1GetFrameOpacityRate( int MHandle, int FrameIndex ) ;
 extern	int			MV1SetFrameBaseVisible( int MHandle, int FrameIndex, int VisibleFlag ) ;
 extern	int			MV1GetFrameBaseVisible( int MHandle, int FrameIndex ) ;
 extern	int			MV1SetFrameTextureAddressTransform( int MHandle, int FrameIndex, float TransU, float TransV, float ScaleU, float ScaleV, float RotCenterU, float RotCenterV, float Rotate ) ;
 extern	int			MV1ResetFrameTextureAddressTransform( int MHandle, int FrameIndex ) ;
 }
 using namespace DxLib;
#include "Console.h"
#include "Script.h"
#include "Camera.h"
#include "Room.h"
#include "Player.h"
#include "Mess.h"
#include "Twod.h"
#include "Pad.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_VECTOR (lua_State* tolua_S)
{
 VECTOR* self = (VECTOR*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
 delete self;
 return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Player");
 tolua_usertype(tolua_S,"Twod");
 tolua_usertype(tolua_S,"Camera");
 tolua_usertype(tolua_S,"Console");
 tolua_usertype(tolua_S,"Room");
 tolua_usertype(tolua_S,"VECTOR");
 tolua_usertype(tolua_S,"Sound");
 tolua_usertype(tolua_S,"Mess");
}

/* get function: x of class  VECTOR */
static int tolua_get_VECTOR_VECTOR_x(lua_State* tolua_S)
{
  VECTOR* self = (VECTOR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->x);
 return 1;
}

/* set function: x of class  VECTOR */
static int tolua_set_VECTOR_VECTOR_x(lua_State* tolua_S)
{
  VECTOR* self = (VECTOR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->x = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: y of class  VECTOR */
static int tolua_get_VECTOR_VECTOR_y(lua_State* tolua_S)
{
  VECTOR* self = (VECTOR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->y);
 return 1;
}

/* set function: y of class  VECTOR */
static int tolua_set_VECTOR_VECTOR_y(lua_State* tolua_S)
{
  VECTOR* self = (VECTOR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->y = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: z of class  VECTOR */
static int tolua_get_VECTOR_VECTOR_z(lua_State* tolua_S)
{
  VECTOR* self = (VECTOR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'z'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->z);
 return 1;
}

/* set function: z of class  VECTOR */
static int tolua_set_VECTOR_VECTOR_z(lua_State* tolua_S)
{
  VECTOR* self = (VECTOR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'z'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->z = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* method: new of class  VECTOR */
static int tolua_lua_header_VECTOR_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"VECTOR",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
 {
  VECTOR* tolua_ret = (VECTOR*)  new VECTOR(x,y,z);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"VECTOR");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: operator+ of class  VECTOR */
static int tolua_lua_header_VECTOR_operator_add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"VECTOR",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"VECTOR",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  VECTOR* self = (VECTOR*)  tolua_tousertype(tolua_S,1,0);
  VECTOR* b = ((VECTOR*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'",NULL);
#endif
 {
  VECTOR tolua_ret =  self->operator+(*b);
 {
#ifdef __cplusplus
 void* tolua_obj = new VECTOR(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_VECTOR),"VECTOR");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(VECTOR));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"VECTOR");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}

/* method: operator- of class  VECTOR */
static int tolua_lua_header_VECTOR_operator_sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"VECTOR",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"VECTOR",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  VECTOR* self = (VECTOR*)  tolua_tousertype(tolua_S,1,0);
  VECTOR* b = ((VECTOR*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'",NULL);
#endif
 {
  VECTOR tolua_ret =  self->operator-(*b);
 {
#ifdef __cplusplus
 void* tolua_obj = new VECTOR(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_VECTOR),"VECTOR");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(VECTOR));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"VECTOR");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}

/* method: operator* of class  VECTOR */
static int tolua_lua_header_VECTOR_operator_mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"VECTOR",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  VECTOR* self = (VECTOR*)  tolua_tousertype(tolua_S,1,0);
  float b = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'",NULL);
#endif
 {
  VECTOR tolua_ret =  self->operator*(b);
 {
#ifdef __cplusplus
 void* tolua_obj = new VECTOR(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_VECTOR),"VECTOR");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(VECTOR));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"VECTOR");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}

/* method: operator/ of class  VECTOR */
static int tolua_lua_header_VECTOR_operator_div00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"VECTOR",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  VECTOR* self = (VECTOR*)  tolua_tousertype(tolua_S,1,0);
  float b = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator/'",NULL);
#endif
 {
  VECTOR tolua_ret =  self->operator/(b);
 {
#ifdef __cplusplus
 void* tolua_obj = new VECTOR(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_VECTOR),"VECTOR");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(VECTOR));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"VECTOR");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.div'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1SetPosition */
static int tolua_lua_header_MV1SetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"VECTOR",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  VECTOR Position = *((VECTOR*)  tolua_tousertype(tolua_S,2,0));
 {
  int tolua_ret = (int)  MV1SetPosition(MHandle,Position);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1SetPosition'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1GetPosition */
static int tolua_lua_header_MV1GetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
 {
  VECTOR tolua_ret =  MV1GetPosition(MHandle);
 {
#ifdef __cplusplus
 void* tolua_obj = new VECTOR(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_VECTOR),"VECTOR");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(VECTOR));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"VECTOR");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1GetPosition'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1SetScale */
static int tolua_lua_header_MV1SetScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"VECTOR",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  VECTOR Scale = *((VECTOR*)  tolua_tousertype(tolua_S,2,0));
 {
  int tolua_ret = (int)  MV1SetScale(MHandle,Scale);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1SetScale'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1GetScale */
static int tolua_lua_header_MV1GetScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
 {
  VECTOR tolua_ret =  MV1GetScale(MHandle);
 {
#ifdef __cplusplus
 void* tolua_obj = new VECTOR(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_VECTOR),"VECTOR");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(VECTOR));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"VECTOR");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1GetScale'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1SetRotationXYZ */
static int tolua_lua_header_MV1SetRotationXYZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"VECTOR",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  VECTOR Rotate = *((VECTOR*)  tolua_tousertype(tolua_S,2,0));
 {
  int tolua_ret = (int)  MV1SetRotationXYZ(MHandle,Rotate);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1SetRotationXYZ'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1GetRotationXYZ */
static int tolua_lua_header_MV1GetRotationXYZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
 {
  VECTOR tolua_ret =  MV1GetRotationXYZ(MHandle);
 {
#ifdef __cplusplus
 void* tolua_obj = new VECTOR(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_VECTOR),"VECTOR");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(VECTOR));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"VECTOR");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1GetRotationXYZ'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1SetVisible */
static int tolua_lua_header_MV1SetVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  int VisibleFlag = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  int tolua_ret = (int)  MV1SetVisible(MHandle,VisibleFlag);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1SetVisible'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1GetVisible */
static int tolua_lua_header_MV1GetVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
 {
  int tolua_ret = (int)  MV1GetVisible(MHandle);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1GetVisible'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1GetFrameNum */
static int tolua_lua_header_MV1GetFrameNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
 {
  int tolua_ret = (int)  MV1GetFrameNum(MHandle);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1GetFrameNum'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1SearchFrame */
static int tolua_lua_header_MV1SearchFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  const char* FrameName = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  int tolua_ret = (int)  MV1SearchFrame(MHandle,FrameName);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1SearchFrame'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1SearchFrameChild */
static int tolua_lua_header_MV1SearchFrameChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,1,&tolua_err) || 
 !tolua_isstring(tolua_S,3,1,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  int FrameIndex = ((int)  tolua_tonumber(tolua_S,2,-1));
  const char* ChildName = ((const char*)  tolua_tostring(tolua_S,3,NULL));
 {
  int tolua_ret = (int)  MV1SearchFrameChild(MHandle,FrameIndex,ChildName);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1SearchFrameChild'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1GetFrameName */
static int tolua_lua_header_MV1GetFrameName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  int FrameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  const char* tolua_ret = (const char*)  MV1GetFrameName(MHandle,FrameIndex);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1GetFrameName'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1GetFrameParent */
static int tolua_lua_header_MV1GetFrameParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  int FrameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  int tolua_ret = (int)  MV1GetFrameParent(MHandle,FrameIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1GetFrameParent'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1GetFrameChildNum */
static int tolua_lua_header_MV1GetFrameChildNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,1,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  int FrameIndex = ((int)  tolua_tonumber(tolua_S,2,-1));
 {
  int tolua_ret = (int)  MV1GetFrameChildNum(MHandle,FrameIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1GetFrameChildNum'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1GetFrameChild */
static int tolua_lua_header_MV1GetFrameChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,1,&tolua_err) || 
 !tolua_isnumber(tolua_S,3,1,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  int FrameIndex = ((int)  tolua_tonumber(tolua_S,2,-1));
  int ChildIndex = ((int)  tolua_tonumber(tolua_S,3,0));
 {
  int tolua_ret = (int)  MV1GetFrameChild(MHandle,FrameIndex,ChildIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1GetFrameChild'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1GetFramePosition */
static int tolua_lua_header_MV1GetFramePosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  int FrameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  VECTOR tolua_ret =  MV1GetFramePosition(MHandle,FrameIndex);
 {
#ifdef __cplusplus
 void* tolua_obj = new VECTOR(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_VECTOR),"VECTOR");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(VECTOR));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"VECTOR");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1GetFramePosition'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1ResetFrameUserLocalMatrix */
static int tolua_lua_header_MV1ResetFrameUserLocalMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  int FrameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  int tolua_ret = (int)  MV1ResetFrameUserLocalMatrix(MHandle,FrameIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1ResetFrameUserLocalMatrix'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1GetFrameMaxVertexLocalPosition */
static int tolua_lua_header_MV1GetFrameMaxVertexLocalPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  int FrameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  VECTOR tolua_ret =  MV1GetFrameMaxVertexLocalPosition(MHandle,FrameIndex);
 {
#ifdef __cplusplus
 void* tolua_obj = new VECTOR(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_VECTOR),"VECTOR");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(VECTOR));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"VECTOR");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1GetFrameMaxVertexLocalPosition'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1GetFrameMinVertexLocalPosition */
static int tolua_lua_header_MV1GetFrameMinVertexLocalPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  int FrameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  VECTOR tolua_ret =  MV1GetFrameMinVertexLocalPosition(MHandle,FrameIndex);
 {
#ifdef __cplusplus
 void* tolua_obj = new VECTOR(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_VECTOR),"VECTOR");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(VECTOR));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"VECTOR");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1GetFrameMinVertexLocalPosition'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1GetFrameAvgVertexLocalPosition */
static int tolua_lua_header_MV1GetFrameAvgVertexLocalPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  int FrameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  VECTOR tolua_ret =  MV1GetFrameAvgVertexLocalPosition(MHandle,FrameIndex);
 {
#ifdef __cplusplus
 void* tolua_obj = new VECTOR(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_VECTOR),"VECTOR");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(VECTOR));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"VECTOR");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1GetFrameAvgVertexLocalPosition'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1GetFrameTriangleNum */
static int tolua_lua_header_MV1GetFrameTriangleNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  int FrameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  int tolua_ret = (int)  MV1GetFrameTriangleNum(MHandle,FrameIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1GetFrameTriangleNum'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1GetFrameMeshNum */
static int tolua_lua_header_MV1GetFrameMeshNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  int FrameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  int tolua_ret = (int)  MV1GetFrameMeshNum(MHandle,FrameIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1GetFrameMeshNum'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1GetFrameMesh */
static int tolua_lua_header_MV1GetFrameMesh00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  int FrameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  int Index = ((int)  tolua_tonumber(tolua_S,3,0));
 {
  int tolua_ret = (int)  MV1GetFrameMesh(MHandle,FrameIndex,Index);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1GetFrameMesh'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1SetFrameVisible */
static int tolua_lua_header_MV1SetFrameVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  int FrameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  int VisibleFlag = ((int)  tolua_tonumber(tolua_S,3,0));
 {
  int tolua_ret = (int)  MV1SetFrameVisible(MHandle,FrameIndex,VisibleFlag);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1SetFrameVisible'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1GetFrameVisible */
static int tolua_lua_header_MV1GetFrameVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  int FrameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  int tolua_ret = (int)  MV1GetFrameVisible(MHandle,FrameIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1GetFrameVisible'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1GetFrameSemiTransState */
static int tolua_lua_header_MV1GetFrameSemiTransState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  int FrameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  int tolua_ret = (int)  MV1GetFrameSemiTransState(MHandle,FrameIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1GetFrameSemiTransState'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1SetFrameOpacityRate */
static int tolua_lua_header_MV1SetFrameOpacityRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  int FrameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  float Rate = ((float)  tolua_tonumber(tolua_S,3,0));
 {
  int tolua_ret = (int)  MV1SetFrameOpacityRate(MHandle,FrameIndex,Rate);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1SetFrameOpacityRate'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1GetFrameOpacityRate */
static int tolua_lua_header_MV1GetFrameOpacityRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  int FrameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  float tolua_ret = (float)  MV1GetFrameOpacityRate(MHandle,FrameIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1GetFrameOpacityRate'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1SetFrameBaseVisible */
static int tolua_lua_header_MV1SetFrameBaseVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  int FrameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  int VisibleFlag = ((int)  tolua_tonumber(tolua_S,3,0));
 {
  int tolua_ret = (int)  MV1SetFrameBaseVisible(MHandle,FrameIndex,VisibleFlag);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1SetFrameBaseVisible'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1GetFrameBaseVisible */
static int tolua_lua_header_MV1GetFrameBaseVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  int FrameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  int tolua_ret = (int)  MV1GetFrameBaseVisible(MHandle,FrameIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1GetFrameBaseVisible'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1SetFrameTextureAddressTransform */
static int tolua_lua_header_MV1SetFrameTextureAddressTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,5,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,6,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,7,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,8,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,9,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,10,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  int FrameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  float TransU = ((float)  tolua_tonumber(tolua_S,3,0));
  float TransV = ((float)  tolua_tonumber(tolua_S,4,0));
  float ScaleU = ((float)  tolua_tonumber(tolua_S,5,0));
  float ScaleV = ((float)  tolua_tonumber(tolua_S,6,0));
  float RotCenterU = ((float)  tolua_tonumber(tolua_S,7,0));
  float RotCenterV = ((float)  tolua_tonumber(tolua_S,8,0));
  float Rotate = ((float)  tolua_tonumber(tolua_S,9,0));
 {
  int tolua_ret = (int)  MV1SetFrameTextureAddressTransform(MHandle,FrameIndex,TransU,TransV,ScaleU,ScaleV,RotCenterU,RotCenterV,Rotate);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1SetFrameTextureAddressTransform'.",&tolua_err);
 return 0;
#endif
}

/* function: MV1ResetFrameTextureAddressTransform */
static int tolua_lua_header_MV1ResetFrameTextureAddressTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int MHandle = ((int)  tolua_tonumber(tolua_S,1,0));
  int FrameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  int tolua_ret = (int)  MV1ResetFrameTextureAddressTransform(MHandle,FrameIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MV1ResetFrameTextureAddressTransform'.",&tolua_err);
 return 0;
#endif
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

/* get function: camera of class  Player */
static int tolua_get_Player_Player_camera_ptr(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'camera'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->camera,"Camera");
 return 1;
}

/* set function: camera of class  Player */
static int tolua_set_Player_Player_camera_ptr(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'camera'",NULL);
 if (!tolua_isusertype(tolua_S,2,"Camera",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->camera = ((Camera*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: console of class  Player */
static int tolua_get_Player_Player_console_ptr(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'console'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->console,"Console");
 return 1;
}

/* set function: console of class  Player */
static int tolua_set_Player_Player_console_ptr(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'console'",NULL);
 if (!tolua_isusertype(tolua_S,2,"Console",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->console = ((Console*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: room of class  Player */
static int tolua_get_Player_Player_room_ptr(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'room'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->room,"Room");
 return 1;
}

/* set function: room of class  Player */
static int tolua_set_Player_Player_room_ptr(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'room'",NULL);
 if (!tolua_isusertype(tolua_S,2,"Room",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->room = ((Room*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: area of class  Player */
static int tolua_get_Player_Player_area(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'area'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->area);
 return 1;
}

/* set function: area of class  Player */
static int tolua_set_Player_Player_area(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'area'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->area = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: count of class  Player */
static int tolua_get_Player_Player_count(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'count'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->count);
 return 1;
}

/* set function: count of class  Player */
static int tolua_set_Player_Player_count(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'count'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->count = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: time_limit of class  Player */
static int tolua_get_Player_Player_time_limit(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'time_limit'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->time_limit);
 return 1;
}

/* set function: time_limit of class  Player */
static int tolua_set_Player_Player_time_limit(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'time_limit'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->time_limit = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: get_paper of class  Player */
static int tolua_get_Player_Player_get_paper(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'get_paper'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->get_paper);
 return 1;
}

/* set function: get_paper of class  Player */
static int tolua_set_Player_Player_get_paper(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'get_paper'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->get_paper = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* Open lib function */
LUALIB_API int luaopen_lua_header (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"VECTOR","VECTOR","",tolua_collect_VECTOR);
#else
 tolua_cclass(tolua_S,"VECTOR","VECTOR","",NULL);
#endif
 tolua_beginmodule(tolua_S,"VECTOR");
 tolua_variable(tolua_S,"x",tolua_get_VECTOR_VECTOR_x,tolua_set_VECTOR_VECTOR_x);
 tolua_variable(tolua_S,"y",tolua_get_VECTOR_VECTOR_y,tolua_set_VECTOR_VECTOR_y);
 tolua_variable(tolua_S,"z",tolua_get_VECTOR_VECTOR_z,tolua_set_VECTOR_VECTOR_z);
 tolua_function(tolua_S,"new",tolua_lua_header_VECTOR_new00);
 tolua_function(tolua_S,".add",tolua_lua_header_VECTOR_operator_add00);
 tolua_function(tolua_S,".sub",tolua_lua_header_VECTOR_operator_sub00);
 tolua_function(tolua_S,".mul",tolua_lua_header_VECTOR_operator_mul00);
 tolua_function(tolua_S,".div",tolua_lua_header_VECTOR_operator_div00);
 tolua_endmodule(tolua_S);
 tolua_function(tolua_S,"MV1SetPosition",tolua_lua_header_MV1SetPosition00);
 tolua_function(tolua_S,"MV1GetPosition",tolua_lua_header_MV1GetPosition00);
 tolua_function(tolua_S,"MV1SetScale",tolua_lua_header_MV1SetScale00);
 tolua_function(tolua_S,"MV1GetScale",tolua_lua_header_MV1GetScale00);
 tolua_function(tolua_S,"MV1SetRotationXYZ",tolua_lua_header_MV1SetRotationXYZ00);
 tolua_function(tolua_S,"MV1GetRotationXYZ",tolua_lua_header_MV1GetRotationXYZ00);
 tolua_function(tolua_S,"MV1SetVisible",tolua_lua_header_MV1SetVisible00);
 tolua_function(tolua_S,"MV1GetVisible",tolua_lua_header_MV1GetVisible00);
 tolua_function(tolua_S,"MV1GetFrameNum",tolua_lua_header_MV1GetFrameNum00);
 tolua_function(tolua_S,"MV1SearchFrame",tolua_lua_header_MV1SearchFrame00);
 tolua_function(tolua_S,"MV1SearchFrameChild",tolua_lua_header_MV1SearchFrameChild00);
 tolua_function(tolua_S,"MV1GetFrameName",tolua_lua_header_MV1GetFrameName00);
 tolua_function(tolua_S,"MV1GetFrameParent",tolua_lua_header_MV1GetFrameParent00);
 tolua_function(tolua_S,"MV1GetFrameChildNum",tolua_lua_header_MV1GetFrameChildNum00);
 tolua_function(tolua_S,"MV1GetFrameChild",tolua_lua_header_MV1GetFrameChild00);
 tolua_function(tolua_S,"MV1GetFramePosition",tolua_lua_header_MV1GetFramePosition00);
 tolua_function(tolua_S,"MV1ResetFrameUserLocalMatrix",tolua_lua_header_MV1ResetFrameUserLocalMatrix00);
 tolua_function(tolua_S,"MV1GetFrameMaxVertexLocalPosition",tolua_lua_header_MV1GetFrameMaxVertexLocalPosition00);
 tolua_function(tolua_S,"MV1GetFrameMinVertexLocalPosition",tolua_lua_header_MV1GetFrameMinVertexLocalPosition00);
 tolua_function(tolua_S,"MV1GetFrameAvgVertexLocalPosition",tolua_lua_header_MV1GetFrameAvgVertexLocalPosition00);
 tolua_function(tolua_S,"MV1GetFrameTriangleNum",tolua_lua_header_MV1GetFrameTriangleNum00);
 tolua_function(tolua_S,"MV1GetFrameMeshNum",tolua_lua_header_MV1GetFrameMeshNum00);
 tolua_function(tolua_S,"MV1GetFrameMesh",tolua_lua_header_MV1GetFrameMesh00);
 tolua_function(tolua_S,"MV1SetFrameVisible",tolua_lua_header_MV1SetFrameVisible00);
 tolua_function(tolua_S,"MV1GetFrameVisible",tolua_lua_header_MV1GetFrameVisible00);
 tolua_function(tolua_S,"MV1GetFrameSemiTransState",tolua_lua_header_MV1GetFrameSemiTransState00);
 tolua_function(tolua_S,"MV1SetFrameOpacityRate",tolua_lua_header_MV1SetFrameOpacityRate00);
 tolua_function(tolua_S,"MV1GetFrameOpacityRate",tolua_lua_header_MV1GetFrameOpacityRate00);
 tolua_function(tolua_S,"MV1SetFrameBaseVisible",tolua_lua_header_MV1SetFrameBaseVisible00);
 tolua_function(tolua_S,"MV1GetFrameBaseVisible",tolua_lua_header_MV1GetFrameBaseVisible00);
 tolua_function(tolua_S,"MV1SetFrameTextureAddressTransform",tolua_lua_header_MV1SetFrameTextureAddressTransform00);
 tolua_function(tolua_S,"MV1ResetFrameTextureAddressTransform",tolua_lua_header_MV1ResetFrameTextureAddressTransform00);
 tolua_function(tolua_S,"console_d_bag",tolua_lua_header_console_d_bag00);
 tolua_function(tolua_S,"Player_get_area",tolua_lua_header_Player_get_area00);
 tolua_function(tolua_S,"Player_get_hougaku",tolua_lua_header_Player_get_hougaku00);
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
 tolua_variable(tolua_S,"get_hammer",tolua_get_Room_Room_get_hammer,tolua_set_Room_Room_get_hammer);
 tolua_variable(tolua_S,"break_pot",tolua_get_Room_Room_break_pot,tolua_set_Room_Room_break_pot);
 tolua_variable(tolua_S,"get_paper0",tolua_get_Room_Room_get_paper0,tolua_set_Room_Room_get_paper0);
 tolua_variable(tolua_S,"get_paper1",tolua_get_Room_Room_get_paper1,tolua_set_Room_Room_get_paper1);
 tolua_variable(tolua_S,"x",tolua_get_Room_Room_x,tolua_set_Room_Room_x);
 tolua_variable(tolua_S,"y",tolua_get_Room_Room_y,tolua_set_Room_Room_y);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Player","Player","",NULL);
 tolua_beginmodule(tolua_S,"Player");
 tolua_variable(tolua_S,"camera",tolua_get_Player_Player_camera_ptr,tolua_set_Player_Player_camera_ptr);
 tolua_variable(tolua_S,"console",tolua_get_Player_Player_console_ptr,tolua_set_Player_Player_console_ptr);
 tolua_variable(tolua_S,"room",tolua_get_Player_Player_room_ptr,tolua_set_Player_Player_room_ptr);
 tolua_variable(tolua_S,"area",tolua_get_Player_Player_area,tolua_set_Player_Player_area);
 tolua_variable(tolua_S,"count",tolua_get_Player_Player_count,tolua_set_Player_Player_count);
 tolua_variable(tolua_S,"time_limit",tolua_get_Player_Player_time_limit,tolua_set_Player_Player_time_limit);
 tolua_variable(tolua_S,"get_paper",tolua_get_Player_Player_get_paper,tolua_set_Player_Player_get_paper);
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
