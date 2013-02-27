#ifndef DEF_COMPILER_H //二重include防止

#define DEF_COMPILER_H

struct Compiler;

// 初期化をする
Compiler *Compiler_Initialize();

// 動きを計算する
void Compiler_Update( Compiler *Compiler );

// 描画する
void Compiler_Draw( Compiler *Compiler );

// 終了処理をする
void Compiler_Finalize( Compiler *Compiler );

#endif