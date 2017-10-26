//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: level.cpp
// Description	: Level instance initialisation, works for quick game
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
#include "background.h"
#include <time.h>
#include "sounds.h"
#include "powerup.h"
#include "resource.h"


// This Include
#include "Level.h"

#define DEFAULT_BALL_SPEED 75.00


CLevel::CLevel()
: m_iBricksRemaining(0)
, m_pPaddle1(0)
, m_pPaddle2(0)
, m_pBall(0)
, m_pBall2(0)
, m_pBall3(0)
, m_iWidth(0)
, m_iHeight(0)
{
}

CLevel::~CLevel()
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

	delete m_pBackground;
	m_pBackground = 0;

	delete m_pBall2;
	m_pBall2 = 0;


	delete m_pBall3;
	m_pBall3 = 0;

	delete m_pTimer1;
	m_pTimer1 = 0;

	delete m_pTimer2;
	m_pTimer2 = 0;

	delete m_pTimerP2A;
	m_pTimerP2A = 0;

	delete m_pTimerP2B;
	m_pTimerP2B = 0;


}

bool CLevel::Initialise(int _iWidth, int _iHeight, CSounds SoundEffect)
{
	_sound = SoundEffect;

	_sound.InitFmod();
	_sound.LoadSound();

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

	const int kiNumBricks = 45;
	const int kg_iStartX = m_iWidth / 2 - 80;
	const int kg_iStartY = 30;
	const int kiGap = 5;

	int iCurrentX = kg_iStartX;
	int iCurrentY = kg_iStartY;

	for (int i = 0; i < kiNumBricks; ++i)
	{
		CBrick* pBrick = new CBrick();
		VALIDATE(pBrick->Initialise());

		pBrick->SetX(static_cast<float>(iCurrentX));
		pBrick->SetY(static_cast<float>(iCurrentY));

		iCurrentY += static_cast<int>(pBrick->GetHeight()) + kiGap;

		if (iCurrentY > _iHeight)
		{
			iCurrentY = kg_iStartY;
			iCurrentX += 30;

		}

		m_vecBricks.push_back(pBrick);
	}

	SetBricksRemaining(kiNumBricks);

	return (true);
}

void CLevel::Draw()
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
	if (m_pBall2 != nullptr)
	{
		m_pBall2->Draw();
	}
	if (m_pBall3 != nullptr)
	{
		m_pBall3->Draw();
	}
	if (m_pTimer1 != nullptr)
	{
		m_pTimer1->Draw();
	}
	if (m_pTimer2 != nullptr)
	{
		m_pTimer2->Draw();
	}
	if (m_pTimerP2A != nullptr)
	{
		m_pTimerP2A->Draw();
	}
	if (m_pTimerP2B != nullptr)
	{
		m_pTimerP2B->Draw();
	}

    DrawScore();
}

