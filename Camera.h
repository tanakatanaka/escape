#ifndef DEF_Camera_H //“ñdinclude–h~

#define DEF_Camera_H

struct Camera;

// ‰Šú‰»‚ğ‚·‚é
Camera *Camera_Initialize( );

// “®‚«‚ğŒvZ‚·‚é
void Camera_Update( Camera *Camera );

// •`‰æ‚·‚é
void Camera_Draw( Camera *Camera );

// I—¹ˆ—‚ğ‚·‚é
void Camera_Finalize( Camera *Camera );

#endif