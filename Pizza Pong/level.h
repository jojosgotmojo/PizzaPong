//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: level.h
// Description	: header file for level instance
// Author		: Pizza Party - Aimee Constable, Chloe Cantwell, Joseph Maton, Nick Lacy
// Mail			: aimee.con6886@mediadesign.school.nz, chloe.can6956@mediadesign.school.nz, joseph.mat3620@mediadesign.school.nz, darcy.lac6935@mediadesign.school.nz
//

#pragma once

#if !defined(__LEVEL_H__)
#define __LEVEL_H__

// Library Includes
#include <vector>
#include <string>
#include "sounds.h"

class CBall;
class CPaddle;
class CBrick;
class CBackGround;

class CLevel
{
public:
    CLevel();
    virtual ~CLevel();

    virtual bool Initialise(int _iWidth, int _iHeight, CSounds _sound);

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

    CPaddle* GetPaddle() const;

    int GetBricksRemaining() const;

protected:
    void ProcessBallWallCollision();
    void ProcessBallPaddle1Collision();
	void ProcessBallPaddle2Collision();
    void ProcessBallBrickCollision();
    void ProcessBallBounds();

    void UpdateScoreText();
    void DrawScore();

    void SetBricksRemaining(int _i);

private:
    CLevel(const CLevel& _kr);

protected:
	CBackGround* m_pBackground;
    CBall* m_pBall;
    CPaddle* m_pPaddle1;
	CPaddle* m_pPaddle2;
    std::vector<CBrick*> m_vecBricks;
	CSounds _sound;

    int m_iWidth;
    int m_iHeight;

    int m_iBricksRemaining;

    std::string m_strScore;
};

#endif    // __LEVEL_H__
