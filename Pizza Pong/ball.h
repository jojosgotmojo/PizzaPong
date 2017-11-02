//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: ball.h
// Description	: Header file for the ball instance
// Author		: Pizza Party - Aimee Constable, Chloe Cantwell, Joseph Maton, Nick Lacy
// Mail			: aimee.con6886@mediadesign.school.nz, chloe.can6956@mediadesign.school.nz, joseph.mat3620@mediadesign.school.nz, darcy.lac6935@mediadesign.school.nz
//

#pragma once

#if !defined(__BALL_H__)
#define __BALL_H__

// Local Includes
#include "entity.h"


class CSprite;

class CBall : public CEntity
{
    // Member Functions
public:
    CBall();
    virtual ~CBall();

    virtual bool Initialise(float _fPosX, float _fPosY, float _fVelocityX, float _fVelocityY);

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

    float GetVelocityX() const;
    float GetVelocityY() const;
    void SetVelocityX(float _fX);
    void SetVelocityY(float _fY);

    float GetRadius() const;

private:
    CBall(const CBall& _kr);

protected:
    float m_fVelocityX;
    float m_fVelocityY;


};


#endif    // __BALL_H__