void CLevel::Process(float _fDeltaTick)
{
	m_pBackground->Process(_fDeltaTick);
	if (m_pBall != nullptr)
	{
		m_pBall->Process(_fDeltaTick);
	}
	if (m_pBall2 != nullptr)
	{
		m_pBall2->Process(_fDeltaTick);
	}
	if (m_pBall3 != nullptr)
	{
		m_pBall3->Process(_fDeltaTick);
	}
	
	m_pPaddle1->Process(_fDeltaTick);
	m_pPaddle2->Process(_fDeltaTick);
	m_Powerup1->Process(_fDeltaTick);
	m_Powerup2->Process(_fDeltaTick);
	ProcessBallWallCollision(m_pBall);
	ProcessBallPaddle1Collision(m_pBall);
	ProcessBallPaddle2Collision(m_pBall);
	ProcessBallBrickCollision(m_pBall);
	ProcessBallBounds(m_pBall);
	ProcessBallPowerup1(m_pBall);
	ProcessBallPowerup2(m_pBall);
	ProcessBallPowerup3(m_pBall);

	if (m_pBall2 != nullptr)
	{
		ProcessBallWallCollision(m_pBall2);
		ProcessBallPaddle1Collision(m_pBall2);
		ProcessBallPaddle2Collision(m_pBall2);
		ProcessBallBrickCollision(m_pBall2);
		ProcessBallBounds(m_pBall2);
		ProcessBallPowerup1(m_pBall2);
		ProcessBallPowerup2(m_pBall2);
		ProcessBallPowerup3(m_pBall2);
	}
	if (m_pBall3 != nullptr)
	{
		ProcessBallWallCollision(m_pBall3);
		ProcessBallPaddle1Collision(m_pBall3);
		ProcessBallPaddle2Collision(m_pBall3);
		ProcessBallBrickCollision(m_pBall3);
		ProcessBallBounds(m_pBall3);
		ProcessBallPowerup1(m_pBall3);
		ProcessBallPowerup2(m_pBall3);
		ProcessBallPowerup3(m_pBall3);
	}
	

	if (m_pTimer1 != nullptr && m_pTimer1->IsActive() == false)
	{
		switch (m_iPowerUp1Identifier)
		{
		case 0:
		{
			m_pPaddle1->ChangeSprite(IDB_PADDLESPRITE, IDB_PADDLEMASK);
			m_Powerup1->SetHit(false);
			delete m_pTimer1;
			m_pTimer1 = nullptr;
			break;
		}
		case 1:
		{
			m_pPaddle1->ResetSpeed();
			m_Powerup1->SetHit(false);
			delete m_pTimer1;
			m_pTimer1 = nullptr;
			break;
		}
		case 2:
		{
			if (m_pBall2 != nullptr)
			{
				delete m_pBall2;
				m_pBall2 = nullptr;
			}
			
			m_Powerup1->SetHit(false);
			delete m_pTimer1;
			m_pTimer1 = nullptr;
			break;
		}
		default:break;
		}
	}
	if (m_pTimer2 != nullptr && m_pTimer2->IsActive() == false)
	{
		switch (m_iPowerUp2Identifier)
		{
		case 0:
		{
			m_pPaddle1->ChangeSprite(IDB_PADDLESPRITE, IDB_PADDLEMASK);
			m_Powerup2->SetHit(false);
			delete m_pTimer2;
			m_pTimer2 = nullptr;
			break;
		}
		case 1:
		{
			m_pPaddle1->ResetSpeed();
			m_Powerup2->SetHit(false);
			delete m_pTimer2;
			m_pTimer2 = nullptr;
			break;
		}
		case 2:
		{
			if (m_pBall2 != nullptr)
			{
				delete m_pBall2;
				m_pBall2 = nullptr;
			}
			m_Powerup2->SetHit(false);
			delete m_pTimer2;
			m_pTimer2 = nullptr;
			break;
		}
		default:break;
		}
	}
	if (m_pTimerP2A != nullptr && m_pTimerP2A->IsActive() == false)
	{
		switch (m_iPowerUp2Identifier)
		{
		case 0:
		{
			m_pPaddle2->ChangeSprite(IDB_PADDLESPRITEFLIPPED, IDB_PADDLESPRITEFLIPPEDMASK);
			m_Powerup2->SetHit(false);
			delete m_pTimerP2A;
			m_pTimerP2A = nullptr;
			break;
		}
		case 1:
		{
			m_pPaddle2->ResetSpeed();
			m_Powerup2->SetHit(false);
			delete m_pTimerP2A;
			m_pTimerP2A = nullptr;
			break;
		}
		case 2:
		{
			if (m_pBall2 != nullptr)
			{
				delete m_pBall2;
				m_pBall2 = nullptr;
			}
			
			m_Powerup2->SetHit(false);
			delete m_pTimerP2A;
			m_pTimerP2A = nullptr;
			break;
		}
		default:break;
		}
	}
	if (m_pTimerP2B != nullptr && m_pTimerP2B->IsActive() == false)
	{
		switch (m_iPowerUp2Identifier)
		{
		case 0:
		{
			m_pPaddle2->ChangeSprite(IDB_PADDLESPRITEFLIPPED, IDB_PADDLESPRITEFLIPPEDMASK);
			m_Powerup2->SetHit(false);
			delete m_pTimerP2B;
			m_pTimerP2B = nullptr;
			break;
		}
		case 1:
		{
			m_pPaddle2->ResetSpeed();
			m_Powerup2->SetHit(false);
			delete m_pTimerP2B;
			m_pTimerP2B = nullptr;
			break;
		}
		case 2:
		{
			if (m_pBall2 != nullptr)
			{
				delete m_pBall2;
				m_pBall2 = nullptr;
			}
			
			m_Powerup2->SetHit(false);
			delete m_pTimerP2B;
			m_pTimerP2B = nullptr;
			break;
		}
		default:break;
		}
	}

    for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
    {
        m_vecBricks[i]->Process(_fDeltaTick);
    }
	
}

