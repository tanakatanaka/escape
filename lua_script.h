#ifndef LUA_SCRIPT_H_
#define LUA_SCRIPT_H_

/** Lua�̃X�N���v�g�t�@�C����\���B */
struct LuaScript;

/** �t�@�C����ǂݍ��ށB */
LuaScript *LuaScript_Load(const char *filename);

/** �t�@�C�������B */
void LuaScript_Finalize(LuaScript *);

#endif /* !defined(LUA_SCRIPT_H_) */
