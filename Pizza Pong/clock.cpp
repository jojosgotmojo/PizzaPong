//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: clock.cpp
// Description	: Clock instance initialisation
// Author		: Pizza Party - Aimee Constable, Chloe Cantwell, Joseph Maton, Nick Lacy
// Mail			: aimee.con6886@mediadesign.school.nz, chloe.can6956@mediadesign.school.nz, joseph.mat3620@mediadesign.school.nz, darcy.lac6935@mediadesign.school.nz
//

// Library Includes
#include <windows.h>

// Local Includes
#include "Clock.h"


CClock::CClock()
: m_fTimeElapsed(0.0)
, m_fDeltaTime(0.0)
, m_fLastTime(0.0)
, m_fCurrentTime(0.0)
{

}

CClock::~CClock()
{
	m_fTimeElapsed = 0;
	m_fDeltaTime = 0;
	m_fLastTime = 0;
	m_fCurrentTime = 0;
}

bool CClock::Initialise()
{
	__int64 _TimerFrequency, _currTime;
	QueryPerformanceFrequency((LARGE_INTEGER*)&_TimerFrequency);
	m_SecondsPerCount = 1.0 / static_cast<double>(_TimerFrequency);

	QueryPerformanceCounter((LARGE_INTEGER*)&_currTime);
	m_fCurrentTime = static_cast<double>(_currTime);
	m_fLastTime = static_cast<double>(_currTime);

	return (true);
}

void CClock::Process()
{
	//Get the time this frame.

	__int64 currTime;

	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	m_fCurrentTime = static_cast<double>(currTime);

	//Time difference between this frame and the previous frame
	m_fDeltaTime = (m_fCurrentTime - m_fLastTime)*m_SecondsPerCount;

	//Prepare for the next frame
	m_fLastTime = m_fCurrentTime;

	//Force non-negative
	if (m_fDeltaTime < 0.0)
	{
		m_fDeltaTime = 0.0;
	}

	m_fTimeElapsed += m_fDeltaTime;
}

float CClock::GetDeltaTick()
{
	return static_cast<float>(m_fDeltaTime);
}