//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: game.cpp
// Description	: Implementation file for game class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

// Library Includes
#include <string>
#include <sstream>
#include <fstream>
#include <map>

// Local Includes
#include "Clock.h"
#include "BackBuffer.h"
#include "utils.h"
#include "Level.h"
#include "resource.h"

// This Include
#include "Game.h"

// Static Variables
CGame* CGame::s_pGame = 0;

// Static Function Prototypes
// Implementation
/***********************

 * CGame: Constructor
 * @author:

 ********************/
CGame::CGame()
	: m_pClock(0), 
		m_hApplicationInstance(0), // Default to 0
		m_hMainWindow(0), 
		m_pBackBuffer(0)
{
}

/***********************

 * ~CGame: Deconstructor
 * @author:

 ********************/
CGame::~CGame()
{
	// Delete backbuffer, clock and level
	delete m_pBackBuffer;
	m_pBackBuffer = 0;
	delete m_pClock;
	m_pClock = 0;
	delete m_pLevel;
	m_pLevel = 0;
}

/***********************

 * Initialise: Initialise the level
 * @author:
 * @parameter: HINSTANCE _hInstance, instance
 *				HWND _hWnd, window
 *				int _iWidth, width
 *				int _iHeight height
 * @return: bool

 ********************/
bool CGame::Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight)
{
	// Initialise instance
	m_hApplicationInstance = _hInstance;
	m_hMainWindow = _hWnd;

	// Create, validate & initialise clock
	m_pClock = new CClock();
	VALIDATE(m_pClock ->Initialise());
	// Process clock
	m_pClock->Process();

	// Create, validate & initialise backbuffer
	m_pBackBuffer = new CBackBuffer();
	VALIDATE(m_pBackBuffer->Initialise(_hWnd, _iWidth, _iHeight));

	// Create, validate & initialise level
	m_pLevel = new CLevel();
	VALIDATE(m_pLevel->Initialise(_iWidth, _iHeight));

	// Show cursor
	ShowCursor(true);
	return (true);
}

/***********************

 * Draw: Draw the level
 * @author:

 ********************/
void CGame::Draw()
{
	// Clear backbuffer
	m_pBackBuffer->Clear();
	// Draw level
	m_pLevel->Draw();
	// Ste buffer to present
	m_pBackBuffer->Present();
}

/***********************

 * Process: Process the level
 * @author:
 * @parameter: float _fDeltaTick - delta time

 ********************/
void CGame::Process(float _fDeltaTick)
{
	// Process all the game’s logic here.
	m_pLevel->Process(_fDeltaTick);
}

/***********************

 * ExecuteOneFrame: Execute One Frame of the level
 * @author:

 ********************/
void CGame::ExecuteOneFrame()
{
	// get delta
	float fDT = m_pClock->GetDeltaTick();
	// Process
	Process(fDT);
	// Draw
	Draw();
	// Process clock
	m_pClock->Process();
	// Sleeps
	Sleep(g_iGameSpeed);
}

/***********************

 * GetInstance: Get the game instance
 * @author:

 ********************/
CGame& CGame::GetInstance()
{
	// If it doesnt exist
	if (s_pGame == 0)
	{
		// Make a new one
		s_pGame = new CGame();
	}
	return (*s_pGame);
}

/***********************

 * DestroyInstance: Destroy the game instance
 * @author:

 ********************/
void CGame::DestroyInstance()
{
	delete s_pGame;
	s_pGame = 0;
}

/***********************

 * GetBackBuffer: Get the Back Buffer
 * @author:

 ********************/
CBackBuffer* CGame::GetBackBuffer()
{
	// Return member variable
	return (m_pBackBuffer);
}

/***********************

 * GetAppInstance: Get the instance
 * @author:

 ********************/
HINSTANCE CGame::GetAppInstance()
{
	// Return member variable
	return (m_hApplicationInstance);
}

/***********************

 * GetWindow: Get the window
 * @author:

 ********************/
HWND CGame::GetWindow()
{
	return (m_hMainWindow);
}

/***********************

 * SetMouseCoords: Set mouse coordinates for game
 * @author: 
 * @parameters: int _x, x pos
 *				int _y, y pos

 ********************/
void CGame::SetMouseCoords(int _iX, int _iY)
{
	// Call level set mouse using xy
	m_pLevel->SetMouseCoords( _iX,_iY );
}

/***********************

 * GetLevel: Get level for game
 * @author: 
 * @return: CLevel*

 ********************/
