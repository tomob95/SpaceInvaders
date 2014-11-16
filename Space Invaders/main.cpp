//Library Includes
#include <windows.h>
#include <windowsx.h>
//Local Includes
#include "Game.h"
#include "level.h"
#include "Clock.h"
#include "utils.h"
#define WINDOW_CLASS_NAME L"Space Invaders"


LRESULT CALLBACK WindowProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uiMsg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return(0);
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
				CGame::GetInstance().GetLevel()->CreateBullet( 1, _iMouseX, 400 );
		}
		break;

		default:break;
	}

	return (DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam));
}

HWND CreateAndRegisterWindow(HINSTANCE _hInstance, int _iWidth, int _iHeight, LPCWSTR _pcTitle)
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

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdline, int _iCmdshow)
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	const int kiWidth = 835;
	const int kiHeight = 800;
	HWND hwnd = CreateAndRegisterWindow(_hInstance, kiWidth, kiHeight, L"Space Invaders");
	CGame& rGame = CGame::GetInstance();



	if (!rGame.Initialise(_hInstance, hwnd, kiWidth, kiHeight))
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