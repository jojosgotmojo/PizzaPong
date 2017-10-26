//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: MainMenu.cpp
// Description	: Menu windows initialisation
// Author		: Pizza Party - Aimee Constable, Chloe Cantwell, Joseph Maton, Nick Lacy
// Mail			: aimee.con6886@mediadesign.school.nz, chloe.can6956@mediadesign.school.nz, joseph.mat3620@mediadesign.school.nz, darcy.lac6935@mediadesign.school.nz
//

#include "Game.h"
#include "BackBuffer.h"
#include "utils.h"
#include "resource.h"

#include "MainMenu.h"


HDC CMainMenu::s_hSharedMainMenuDC = 0;
int CMainMenu::s_iRefCount = 0;
CMainMenu* CMainMenu::s_pMain = 0;
CBackBuffer* CMainMenu::m_pBackBuffer = 0;

CMainMenu::CMainMenu()
	: m_iX(0)
	, m_iY(0)
{
	++s_iRefCount;
}

CMainMenu::~CMainMenu()
{
	DeleteObject(m_hMainMenu);
	DeleteObject(m_hMask);


	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	--s_iRefCount;

	if (s_iRefCount == 0)
	{
		DeleteDC(s_hSharedMainMenuDC);
		s_hSharedMainMenuDC = 0;
	}
	s_pMain = 0;
}

CBackBuffer* CMainMenu::GetBackBuffer()
{
	return (m_pBackBuffer);
}

bool CMainMenu::Initialise(int _iMainMenuResourceID, int _iMaskResourceID, HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight)
{
	HINSTANCE hInstance = _hInstance;
	hWnd = _hWnd;

	m_pBackBuffer = new CBackBuffer();
	VALIDATE(m_pBackBuffer->Initialise(hWnd, _iWidth, _iHeight));

	if (!s_hSharedMainMenuDC)
	{
		s_hSharedMainMenuDC = CreateCompatibleDC(NULL);
	}

	m_hMainMenu = LoadBitmap(hInstance, MAKEINTRESOURCE(_iMainMenuResourceID));
	VALIDATE(m_hMainMenu);
	m_hMask = LoadBitmap(hInstance, MAKEINTRESOURCE(_iMaskResourceID));
	VALIDATE(m_hMask);

	GetObject(m_hMainMenu, sizeof(BITMAP), &m_bitmapMainMenu);
	GetObject(m_hMask, sizeof(BITMAP), &m_bitmapMask);

	return (true);
}

CMainMenu* CMainMenu::GetInstance()
{
	if (s_pMain == 0)
	{
		s_pMain = new CMainMenu();
	}

	return (s_pMain);
}

void CMainMenu::Draw()
{
	m_pBackBuffer->Clear();

	int iW = GetWidth();
	int iH = GetHeight();

	int iX = m_iX;
	int iY = m_iY;

	HDC hWindowDC = ::GetDC(hWnd);

	HDC hDC = CreateCompatibleDC(hWindowDC);

	CBackBuffer* pBackBuffer = CMainMenu::GetInstance()->GetBackBuffer();

	HGDIOBJ hOldObj = SelectObject(s_hSharedMainMenuDC, m_hMask);

	BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedMainMenuDC, 0, 0, SRCAND);

	SelectObject(s_hSharedMainMenuDC, m_hMainMenu);

	BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedMainMenuDC, 0, 0, SRCPAINT);

	SelectObject(s_hSharedMainMenuDC, hOldObj);

	m_pBackBuffer->Present();
}

int CMainMenu::GetWidth() const
{
	RECT _rect;
	GetClientRect(hWnd, &_rect);
	return (_rect.right);
}

int CMainMenu::GetHeight() const
{
	RECT _rect;
	GetClientRect(hWnd, &_rect);
	return (_rect.bottom);
}

int CMainMenu::GetX() const
{
	return (m_iX);
}

int CMainMenu::GetY() const
{
	return (m_iY);
}

void CMainMenu::SetX(int _i)
{
	m_iX = _i;
}

void CMainMenu::SetY(int _i)
{
	m_iY = _i;
}

void CMainMenu::TranslateRelative(int _iX, int _iY)
{
	m_iX += _iX;
	m_iY += _iY;
}

void CMainMenu::TranslateAbsolute(int _iX, int _iY)
{
	m_iX = _iX;
	m_iY = _iY;
}
