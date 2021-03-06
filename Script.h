#ifndef DEF_Script_H //二重include防止

#define DEF_Script_H
#include "Camera.h"
#include "Console.h"
#include "Player.h"
#include "Script.h"
#include "Room.h"

struct Script;

// 初期化をする
Script *Script_Initialize(Camera *camera, Console *console, Player *player, Room *room, Sound *sound);

// 動きを計算する
void Script_Update( Script *Script );

// 描画する
void Script_Draw( Script *Script );

// 終了処理をする
void Script_Finalize( Script *Script );

#endif