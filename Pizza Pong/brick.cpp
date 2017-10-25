//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: brick.cpp
// Description	: Brick instance initialisation
// Author		: Pizza Party - Aimee Constable, Chloe Cantwell, Joseph Maton, Nick Lacy
// Mail			: aimee.con6886@mediadesign.school.nz, chloe.can6956@mediadesign.school.nz, joseph.mat3620@mediadesign.school.nz, darcy.lac6935@mediadesign.school.nz
//


// Local Includes
#include "resource.h"
#include "utils.h"
#include "Dependencies\FMOD\fmod.hpp"
#include "sounds.h"

// This Include
#include "Brick.h"

CBrick::CBrick()
: m_bHit(false)
{

}

CBrick::~CBrick()
{

}

bool CBrick::Initialise()
{
    VALIDATE(CEntity::Initialise(IDB_BRICKSPRITE, IDB_BRICKMASK));

    return (true);
}

void CBrick::Draw()
{
    if (!m_bHit)
    {
        CEntity::Draw();
    }
}

void CBrick::Process(float _fDeltaTick)
{
	m_tpCheck = high_resolution_clock::now();
	double check = duration_cast<milliseconds>(m_tpCheck - m_tpFirst).count() / 1000.00;

	if (check > 20.00 && this->IsHit())
	{
		this->SetHit(false);
	}

    if (!m_bHit)
    {
        CEntity::Process(_fDeltaTick);
    }
}

double CBrick::CheckTimeElapsed() const
{
	high_resolution_clock::time_point Temp = high_resolution_clock::now();

	double dCheck = duration_cast<milliseconds>(Temp - m_tpFirst).count() / 10000.00;
	return dCheck;

}

void CBrick::SetHit(bool _b)
{
	m_tpFirst = high_resolution_clock::now();

    m_bHit = _b;
}

bool CBrick::IsHit() const
{
    return (m_bHit);
}

