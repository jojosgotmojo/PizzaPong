//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: Timer.h
// Description	: header file for timer instance
// Author		: Pizza Party - Aimee Constable, Chloe Cantwell, Joseph Maton, Nick Lacy
// Mail			: aimee.con6886@mediadesign.school.nz, chloe.can6956@mediadesign.school.nz, joseph.mat3620@mediadesign.school.nz, darcy.lac6935@mediadesign.school.nz
//

#pragma once

#if !defined(__TIMER_H__)
#define __TIMER_H__

// Local Includes
#include "entity.h"
#include "Sprite.h"
#include <string>
#include <chrono>


using namespace std::chrono;

class CTimer : public CEntity
{
public:
	CTimer(int _iPowerUpNumber);
	virtual ~CTimer();

	bool Initialise(int _iX, int _iY);


	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	void SetActive(bool _bIsActive);
	bool IsActive() const;

private:
	CTimer(const CTimer& _kr);

private:
	int m_iPowerUpNumber;
	double m_dDuration;
	bool m_bIsActive;
	high_resolution_clock::time_point m_tpInitial;
	high_resolution_clock::time_point m_tpCheck;
	std::string m_TimerString;
};

#endif    // __POWERUP_H__
