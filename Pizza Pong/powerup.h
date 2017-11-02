//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: powerup.h
// Description	: header file for the powerup instance
// Author		: Pizza Party - Aimee Constable, Chloe Cantwell, Joseph Maton, Nick Lacy
// Mail			: aimee.con6886@mediadesign.school.nz, chloe.can6956@mediadesign.school.nz, joseph.mat3620@mediadesign.school.nz, darcy.lac6935@mediadesign.school.nz
//

#pragma once

#if !defined(__POWERUP_H__)
#define __POWERUP_H__

// Local Includes
#include "entity.h"
#include "Sprite.h"


class CPowerup : public CEntity
{
	
public:
	CPowerup(int _iRandomNumber);
	virtual ~CPowerup();

	bool Initialise(int _iX, int _iY);

	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	void SetHit(bool _bIsHit);
	bool IsHit() const;

private:
	CPowerup(const CPowerup& _kr);

private:
	int m_iPowerUpNumber;
	bool m_bIsHit;
};

#endif    // __POWERUP_H__
