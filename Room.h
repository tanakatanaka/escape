#ifndef DEF_Room_H //��dinclude�h�~

#define DEF_Room_H

struct Room;

// ������������
Room *Room_Initialize();

// �������v�Z����
void Room_Update( Room *Room );

// �`�悷��
void Room_Draw( Room *Room );

// �I������������
void Room_Finalize( Room *Room );

#endif