#ifndef DEF_Sound_H //“ñdinclude–h~

#define DEF_Sound_H

struct Sound;

// ‰Šú‰»‚ğ‚·‚é
Sound *Sound_Initialize();

void Sound_type( Sound *self);
void Sound_se( Sound *self, const char *name);

// I—¹ˆ—‚ğ‚·‚é
void Sound_Finalize( Sound *Sound );

#endif