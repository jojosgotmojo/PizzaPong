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

// Library Includes

// Local Includes
#include "Game.h"
#include "Paddle.h"
#include "Brick.h"
#include "Ball.h"
#include "utils.h"
#include "backbuffer.h"
#include "framecounter.h"
#include "background.h"

// This Include
#include "Tournament.h"

// Static Variables

// Static Function Prototypes

// Implementation

//#define CHEAT_BOUNCE_ON_BACK_WALL

CTournament::CTournament()
	: m_iBricksRemaining(0)
	, m_pPaddle1(0)
	, m_pPaddle2(0)
	, m_pBall(0)
	, m_iWidth(0)
	, m_iHeight(0)
	, m_fpsCounter(0)
	, m_iPlayer1WinCount(0)
	, m_iPlayer2WinCount(0)
	, m_iNumberOfGamesPlayed(0)
{

}

CTournament::~CTournament()
{
	while (m_vecBricks.size() > 0)
	{
		CBrick* pBrick = m_vecBricks[m_vecBricks.size() - 1];

		m_vecBricks.pop_back();

		delete pBrick;
	}

	delete m_pPaddle1;
	m_pPaddle1 = 0;

	delete m_pPaddle2;
	m_pPaddle2 = 0;

	delete m_pBall;
	m_pBall = 0;

	delete m_fpsCounter;
	m_fpsCounter = 0;

	delete m_pBackground;
	m_pBackground = 0;

}

bool CTournament::Initialise(int _iWidth, int _iHeight)
{
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	const float fBallVelX = 200.0f;
	const float fBallVelY = 75.0f;

	m_pBackground = new CBackGround();
	VALIDATE(m_pBackground->Initialise());
	//Set the background position to start from {0,0}
	m_pBackground->SetX((float)m_iWidth / 2);
	m_pBackground->SetY((float)m_iHeight / 2);

	m_pBall = new CBall();
	VALIDATE(m_pBall->Initialise(m_iWidth / 4.0f, m_iHeight / 2.0f, -fBallVelX, fBallVelY));

	m_pPaddle1 = new CPaddle(0);
	m_pPaddle2 = new CPaddle(1);
	VALIDATE(m_pPaddle1->Initialise());
	VALIDATE(m_pPaddle2->Initialise());

	// Set the paddle's position to be centered on the x, 
	// and a little bit up from the bottom of the window.
	m_pPaddle1->SetX(m_pPaddle1->GetWidth() / 2);
	m_pPaddle1->SetY(_iHeight / 2);
	m_pPaddle2->SetX(m_iWidth - m_pPaddle2->GetWidth() / 2);
	m_pPaddle2->SetY(_iHeight / 2);

	const int kiNumBricks = 15;
	const int kiStartX = m_iWidth / 2;
	const int kiGap = 5;

	int iCurrentX = kiStartX;
	int iCurrentY = 20;

	for (int i = 0; i < kiNumBricks; ++i)
	{
		CBrick* pBrick = new CBrick();
		VALIDATE(pBrick->Initialise());

		pBrick->SetX(static_cast<float>(iCurrentX));
		pBrick->SetY(static_cast<float>(iCurrentY));

		iCurrentY += static_cast<int>(pBrick->GetHeight()) + kiGap;

		if (iCurrentX > _iHeight)
		{
			iCurrentX = kiStartX;
			iCurrentY += 20;
		}

		m_vecBricks.push_back(pBrick);
	}

	SetBricksRemaining(kiNumBricks);
	m_fpsCounter = new CFPSCounter();
	VALIDATE(m_fpsCounter->Initialise());

	return (true);
}

void CTournament::Draw()
{
	m_pBackground->Draw();
	for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
	{
		m_vecBricks[i]->Draw();
	}

	m_pPaddle1->Draw();
	m_pPaddle2->Draw();

	m_pBall->Draw();

	DrawScore();
	//DrawFPS();
}

