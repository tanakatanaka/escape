#ifndef DEF_Shader_H //��dinclude�h�~
#define DEF_Shader_H

#define SHADER_PASS_

struct Shader;

// ������������
Shader *Shader_Initialize();

// �w�肵���ԍ��̃V�F�[�_���g���͂��߂� (�J�����̐ݒ�Ȃǂ��e�������)
void Shader_Begin(Shader *self, int pass);

// �V�F�[�_���g���I���� (�J�����̐ݒ�Ȃǂ��e�������)
void Shader_End(Shader *self);

// �I������������
void Shader_Finalize(Shader *shader);

#endif