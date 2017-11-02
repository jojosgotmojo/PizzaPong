//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: background.h
// Description	: Header file to create the background sprite
// Author		: Pizza Party - Aimee Constable, Chloe Cantwell, Joseph Maton, Nick Lacy
// Mail			: aimee.con6886@mediadesign.school.nz, chloe.can6956@mediadesign.school.nz, joseph.mat3620@mediadesign.school.nz, darcy.lac6935@mediadesign.school.nz
//

#pragma once

#if !defined(__BACKGROUND_H__)
#define __BACKGROUND_H__

// Local Includes
#include "entity.h"


class CSprite;

class CBackGround : public CEntity
{
	// Member Functions
public:
	CBackGround();
	virtual ~CBackGround();

	virtual bool Initialise();

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

private:
	CBackGround(const CBackGround& _kr);


};

#endif