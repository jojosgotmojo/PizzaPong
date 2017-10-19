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
// Author		: Pizza Party - Aimee Constable, Chloe Cantwell, Joseph Maton, Nick Lacey
// Mail			: aimee.con6886@mediadesign.school.nz, chloe.can6956@mediadesign.school.nz, joseph.mat3620@mediadesign.school.nz, darcy.lac6935@mediadesign.school.nz
//

//Library Includes
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>

//Local Includes
#include "Game.h"
#include "Clock.h"
#include "utils.h"
#include "level.h"
#include "paddle.h"
#include "background.h"
#include "backbuffer.h"
#include "MainMenu.h"
#include <time.h>

//#include <vld.h>

#include "resource.h"

HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

const int kiWidth = 1280;
const int kiHeight = 720;
HDC hDC;
HFONT font = CreateFont(18, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
	CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Courier New"));

enum GameState
{
	MainMenu,
	QuickGame,
	Tournament,
	Credits,
	QuitGame,
	Instructions,
	Instructions2

};

GameState currentState = MainMenu;

POINT iStart;
#define WINDOW_CLASS_NAME L"BSENGGFRAMEWORK"
#define WINDOW_CLASS_NAME_2 L"Main Game Window"

LRESULT CALLBACK WindowProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uiMsg)
	{
	case WM_CHAR:
	{
		switch (_wParam)
		{
		case VK_ESCAPE:
		{
			SendMessage(_hWnd, WM_CLOSE, _wParam, _lParam);
			return (0);
		}
		default:break;
		}
	}
	break;

	case WM_CREATE:
	{
		SelectFont(hDC, font);

	}
	case WM_MOUSEMOVE:
	{
		int iMouseX = LOWORD(_lParam);

		return (0);
	}
	break;
	case WM_LBUTTONDOWN:
	{

		iStart.x = LOWORD(_lParam);
		iStart.y = HIWORD(_lParam);


		//Main Menu Buttons
		if (currentState == MainMenu)
		{
			//quick game button
			if ((iStart.x > 392) && (iStart.x < 840) && (iStart.y > 198) && (iStart.y < 289))
			{
				currentState = QuickGame;
			}

			//tournament mode button
			else if ((iStart.x > 316) && (iStart.x < 927) && (iStart.y > 296) && (iStart.y < 380))
			{
				currentState = Tournament;
			}

			//Credits button
			else if ((iStart.x > 480) && (iStart.x < 742) && (iStart.y > 392) && (iStart.y < 477))
			{
				currentState = Credits;
			}

			//Instructions button
			else if ((iStart.x > 428) && (iStart.x < 827) && (iStart.y > 488) && (iStart.y < 555))
			{
				currentState = Instructions;
			}

			//quit button
			else if ((iStart.x > 540) && (iStart.x < 692) && (iStart.y > 571) && (iStart.y < 642))
			{
				currentState = QuitGame;
			}

		}
		else if (currentState == Credits)
		{
			//back button
			if ((iStart.x > 923) && (iStart.x < 1231) && (iStart.y > 603) && (iStart.y < 687))
			{
				currentState = MainMenu;
			}
		}
		else if (currentState == Instructions)
		{
			//back button
			if ((iStart.x > 895) && (iStart.x < 1215) && (iStart.y > 585) && (iStart.y < 677))
			{
				currentState = MainMenu;
			}
			if ((iStart.x > 604) && (iStart.x < 858) && (iStart.y > 579) && (iStart.y < 666))
			{
				currentState = Instructions2;
			}
		}
		else if (currentState == Instructions2)
		{
			//back button
			if ((iStart.x > 895) && (iStart.x < 1215) && (iStart.y > 585) && (iStart.y < 677))
			{
				currentState = MainMenu;
			}
			if ((iStart.x > 604) && (iStart.x < 858) && (iStart.y > 579) && (iStart.y < 666))
			{
				currentState = Instructions;
			}
		}
			
	}
	break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);

		return(0);
	}
	break;
	case WM_CLOSE:
	{
		MessageBox(GetActiveWindow(), L"Do you want to exit the game?", L"Close", MB_YESNO);
		if (IDYES)
		{
			PostQuitMessage(0);
		}
		else
		{
			break;
		}
			

	}
	case WM_QUIT:
	{
		currentState = QuitGame;
		break;
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

//Testchange
int iTest = 0;

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdline, int _iCmdshow)
{
	PlaySound(TEXT("win.wav"), NULL, SND_ASYNC | SND_LOOP);

	MSG msg;
	RECT _rect;
	ZeroMemory(&msg, sizeof(MSG));
	HWND hwnd1;

	srand(time(NULL));
	
	hwnd1 = CreateAndRegisterWindow(_hInstance, kiWidth, kiHeight, L"Pizza Pong");

	while (currentState != QuitGame)
	{
		
		switch (currentState)
		{
		case MainMenu:
		{
			
			ShowCursor(true);
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
				if (currentState != MainMenu)
				{
					break;
				}
			}
			
			CMainMenu::DestroyInstance();

			
			break;
		}
		case QuickGame:
		{
			ShowCursor(false);
			CGame& rGame = CGame::GetInstance(false);

			GetClientRect(hwnd1, &_rect);

			//if (!rGame.Initialise(_hInstance, hwnd, kiWidth, kiHeight))
			if (!rGame.Initialise(_hInstance, hwnd1, _rect.right, _rect.bottom))
			{
				// Failed
				return (0);
			}

			while (msg.message != WM_QUIT)
			{
				if (rGame.GetGameState() == true)
				{
					currentState = MainMenu;
					break;
				}

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
			break;
		}
		case Tournament:
		{
			ShowCursor(false);
			CGame& rGame = CGame::GetInstance(true);

			GetClientRect(hwnd1, &_rect);

			//if (!rGame.Initialise(_hInstance, hwnd, kiWidth, kiHeight))
			if (!rGame.Initialise(_hInstance, hwnd1, _rect.right, _rect.bottom))
			{
				// Failed
				return (0);
			}

			while (msg.message != WM_QUIT)
			{
				if (rGame.GetGameState() == true)
				{
					currentState = MainMenu;
					break;
				}

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
			break;
		}
		case Credits:
		{
			ShowCursor(true);
			CMainMenu& rMain = CMainMenu::GetInstance();
			VALIDATE(rMain.Initialise(IDB_CREDITS, IDB_CREDITS, _hInstance, hwnd1, kiWidth, kiHeight));
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
				if (currentState != Credits)
				{
					break;
				}
			}

			CMainMenu::DestroyInstance();
			//return(static_cast<int>(msg.wParam));

			break;

		}
		case Instructions:
		{
			ShowCursor(true);
			CMainMenu& rMain = CMainMenu::GetInstance();
			VALIDATE(rMain.Initialise(IDB_INSTRUCT, IDB_INSTRUCT, _hInstance, hwnd1, kiWidth, kiHeight));
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
				if (currentState != Credits)
				{
					break;
				}
			}

			CMainMenu::DestroyInstance();
			//return(static_cast<int>(msg.wParam));

			break;

		}
		case Instructions2:
		{
			ShowCursor(true);
			CMainMenu& rMain = CMainMenu::GetInstance();
			VALIDATE(rMain.Initialise(IDB_INSTRUCTIONS2, IDB_INSTRUCTIONS2, _hInstance, hwnd1, kiWidth, kiHeight));
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
				if (currentState != Credits)
				{
					break;
				}
			}

			CMainMenu::DestroyInstance();
			//return(static_cast<int>(msg.wParam));

			break;

		}
		case QuitGame:
		{
			return(static_cast<int>(msg.wParam));
		}
		default:
		{
			return 0;
		}
		}
	}
}
