//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: Tournament.h
// Description	: header file for tournament instance
// Author		: Pizza Party - Aimee Constable, Chloe Cantwell, Joseph Maton, Nick Lacy
// Mail			: aimee.con6886@mediadesign.school.nz, chloe.can6956@mediadesign.school.nz, joseph.mat3620@mediadesign.school.nz, darcy.lac6935@mediadesign.school.nz
//

#pragma once

#if !defined(__TOURNAMENT_H__)
#define __TOURNAMENT_H__

// Library Includes
#include <vector>
#include <string>
#include <chrono>
#include "sounds.h"
#include "Timer.h"

using namespace std::chrono;

class CBall;
class CPaddle;
class CBrick;
class CBackGround;
class CPowerup;

class CTournament
{
public:
	CTournament();
	virtual ~CTournament();

	virtual bool Initialise(int _iWidth, int _iHeight, CSounds SoundEffect);

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	int GetNumberOfGamesPlayed();
	int GetNumberOfWinsPlayer1();
	int GetNumberOfWinsPlayer2();
	void IncrementWinsPlayer1();
	void IncrementWinsPlayer2();
	CPaddle* GetPaddle() const;
	void UpdateScoreText();
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
	CTournament(const CTournament& _kr);

protected:
	CBackGround* m_pBackground;
	CBall* m_pBall;
	CBall* m_pBall2;
	CBall* m_pBall3;
	CPaddle* m_pPaddle1;
	CPaddle* m_pPaddle2;
	CPaddle* m_pLastPlayer;
	CPowerup* m_Powerup1;
	CPowerup* m_Powerup2;
	CTimer* m_pTimer1;
	CTimer* m_pTimer2;
	CTimer* m_pTimerP2A;
	CTimer* m_pTimerP2B;
	std::vector<CBrick*> m_vecBricks;
	CSounds _sound;

	int m_iPowerUp1Identifier;
	int m_iPowerUp2Identifier;
	int m_iPlayer1WinCount;
	int m_iPlayer2WinCount;
	int m_iNumberOfGamesPlayed;

	int m_iWidth;
	int m_iHeight;

	int m_iBricksRemaining;

	std::string m_strScore1;
	std::string m_strScore2;
	std::string m_strScore3;

};

#endif