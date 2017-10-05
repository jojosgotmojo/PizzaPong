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
#include "powerup.h"

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
	, m_iNumberOfGamesPlayed(1)
{
	m_tpInitialTimer1 = high_resolution_clock::now();
	m_tpInitialTimer2 = high_resolution_clock::now();
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

	m_iPowerUp1Identifier = rand() % 3;
	m_iPowerUp2Identifier = rand() % 3;

	int iRandomX1 = rand() % 550 + 50;
	int iRandomX2 = rand() % 550 + 680;
	int iRandomY1 = rand() % 660 + 30;
	int iRandomY2 = rand() % 660 + 30;

	m_Powerup1 = new CPowerup(m_iPowerUp1Identifier);
	m_Powerup2 = new CPowerup(m_iPowerUp2Identifier);
	VALIDATE(m_Powerup1->Initialise(iRandomX1, iRandomY1));
	VALIDATE(m_Powerup2->Initialise(iRandomX2, iRandomY2));

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

	m_Powerup1->Draw();
	m_Powerup2->Draw();

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
	m_Powerup1->Process(_fDeltaTick);
	m_Powerup2->Process(_fDeltaTick);
	ProcessBallWallCollision();
	ProcessBallPaddle1Collision();
	ProcessBallPaddle2Collision();
	ProcessBallBrickCollision();
	ProcessBallBounds();
	ProcessBallPowerup1();
	ProcessBallPowerup2();

	m_tpCheckTimer1 = high_resolution_clock::now();
	m_tpCheckTimer2 = high_resolution_clock::now();
	
	m_dDuration1 = duration_cast<milliseconds>(m_tpCheckTimer1 - m_tpInitialTimer1).count() / 1000.00;
	m_dDuration2 = duration_cast<milliseconds>(m_tpCheckTimer2 - m_tpInitialTimer2).count() / 1000.00;

	if (m_dDuration1 >= 20.00 && m_pSnapShot1 != nullptr)
	{
		switch (m_iPowerUp1Identifier)
		{
			case 0:
			{
				m_pSnapShot1->Initialise();
				break;
			}
			case 1:
			{
				m_pSnapShot1->ResetSpeed();
				break;
			}
			case 2:
			{
				break;
			}
			default:break;
		}
	}
	if (m_dDuration2 >= 20.00&& m_pSnapShot2 != nullptr)
	{
		switch (m_iPowerUp2Identifier)
		{
		case 0:
		{
			m_pSnapShot2->Initialise();
			break;
		}
		case 1:
		{
			m_pSnapShot2->ResetSpeed();
			break;
		}
		case 2:
		{
			break;
		}
		default:break;
		}
	}

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
		this->IncrementWinsPlayer2();
		this->UpdateScoreText();
		m_pBall->SetX(static_cast<float>(m_iWidth / 4.0f * 3));
		if (this->GetNumberOfGamesPlayed() >= 11)
		{
			CGame::GetInstance(true).GameOverWinner();
		}
	}
	else if (fBallX > m_iWidth - fHalfBallW) //represents the situation when the ball has hit the right wall
	{
		this->IncrementWinsPlayer1();
		this->UpdateScoreText();
		m_pBall->SetX(static_cast<float>(m_iWidth / 4.0f));

		if ((this->GetNumberOfGamesPlayed() >= 11 && (this->GetNumberOfWinsPlayer1() > this->GetNumberOfWinsPlayer2())) || (this->GetNumberOfGamesPlayed() >= 11 && (this->GetNumberOfWinsPlayer1() < this->GetNumberOfWinsPlayer2())))
		{
			CGame::GetInstance(true).GameOverWinner();
		}
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
		m_pBall->SetVelocityX(m_pBall->GetVelocityX() * -1); //Reverse ball's X direction


		int iRand = rand() % 1 + 9;
		float ReducedValue = static_cast<float>(iRand) / 10;


		if ((m_pBall->GetVelocityY() < 0) && (m_pBall->GetY() > fPaddle1Y))
		{
			if (m_pBall->GetVelocityY() < -225.00f)
			{
				m_pBall->SetVelocityY(-225.00f);
			}

			m_pBall->SetVelocityY(m_pBall->GetVelocityY() * (-1 - ReducedValue)); //Reverse ball's Y direction
		}
		else if ((m_pBall->GetVelocityY() > 0) && (m_pBall->GetY() < fPaddle1Y))
		{

			if (m_pBall->GetVelocityY() > 225.00f)
			{
				m_pBall->SetVelocityY(225.00f);
			}
			m_pBall->SetVelocityY(m_pBall->GetVelocityY() * (-1 - ReducedValue)); //Reverse ball's Y direction
		}
		else
		{
			m_pBall->SetVelocityY(m_pBall->GetVelocityY() * (1 + ReducedValue));
		}
		m_pLastPlayer = m_pPaddle1;
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
		int iRand = rand() % 1 + 9;
		float ReducedValue = static_cast<float>(iRand) / 10;

		m_pBall->SetX((fPaddle2X - fPaddle2W / 2) - fBallR);  //Set the ball.bottom = paddle.top; to prevent the ball from going through the paddle!
		m_pBall->SetVelocityX(m_pBall->GetVelocityX() * -1); //Reverse ball's Y direction

		if ((m_pBall->GetVelocityY() < 0) && (m_pBall->GetY() > fPaddle2Y))
		{
			if (m_pBall->GetVelocityY() < -225.00f)
			{
				m_pBall->SetVelocityY(-225.00f);
			}

			m_pBall->SetVelocityY(m_pBall->GetVelocityY() * (-1 - ReducedValue)); //Reverse ball's Y direction
		}
		else if ((m_pBall->GetVelocityY() > 0) && (m_pBall->GetY() < fPaddle2Y))
		{

			if (m_pBall->GetVelocityY() > 225.00f)
			{
				m_pBall->SetVelocityY(225.00f);
			}
			m_pBall->SetVelocityY(m_pBall->GetVelocityY() * (-1 - ReducedValue)); //Reverse ball's Y direction
		}
		else
		{
			m_pBall->SetVelocityY(m_pBall->GetVelocityY() * (1 + ReducedValue));
		}
		m_pLastPlayer = m_pPaddle2;
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
				int iDirection = rand() % 2;

				//Hit the front side of the brick...
				m_pBall->SetX((fBrickX + fBrickW / 2.0f) - fBallR);
				m_pBall->SetVelocityX(m_pBall->GetVelocityX() * -1);
				if (iDirection == 1)
				{
					m_pBall->SetVelocityY(m_pBall->GetVelocityY() * -1);
				}
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

void CTournament::ProcessBallPowerup1()
{
	float fBallR = m_pBall->GetRadius();

	float fBallX = m_pBall->GetX();
	float fBallY = m_pBall->GetY();

	float fPowerUp1X = m_Powerup1->GetX();
	float fPowerUp1Y = m_Powerup1->GetY();
	float fPowerUp2X = m_Powerup2->GetX();
	float fPowerUp2Y = m_Powerup2->GetY();

	float fPowerUp1H = m_Powerup1->GetHeight();
	float fPowerUp1W = m_Powerup1->GetWidth();
	float fPowerUp2H = m_Powerup2->GetHeight();
	float fPowerUp2W = m_Powerup2->GetWidth();

	if (m_iPowerUp1Identifier == 0 && m_Powerup1->IsHit() == false)
	{
		if ((fBallX + fBallR > fPowerUp1X - fPowerUp1W / 2) &&
			(fBallX - fBallR < fPowerUp1X + fPowerUp1W / 2) &&
			(fBallY + fBallR > fPowerUp1Y - fPowerUp1H / 2) &&
			(fBallY - fBallR < fPowerUp1Y + fPowerUp1H / 2))
		{
			m_tpInitialTimer1 = high_resolution_clock::now();
			m_pLastPlayer->Enlarge();
			m_Powerup1->SetHit(true);
			m_pSnapShot1 = m_pLastPlayer;
		}
	}

	if (m_iPowerUp2Identifier == 0 && m_Powerup2->IsHit() == false)
	{
		if ((fBallX + fBallR > fPowerUp2X - fPowerUp2W / 2) &&
			(fBallX - fBallR < fPowerUp2X + fPowerUp2W / 2) &&
			(fBallY + fBallR > fPowerUp2Y - fPowerUp2H / 2) &&
			(fBallY - fBallR < fPowerUp2Y + fPowerUp2H / 2))
		{
			m_tpInitialTimer2 = high_resolution_clock::now();
			m_pLastPlayer->Enlarge();
			m_Powerup2->SetHit(true);
			m_pSnapShot2 = m_pLastPlayer;
		}
	}

}

void CTournament::ProcessBallPowerup2()
{
	float fBallR = m_pBall->GetRadius();

	float fBallX = m_pBall->GetX();
	float fBallY = m_pBall->GetY();

	float fPowerUp1X = m_Powerup1->GetX();
	float fPowerUp1Y = m_Powerup1->GetY();
	float fPowerUp2X = m_Powerup2->GetX();
	float fPowerUp2Y = m_Powerup2->GetY();

	float fPowerUp1H = m_Powerup1->GetHeight();
	float fPowerUp1W = m_Powerup1->GetWidth();
	float fPowerUp2H = m_Powerup2->GetHeight();
	float fPowerUp2W = m_Powerup2->GetWidth();

	if (m_iPowerUp1Identifier == 1 && m_Powerup1->IsHit() == false)
	{
		if ((fBallX + fBallR > fPowerUp1X - fPowerUp1W / 2) &&
			(fBallX - fBallR < fPowerUp1X + fPowerUp1W / 2) &&
			(fBallY + fBallR > fPowerUp1Y - fPowerUp1H / 2) &&
			(fBallY - fBallR < fPowerUp1Y + fPowerUp1H / 2))
		{
			m_tpInitialTimer1 = high_resolution_clock::now();
			m_pLastPlayer->SpeedUp();
			m_Powerup1->SetHit(true);
			m_pSnapShot1 = m_pLastPlayer;
		}
	}

	if (m_iPowerUp2Identifier == 1 && m_Powerup2->IsHit() == false)
	{
		if ((fBallX + fBallR > fPowerUp2X - fPowerUp2W / 2) &&
			(fBallX - fBallR < fPowerUp2X + fPowerUp2W / 2) &&
			(fBallY + fBallR > fPowerUp2Y - fPowerUp2H / 2) &&
			(fBallY - fBallR < fPowerUp2Y + fPowerUp2H / 2))
		{
			m_tpInitialTimer2 = high_resolution_clock::now();
			m_pLastPlayer->SpeedUp();
			m_Powerup2->SetHit(true);
			m_pSnapShot2 = m_pLastPlayer;
		}
	}
}

void CTournament::ProcessBallPowerup3()
{


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
	const int kiX3 = m_iWidth / 2 - 50;
	const int kiY3 = 20;
	SetBkMode(hdc, TRANSPARENT);
	TextOutA(hdc, kiX, kiY, m_strScore1.c_str(), static_cast<int>(m_strScore1.size()));
	TextOutA(hdc, kiX2, kiY2, m_strScore2.c_str(), static_cast<int>(m_strScore2.size()));
	
	TextOutA(hdc, kiX3, kiY3, m_strScore3.c_str(), static_cast<int>(m_strScore3.size()));
}

void CTournament::UpdateScoreText()
{
	m_strScore1 = "Player 1: ";
	m_strScore1 += ToString(GetNumberOfWinsPlayer1());

	m_strScore2 = "Player 2: ";
	m_strScore2 += ToString(GetNumberOfWinsPlayer2());

	m_strScore3 = "Round ";
	m_strScore3 += ToString(GetNumberOfGamesPlayed());
}


//void CTournament::DrawFPS()
//{
//	HDC hdc = CGame::GetInstance(true).GetBackBuffer()->GetBFDC();
//
//	m_fpsCounter->DrawFPSText(hdc, m_iWidth, m_iHeight);
//
//}
