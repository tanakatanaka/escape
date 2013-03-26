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
	self->se.push_back( LoadSoundMem( "sound/se/butotn6.mp3" ) );
	self->se.push_back( LoadSoundMem( "sound/se/cancel6.mp3" ) );
	//タイプ音
	self->se.push_back( LoadSoundMem( "sound/se/type1.mp3" ) );
	self->se.push_back( LoadSoundMem( "sound/se/enter.mp3" ) );
	//足音
	self->se.push_back( LoadSoundMem( "sound/se/ashioto.mp3" ) );
	//部屋のギミック音
	self->se.push_back( LoadSoundMem( "sound/se/dooropen.mp3" ) );
	self->se.push_back( LoadSoundMem( "sound/se/door_close.mp3" ) );
	self->se.push_back( LoadSoundMem( "sound/se/autodoor.mp3" ) );
	self->se.push_back( LoadSoundMem( "sound/se/right2.mp3" ) );


	return self;
}

void Sound_type( Sound *self, int type)
{
	type += 2;
	PlaySoundMem(  self->se[type] , DX_PLAYTYPE_BACK , FALSE ) ;
}

int num_combert(std::string name)
{
	if(name == "decide"){return 0;}
	else if(name == "cancel"){return 1;}
	else if(name == "ashioto"){return 4;}
	else if(name == "door_open"){return 5;}
	else if(name == "door_close"){return 6;}



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
