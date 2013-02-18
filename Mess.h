#ifndef DEF_Mess_H //“ñdinclude–h~

#define DEF_Mess_H

struct Mess;

// ‰Šú‰»‚ğ‚·‚é
Mess *Mess_Initialize();
//Œ¾—t‚ğ’Ç‰Á
void Mess_add_word(Mess *self,int x, int y, const char *word);
//Œ¾—t‚ğíœ
void mess_erase_word(Mess *self, const char *tag);
// “®‚«‚ğŒvZ‚·‚é
void Mess_Update( Mess *Mess );

// •`‰æ‚·‚é
void Mess_Draw( Mess *Mess );

// I—¹ˆ—‚ğ‚·‚é
void Mess_Finalize( Mess *Mess );

#endif