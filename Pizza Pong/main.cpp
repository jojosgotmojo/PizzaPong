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
#include <time.h>

//Local Includes
#include "Game.h"
#include "utils.h"
#include "level.h"
#include "paddle.h"
#include "background.h"
#include "backbuffer.h"
#include "MainMenu.h"
#include "resource.h"
#include "sounds.h"
#include "backgroundmusic.h"

#include "Dependencies\FMOD\fmod.hpp"


//#include <vld.h>   //*VISUAL LEAK DETECTOR*

//Global variables
HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

const int g_kiWidth = 1280;
const int g_kiHeight = 720;
POINT g_iStart;
#define WINDOW_CLASS_NAME L"Pizza Pong"
HFONT g_Font = CreateFont(18, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
	CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Courier New"));

CSounds SoundEffect; //all sound effects
CBGMUSIC Back; //background music


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

GameState g_currentState = MainMenu;

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
			SelectFont(GetDC(_hWnd), g_Font);
		}
		
		case WM_LBUTTONDOWN:
		{
			g_iStart.x = LOWORD(_lParam);
			g_iStart.y = HIWORD(_lParam);

			//Main Menu Buttons
			if (g_currentState == MainMenu)
			{
				//quick game button
				if ((g_iStart.x > 392) && (g_iStart.x < 840) && (g_iStart.y > 198) && (g_iStart.y < 289))
				{
					g_currentState = QuickGame;
				}

				//tournament mode button
				else if ((g_iStart.x > 316) && (g_iStart.x < 927) && (g_iStart.y > 296) && (g_iStart.y < 380))
				{
					g_currentState = Tournament;
				}

				//Credits button
				else if ((g_iStart.x > 480) && (g_iStart.x < 742) && (g_iStart.y > 392) && (g_iStart.y < 477))
				{
					g_currentState = Credits;
				}

				//Instructions button
				else if ((g_iStart.x > 428) && (g_iStart.x < 827) && (g_iStart.y > 488) && (g_iStart.y < 555))
				{
					g_currentState = Instructions;
				}

				//quit button
				else if ((g_iStart.x > 540) && (g_iStart.x < 692) && (g_iStart.y > 571) && (g_iStart.y < 642))
				{
					g_currentState = QuitGame;
				}

			}
			else if (g_currentState == Credits)
			{
				//back button
				if ((g_iStart.x > 923) && (g_iStart.x < 1231) && (g_iStart.y > 603) && (g_iStart.y < 687))
				{
					g_currentState = MainMenu;
				}
			}
			else if (g_currentState == Instructions)
			{
				//main menu button
				if ((g_iStart.x > 895) && (g_iStart.x < 1215) && (g_iStart.y > 585) && (g_iStart.y < 677))
				{
					g_currentState = MainMenu;
				}
				//next button
				if ((g_iStart.x > 604) && (g_iStart.x < 858) && (g_iStart.y > 579) && (g_iStart.y < 666))
				{
					g_currentState = Instructions2;
				}
			}
			else if (g_currentState == Instructions2)
			{
				//main menu button
				if ((g_iStart.x > 895) && (g_iStart.x < 1215) && (g_iStart.y > 585) && (g_iStart.y < 677))
				{
					g_currentState = MainMenu;
				}
				//back button
				if ((g_iStart.x > 604) && (g_iStart.x < 858) && (g_iStart.y > 579) && (g_iStart.y < 666))
				{
					g_currentState = Instructions;
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
			g_currentState = QuitGame;
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

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdline, int _iCmdshow)
{
	Back.PlaySoundQ();  //Plays Background Music 


	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	HWND hwnd1;
	RECT _rect;
	srand(time(NULL));
	
	hwnd1 = CreateAndRegisterWindow(_hInstance, g_kiWidth, g_kiHeight, L"Pizza Pong");
	ShowCursor(true);


	while (g_currentState != QuitGame)
	{
		
		switch (g_currentState)
		{

		case MainMenu:
		{
			CMainMenu* rMain = CMainMenu::GetInstance();
			VALIDATE(rMain->Initialise(IDB_MAINTEST, IDB_MAINTEST, _hInstance, hwnd1, g_kiWidth, g_kiHeight));
			ShowCursor(true);
			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					rMain->Draw();
				}
				if (g_currentState != MainMenu)
				{
					delete rMain;
					rMain = 0;
					break;
				}
			}
				
			break;
		}
		case QuickGame:
		{
			
			CGame* rGame = CGame::GetInstance(false);
			GetClientRect(hwnd1, &_rect);

			if (!rGame->Initialise(_hInstance, hwnd1, _rect.right, _rect.bottom, SoundEffect))
			{
				// Failed
				return (0);
			}
			ShowCursor(false);

			while (msg.message != WM_QUIT)
			{
				if (rGame->GetGameState() == true)
				{
					g_currentState = MainMenu;
					delete rGame;
					rGame = 0;
					break;
				}

				if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					rGame->ExecuteOneFrame();
				}
			}
			break;
		}
		case Tournament:
		{
		
			CGame* rGame = CGame::GetInstance(true);
			GetClientRect(hwnd1, &_rect);

			if (!rGame->Initialise(_hInstance, hwnd1, _rect.right, _rect.bottom, SoundEffect))
			{
				// Failed
				return (0);
			}
			ShowCursor(false);
			while (msg.message != WM_QUIT)
			{
				if (rGame->GetGameState() == true)
				{
					g_currentState = MainMenu;
					delete rGame;
					rGame = 0;
					break;
				}

				if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					rGame->ExecuteOneFrame();
				}
			}
			break;
		}
		case Credits:
		{
			
			CMainMenu* rMain = CMainMenu::GetInstance();
			VALIDATE(rMain->Initialise(IDB_CREDITS, IDB_CREDITS, _hInstance, hwnd1, g_kiWidth, g_kiHeight));
			ShowCursor(true);
			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					rMain->Draw();
				}
				if (g_currentState != Credits)
				{
					delete rMain;
					rMain = 0;
					break;
				}
			}
			break;
		}
		case Instructions:
		{
			
			CMainMenu* rMain = CMainMenu::GetInstance();
			VALIDATE(rMain->Initialise(IDB_INSTRUCT, IDB_INSTRUCT, _hInstance, hwnd1, g_kiWidth, g_kiHeight));
			ShowCursor(true);
			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					rMain->Draw();
				}
				if (g_currentState != Credits)
				{
					delete rMain;
					rMain = 0;
					break;
				}
			}
			break;
		}

		case Instructions2:
		{
			
			CMainMenu* rMain = CMainMenu::GetInstance();
			VALIDATE(rMain->Initialise(IDB_INSTRUCTIONS2, IDB_INSTRUCTIONS2, _hInstance, hwnd1, g_kiWidth, g_kiHeight));
			ShowCursor(true);
			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					rMain->Draw();
				}
				if (g_currentState != Credits)
				{
					delete rMain;
					rMain = 0;

					break;
				}
			}
			break;
		}
		case QuitGame:
		{
			return(static_cast<int>(msg.wParam));
			break;
		}
		default:
		{
			g_currentState = g_currentState;
			break;
		}
		}
	}
	return 0;
}
