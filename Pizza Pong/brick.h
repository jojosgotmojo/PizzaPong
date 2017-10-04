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

#if !defined(__BRICK_H__)
#define __BRICK_H__

// Library Includes
#include <chrono>
// Local Includes
#include "entity.h"


using namespace std::chrono;
// Types

// Constants

// Prototypes

class CBrick : public CEntity
{
    // Member Functions
public:
    CBrick();
    virtual ~CBrick();

    virtual bool Initialise();

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

    void SetHit(bool _b);
    bool IsHit() const;

protected:

private:
    CBrick(const CBrick& _kr);
	high_resolution_clock::time_point m_tpFirst;
	high_resolution_clock::time_point m_tpCheck;
    // Member Variables
public:

protected:
    bool m_bHit;

private:

};


#endif    // __BRICK_H__

