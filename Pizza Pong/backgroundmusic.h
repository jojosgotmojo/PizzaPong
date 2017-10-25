//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: backgroundmusic.h
// Description	: Initiates, loads and plays the background music
// Author		: Pizza Party - Aimee Constable, Chloe Cantwell, Joseph Maton, Nick Lacy
// Mail			: aimee.con6886@mediadesign.school.nz, chloe.can6956@mediadesign.school.nz, joseph.mat3620@mediadesign.school.nz, darcy.lac6935@mediadesign.school.nz
//

#include "Dependencies\FMOD\fmod.hpp"
#include <string>

class CBGMUSIC
{
public:
	FMOD::System* _audioMgr;
	FMOD::Sound* bgMusic;
	FMOD::Channel* channel;
	FMOD_RESULT result;

	//initialises FMOD 
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

	//loads the background music
	const bool LoadSound()
	{
		result = _audioMgr->createSound("Sounds/win.wav", FMOD_DEFAULT, 0, &bgMusic);
		bgMusic->setMode(FMOD_LOOP_NORMAL);


		return true;
	}

	//Plays the music
	const bool PlaySoundQ()
	{
		InitFmod();
		LoadSound();

		_audioMgr->playSound(bgMusic, 0, false, &channel);

		return true;
	}

};

