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

#if !defined(__PADDLE_H__)
#define __PADDLE_H__

// Library Includes

// Local Includes
#include "entity.h"
#include "Sprite.h"

// Types

// Constants

// Prototypes
class CPaddle : public CEntity
{
    // Member Functions
public:
    CPaddle(int _iPlayerNumber);
    virtual ~CPaddle();

    virtual bool Initialise();
	virtual bool Enlarge();

    virtual void Draw();
    virtual void Process(float _fDeltaTick);
	void SpeedUp();
	void ResetSpeed();

protected:

private:
    CPaddle(const CPaddle& _kr);

    // Member Variables
public:

protected:

private:
	int m_iPlayerNumber;
	int m_fYVelocity;
};

#endif    // __PADDLE_H__
