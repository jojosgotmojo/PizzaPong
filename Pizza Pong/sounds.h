//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: sounds.h
// Description	: Initialises, loads and plays sounds
// Author		: Pizza Party - Aimee Constable, Chloe Cantwell, Joseph Maton, Nick Lacy
// Mail			: aimee.con6886@mediadesign.school.nz, chloe.can6956@mediadesign.school.nz, joseph.mat3620@mediadesign.school.nz, darcy.lac6935@mediadesign.school.nz
//

#pragma once

#include "Dependencies\FMOD\fmod.hpp"
#include <string>


class CSounds
{
	public:
	FMOD::System* _audio;

	FMOD::Sound* hitSound;
	FMOD::Sound* paddleHit;
	FMOD::Sound* WinSound;
	FMOD::Sound* PowerupStart;
	FMOD::Sound* PowerupEnd;

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
		result = _audio->createSound("Sounds/percussion.mp3", FMOD_DEFAULT, 0, &hitSound);
		//result = _audio->createSound("Sounds/hitsound.wav", FMOD_DEFAULT, 0, &PowerupEnd);
		result = _audio->createSound("Sounds/powerupstart.mp3", FMOD_DEFAULT, 0, &PowerupStart);
		result = _audio->createSound("Sounds/hitsound2.mp3", FMOD_DEFAULT, 0, &paddleHit);
		result = _audio->createSound("Sounds/winsound.mp3", FMOD_DEFAULT, 0, &WinSound);

		return true;
	}

		

	const bool PlaySoundQ(std::string Sound)
	{
		if (Sound == "hitSound")
		{
			_audio->playSound(hitSound, 0, false, &channel);

		}
		else if (Sound == "PowerupEnd")
		{
			_audio->playSound(PowerupEnd, 0, false, &channel);

		}
		else if (Sound == "PowerupStart")
		{
			_audio->playSound(PowerupStart, 0, false, &channel);

		}
		else if (Sound == "PaddleHit")
		{
			_audio->playSound(paddleHit, 0, false, &channel);

		}
		else if (Sound == "WinSound")
		{
			_audio->playSound(WinSound, 0, false, &channel);

		}

	
		return true;
	}



};

