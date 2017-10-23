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


#include "Game.h"
#include "BackBuffer.h"
#include "utils.h"
#include "resource.h"

#include "Credits.h"


HDC CCredits::s_hSharedCreditsDC = 0;
int CCredits::s_iRefCount = 0;
CCredits* CCredits::s_pMain = 0;
CBackBuffer* CCredits::m_pBackBuffer = 0;

CCredits::CCredits()
	: m_iX(0)
	, m_iY(0)
{
	++s_iRefCount;
}

CCredits::~CCredits()
{
	DeleteObject(m_hCredits);
	DeleteObject(m_hMask);

	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	--s_iRefCount;

	if (s_iRefCount == 0)
	{
		DeleteDC(s_hSharedCreditsDC);
		s_hSharedCreditsDC = 0;
	}
}

CBackBuffer* CCredits::GetBackBuffer()
{
	return (m_pBackBuffer);
}

bool CCredits::Initialise(int _iCreditsResourceID, int _iMaskResourceID, HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight)
{
	HINSTANCE hInstance = _hInstance;
	hWnd = _hWnd;

	m_pBackBuffer = new CBackBuffer();
	VALIDATE(m_pBackBuffer->Initialise(hWnd, _iWidth, _iHeight));

	if (!s_hSharedCreditsDC)
	{
		s_hSharedCreditsDC = CreateCompatibleDC(NULL);
	}

	m_hCredits = LoadBitmap(hInstance, MAKEINTRESOURCE(_iCreditsResourceID));
	VALIDATE(m_hCredits);
	m_hMask = LoadBitmap(hInstance, MAKEINTRESOURCE(_iMaskResourceID));
	VALIDATE(m_hMask);

	GetObject(m_hCredits, sizeof(BITMAP), &m_bitmapCredits);
	GetObject(m_hMask, sizeof(BITMAP), &m_bitmapMask);

	return (true);
}

CCredits& CCredits::GetInstance()
{
	if (s_pMain == 0)
	{
		s_pMain = new CCredits();
	}

	return (*s_pMain);
}

void CCredits::DestroyInstance()
{
	delete s_pMain;
	s_pMain = 0;

	delete m_pBackBuffer;
	m_pBackBuffer = 0;

}

void CCredits::Draw()
{
	m_pBackBuffer->Clear();

	int iW = GetWidth();
	int iH = GetHeight();

	int iX = m_iX;
	int iY = m_iY;

	HDC hWindowDC = ::GetDC(hWnd);

	HDC hDC = CreateCompatibleDC(hWindowDC);

	CBackBuffer* pBackBuffer = CCredits::GetInstance().GetBackBuffer();

	HGDIOBJ hOldObj = SelectObject(s_hSharedCreditsDC, m_hMask);

	BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedCreditsDC, 0, 0, SRCAND);

	SelectObject(s_hSharedCreditsDC, m_hCredits);

	BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedCreditsDC, 0, 0, SRCPAINT);

	SelectObject(s_hSharedCreditsDC, hOldObj);

	m_pBackBuffer->Present();
}

int CCredits::GetWidth() const
{
	RECT _rect;
	GetClientRect(hWnd, &_rect);
	return (_rect.right);
}

int CCredits::GetHeight() const
{
	RECT _rect;
	GetClientRect(hWnd, &_rect);
	return (_rect.bottom);
}

int CCredits::GetX() const
{
	return (m_iX);
}

int CCredits::GetY() const
{
	return (m_iY);
}

void CCredits::SetX(int _i)
{
	m_iX = _i;
}

void CCredits::SetY(int _i)
{
	m_iY = _i;
}

void CCredits::TranslateRelative(int _iX, int _iY)
{
	m_iX += _iX;
	m_iY += _iY;
}

void CCredits::TranslateAbsolute(int _iX, int _iY)
{
	m_iX = _iX;
	m_iY = _iY;
}
