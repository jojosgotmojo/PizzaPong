//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: background.cpp
// Description	: Background sprite initialisation
// Author		: Pizza Party - Aimee Constable, Chloe Cantwell, Joseph Maton, Nick Lacy
// Mail			: aimee.con6886@mediadesign.school.nz, chloe.can6956@mediadesign.school.nz, joseph.mat3620@mediadesign.school.nz, darcy.lac6935@mediadesign.school.nz
//

// Local Includes
#include "resource.h"
#include "utils.h"
#include "backbuffer.h"
#include "game.h"

// This Include
#include "background.h"

CBackGround::CBackGround()
{

}

CBackGround::~CBackGround()
{

}

bool CBackGround::Initialise()
{
	CEntity::Initialise(IDB_PIZZA, IDB_PIZZAMASK);

	return (true);
}

void CBackGround::Draw()
{
	CEntity::Draw();
}

void CBackGround::Process(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);
}
