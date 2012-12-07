#ifndef DEF_Console_H //“ñdinclude–h~

#define DEF_Console_H

struct Console;

// ‰Šú‰»‚ğ‚·‚é
Console *Console_Initialize( );

int Console_over(Console *Console);

// “®‚«‚ğŒvZ‚·‚é
void Console_Update( Console *Console );

// •`‰æ‚·‚é
void Console_Draw( Console *Console );

// I—¹ˆ—‚ğ‚·‚é
void Console_Finalize( Console *Console );

#endif