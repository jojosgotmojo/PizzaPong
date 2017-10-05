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
#include "Brick.h"

// Static Variables

// Static Function Prototypes

// Implementation

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

void CBrick::SetHit(bool _b)
{
	m_tpFirst = high_resolution_clock::now();

    m_bHit = _b;
}

bool CBrick::IsHit() const
{
    return (m_bHit);
}

