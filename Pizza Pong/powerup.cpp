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
#include "resource.h"
#include "utils.h"

// This Include
#include "powerup.h"

// Static Variables

// Static Function Prototypes

// Implementation

CPowerup::CPowerup(int _iRandomNumber)
	: m_iPowerUpNumber(_iRandomNumber)
{

}

CPowerup::~CPowerup()
{

}

bool CPowerup::Initialise(int _iX, int _iY)
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

void CPowerup::Draw()
{
	CEntity::Draw();
}

void CPowerup::Process(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);
}
