#ifndef LUA_SCRIPT_H_
#define LUA_SCRIPT_H_

/** Luaのスクリプトエンジンを表す。 */
struct LuaScript;

/** インタプリタを初期化する。 */
LuaScript *LuaScript_Initialize();

/** ファイルを読み込む。エラーだったらfalseを返す。 */
bool LuaScript_Load(LuaScript *self, const char *filename);

/**
  スクリプト内で使う変数(なんかの構造体のポインタに限る)を設定する。
  type: 型名
  name: 変数名
  data: ポインタ
*/
void LuaScript_Set(LuaScript *self, const char *type, const char *name, void *data);

/** ファイルを閉じる。 */
void LuaScript_Finalize(LuaScript *);

#endif /* !defined(LUA_SCRIPT_H_) */
