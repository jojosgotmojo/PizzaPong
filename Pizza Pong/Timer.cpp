//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: Timer.cpp
// Description	: Timer instance initialisation
// Author		: Pizza Party - Aimee Constable, Chloe Cantwell, Joseph Maton, Nick Lacy
// Mail			: aimee.con6886@mediadesign.school.nz, chloe.can6956@mediadesign.school.nz, joseph.mat3620@mediadesign.school.nz, darcy.lac6935@mediadesign.school.nz
//

// Local Includes
#include "resource.h"
#include "utils.h"
#include "game.h"
#include "backbuffer.h"

// This Include
#include "timer.h"

CTimer::CTimer(int _iPowerUpNumber)
	: m_iPowerUpNumber(_iPowerUpNumber)
{
	m_bIsActive = true;
	m_tpInitial = high_resolution_clock::now();
}

CTimer::~CTimer()
{

}

bool CTimer::Initialise(int _iX, int _iY)
{
	switch (m_iPowerUpNumber)
	{
	case 0:
	{
		//Increase paddle size
		VALIDATE(CEntity::Initialise(IDB_TOMATOSPRITE, IDB_TOMATOMASK));
		this->m_fX = _iX;
		this->m_fY = _iY;
		break;
	}
	case 1:
	{
		//Paddle speed up
		VALIDATE(CEntity::Initialise(IDB_CHILIMASK, IDB_CHILISPRITE));
		this->m_fX = _iX;
		this->m_fY = _iY;
		break;
	}
	case 2:
	{
		//Add extra ball
		VALIDATE(CEntity::Initialise(IDB_GREENPEPPERSPRITE, IDB_GREENPEPPERMASK));
		this->m_fX = _iX;
		this->m_fY = _iY;
		break;
	}
	default: break;
	}

	return (true);
}

void CTimer::Draw()
{

	if (m_bIsActive)
	{
		CEntity::Draw();
	}

	m_tpCheck = high_resolution_clock::now();
	m_dDuration = duration_cast<milliseconds>(m_tpCheck - m_tpInitial).count() / 1000.00;

	if (m_dDuration >= 20.00)
	{
		this->SetActive(false);
	}


	HDC hdc = CGame::GetInstance(true).GetBackBuffer()->GetBFDC();
	HFONT font = CreateFont(46, 20, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Courier New"));
	SetBkMode(hdc, TRANSPARENT);
	HFONT hTmp = (HFONT)SelectObject(hdc, font);

	m_TimerString = ToString(20 - (int)m_dDuration);

	TextOutA(hdc, this->GetX(), this->GetY(), m_TimerString.c_str(), static_cast<int>(m_TimerString.size()));

	DeleteObject(SelectObject(hdc, hTmp));
}

void CTimer::Process(float _fDeltaTick)
{

	CEntity::Process(_fDeltaTick);
}

void CTimer::SetActive(bool _bIsActive)
{
	m_bIsActive = _bIsActive;
}

bool CTimer::IsActive() const
{
	return m_bIsActive;
}