CPaddle* CLevel::GetPaddle() const
{
    return (m_pPaddle1);
}

void CLevel::ProcessBallWallCollision(CBall* ballnum)
{

	float fBallX = ballnum->GetX();
	float fBallY = ballnum->GetY();
	float fBallW = ballnum->GetWidth();
	float fBallH = ballnum->GetHeight();

	float fHalfBallW = fBallW / 2;
	float fHalfBallH = fBallH / 2;

	if (fBallX < fHalfBallW) //represents the situation when the ball has hit the left wall
	{
		
		ballnum->SetX(static_cast<float>(m_iWidth / 4.0f * 3));
		ballnum->SetVelocityY(DEFAULT_BALL_SPEED);

		_sound.PlaySoundQ("WinSound");
		CGame::GetInstance(false).GameOverLostPlayer1();
		
	}
	else if (fBallX > m_iWidth - fHalfBallW) //represents the situation when the ball has hit the right wall
	{
	
		ballnum->SetX(static_cast<float>(m_iWidth / 4.0f));
		ballnum->SetVelocityY(DEFAULT_BALL_SPEED);

		_sound.PlaySoundQ("WinSound");
		CGame::GetInstance(false).GameOverLostPlayer2();
		
	}

	if (fBallY < fHalfBallH) //represents the situation when the ball has hit the top wall
	{
		ballnum->SetVelocityY(ballnum->GetVelocityY() * -1); //reverse the ball's y velocity
	}

	if (fBallY  > m_iHeight - fHalfBallH)  //represents the situation when the ball has hit the bottom wall
	{
		ballnum->SetVelocityY(ballnum->GetVelocityY() * -1); //reverse the ball's y velocity
	}

}

void CLevel::ProcessBallPaddle1Collision(CBall* ballnum)
{
	float fBallR = ballnum->GetRadius();

	float fBallX = ballnum->GetX();
	float fBallY = ballnum->GetY();

	float fPaddle1X = m_pPaddle1->GetX();
	float fPaddle1Y = m_pPaddle1->GetY();

	float fPaddle1H = m_pPaddle1->GetHeight();
	float fPaddle1W = m_pPaddle1->GetWidth();

	if ((fBallX + fBallR > fPaddle1X - fPaddle1W / 2) && //ball.right > paddle.left
		(fBallX - fBallR < fPaddle1X + fPaddle1W / 2) && //ball.left < paddle.right
		(fBallY + fBallR > fPaddle1Y - fPaddle1H / 2) && //ball.bottom > paddle.top
		(fBallY - fBallR < fPaddle1Y + fPaddle1H / 2))  //ball.top < paddle.bottom
	{
		ballnum->SetVelocityX(ballnum->GetVelocityX() * -1); //Reverse ball's X direction


		int iRand = rand() % 1 + 9;
		float ReducedValue = static_cast<float>(iRand) / 10;


		if ((ballnum->GetVelocityY() < 0) && (ballnum->GetY() > fPaddle1Y))
		{
			if (ballnum->GetVelocityY() < -225.00f)
			{
				ballnum->SetVelocityY(-225.00f);
			}

			ballnum->SetVelocityY(ballnum->GetVelocityY() * (-1 - ReducedValue)); //Reverse ball's Y direction
		}
		else if ((ballnum->GetVelocityY() > 0) && (ballnum->GetY() < fPaddle1Y))
		{

			if (ballnum->GetVelocityY() > 225.00f)
			{
				ballnum->SetVelocityY(225.00f);
			}
			ballnum->SetVelocityY(ballnum->GetVelocityY() * (-1 - ReducedValue)); //Reverse ball's Y direction
		}
		else
		{
			ballnum->SetVelocityY(ballnum->GetVelocityY() * (1 + ReducedValue));
		}
		m_pLastPlayer = m_pPaddle1;
		_sound.PlaySoundQ("PaddleHit");

	}
}

