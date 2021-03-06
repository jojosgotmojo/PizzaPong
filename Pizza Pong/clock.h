//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: clock.h
// Description	: header file for the clock instance
// Author		: Pizza Party - Aimee Constable, Chloe Cantwell, Joseph Maton, Nick Lacy
// Mail			: aimee.con6886@mediadesign.school.nz, chloe.can6956@mediadesign.school.nz, joseph.mat3620@mediadesign.school.nz, darcy.lac6935@mediadesign.school.nz
//

#pragma once

#if !defined(__CLOCK_H__)
#define __CLOCK_H__

// Library Includes
#include <Windows.h>


class CClock
{
  
public:
    CClock();
    ~CClock();

    bool Initialise();

    void Process();

    float GetDeltaTick();

private:
    CClock(const CClock& _kr);

protected:
    double m_fTimeElapsed;
	double m_fDeltaTime;
	double m_fLastTime;
	double m_fCurrentTime;
	double m_SecondsPerCount;

};


#endif    // __CLOCK_H__
