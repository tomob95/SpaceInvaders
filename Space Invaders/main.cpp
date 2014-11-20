//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: main.cpp
// Description	: Implementation file for main class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

//Library Includes
#include <windows.h>
#include <windowsx.h>
#include <time.h>

//Local Includes
#include "Game.h"
#include "level.h"
#include "Clock.h"
#include "utils.h"
#include "resource.h"

#define WINDOW_CLASS_NAME L"Space Invaders"

// Global variables
HINSTANCE g_hInstance;

/***********************

 * SettingsDlgProc: Function for the Dialog Box
 * @author: Kelsey Scheurich
 * @parameter: HWND - dialog handler
 *			   UINT - message
 *			   WPARAM - wparam
 *			   LPARAM - lapram
 * @return: BOOL

 ********************/
BOOL CALLBACK SettingsDialogProc( HWND _hDlg,
								UINT _msg,
								WPARAM _wparam,
								LPARAM _lparam )
{
	// Switch the message from the dialog box
	switch( _msg )
	{
		// Initialisation
	case WM_INITDIALOG:
		{
			// Initialise input text boxes
			SetDlgItemInt( _hDlg, IDC_EDIT1, 0, 1 );
			SetDlgItemInt( _hDlg, IDC_EDIT2, 0, 1 );
			return( true );
		}
		break;

		// If user clicks close
	case WM_CLOSE:
		{
			EndDialog( _hDlg, 1 );
			return( true );
		}
		break;

		// When a command is sent from the dialog box
	case WM_COMMAND:
		{
			// Switch on the word parameter, use loword to get last 16 bits ( instruction )
			switch( LOWORD( _wparam ) )
			{
			case IDOK:
				{ 
					// Get invader speed & bullet speed
					int iInvaderSpeed = GetDlgItemInt( _hDlg, IDC_EDIT1, 0, 1 );
					int iBulletSpeed = GetDlgItemInt( _hDlg, IDC_EDIT2, 0, 1 );

					// Validate input
					if( iInvaderSpeed > 0 && iBulletSpeed > 0 )
					{
						// If valid, process into game
						CGame::GetInstance().SetDlgProperties( iInvaderSpeed, iBulletSpeed );
					}
					else
					{
						// Else invalid, show message box
						MessageBox( _hDlg, L"Please enter a number greater than 0!", L"Invalid input", 0 );
						return( true );
					}

					// End dialog box
					EndDialog( _hDlg, 1 );
					return( true );
				}
				break;

			case IDCANCEL:
				{
					EndDialog( _hDlg, 1 );
					return( true );
				}
				break;

				default: break;

			} // End switch
		}
		break;

	default: break;

	} // End switch

	return( false );

}

/***********************

 * WindowProc: Main message handler
 * @author:
 * @parameter: HWND _hWnd, window handler
 *				UINT _uiMsg, message
 *				WPARAM _wParam, wparam
 *				LPARAM _lParam, lparam
 * @return: LRESULT CALLBACK

 ********************/
LRESULT CALLBACK WindowProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
{
	// Switch message
	switch (_uiMsg)
	{
		// If user closes
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return(0);
		}
		break;

		case WM_KEYDOWN:
		{
			switch(_wParam)
			{
			case VK_ESCAPE:
				{
					PostQuitMessage(0);
				}
			case VK_F2:
				{
					//CGame::GetInstance().RestartGame();
				}
				break;
			case VK_F1:
				{
					DialogBox( g_hInstance, MAKEINTRESOURCE( IDD_SETTINGS_DLG ), _hWnd, SettingsDialogProc );
					//CreateDialog( g_hInstance, MAKEINTRESOURCE( IDD_SETTINGS_DLG ), _hWnd, SettingsDialogProc )
				}
				break;
			}
		}
		break;

		// When user moves mouse
		case WM_MOUSEMOVE:
		{
			// Get instance, set x y pos
			CGame::GetInstance().SetMouseCoords( LOWORD( _lParam ), HIWORD( _lParam ) );
		}
		break;

		// When user clicks left mouse button
		case WM_LBUTTONDOWN:
		{
			// Check if user bullet exists
				// Get mouse coords
				// Set mouse coords
				int _iMouseX = LOWORD( _lParam ); 
				int _iMouseY = HIWORD( _lParam );
				CGame::GetInstance().SetMouseCoords( _iMouseX, _iMouseY );
				// Create new bullet
				CGame::GetInstance().GetLevel()->CreateBullet( 0, _iMouseX, kiYPos );
		}
		break;

		default:break;
	}

	return (DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam));
}

/***********************

 * CreateAndRegisterWindow: Create and register the window
 * @author:
 * @parameter: HINSTANCE _hInstance, instance
 *				int _iWidth, width
 *				int _iHeight, height
 *				LPCWSTR _pcTitle, title
 * @return: HWND

 ********************/
HWND CreateAndRegisterWindow(HINSTANCE _hInstance, int _iWidth, int _iHeight, LPCWSTR _pcTitle)
{
	// Initialise
	WNDCLASSEX winclass;
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&winclass))
	{
		// Failed to register.
		return (0);
	}
	HWND hwnd;
	hwnd = CreateWindowEx(	NULL,
							WINDOW_CLASS_NAME,
							_pcTitle,
							WS_BORDER | WS_SYSMENU | WS_VISIBLE,
							CW_USEDEFAULT, CW_USEDEFAULT,
							_iWidth, _iHeight,
							NULL,
							NULL,
							_hInstance,
							NULL);
	if (!hwnd)
	{
		// Failed to create.
		return (0);
	}
	return (hwnd);
}

/***********************

 * WinMain: Main implementation of the class
 * @author:
 * @parameter: HINSTANCE _hInstance, instance
 *				HINSTANCE _hPrevInstance, previous instance
 *				LPSTR _lpCmdline, cmd line
 *				int _iCmdshow, cmd show
 * @return: HWND

 ********************/
int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdline, int _iCmdshow)
{
	// Initialise msg
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	srand(time(NULL));

	g_hInstance = _hInstance;

	// Initialise width & height
	const int kiWidth = 835;
	const int kiHeight = 800;

	// Create window
	HWND hwnd = CreateAndRegisterWindow(_hInstance, kiWidth, kiHeight, L"Space Invaders");
	// Create game
	CGame& rGame = CGame::GetInstance();

	// If game failed to initialise
	if (!rGame.Initialise(_hInstance, hwnd, kiWidth, kiHeight))
	{
		// Failed
		return (0);
	}

	// Main event loops
	// While the user has not quite
	while (msg.message != WM_QUIT)
	{
		// Do message things
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// Otherwise play the game
		else
		{
			rGame.ExecuteOneFrame();
		}
	}

	// Destory the game
	CGame::DestroyInstance();

	return (static_cast<int>(msg.wParam));
}