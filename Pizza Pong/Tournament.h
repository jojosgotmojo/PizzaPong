//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: main.cpp
// Description	: Base window initialisation
// Author		: Pizza Party - Aimee Constable, Chloe Cantwell, Joseph Maton, Nick Lacy
// Mail			: aimee.con6886@mediadesign.school.nz, chloe.can6956@mediadesign.school.nz, joseph.mat3620@mediadesign.school.nz, darcy.lac6935@mediadesign.school.nz
//

#pragma once

#if !defined(__TOURNAMENT_H__)
#define __TOURNAMENT_H__

// Library Includes
#include <vector>
#include <string>

// Local Includes

// Types

// Constants

// Prototypes
class CBall;
class CPaddle;
class CBrick;
class CFPSCounter;
class CBackGround;

class CTournament
{
	// Member Functions
public:
	CTournament();
	virtual ~CTournament();

	virtual bool Initialise(int _iWidth, int _iHeight);

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
	void ProcessBallWallCollision();
	void ProcessBallPaddle1Collision();
	void ProcessBallPaddle2Collision();
	void ProcessBallBrickCollision();
	void ProcessBallBounds();

	
	void DrawScore();
	//void DrawFPS();

	void SetBricksRemaining(int _i);

private:
	CTournament(const CTournament& _kr);

	// Member Variables
public:

protected:
	CBackGround* m_pBackground;
	CBall* m_pBall;
	CPaddle* m_pPaddle1;
	CPaddle* m_pPaddle2;
	std::vector<CBrick*> m_vecBricks;
	CFPSCounter* m_fpsCounter;

	int m_iPlayer1WinCount;
	int m_iPlayer2WinCount;
	int m_iNumberOfGamesPlayed;

	int m_iWidth;
	int m_iHeight;

	int m_iBricksRemaining;

	std::string m_strScore1;
	std::string m_strScore2;
	std::string m_strScore3;

private:

};

#endif