void CLevel::ProcessBallPaddle2Collision(CBall* ballnum)
{
	float fBallR = ballnum->GetRadius();

	float fBallX = ballnum->GetX();
	float fBallY = ballnum->GetY();

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

		ballnum->SetX((fPaddle2X - fPaddle2W / 2) - fBallR);  //Set the ball.bottom = paddle.top; to prevent the ball from going through the paddle!
		ballnum->SetVelocityX(ballnum->GetVelocityX() * -1); //Reverse ball's Y direction

		if ((ballnum->GetVelocityY() < 0) && (ballnum->GetY() > fPaddle2Y))
		{
			if (ballnum->GetVelocityY() < -225.00f)
			{
				ballnum->SetVelocityY(-225.00f);
			}

			ballnum->SetVelocityY(ballnum->GetVelocityY() * (-1 - ReducedValue)); //Reverse ball's Y direction
		}
		else if ((ballnum->GetVelocityY() > 0) && (ballnum->GetY() < fPaddle2Y))
		{

			if (ballnum->GetVelocityY() > 225.00f)
			{
				ballnum->SetVelocityY(225.00f);
			}
			ballnum->SetVelocityY(ballnum->GetVelocityY() * (-1 - ReducedValue)); //Reverse ball's Y direction
		}
		else
		{
			ballnum->SetVelocityY(ballnum->GetVelocityY() * (1 + ReducedValue));
		}
		m_pLastPlayer = m_pPaddle2;
		_sound.PlaySoundQ("PaddleHit");

	}
}

void CLevel::ProcessBallBrickCollision(CBall* ballnum)
{

	for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
	{
		if (!m_vecBricks[i]->IsHit())
		{
			float fBallR = ballnum->GetRadius();

			float fBallX = ballnum->GetX();
			float fBallY = ballnum->GetY();

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

				if (m_vecBricks[(i > 0 ? i - 1 : i)]->CheckTimeElapsed() <= 2.00)// || (m_vecBricks[(i < m_vecBricks.size() ? i : i - 1)]->IsHit() && m_vecBricks[(i < m_vecBricks.size() ? i : i - 1)]->timeElapsed() <= 2.00))
				{
					ballnum->SetVelocityX(ballnum->GetVelocityX() * 1);
					if (ballnum->GetVelocityX() >= 1)
					{
						ballnum->SetX((fBrickX + (fBrickW / 2.0f)) - fBallR);
					}
					if (ballnum->GetVelocityX() <= -1)
					{
						ballnum->SetX((fBrickX + (fBrickW / 2.0f)) + fBallR);
					}
				}
				else
				{
					ballnum->SetVelocityX(ballnum->GetVelocityX() * -1);
					if (ballnum->GetVelocityX() >= 1)
					{
						ballnum->SetX((fBrickX + (fBrickW / 2.0f)) - fBallR);
					}
					if (ballnum->GetVelocityX() <= -1)
					{
						ballnum->SetX((fBrickX + (fBrickW / 2.0f)) + fBallR);
					}
				}

				m_vecBricks[i]->SetHit(true);
				_sound.PlaySoundQ("hitSound");

				SetBricksRemaining(GetBricksRemaining() - 1);
				_sound.PlaySoundQ("hitSound");
			}
		}
	}
}

void CLevel::ProcessBallBounds(CBall* ballnum)
{
	if (ballnum->GetY() < 0)
	{
		ballnum->SetY(ballnum->GetRadius());
	}
	else if (ballnum->GetY() > m_iHeight)
	{
		ballnum->SetY(m_iHeight - ballnum->GetRadius());
	}

	if (ballnum->GetX() < 0)
	{
		ballnum->SetX(ballnum->GetRadius());
	}
	else if (ballnum->GetX() > m_iWidth)
	{
		/*CGame::GetInstance().GameOverLost();
		ballnum->SetX(static_cast<float>(m_iWidth));*/
	}
}

