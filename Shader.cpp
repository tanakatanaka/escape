#include "DxLib.h"
#include "Shader.h"

struct Shader
{
	MATRIX light_camera_view_matrix;
	MATRIX light_camera_projection_matrix;
	int depthmap_vs;
	int depthmap_ps;
	int phong_vs;
	int phong_ps;
	int active_pass;
	int depthmap_screen;
};

/// 影つけ用の深度マップを焼き付ける画像を初期化
static int create_depthmap_buffer()
{
	int saved1 = GetDrawValidFloatTypeGraphCreateFlag();
	int saved2 = GetCreateDrawValidGraphChannelNum();
	int saved3 = GetCreateGraphColorBitDepth();

	SetDrawValidFloatTypeGraphCreateFlag(TRUE);
	SetCreateDrawValidGraphChannelNum(1);
	SetCreateGraphColorBitDepth(16);

	int id = MakeScreen(8192, 8192, FALSE);

	SetDrawValidFloatTypeGraphCreateFlag(saved1);
	SetCreateDrawValidGraphChannelNum(saved2);
	SetCreateGraphColorBitDepth(saved3);

	return id;
}

// 初期化をする
Shader *Shader_Initialize()
{
	Shader *self = new Shader();

	self->depthmap_vs = LoadVertexShader("shader/depthmap.vs.vso");
	self->depthmap_ps = LoadPixelShader("shader/depthmap.ps.pso");
	self->phong_vs = LoadVertexShader("shader/phong.vs.vso");
	self->phong_ps = LoadPixelShader("shader/phong.ps.pso");

	self->active_pass = -1;
	self->depthmap_screen = create_depthmap_buffer();

	return self;
}

static void begin_depthmap_pass(Shader *self)
{
	// 描画先を影用深度記録画像にする
	SetDrawScreen(self->depthmap_screen);

	// 影用深度記録画像を真っ白にクリア
	SetBackgroundColor(255, 255, 255);
	ClearDrawScreen();
	SetBackgroundColor(0, 0, 0);

	// カメラのタイプを正射影タイプにセット、描画範囲も指定
	SetupCamera_Ortho(13250.0f);

	// 描画する奥行き範囲をセット
	SetCameraNearFar(10.0f, 13050.0f);

	// カメラの位置と注視点はステージ全体が見渡せる位置
	VECTOR LightTarget = VGet(3620.0f, 0.0f, 3830.0f);

	// カメラの向きはライトの向き
	VECTOR LightDirection = VScale(GetLightDirection(), -12400.0f);

	// カメラの位置と注視点はステージ全体が見渡せる位置
	VECTOR LightPosition = VAdd(LightTarget, LightDirection);

	SetCameraPositionAndTarget_UpVecY(LightPosition, LightTarget);

	self->light_camera_view_matrix = GetCameraViewMatrix();
	self->light_camera_projection_matrix = GetCameraProjectionMatrix();

	SetUseVertexShader(self->depthmap_vs);
	SetUsePixelShader(self->depthmap_ps);
}

static void begin_phong_pass(Shader *self)
{
	// 影用深度記録画像を描画したときのカメラのビュー行列と射影行列を定数に設定する
	SetVSConstFMtx(43, self->light_camera_view_matrix);
	SetVSConstFMtx(47, self->light_camera_projection_matrix);

	// 影用深度記録画像をテクスチャ１にセット
	SetUseTextureToShader(1, self->depthmap_screen);

	SetUseVertexShader(self->phong_vs);
	SetUsePixelShader(self->phong_ps);
}

void Shader_Begin(Shader *self, int pass)
{
	if (self->active_pass != -1)
	{
		fprintf(stderr, "warning: Shader: already shader active\n");
	}

	if (pass == 0)
	{
		begin_depthmap_pass(self);
	}
	else if (pass == 1)
	{
		begin_phong_pass(self);
	}
	else
	{
		fprintf(stderr, "warning: Shader: unexpected pass number\n");
		return;
	}

	self->active_pass = pass;
	MV1SetUseOrigShader(TRUE);
}

void Shader_End(Shader *self)
{
	if (self->active_pass == 0)
	{
		SetDrawScreen(DX_SCREEN_BACK);
	}
	else if (self->active_pass == 1)
	{
		SetUseTextureToShader(1, -1);
		ResetVSConstF(43, 8);
	}
	else if (self->active_pass == -1)
	{
		fprintf(stderr, "warning: Shader: shader not active\n");
	}
	else
	{
		fprintf(stderr, "warning: Shader: unexpected pass number\n");
	}

	MV1SetUseOrigShader(FALSE);
	self->active_pass = -1;
}

// 終了処理をする
void Shader_Finalize(Shader *self)
{
	if (self->active_pass != -1)
	{
		fprintf(stderr, "warning: unfinished pass (#%d)\n", self->active_pass);
	}

	DeleteGraph(self->depthmap_screen);
	DeleteShader(self->depthmap_vs);
	DeleteShader(self->depthmap_ps);
	DeleteShader(self->phong_vs);
	DeleteShader(self->phong_ps);

	delete self;
}
