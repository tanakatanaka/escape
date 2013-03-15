#include "DxLib.h"
#include "Sound.h"
#include "Player.h"
#include <stdlib.h>
#include <string>
#include <vector>
#include <time.h>

struct Sound
{
	int se[100];
	int music[100];
};

// ‰Šú‰»‚ğ‚·‚é
Sound *Sound_Initialize()
{
	Sound *self;
	self = new Sound();

	self->se[0] = LoadSoundMem( "sound/se/type1.mp3" ) ;
	self->se[1] = LoadSoundMem( "sound/se/enter.mp3" ) ;

	return self;
}

void Sound_type( Sound *self, int type)
{
	PlaySoundMem(  self->se[type] , DX_PLAYTYPE_BACK , FALSE ) ;
}

int num_combert(std::string name)
{
	if(name == "enter"){return 4;}


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


// I—¹ˆ—‚ğ‚·‚é
void Sound_Finalize( Sound *self )
{
    
}