CLevel* CGame::GetLevel()
{
	return( m_pLevel );
}

/***********************

 * GameOver: Post a quit message
 * @author: 
 * @return: void

 ********************/
void CGame::GameOver()
{
	//Show score dialog box
	//
	InputHighScore();
	DisplayHighScore();
	
	PostQuitMessage(0);
}

/*******************

 * SetDlgProperties: Set the dialog values
 * @author: 
 * @parameters: int _iInvSpeed, speed of invaders
 *				int _iBulletSpeed, speed of bullet

 ********************/
void CGame::SetDlgProperties( int _iInvSpeed, int _iBulletSpeed )
{
	m_pLevel->SetBulletSpeed( _iBulletSpeed );
	m_pLevel->SetInvaderSpeed( _iInvSpeed );
}

/*******************

 * DisplayHighScore: Show the current high score list
 * @author: 
 * @return: void

 ********************/
void CGame::DisplayHighScore()
{
	std::string sInput;
	std::string sName;
	int iScore;
	
	m_mHighScores.clear();

	std::ifstream ifs;
	ifs.open("HighScores.txt");
	if(!ifs.is_open() || !ifs.good())
	{
		MessageBox(0, "No High Scores could be found", "Space Invaders", MB_OK);
	}
	while(std::getline(ifs, sInput))
	{

		size_t pos = sInput.find(":",0);
		sName = sInput.substr(0, pos);
		sInput.erase(0, pos + 1);
		iScore = std::stoi(sInput);
		// do something with token
		m_mHighScores.insert(std::pair<int, std::string>(iScore, sName));

	}
	DialogBox(GetAppInstance(), MAKEINTRESOURCE( IDD_DIALOG3 ), GetWindow(), (DLGPROC)HighScoreDialogProc);
}

/*******************

 * InputHighScore: Prompt the user to input their name to store their score
 * @author: 
 * @return: void

 ********************/
void CGame::InputHighScore()
{
	DialogBox( GetAppInstance(), MAKEINTRESOURCE( IDD_DIALOG2 ), GetWindow(), (DLGPROC)InputDialogProc);
}


BOOL CALLBACK CGame::InputDialogProc( HWND _hDlg,UINT _msg,WPARAM _wparam,LPARAM _lparam )
{
	int _iScore = CGame::GetInstance().GetLevel()->GetScore();
	switch(_msg)
	{
	case WM_INITDIALOG:
		{
			int _iScore = CGame::GetInstance().GetLevel()->GetScore();
			SetDlgItemText(_hDlg, IDC_SCORETEXT, ToString(_iScore).c_str());
			return TRUE;
		}
		break;
	case WM_CLOSE:
		{
			EndDialog( _hDlg, 1 );
			return( true );
		}
		break;

	case WM_COMMAND:
		{
			switch(_wparam)
			{
			case IDOK:
				{
					//Insert name into high scores
					char _cName[256];
					if(!GetDlgItemText(_hDlg, IDC_NAMEINPUT, _cName, 256))
					{
						MessageBox(0, "Please enter a name", "Space Invaders", MB_OK);
						return( false );
					}
					std::ofstream out;
					out.open("HighScores.txt", std::ios::app);
					out << '\n' + ToString(_cName) + ':' + ToString(_iScore);
					out.close();
					EndDialog( _hDlg, 1 );
					return( true );
				}
				break;
			}

			return( true );
		}
		break;
	}
	return FALSE;
}

BOOL CALLBACK CGame::HighScoreDialogProc( HWND _hDlg,UINT _msg,WPARAM _wparam,LPARAM _lparam )
{
	switch(_msg)
	{
	case WM_INITDIALOG:
		{
			std::string sInput;
			std::multimap<int, std::string>::iterator it;
			for (it = CGame::GetInstance().m_mHighScores.begin(); it != CGame::GetInstance().m_mHighScores.end(); ++it)
			{
				sInput = ToString((*it).first) + " - " + ToString((*it).second);
				SendDlgItemMessage(_hDlg, IDC_LIST1, LB_INSERTSTRING, 0, (LPARAM)sInput.c_str());  
			 }
			return TRUE;
		}
		break;
	case WM_CLOSE:
		{
			EndDialog( _hDlg, 1 );
			return( true );
		}
		break;
	case WM_COMMAND:
		{
			switch(_wparam)
			{
			case IDOK:
				{
					EndDialog( _hDlg, 1 );
					return true;
				}
				break;
			}
			return ( true );
		}
		break;
	}
	return FALSE;
}