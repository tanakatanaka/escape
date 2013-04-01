#include "DxLib.h"
#include "Sound.h"
#include "Player.h"
#include <stdlib.h>
#include <string>
#include <vector>
#include <time.h>

struct Sound
{
	std::vector<int> se;
	std::vector<int> music;
};

// 初期化をする
Sound *Sound_Initialize()
{
	Sound *self;
	self = new Sound();
	
	//システム音
	self->se.push_back( LoadSoundMem( "sound/se/butotn6.wav" ) );
	self->se.push_back( LoadSoundMem( "sound/se/select.mp3" ) );
	//タイプ音
	self->se.push_back( LoadSoundMem( "sound/se/type1.wav" ) );
	self->se.push_back( LoadSoundMem( "sound/se/enter.wav" ) );
	//足音
	self->se.push_back( LoadSoundMem( "sound/se/ashioto.wav" ) );
	//部屋のギミック音
	self->se.push_back( LoadSoundMem( "sound/se/dooropen.wav" ) );
	self->se.push_back( LoadSoundMem( "sound/se/door_close.wav" ) );
	self->se.push_back( LoadSoundMem( "sound/se/right2.wav" ) );
	self->se.push_back( LoadSoundMem( "sound/se/glass.wav" ) );

	return self;
}

void Sound_type( Sound *self, int type)
{
	type += 2;
	PlaySoundMem(  self->se[type] , DX_PLAYTYPE_BACK , TRUE ) ;
}

int num_combert(std::string name)
{
	if(name == "decide"){return 0;}
	else if(name == "selection"){return 1;}
	else if(name == "ashioto"){return 4;}
	else if(name == "door_open"){return 5;}
	else if(name == "door_close"){return 6;}
	else if(name == "seikai"){return 7;}
	else if(name == "glass"){return 8;}
	return -1;
}


void Sound_se( Sound *self, const char *name)
{
	int num = num_combert(name);

	if(num != -1)
	{
		
		PlaySoundMem(  self->se[num] , DX_PLAYTYPE_BACK , FALSE ) ;
	}
}

void Sound_music( Sound *self, const char *name)
{
	int num = num_combert(name);

	if(num != -1)
	{
		PlaySoundMem(  self->music[num] , DX_PLAYTYPE_BACK , FALSE ) ;
	}
}


// 終了処理をする
void Sound_Finalize( Sound *self )
{
	InitSoundMem();
    delete self;
}
