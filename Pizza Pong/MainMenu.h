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

#if !defined(__MainMenu_H__)
#define __MainMenu_H__

// Library Includes
#include "windows.h"
#include "backbuffer.h"

// Local Includes

// Types

// Constants

// Prototypes
class CMainMenu
{
	// Member Functions
public:
	CMainMenu();
	~CMainMenu();

	bool Initialise(int _iResourceID, int _iMaskResourceID, HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight);

	void Draw();
	void Process(float _fDeltaTick);

	int GetWidth() const;
	int GetHeight() const;

	int GetX() const;
	int GetY() const;
	void SetX(int _i);
	void SetY(int _i);

	CBackBuffer* GetBackBuffer();
	static CMainMenu& GetInstance();

	void TranslateRelative(int _iX, int _iY);
	void TranslateAbsolute(int _iX, int _iY);

protected:


private:
	CMainMenu(const CMainMenu& _kr);
	CBackBuffer* m_pBackBuffer;

	// Member Variables
public:

protected:
	//Center handle

	HWND hWnd;

	int m_iX;
	int m_iY;

	HBITMAP m_hMainMenu;
	HBITMAP m_hMask;

	BITMAP m_bitmapMainMenu;
	BITMAP m_bitmapMask;

	static HDC s_hSharedMainMenuDC;
	static int s_iRefCount;

	static CMainMenu* s_pMain;

private:

};

#endif    // __MainMenu_H__
