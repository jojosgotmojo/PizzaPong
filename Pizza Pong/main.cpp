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

//Library Includes
#include <windows.h>
#include <windowsx.h>

//Local Includes
#include "Game.h"
#include "Clock.h"
#include "utils.h"
#include "level.h"
#include "paddle.h"
#include "background.h"
#include "backbuffer.h"
#include "MainMenu.h"

#include "resource.h"

const int kiWidth = 1280;
const int kiHeight = 720;




#define WINDOW_CLASS_NAME L"BSENGGFRAMEWORK"

LRESULT CALLBACK WindowProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uiMsg)
	{
		case WM_MOUSEMOVE:
		{
			int iMouseX = LOWORD(_lParam);
			//CGame::GetInstance().GetLevel()->GetPaddle()->SetX(static_cast<float>(iMouseX));
			return (0);
		}
		break;
		case WM_DESTROY:
		{
			PostQuitMessage(0);

			return(0);
		}
		break;

		default:break;
	}

	return (DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam));
}

HWND CreateAndRegisterWindow(HINSTANCE _hInstance, int _iWidth, int _iHeight, const wchar_t* _pcTitle)
{
	WNDCLASSEX winclass;

	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = static_cast<HBRUSH> (GetStockObject(NULL_BRUSH));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&winclass))
	{
		// Failed to register.
		return (0);
	}

	HWND hwnd;
	hwnd = CreateWindowEx(NULL, WINDOW_CLASS_NAME, _pcTitle, WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, _iWidth, _iHeight, NULL, NULL, _hInstance, NULL);

	if (!hwnd)
	{
		// Failed to create.
		return (0);
	}

	return (hwnd);
}

enum GameState
{
	MainMenu,
	QuickGame,
	Tournament,
	Credits
};

GameState currentState = MainMenu;

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdline, int _iCmdshow)
{
	MSG msg;
	RECT _rect;
	ZeroMemory(&msg, sizeof(MSG));
	HWND hwnd1;
	

	switch (currentState)
	{
		case MainMenu:
		{
			hwnd1 = CreateAndRegisterWindow(_hInstance, kiWidth, kiHeight, L"Pizza Pong");
			
			CMainMenu& rMain = CMainMenu::GetInstance();
			VALIDATE(rMain.Initialise(IDB_MAINTEST, IDB_MAINTEST, _hInstance, hwnd1, kiWidth, kiHeight));
			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					rMain.Draw();
				}
			}
			
			return (static_cast<int>(msg.wParam));
		}
		case QuickGame:
		{
			hwnd1 = CreateAndRegisterWindow(_hInstance, kiWidth, kiHeight, L"Pizza Pong");
			CGame& rGame = CGame::GetInstance();

			GetClientRect(hwnd1, &_rect);

			//if (!rGame.Initialise(_hInstance, hwnd, kiWidth, kiHeight))
			if (!rGame.Initialise(_hInstance, hwnd1, _rect.right, _rect.bottom))
			{
				// Failed
				return (0);
			}

			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					rGame.ExecuteOneFrame();
				}
			}

			CGame::DestroyInstance();

			return (static_cast<int>(msg.wParam));
		}
		default:
		{
			return 0;
		}
	}
}