void CTournament::Process(float _fDeltaTick)
{
	m_pBackground->Process(_fDeltaTick);
	if (m_pBall != nullptr)
	{
		m_pBall->Process(_fDeltaTick);
	}

	m_pPaddle1->Process(_fDeltaTick);
	m_pPaddle2->Process(_fDeltaTick);
	ProcessBallWallCollision();
	ProcessBallPaddle1Collision();
	ProcessBallPaddle2Collision();
	ProcessBallBrickCollision();
	ProcessBallBounds();

	for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
	{
		m_vecBricks[i]->Process(_fDeltaTick);
	}



	m_fpsCounter->CountFramesPerSecond(_fDeltaTick);
}

int CTournament::GetNumberOfGamesPlayed()
{
	return m_iNumberOfGamesPlayed;
}

int CTournament::GetNumberOfWinsPlayer1()
{
	return (m_iPlayer1WinCount);
}

int CTournament::GetNumberOfWinsPlayer2()
{
	return (m_iPlayer2WinCount);
}

void CTournament::IncrementWinsPlayer1()
{
	m_iPlayer1WinCount++;
	m_iNumberOfGamesPlayed++;
}

void CTournament::IncrementWinsPlayer2()
{
	m_iPlayer2WinCount++;
	m_iNumberOfGamesPlayed++;
}

CPaddle* CTournament::GetPaddle() const
{
	return (m_pPaddle1);
}

void CTournament::ProcessBallWallCollision()
{
	float fBallX = m_pBall->GetX();
	float fBallY = m_pBall->GetY();
	float fBallW = m_pBall->GetWidth();
	float fBallH = m_pBall->GetHeight();

	float fHalfBallW = fBallW / 2;
	float fHalfBallH = fBallH / 2;

	if (fBallX < fHalfBallW) //represents the situation when the ball has hit the left wall
	{
		CGame::GetInstance(true).GameOverLostPlayer1();
		m_pBall->SetX(static_cast<float>(m_iWidth));
		// m_pBall->SetVelocityX(m_pBall->GetVelocityX() * -1); //reverse the ball's x velocity
	}
	else if (fBallX > m_iWidth - fHalfBallW) //represents the situation when the ball has hit the right wall
	{
		CGame::GetInstance(true).GameOverLostPlayer2();
		m_pBall->SetX(static_cast<float>(m_iWidth));
		// m_pBall->SetVelocityX(m_pBall->GetVelocityX() * -1); //reverse the ball's x velocity direction
	}

	if (fBallY < fHalfBallH) //represents the situation when the ball has hit the top wall
	{
		m_pBall->SetVelocityY(m_pBall->GetVelocityY() * -1); //reverse the ball's y velocity
	}

	if (fBallY  > m_iHeight - fHalfBallH)  //represents the situation when the ball has hit the bottom wall
	{
		m_pBall->SetVelocityY(m_pBall->GetVelocityY() * -1); //reverse the ball's y velocity
	}

}

void CTournament::ProcessBallPaddle1Collision()
{
	float fBallR = m_pBall->GetRadius();

	float fBallX = m_pBall->GetX();
	float fBallY = m_pBall->GetY();

	float fPaddle1X = m_pPaddle1->GetX();
	float fPaddle1Y = m_pPaddle1->GetY();

	float fPaddle1H = m_pPaddle1->GetHeight();
	float fPaddle1W = m_pPaddle1->GetWidth();

	if ((fBallX + fBallR > fPaddle1X - fPaddle1W / 2) && //ball.right > paddle.left
		(fBallX - fBallR < fPaddle1X + fPaddle1W / 2) && //ball.left < paddle.right
		(fBallY + fBallR > fPaddle1Y - fPaddle1H / 2) && //ball.bottom > paddle.top
		(fBallY - fBallR < fPaddle1Y + fPaddle1H / 2))  //ball.top < paddle.bottom
	{
		m_pBall->SetX((fPaddle1X + fPaddle1W / 2) + fBallR);  //Set the ball.bottom = paddle.top; to prevent the ball from going through the paddle!
		m_pBall->SetVelocityX(m_pBall->GetVelocityX() * -1); //Reverse ball's X direction
	}
}

