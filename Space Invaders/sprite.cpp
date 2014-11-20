//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: sprite.cpp
// Description	: Implementation file for sprite class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

// Local Includes
#include "resource.h"
#include "game.h"
#include "backbuffer.h"
#include "utils.h"

// This include
#include "Sprite.h"

// Static Variables
HDC CSprite::s_hSharedSpriteDC = 0;
int CSprite::s_iRefCount = 0;

// Implementation
/***********************

 * CSprite: Constructor
 * @author:

 ********************/
CSprite::CSprite()
	: m_iX(0), 
		m_iY(0)
{
	++s_iRefCount;
}

/***********************

 * ~CSprite: Deconstructor
 * @author:

 ********************/
CSprite::~CSprite()
{
	// Delete the sprie
	DeleteObject(m_hSprite);
	// Delete the mask
	DeleteObject(m_hMask);
	// Subtract from ref count
	--s_iRefCount;
	// If it reaches 0
	if (s_iRefCount == 0)
	{
		// Delete DC
		DeleteDC(s_hSharedSpriteDC);
		s_hSharedSpriteDC = 0;
	}
}

/***********************

 * Initialise: Initialise the sprite
 * @author:
 * @parameter: int _iSpriteResourceID, sprite id
 * @return: bool

 ********************/
bool CSprite::Initialise(int _iSpriteResourceID)
{
	// Get instance
	HINSTANCE hInstance = CGame::GetInstance().GetAppInstance();

	// If its not there
	if (!s_hSharedSpriteDC)
	{
		// Create sprite DC
		s_hSharedSpriteDC = CreateCompatibleDC(NULL);
	}

	// Load sprite
	m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(_iSpriteResourceID));

	//Crashes here
	VALIDATE(m_hSprite);
	GetObject(m_hSprite, sizeof(BITMAP), &m_bitmapSprite);
	return (true);
}

/***********************

 * Initialise: Initialise the sprite
 * @author:
 * @parameter: int _iSpriteResourceID, sprite id
 *             int _iMaskResourceID, masks id
 * @return: bool

 ********************/
bool CSprite::Initialise(int _iSpriteResourceID, int _iMaskResourceID)
{
	// Get instance
	HINSTANCE hInstance = CGame::GetInstance().GetAppInstance();

	// If not exist
	if (!s_hSharedSpriteDC)
	{
		// Create compatible bitmap
		s_hSharedSpriteDC = CreateCompatibleDC(NULL);
	}

	// Load bitmap
	m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(_iSpriteResourceID));
	// Validate
	VALIDATE(m_hSprite);
	// Load mask
	m_hMask = LoadBitmap(hInstance, MAKEINTRESOURCE(_iMaskResourceID));
	// Validate
	VALIDATE(m_hMask);
	// get sprites/mask
	GetObject(m_hSprite, sizeof(BITMAP), &m_bitmapSprite);
	GetObject(m_hMask, sizeof(BITMAP), &m_bitmapMask);

	return (true);
}

/***********************

 * Draw: Draw the sprite
 * @author:

 ********************/
void CSprite::Draw()
{
	// Get x, y, width, height
	int iW = GetWidth();
	int iH = GetHeight();
	int iX = m_iX - (iW / 2);
	int iY = m_iY - (iH / 2);

	// Get backbuffer
	CBackBuffer* pBackBuffer = CGame::GetInstance().GetBackBuffer();
	// Get sprite DC and masks
	HGDIOBJ hOldObj = SelectObject(s_hSharedSpriteDC, m_hMask);

	// If mask is alive
	if(m_hMask)
	{
		// Bitblt
		BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedSpriteDC, 0, 0, SRCAND);
	}
	// Select the sprite and the DC
	SelectObject(s_hSharedSpriteDC, m_hSprite);
	// Ooutput
	BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedSpriteDC, 0, 0, SRCPAINT);
	SelectObject(s_hSharedSpriteDC, hOldObj);
}

/***********************

 * Process: Process the sprite
 * @author:
 * @parameter: float _fDeltaTick - delta tick

 ********************/
void CSprite::Process(float _fDeltaTick)
{
}

/***********************

 * GetWidth: Get the width
 * @author:
 * @return: int

 ********************/
int CSprite::GetWidth() const
{
	// return sprite width
	return (m_bitmapSprite.bmWidth);
}

/***********************

 * GetHeight: Get the heights
 * @author:
 * @return: int

 ********************/
int CSprite::GetHeight() const
{
	// return sprite heights
	return (m_bitmapSprite.bmHeight);
}

/***********************

 * GetX: Get the x
 * @author:
 * @return: int

 ********************/
int CSprite::GetX() const
{
	return (m_iX);
}

/***********************

 * GetX: Get the x
 * @author:
 * @return: int

 ********************/
int CSprite::GetY() const
{
	// Return member variable
	return (m_iY);
}

/***********************

 * SetX: Set the x
 * @author:
 * parameter: int _i, 

 ********************/
void CSprite::SetX(int _i)
{
	// Set memeber variable
	m_iX = _i;	
}

/***********************

 * SetY: Set the y
 * @author:
 * parameter: int _i, 

 ********************/
void CSprite::SetY(int _i)
{
	// Set memeber variable
	m_iY = _i;
}

/***********************

 * TranslateRelative: Set the y
 * @author:
 * parameter: int _i, 

 ********************/
void CSprite::TranslateRelative(int _iX, int _iY)
{
	// Add to current x & y value
	m_iX += _iX;
	m_iY += _iY;
}

void CSprite::TranslateAbsolute(int _iX, int _iY)
{
	m_iX = _iX;
	m_iY = _iY;
}