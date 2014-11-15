//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: game.h
// Description	: Header file for game class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#pragma once

#if !defined(__GAME_H__)
#define __GAME_H__

// Library Includes
#include <windows.h>
#include <vector>

// Local Includes
#include "clock.h"

// Types
// Constants

// Prototypes
class CBackBuffer;
class CLevel;
class CGame
{
// Member Functions
public:
	// Destructor
	~CGame();

	bool Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight);
	void Draw();
	void Process(float _fDeltaTick);
	void ExecuteOneFrame();
	CBackBuffer* GetBackBuffer();
	HINSTANCE GetAppInstance();
	HWND GetWindow();

	// Singleton Methods
	static CGame& GetInstance();
	static void DestroyInstance();

protected:
private:
	// Singleton constructors
	CGame();
	CGame(const CGame& _kr);
	// Operator overload
	CGame& operator= (const CGame& _kr);

// Member Variables
public:
protected:
	CClock* m_pClock;
	CBackBuffer* m_pBackBuffer;
	CLevel* m_pLevel;

	//Application data
	HINSTANCE m_hApplicationInstance;
	HWND m_hMainWindow;

	// Singleton Instance
	static CGame* s_pGame;
private:
};
#endif // __GAME_H__