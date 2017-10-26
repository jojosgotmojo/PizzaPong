//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: game.cpp
// Description	: Game instance initialisation
// Author		: Pizza Party - Aimee Constable, Chloe Cantwell, Joseph Maton, Nick Lacy
// Mail			: aimee.con6886@mediadesign.school.nz, chloe.can6956@mediadesign.school.nz, joseph.mat3620@mediadesign.school.nz, darcy.lac6935@mediadesign.school.nz
//

// Local Includes
#include "Clock.h"
#include "Level.h"
#include "Tournament.h"
#include "BackBuffer.h"
#include "utils.h"
#include "sounds.h"

// This Include
#include "Game.h"

// Static Variables
CGame* CGame::s_pGame = 0;


CGame::CGame(bool _bMode)
	: m_pLevel(0)
	, m_pClock(0)
	, m_hApplicationInstance(0)
	, m_hMainWindow(0)
	, m_pBackBuffer(0)
	, m_bIsLevelOver(false)
	, m_bIsTournament(_bMode)
{

}

CGame::~CGame()
{
	delete m_pLevel;
	m_pLevel = 0;

	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	delete m_pClock;
	m_pClock = 0;

	delete s_pGame;
	s_pGame = 0;
}

bool CGame::Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight, CSounds SoundEffect)
{
	m_hApplicationInstance = _hInstance;
	m_hMainWindow = _hWnd;

	m_pClock = new CClock();
	VALIDATE(m_pClock->Initialise());
	m_pClock->Process();

	m_pBackBuffer = new CBackBuffer();
	VALIDATE(m_pBackBuffer->Initialise(_hWnd, _iWidth, _iHeight));

	if (m_bIsTournament == false)
	{
		m_pLevel = new CLevel();
		VALIDATE(m_pLevel->Initialise(_iWidth, _iHeight, SoundEffect));
	}
	else if (m_bIsTournament == true)
	{
		m_pTournament = new CTournament();
		VALIDATE(m_pTournament->Initialise(_iWidth, _iHeight, SoundEffect));
	}

	
	ShowCursor(false);

	return (true);
}

void CGame::Draw()
{
	m_pBackBuffer->Clear();

	if (m_bIsTournament == false)
	{
		m_pLevel->Draw();
	}
	else if (m_bIsTournament == true)
	{
		m_pTournament->Draw();
	}
	m_pBackBuffer->Present();
}

void CGame::Process(float _fDeltaTick)
{

	if (m_bIsTournament == false)
	{
		m_pLevel->Process(_fDeltaTick);
	}
	else if (m_bIsTournament == true)
	{
		m_pTournament->Process(_fDeltaTick);
	}
}

void CGame::ExecuteOneFrame()
{
	float fDT = m_pClock->GetDeltaTick();

	Process(fDT);
	Draw();

	m_pClock->Process();

	Sleep(1);
}

CGame* CGame::GetInstance(bool _bMode)
{
	if (s_pGame == 0)
	{
		s_pGame = new CGame(_bMode);
	}

	return (s_pGame);
}

void CGame::GameOverLostPlayer1()
{
	MessageBox(m_hMainWindow, L"Player 2 wins!", L"Game Over", MB_OK);
	m_bIsLevelOver = true;
	}

void CGame::GameOverLostPlayer2()
{
	MessageBox(m_hMainWindow, L"Player 1 wins!", L"Game Over", MB_OK);
	m_bIsLevelOver = true;
}

void CGame::GameOverWinner()
{
	if (m_pTournament->GetNumberOfWinsPlayer1() > m_pTournament->GetNumberOfWinsPlayer2())
	{
		MessageBox(m_hMainWindow, L"Player 1 wins the Tournament!", L"Winner!", MB_OK);
	}
	else
	{
		MessageBox(m_hMainWindow, L"Player 2 wins the Tournament!", L"Winner!", MB_OK);
	}
	m_bIsLevelOver = true;
}

CBackBuffer* CGame::GetBackBuffer()
{
	return (m_pBackBuffer);
}

CLevel* CGame::GetLevel()
{
	return (m_pLevel);
}

CTournament * CGame::GetTournament()
{
	return (m_pTournament);
}

HINSTANCE CGame::GetAppInstance()
{
	return (m_hApplicationInstance);
}

HWND CGame::GetWindow()
{
	return (m_hMainWindow);
}

bool CGame::GetGameState()
{
	return m_bIsLevelOver;
}

bool CGame::GetGameMode()
{
	return m_bIsTournament;
}

