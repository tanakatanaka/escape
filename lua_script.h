#ifndef LUA_SCRIPT_H_
#define LUA_SCRIPT_H_

/** Lua�̃X�N���v�g�G���W����\���B */
struct LuaScript;

/** �C���^�v���^������������B */
LuaScript *LuaScript_Initialize();

/** �t�@�C����ǂݍ��ށB�G���[��������false��Ԃ��B */
bool LuaScript_Load(LuaScript *self, const char *filename);

/** �X�N���v�g���Ŏg���ϐ���ݒ肷��B */
void LuaScript_Set(LuaScript *self, const char *name, void *data);

/** �t�@�C�������B */
void LuaScript_Finalize(LuaScript *);

#endif /* !defined(LUA_SCRIPT_H_) */
