#ifndef DEF_Twod_H //��dinclude�h�~

#define DEF_Twod_H

struct Twod;

// ������������
Twod *Twod_Initialize();
//�摜��`�惂�[�h�ɂ���
void Twod_add_image(Twod *self, int x, int y, int id , const char *tag);
//�摜�̕`�惂�[�h������
void twod_erase_image(Twod *self, const char *tag);
// �������v�Z����
void Twod_Update( Twod *Twod );
// �`�悷��
void Twod_Draw( Twod *Twod );
// �I������������
void Twod_Finalize( Twod *Twod );

#endif