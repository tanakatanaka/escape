#ifndef DEF_Camera_H //“ñdinclude–h~

#define DEF_Camera_H

struct Camera;

// ‰Šú‰»‚ğ‚·‚é
Camera *Camera_Initialize( );

//game‚©‚çŒ»İ‚ÌˆÊ’u‚ğ‚à‚ç‚¤ŠÖ”
void Camera_get_area(Camera *self, int area);
//game‚©‚ç¶‰E‰ñ“]‚ğ‚à‚ç‚¤ŠÖ”
void Camera_get_rl(Camera *self, int rl);

// “®‚«‚ğŒvZ‚·‚é
void Camera_Update( Camera *Camera );

// •`‰æ‚·‚é
void Camera_Draw( Camera *Camera );

// I—¹ˆ—‚ğ‚·‚é
void Camera_Finalize( Camera *Camera );

#endif