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
CGame::CGame():	m_pClock(0)
				, m_hApplicationInstance(0)
				, m_hMainWindow(0)
				, m_pBackBuffer(0)
{
}

CGame::~CGame()
{
	delete m_pBackBuffer;
	m_pBackBuffer = 0;
	delete m_pClock;
	m_pClock = 0;
	delete m_pLevel;
	m_pLevel = 0;
}

bool CGame::Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight)
{
	m_hApplicationInstance = _hInstance;
	m_hMainWindow = _hWnd;
	m_pClock = new CClock();
	VALIDATE(m_pClock ->Initialise());
	m_pClock->Process();
	m_pLevel = new CLevel();
	VALIDATE(m_pLevel->Initialise(_iWidth, _iHeight));
	m_pBackBuffer = new CBackBuffer();
	VALIDATE(m_pBackBuffer->Initialise(_hWnd, _iWidth, _iHeight));


	ShowCursor(true);
	return (true);
}

void CGame::Draw()
{
	m_pBackBuffer->Clear();
	m_pLevel->Draw();
	// Do all the game’s drawing here...

	m_pBackBuffer->Present();
}

void CGame::Process(float _fDeltaTick)
{
// Process all the game’s logic here.
	m_pLevel->Process(_fDeltaTick);
}

void CGame::ExecuteOneFrame()
{
	float fDT = m_pClock->GetDeltaTick();
	Process(fDT);
	Draw();
	m_pClock->Process();
	Sleep(1);
}

CGame& CGame::GetInstance()
{
	if (s_pGame == 0)
	{
		s_pGame = new CGame();
	}
	return (*s_pGame);
}

void CGame::DestroyInstance()
{
	delete s_pGame;
	s_pGame = 0;
}

CBackBuffer* CGame::GetBackBuffer()
{
	return (m_pBackBuffer);
}

HINSTANCE CGame::GetAppInstance()
{
	return (m_hApplicationInstance);
}

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