void CLevel::ProcessBallPowerup1(CBall* ballnum)
{
	float fBallR = ballnum->GetRadius();

	float fBallX = ballnum->GetX();
	float fBallY = ballnum->GetY();

	float fPowerUp1X = m_Powerup1->GetX();
	float fPowerUp1Y = m_Powerup1->GetY();
	float fPowerUp2X = m_Powerup2->GetX();
	float fPowerUp2Y = m_Powerup2->GetY();

	float fPowerUp1H = m_Powerup1->GetHeight();
	float fPowerUp1W = m_Powerup1->GetWidth();
	float fPowerUp2H = m_Powerup2->GetHeight();
	float fPowerUp2W = m_Powerup2->GetWidth();

	if (m_iPowerUp1Identifier == 0 && m_pLastPlayer != nullptr)
	{
		if ((fBallX + fBallR > fPowerUp1X - fPowerUp1W / 2) &&
			(fBallX - fBallR < fPowerUp1X + fPowerUp1W / 2) &&
			(fBallY + fBallR > fPowerUp1Y - fPowerUp1H / 2) &&
			(fBallY - fBallR < fPowerUp1Y + fPowerUp1H / 2))
		{
			if (m_Powerup1->IsHit() == false)
			{
				if (m_pLastPlayer == m_pPaddle1)
				{
					m_pPaddle1->ChangeSprite(IDB_ENLARGEDPADDLE, IDB_ENLARGEDPADDLEMASK);

					if (m_pTimer1 == nullptr)
					{
						m_pTimer1 = new CTimer(0);
						m_pTimer1->Initialise(20, m_iHeight - 100);
					}
					else if (m_pTimer1 != nullptr)
					{
						m_pTimer2 = new CTimer(0);
						m_pTimer2->Initialise(100, m_iHeight - 100);
					}
				}
				if (m_pLastPlayer == m_pPaddle2)
				{
					m_pPaddle2->ChangeSprite(IDB_PADDLEFLIPPEDENLARGED, IDB_PADDLEFLIPPEDENLARGEDMASK);

					if (m_pTimerP2A == nullptr)
					{
						m_pTimerP2A = new CTimer(0);
						m_pTimerP2A->Initialise(m_iWidth - 80, m_iHeight - 100);
					}
					else if (m_pTimerP2A != nullptr)
					{
						m_pTimerP2B = new CTimer(0);
						m_pTimerP2B->Initialise(m_iWidth - 160, m_iHeight - 100);
					}
				}
				m_Powerup1->SetHit(true);
				_sound.PlaySoundQ("PowerupStart");

			}
		}
	}

	if (m_iPowerUp2Identifier == 0 && m_pLastPlayer != nullptr)
	{
		if ((fBallX + fBallR > fPowerUp2X - fPowerUp2W / 2) &&
			(fBallX - fBallR < fPowerUp2X + fPowerUp2W / 2) &&
			(fBallY + fBallR > fPowerUp2Y - fPowerUp2H / 2) &&
			(fBallY - fBallR < fPowerUp2Y + fPowerUp2H / 2))
		{
			if (m_Powerup2->IsHit() == false)
			{
				if (m_pLastPlayer == m_pPaddle1)
				{
					m_pPaddle1->ChangeSprite(IDB_ENLARGEDPADDLE, IDB_ENLARGEDPADDLEMASK);

					if (m_pTimer1 == nullptr)
					{
						m_pTimer1 = new CTimer(0);
						m_pTimer1->Initialise(20, m_iHeight - 100);
					}
					else if (m_pTimer1 != nullptr)
					{
						m_pTimer2 = new CTimer(0);
						m_pTimer2->Initialise(100, m_iHeight - 100);
					}
				}
				if (m_pLastPlayer == m_pPaddle2)
				{
					m_pPaddle2->ChangeSprite(IDB_PADDLEFLIPPEDENLARGED, IDB_PADDLEFLIPPEDENLARGEDMASK);

					if (m_pTimerP2A == nullptr)
					{
						m_pTimerP2A = new CTimer(0);
						m_pTimerP2A->Initialise(m_iWidth - 80, m_iHeight - 100);
					}
					else if (m_pTimerP2A != nullptr)
					{
						m_pTimerP2B = new CTimer(0);
						m_pTimerP2B->Initialise(m_iWidth - 160, m_iHeight - 100);
					}
				}
				_sound.PlaySoundQ("PowerupStart");

				m_Powerup2->SetHit(true);
			}
		}
	}

}

