#ifndef LUA_SCRIPT_H_
#define LUA_SCRIPT_H_

/** Luaのスクリプトファイルを表す。 */
struct LuaScript;

/** ファイルを読み込む。 */
LuaScript *LuaScript_Load(const char *filename);

/** ファイルを閉じる。 */
void LuaScript_Finalize(LuaScript *);

#endif /* !defined(LUA_SCRIPT_H_) */
