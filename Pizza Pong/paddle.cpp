//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: paddle.cpp
// Description	: Paddle instance initialisation
// Author		: Pizza Party - Aimee Constable, Chloe Cantwell, Joseph Maton, Nick Lacy
// Mail			: aimee.con6886@mediadesign.school.nz, chloe.can6956@mediadesign.school.nz, joseph.mat3620@mediadesign.school.nz, darcy.lac6935@mediadesign.school.nz
//

// Local Includes
#include "resource.h"
#include "utils.h"

// This Include
#include "Paddle.h"


CPaddle::CPaddle(int _iPlayerNumber)
	: m_iPlayerNumber(_iPlayerNumber)
{
	m_fYVelocity = 400.00f;
}

CPaddle::~CPaddle()
{

}

bool CPaddle::Initialise()
{
	if (m_iPlayerNumber == 1)
	{
		VALIDATE(CEntity::Initialise(IDB_PADDLESPRITEFLIPPED, IDB_PADDLESPRITEFLIPPEDMASK));
	}
	else
	{
		VALIDATE(CEntity::Initialise(IDB_PADDLESPRITE, IDB_PADDLEMASK));
	}


    return (true);
}

void CPaddle::Draw()
{
    CEntity::Draw();
}

void CPaddle::Process(float _fDeltaTick)
{
	RECT rect;
	HWND hwnd = GetActiveWindow();

	GetClientRect(hwnd, &rect);


	float fHalfPaddleH = this->GetHeight() / 2.0;

	if (m_iPlayerNumber == 1)
	{

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			m_fY -= m_fYVelocity * _fDeltaTick;
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			m_fY += m_fYVelocity * _fDeltaTick;
		}

	}
	else
	{
		if (GetAsyncKeyState(0x57) & 0x8000)
		{
			m_fY -= m_fYVelocity * _fDeltaTick;
		}
		else if (GetAsyncKeyState(0x53) & 0x8000)
		{
			m_fY += m_fYVelocity * _fDeltaTick;
		}
	}
	if (m_fY - fHalfPaddleH <= rect.top)
	{
		m_fY = fHalfPaddleH;
	}
	else if (m_fY + fHalfPaddleH >= rect.bottom)
	{
		m_fY = rect.bottom- fHalfPaddleH;
	}
	
	CEntity::Process(_fDeltaTick);
}

void CPaddle::SpeedUp()
{
	m_fYVelocity *= 1.5f;

}

void CPaddle::ResetSpeed()
{
	m_fYVelocity = 400.00f;
}