void CLevel::ProcessBallPowerup2(CBall* ballnum)
{
	float fBallR = ballnum->GetRadius();

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

	if (m_iPowerUp1Identifier == 1 && m_pLastPlayer != nullptr)
	{
		if ((fBallX + fBallR > fPowerUp1X - fPowerUp1W / 2) &&
			(fBallX - fBallR < fPowerUp1X + fPowerUp1W / 2) &&
			(fBallY + fBallR > fPowerUp1Y - fPowerUp1H / 2) &&
			(fBallY - fBallR < fPowerUp1Y + fPowerUp1H / 2))
		{
			if (m_Powerup1->IsHit() == false)
			{
				if (m_pLastPlayer == m_pPaddle1)
				{
					m_pPaddle1->SpeedUp();

					if (m_pTimer1 == nullptr)
					{
						m_pTimer1 = new CTimer(1);
						m_pTimer1->Initialise(20, m_iHeight - 100);
					}
					else if (m_pTimer1 != nullptr)
					{
						m_pTimer2 = new CTimer(1);
						m_pTimer2->Initialise(100, m_iHeight - 100);
					}
				}
				if (m_pLastPlayer == m_pPaddle2)
				{
					m_pPaddle2->SpeedUp();

					if (m_pTimerP2A == nullptr)
					{
						m_pTimerP2A = new CTimer(1);
						m_pTimerP2A->Initialise(m_iWidth - 80, m_iHeight - 100);
					}
					else if (m_pTimerP2A != nullptr)
					{
						m_pTimerP2B = new CTimer(1);
						m_pTimerP2B->Initialise(m_iWidth - 160, m_iHeight - 100);
					}
				}
			}
			m_Powerup1->SetHit(true);
			_sound.PlaySoundQ("PowerupStart");

		}
	}

	if (m_iPowerUp2Identifier == 1 && m_pLastPlayer != nullptr)
	{
		if ((fBallX + fBallR > fPowerUp2X - fPowerUp2W / 2) &&
			(fBallX - fBallR < fPowerUp2X + fPowerUp2W / 2) &&
			(fBallY + fBallR > fPowerUp2Y - fPowerUp2H / 2) &&
			(fBallY - fBallR < fPowerUp2Y + fPowerUp2H / 2))
		{
			if (m_Powerup2->IsHit() == false)
			{
				if (m_pLastPlayer == m_pPaddle1)
				{
					m_pPaddle1->SpeedUp();

					if (m_pTimer1 == nullptr)
					{
						m_pTimer1 = new CTimer(1);
						m_pTimer1->Initialise(20, m_iHeight - 100);
					}
					else if (m_pTimer1 != nullptr)
					{
						m_pTimer2 = new CTimer(1);
						m_pTimer2->Initialise(100, m_iHeight - 100);
					}
				}
				if (m_pLastPlayer == m_pPaddle2)
				{
					m_pPaddle2->SpeedUp();

					if (m_pTimerP2A == nullptr)
					{
						m_pTimerP2A = new CTimer(1);
						m_pTimerP2A->Initialise(m_iWidth - 80, m_iHeight - 100);
					}
					else if (m_pTimerP2A != nullptr)
					{
						m_pTimerP2B = new CTimer(1);
						m_pTimerP2B->Initialise(m_iWidth - 160, m_iHeight - 100);
					}
				}
				_sound.PlaySoundQ("PowerupStart");

				m_Powerup2->SetHit(true);
			}
		}
	}
}

