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

// Local Includes
#include "Clock.h"
#include "BackBuffer.h"
#include "utils.h"
#include "Level.h"

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
	PostQuitMessage(0);
}

/*******************

 * SetDlgProperties: Set the dialog values
 * @author: 
 * @parameters: int _iInvSpeed, speed of invaders
 *				int _iBulletSpeed, speed of bullet

 ********************/
void CGame::SetDlgProperties( int _iInvSpeed, int _iBulletSpeed, int _iPlayerInv, int _iBulletPierce )
{
	m_pLevel->SetBulletSpeed( _iBulletSpeed );
	m_pLevel->SetInvaderSpeed( _iInvSpeed );
	m_pLevel->SetPlayerInvincible( _iPlayerInv );
	m_pLevel->SetBulletPierce( _iBulletPierce );
}

/*******************

 * SetDlgProperties: Set the dialog values
 * @author: 
 * @parameters: int _iInvSpeed, speed of invaders
 *				int _iBulletSpeed, speed of bullet

 ********************/
void CGame::GetDlgProperties()
{
	m_iInvSpeed = m_pLevel->GetInvaderSpeed();
	m_iBulletSpeed = m_pLevel->GetBulletSpeed();
	m_iPlyInvincible = m_pLevel->GetPlayerInvincible();
	m_iBulletPierce = m_pLevel->GetBulletPierce();
}