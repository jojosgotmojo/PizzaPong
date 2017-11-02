//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: backbuffer.h
// Description	: Header file for backbuffer
// Author		: Pizza Party - Aimee Constable, Chloe Cantwell, Joseph Maton, Nick Lacy
// Mail			: aimee.con6886@mediadesign.school.nz, chloe.can6956@mediadesign.school.nz, joseph.mat3620@mediadesign.school.nz, darcy.lac6935@mediadesign.school.nz
//

#pragma once

#if !defined(__BACKBUFFER_H__)
#define __BACKBUFFER_H__

// Library Includes
#include <Windows.h>


class CBackBuffer
{
    // Member Functions
public:
    CBackBuffer();
    ~CBackBuffer();

    bool Initialise(HWND _hWnd, int _iWidth, int _iHeight);

    HDC GetBFDC() const;

    int GetHeight() const;
    int GetWidth() const;

    void Clear();
    void Present();


private:
    CBackBuffer(const CBackBuffer& _kr);

protected:
    HWND m_hWnd;
    HDC m_hDC;
    HBITMAP m_hSurface;
    HBITMAP m_hOldObject;
    int m_iWidth;
    int m_iHeight;

};

#endif    // __BACKBUFFER_H__