bool CLevel::ProcessBallPowerup3(CBall* ballnum)
{
	float fBallR = ballnum->GetRadius();

	float fBallX = ballnum->GetX();
	float fBallY = ballnum->GetY();

	float fPowerUp1X = m_Powerup1->GetX();
	float fPowerUp1Y = m_Powerup1->GetY();
	float fPowerUp2X = m_Powerup2->GetX();
	float fPowerUp2Y = m_Powerup2->GetY();

	float fPowerUp1H = m_Powerup1->GetHeight();
	float fPowerUp1W = m_Powerup1->GetWidth();
	float fPowerUp2H = m_Powerup2->GetHeight();
	float fPowerUp2W = m_Powerup2->GetWidth();

	if (m_iPowerUp1Identifier == 2 && m_pLastPlayer != nullptr)
	{
		if ((fBallX + fBallR > fPowerUp1X - fPowerUp1W / 2) &&
			(fBallX - fBallR < fPowerUp1X + fPowerUp1W / 2) &&
			(fBallY + fBallR > fPowerUp1Y - fPowerUp1H / 2) &&
			(fBallY - fBallR < fPowerUp1Y + fPowerUp1H / 2))
		{
			if (m_Powerup1->IsHit() == false)
			{
				if (m_pLastPlayer == m_pPaddle1)
				{
					if (m_pBall2 == nullptr)
					{
						m_pBall2 = new CBall();
						VALIDATE(m_pBall2->Initialise(fPowerUp1X, fPowerUp1Y, (m_pBall->GetVelocityX() * -1), (m_pBall->GetVelocityY() * -1)));
					}
					

					if (m_pTimer1 == nullptr)
					{
						m_pTimer1 = new CTimer(2);
						m_pTimer1->Initialise(20, m_iHeight - 100);
					}
					else if (m_pTimer1 != nullptr)
					{
						m_pTimer2 = new CTimer(2);
						m_pTimer2->Initialise(100, m_iHeight - 100);
					}
				}
				if (m_pLastPlayer == m_pPaddle2)
				{
					if (m_pBall2 == nullptr)
					{
						m_pBall2 = new CBall();
						VALIDATE(m_pBall2->Initialise(fPowerUp1X, fPowerUp1Y, (m_pBall->GetVelocityX() * -1), (m_pBall->GetVelocityY() * -1)));
					}
					

					if (m_pTimerP2A == nullptr)
					{
						m_pTimerP2A = new CTimer(2);
						m_pTimerP2A->Initialise(m_iWidth - 80, m_iHeight - 100);
					}
					else if (m_pTimerP2A != nullptr)
					{
						m_pTimerP2B = new CTimer(2);
						m_pTimerP2B->Initialise(m_iWidth - 160, m_iHeight - 100);
					}
				}
			}
			m_Powerup1->SetHit(true);
			_sound.PlaySoundQ("PowerupStart");

		}
	}
	if (m_iPowerUp2Identifier == 2 && m_pLastPlayer != nullptr)
	{
		if ((fBallX + fBallR > fPowerUp2X - fPowerUp2W / 2) &&
			(fBallX - fBallR < fPowerUp2X + fPowerUp2W / 2) &&
			(fBallY + fBallR > fPowerUp2Y - fPowerUp2H / 2) &&
			(fBallY - fBallR < fPowerUp2Y + fPowerUp2H / 2))
		{
			if (m_Powerup2->IsHit() == false)
			{
				if (m_pLastPlayer == m_pPaddle1)
				{
					if (m_pBall2 == nullptr)
					{
						m_pBall2 = new CBall();
						VALIDATE(m_pBall2->Initialise(fPowerUp1X, fPowerUp1Y, (m_pBall->GetVelocityX() * -1), (m_pBall->GetVelocityY() * -1)));
					}
					

					if (m_pTimer1 == nullptr)
					{
						m_pTimer1 = new CTimer(2);
						m_pTimer1->Initialise(20, m_iHeight - 100);
					}
					else if (m_pTimer1 != nullptr)
					{
						m_pTimer2 = new CTimer(2);
						m_pTimer2->Initialise(100, m_iHeight - 100);
					}
				}
				if (m_pLastPlayer == m_pPaddle2)
				{
					if (m_pBall2 == nullptr)
					{
						m_pBall2 = new CBall();
						VALIDATE(m_pBall2->Initialise(fPowerUp1X, fPowerUp1Y, (m_pBall->GetVelocityX() * -1), (m_pBall->GetVelocityY() * -1)));
					}
					

					if (m_pTimerP2A == nullptr)
					{
						m_pTimerP2A = new CTimer(2);
						m_pTimerP2A->Initialise(m_iWidth - 80, m_iHeight - 100);
					}
					else if (m_pTimerP2A != nullptr)
					{
						m_pTimerP2B = new CTimer(2);
						m_pTimerP2B->Initialise(m_iWidth - 160, m_iHeight - 100);
					}
				}
				_sound.PlaySoundQ("PowerupStart");

				m_Powerup2->SetHit(true);
			}
		}
	}

	return (true);
}

int CLevel::GetBricksRemaining() const
{
    return (m_iBricksRemaining);
}

void CLevel::SetBricksRemaining(int _i)
{
    m_iBricksRemaining = _i;
}

void CLevel::DrawScore()
{
    HDC hdc = CGame::GetInstance(false).GetBackBuffer()->GetBFDC();

    const int kiX = 0;
    const int kiY = m_iHeight - 14;
	SetBkMode(hdc, TRANSPARENT);
    
}