void CTournament::ProcessBallPaddle2Collision()
{
	float fBallR = m_pBall->GetRadius();

	float fBallX = m_pBall->GetX();
	float fBallY = m_pBall->GetY();

	float fPaddle2X = m_pPaddle2->GetX();
	float fPaddle2Y = m_pPaddle2->GetY();

	float fPaddle2H = m_pPaddle2->GetHeight();
	float fPaddle2W = m_pPaddle2->GetWidth();

	if ((fBallX + fBallR > fPaddle2X - fPaddle2W / 2) && //ball.right > paddle.left
		(fBallX - fBallR < fPaddle2X + fPaddle2W / 2) && //ball.left < paddle.right
		(fBallY + fBallR > fPaddle2Y - fPaddle2H / 2) && //ball.bottom > paddle.top
		(fBallY - fBallR < fPaddle2Y + fPaddle2H / 2))  //ball.top < paddle.bottom
	{
		m_pBall->SetX((fPaddle2X - fPaddle2W / 2) - fBallR);  //Set the ball.bottom = paddle.top; to prevent the ball from going through the paddle!
		m_pBall->SetVelocityX(m_pBall->GetVelocityX() * -1); //Reverse ball's Y direction
	}
}

void CTournament::ProcessBallBrickCollision()
{
	for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
	{
		if (!m_vecBricks[i]->IsHit())
		{
			float fBallR = m_pBall->GetRadius();

			float fBallX = m_pBall->GetX();
			float fBallY = m_pBall->GetY();

			float fBrickX = m_vecBricks[i]->GetX();
			float fBrickY = m_vecBricks[i]->GetY();

			float fBrickH = m_vecBricks[i]->GetHeight();
			float fBrickW = m_vecBricks[i]->GetWidth();

			if ((fBallX + fBallR > fBrickX - fBrickW / 2) &&
				(fBallX - fBallR < fBrickX + fBrickW / 2) &&
				(fBallY + fBallR > fBrickY - fBrickH / 2) &&
				(fBallY - fBallR < fBrickY + fBrickH / 2))
			{
				//Hit the front side of the brick...
				m_pBall->SetX((fBrickX + fBrickW / 2.0f) - fBallR);
				m_pBall->SetVelocityX(m_pBall->GetVelocityX() * -1);
				m_vecBricks[i]->SetHit(true);

				SetBricksRemaining(GetBricksRemaining() - 1);
			}
		}
	}
}

void CTournament::ProcessBallBounds()
{
	if (m_pBall->GetY() < 0)
	{
		m_pBall->SetY(0);
	}
	else if (m_pBall->GetY() > m_iHeight)
	{
		m_pBall->SetY(static_cast<float>(m_iHeight));
	}

	if (m_pBall->GetX() < 0)
	{
		m_pBall->SetX(0.0f);
	}
	else if (m_pBall->GetX() > m_iWidth)
	{
		/*CGame::GetInstance().GameOverLost();
		m_pBall->SetX(static_cast<float>(m_iWidth));*/
	}
}

int CTournament::GetBricksRemaining() const
{
	return (m_iBricksRemaining);
}

void CTournament::SetBricksRemaining(int _i)
{
	m_iBricksRemaining = _i;
	UpdateScoreText();
}

void CTournament::DrawScore()
{
	HDC hdc = CGame::GetInstance(true).GetBackBuffer()->GetBFDC();

	const int kiX = 0;
	const int kiY = m_iHeight - 14;
	const int kiX2 = m_iWidth - 74;
	const int kiY2 = m_iHeight - 14;
	SetBkMode(hdc, TRANSPARENT);

	TextOutA(hdc, kiX, kiY, m_strScore1.c_str(), static_cast<int>(m_strScore1.size()));
	TextOutA(hdc, kiX2, kiY2, m_strScore2.c_str(), static_cast<int>(m_strScore2.size()));
}

void CTournament::UpdateScoreText()
{
	m_strScore1 = "Player 1: ";
	m_strScore1 += ToString(GetNumberOfWinsPlayer1());

	m_strScore2 = "Player 2: ";
	m_strScore2 += ToString(GetNumberOfWinsPlayer2());
}


//void CTournament::DrawFPS()
//{
//	HDC hdc = CGame::GetInstance(true).GetBackBuffer()->GetBFDC();
//
//	m_fpsCounter->DrawFPSText(hdc, m_iWidth, m_iHeight);
//
//}
