#include "DxLib.h"
#include "Camera.h"
#include <math.h>
#include <stdio.h>
#include "pad.h"
#include "console.h"
#include "vector_operator.h"

#ifndef M_PI
#  define M_PI (atanf(1.0) * 4)
#endif

#define MOVE_CUT 50.0f
#define ROLE_CUT 15

/*
0: �O���� -X���� 270�x
1: �E���� -Z���� 0�x
2: ����� +X���� 90�x
3: ������ +Z���� 180�x
*/
struct Camera
{
    Console *console;
    VECTOR pt;
    int role_count;
    int role_swit;
    int move_swit;
    int move_count;
    int area;
    int old_area;
    int muki;

    //���_�֌W�̕ϐ�
    int look_at;
};

static const VECTOR cam_pos[8] =
{
    {2017, 250, -310}, {882, 250, -310}, {195, 250, -310}, { -592, 250, -310},
    { -592, 250, 255}, { -592, 250, 820}, {158, 250, 820}, {928, 250, 450}
};

// ������������
Camera *Camera_Initialize(Console *console)
{
    Camera *self;
    self = new Camera();
    self->console = console;

    self->area = 0;
    self->old_area = 0;
    self->pt = VGet(0, 0, 0);
    self->move_swit = 0;
    self->move_count = -1;
    self->role_swit = 0;
    self->role_count = -1;
    self->muki = 0;

    //���_�֌W�̏����l
    self->look_at = 0;

    return self;
}

void Camera_set_area(Camera *self, int area)
{
    self->area = area;
}

VECTOR Camera_get_angle(Camera *self)
{
	return self->pt;
}

/** ���p�̌v�Z */
static int round_hougaku(float y)
{
    int n = ((int)(y + 0.5f)) % 4;
    if (y < 0)
    {
        n += 3;
    }
    return n;
}

int Camera_get_hougaku(Camera *self)
{
    //play_cam 0:player����@1:camera����
    return round_hougaku(self->pt.y);
}

int Camera_is_look_at(Camera *self)
{
    return self->look_at % 2;
}

static void look_out_over(Camera *self)
{
    float move_point_x = 0.04f;
    float move_point_y = move_point_x / (M_PI / 2);

    if (CheckHitKey(KEY_INPUT_UP)) {self->pt.x -= move_point_x;}
    else if (CheckHitKey(KEY_INPUT_DOWN)) {self->pt.x += move_point_x;}

    if (CheckHitKey(KEY_INPUT_RIGHT)) {self->pt.y += move_point_y;}
    else if (CheckHitKey(KEY_INPUT_LEFT)) {self->pt.y -= move_point_y;}
}

/** ���̃J�����̃��[�l���v�Z����B */
static float calc_yaw(Camera *self)
{
	float y = self->pt.y;
    if (0 <= self->role_count)
    {
        y += self->role_swit * (self->role_count / (float)ROLE_CUT);
    }
    return (y + 3) * M_PI / 2;
}

/** ���E�̎�U���] */
static void role_cam(Camera *self)
{
    if (self->role_swit == 0)
    {
        if (self->move_swit || self->role_swit)
        {
            // �ړ����Ȃ̂łȂɂ����Ȃ�
        }
        else if (Pad_Get(KEY_INPUT_RIGHT) == -1)
        {
            self->role_swit = 1;
            self->role_count = 0;
        }
        else if (Pad_Get(KEY_INPUT_LEFT) == -1)
        {
            self->role_swit = -1;
            self->role_count = 0;
        }
		else if (Pad_Get(KEY_INPUT_DOWN) == -1)
        {
            self->role_swit = 2;
            self->role_count = 0;
        }
    }

    if (self->role_count < 0)
    {
        // �A�j�����łȂ��̂ŉ������Ȃ�
    }
    else if (self->role_count < ROLE_CUT)
    {
        self->role_count++;
    }
    else if (self->role_count >= ROLE_CUT)
    {
        self->pt.y += self->role_swit;
        self->role_count = -1;
        self->role_swit = 0;
    }
}

static void move_cam(Camera *self)
{
    if (self->move_swit == 0 && self->area != self->old_area)
    {
        self->move_swit = 1;
        self->move_count = 0;
    }

    if (self->move_count < 0){ }
    else if (self->move_count < MOVE_CUT)
    {
        self->move_count++;
    }
    if (self->move_count >= MOVE_CUT)
    {
        self->move_count = -1;
        self->move_swit = 0;
        self->old_area = self->area;
    }
}

static void look_at_switch(Camera *self)
{
    if (Pad_Get(KEY_INPUT_Z) == -1)
    {
        self->look_at++;

        if (Camera_is_look_at(self) == 0)
        {
            self->pt.x = 0;
            self->pt.y = (float)Camera_get_hougaku(self);
        }
    }
}

// �������v�Z����
void Camera_Update(Camera *self)
{
    if (Console_is_input(self->console) == 0)
    {
        if (self->look_at % 2 == 0)
        {
            role_cam(self);

            //�ړ��X�C�b�`�ɂ���
            move_cam(self);
        }
        else
        {
            //�J����������
            look_out_over(self);
        }

        look_at_switch(self);
    }
}

static VECTOR calc_cam_pos(Camera *self)
{
    const VECTOR &old = cam_pos[self->old_area];
    const VECTOR &next = cam_pos[self->area];
    VECTOR cam = old;

    if (0 <= self->move_count)
    {
        cam += (next - old) * (self->move_count / (float)MOVE_CUT);
    }

    return cam;
}

// �`�悷��
void Camera_Draw(Camera *self)
{
	VECTOR cam = calc_cam_pos(self);

    // ���p���J������yaw�Ɋ��Z
    float yaw = calc_yaw(self);

    SetCameraPositionAndAngle(cam, self->pt.x, yaw, 0.0f);

}

void Camera_back_Draw(Camera *self)
{
	VECTOR cam = calc_cam_pos(self);

    // ���p���J������yaw�Ɋ��Z
    float yaw = calc_yaw(self);

    SetCameraPositionAndAngle(cam, self->pt.x, yaw, 0.0f);

}

// �I������������
void Camera_Finalize(Camera *self)
{

}
