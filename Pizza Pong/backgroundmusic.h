#pragma once
#pragma once
#include "Dependencies\FMOD\fmod.hpp"
#include <string>

class CBGMUSIC
{
public:
	FMOD::System* _audioMgr;
	FMOD::Sound* bgMusic;
	FMOD::Channel* channel;
	FMOD_RESULT result;

	bool InitFmod()
	{

		result = FMOD::System_Create(&_audioMgr);
		if (result != FMOD_OK)
		{
			return false;
		}
		result = _audioMgr->init(50, FMOD_INIT_NORMAL, 0);
		if (result != FMOD_OK)
		{
			return false;
		}
		return true;
	}

	const bool LoadSound()
	{
		result = _audioMgr->createSound("Sounds/win.wav", FMOD_DEFAULT, 0, &bgMusic);
		bgMusic->setMode(FMOD_LOOP_NORMAL);


		return true;
	}


	const bool PlaySoundQ()
	{
		InitFmod();
		LoadSound();

		_audioMgr->playSound(bgMusic, 0, false, &channel);

		return true;
	}

};

