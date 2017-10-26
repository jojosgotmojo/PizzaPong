//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: level.h
// Description	: header file for level instance
// Author		: Pizza Party - Aimee Constable, Chloe Cantwell, Joseph Maton, Nick Lacy
// Mail			: aimee.con6886@mediadesign.school.nz, chloe.can6956@mediadesign.school.nz, joseph.mat3620@mediadesign.school.nz, darcy.lac6935@mediadesign.school.nz
//

#pragma once

#if !defined(__LEVEL_H__)
#define __LEVEL_H__

// Library Includes
#include <vector>
#include <string>
#include "sounds.h"
#include "powerup.h"
#include "Timer.h"

class CBall;
class CPaddle;
class CBrick;
class CBackGround;
class CPowerup;

using namespace std::chrono;


class CLevel
{
public:
    CLevel();
    virtual ~CLevel();

    virtual bool Initialise(int _iWidth, int _iHeight, CSounds _sound);

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

    CPaddle* GetPaddle() const;

    int GetBricksRemaining() const;

protected:
	void ProcessBallWallCollision(CBall* ballnum);
	void ProcessBallPaddle1Collision(CBall* ballnum);
	void ProcessBallPaddle2Collision(CBall* ballnum);
	void ProcessBallBrickCollision(CBall* ballnum);
	void ProcessBallBounds(CBall* ballnum);
	void ProcessBallPowerup1(CBall* ballnum);
	void ProcessBallPowerup2(CBall* ballnum);
	bool ProcessBallPowerup3(CBall* ballnum);
    void DrawScore();

    void SetBricksRemaining(int _i);

private:
    CLevel(const CLevel& _kr);

protected:
	CBackGround* m_pBackground;
    CBall* m_pBall;
	CBall* m_pBall2;
	CBall* m_pBall3;
    CPaddle* m_pPaddle1;
	CPaddle* m_pPaddle2;
    std::vector<CBrick*> m_vecBricks;
	CSounds _sound;
	CPaddle* m_pLastPlayer;
	CPowerup* m_Powerup1;
	CPowerup* m_Powerup2;
	CTimer* m_pTimer1;
	CTimer* m_pTimer2;
	CTimer* m_pTimerP2A;
	CTimer* m_pTimerP2B;

	high_resolution_clock::time_point m_tpInitialTimer1;
	high_resolution_clock::time_point m_tpInitialTimer2;
	high_resolution_clock::time_point m_tpCheckTimer1;
	high_resolution_clock::time_point m_tpCheckTimer2;
	double m_dDuration1;
	double m_dDuration2;

	int m_iPowerUp1Identifier;
	int m_iPowerUp2Identifier;
	int m_iPlayer1WinCount;
	int m_iPlayer2WinCount;
	int m_iNumberOfGamesPlayed;

	int m_iWidth;
	int m_iHeight;

	int m_iBricksRemaining;

};

#endif    // __LEVEL_H__
