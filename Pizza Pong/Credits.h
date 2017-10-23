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

#if !defined(__Credits_H__)
#define __Credits_H__

// Library Includes
#include "windows.h"
#include "backbuffer.h"

// Prototypes
class CCredits
{
	// Member Functions
public:
	CCredits();
	~CCredits();

	bool Initialise(int _iResourceID, int _iMaskResourceID, HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight);

	void Draw();

	int GetWidth() const;
	int GetHeight() const;

	int GetX() const;
	int GetY() const;
	void SetX(int _i);
	void SetY(int _i);

	CBackBuffer* GetBackBuffer();
	static CCredits& GetInstance();
	static void DestroyInstance();

	void TranslateRelative(int _iX, int _iY);
	void TranslateAbsolute(int _iX, int _iY);

protected:


private:
	CCredits(const CCredits& _kr);
	
public:

protected:

	HWND hWnd;

	int m_iX;
	int m_iY;

	HBITMAP m_hCredits;
	HBITMAP m_hMask;

	BITMAP m_bitmapCredits;
	BITMAP m_bitmapMask;

	static HDC s_hSharedCreditsDC;
	static int s_iRefCount;

	static CBackBuffer* m_pBackBuffer;

	static CCredits* s_pMain;
private:

};

#endif    // __Credits_H__
