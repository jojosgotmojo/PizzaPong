#pragma once
#include "Dependencies\FMOD\fmod.hpp"
#include <string>

class CSounds
{
	public:
	FMOD::System* _audio;
	FMOD::Sound* hitSound;
	
	FMOD::Channel* channel;
	FMOD_RESULT result;



	bool InitFmod()
	{

		result = FMOD::System_Create(&_audio);
		if (result != FMOD_OK)
		{
			return false;
		}
		result = _audio->init(50, FMOD_INIT_NORMAL, 0);
		if (result != FMOD_OK)
		{
			return false;
		}
		return true;
	}

	const bool LoadSound()
	{
		result = _audio->createSound("Sounds/hitsound.mp3", FMOD_DEFAULT, 0, &hitSound);

		return true;
	}

		

	const bool PlaySoundQ(std::string Music)
	{
		

		_audio->playSound(hitSound, 0, false, &channel);
	
		return true;
	}



};

