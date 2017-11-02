//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: game.h
// Description	: header file for the game instance
// Author		: Pizza Party - Aimee Constable, Chloe Cantwell, Joseph Maton, Nick Lacy
// Mail			: aimee.con6886@mediadesign.school.nz, chloe.can6956@mediadesign.school.nz, joseph.mat3620@mediadesign.school.nz, darcy.lac6935@mediadesign.school.nz
//


#pragma once

#if !defined(__GAME_H__)
#define __GAME_H__

// Library Includes
#include <windows.h>
#include <chrono>

// Local Includes
#include "clock.h"
#include "sounds.h"

using namespace std::chrono;

class CLevel;
class CBackBuffer;
class CTournament;

class CGame
{

public:
	virtual ~CGame();

	virtual bool Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight, CSounds SoundEffect);

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	void ExecuteOneFrame();

	CBackBuffer* GetBackBuffer();
	CLevel* GetLevel();
	CTournament* GetTournament();
	HINSTANCE GetAppInstance();
	HWND GetWindow();
	bool GetGameState();
	bool GetGameMode();

	void GameOverLostPlayer1();
	void GameOverLostPlayer2();
	void GameOverWinner();

	static CGame* GetInstance(bool _bMode);


private:
	CGame(bool _bMode);
	CGame(const CGame& _kr);


protected:
	CClock* m_pClock;
	CLevel* m_pLevel;
	CTournament* m_pTournament;
	bool m_bIsLevelOver;
	bool m_bIsTournament;

	CBackBuffer* m_pBackBuffer;

	HINSTANCE m_hApplicationInstance;
	HWND m_hMainWindow;

	static CGame* s_pGame;

};

#endif    // __GAME_H__

