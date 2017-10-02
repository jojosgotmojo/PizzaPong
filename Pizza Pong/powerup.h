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

#pragma once

#if !defined(__POWERUP_H__)
#define __POWERUP_H__

// Library Includes

// Local Includes
#include "entity.h"
#include "Sprite.h"

// Types

// Constants

// Prototypes
class CPowerup : public CEntity
{
	// Member Functions
public:
	CPowerup();
	virtual ~CPowerup();

	virtual bool Initialise();  

	virtual void Draw();
	virtual void Process(float _fDeltaTick);


	//testing powerup functions
	virtual void SpeedUpBall(); 
	virtual void ResizePaddles();
	virtual void ResizeBall();


protected:

private:
	CPowerup(const CPowerup& _kr);

	// Member Variables
public:

protected:

private:
	int m_iPlayerNumber;
};

#endif    // __POWERUP_H__
