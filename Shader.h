#ifndef DEF_Shader_H //二重include防止
#define DEF_Shader_H

#define SHADER_PASS_

struct Shader;

// 初期化をする
Shader *Shader_Initialize();

// 指定した番号のシェーダを使いはじめる (カメラの設定などが影響される)
void Shader_Begin(Shader *self, int pass);

// シェーダを使い終える (カメラの設定などが影響される)
void Shader_End(Shader *self);

// 終了処理をする
void Shader_Finalize(Shader *shader);

#endif