#ifndef DEF_COMPILER_H //“ñdinclude–h~

#define DEF_COMPILER_H

struct Compiler;

// ‰Šú‰»‚ğ‚·‚é
Compiler *Compiler_Initialize();

// “®‚«‚ğŒvZ‚·‚é
void Compiler_Update( Compiler *Compiler );

// •`‰æ‚·‚é
void Compiler_Draw( Compiler *Compiler );

// I—¹ˆ—‚ğ‚·‚é
void Compiler_Finalize( Compiler *Compiler );

#endif