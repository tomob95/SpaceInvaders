//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: backbuffer.cpp
// Description	: Implementation file for backbuffer class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

// This include
#include "BackBuffer.h"

// Implementation
/***********************

 * CBackBuffer: Constructor
 * @author: 

 ********************/
CBackBuffer::CBackBuffer()
			: m_hWnd(0)	// Default to 0
			, m_hDC(0)
			, m_hSurface(0)
			, m_hOldObject(0)
			, m_iWidth(0)
			, m_iHeight(0)
{
}

/***********************

 * ~CBackBuffer: Destructor
 * @author: 

 ********************/
CBackBuffer::~CBackBuffer()
{
	// Delete objects
	SelectObject(m_hDC, m_hOldObject);
	DeleteObject(m_hSurface);
	DeleteObject(m_hDC);
}

/***********************

 * Initialise: Initialise backbuffer
 * @author: 
 * @parameter: HWND _hWnd, window handler
 *				int _iWidth, width
 *				int _iHeight, height
 * @return: bool

 ********************/
bool CBackBuffer::Initialise(HWND _hWnd, int _iWidth, int _iHeight)
{
	// Set input as member variables
	m_hWnd = _hWnd;
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	// Get current windowDC using hwnd and create bitmap compatible surface
	HDC hWindowDC = ::GetDC(m_hWnd);
	m_hDC = CreateCompatibleDC(hWindowDC);
	m_hSurface = CreateCompatibleBitmap(hWindowDC, m_iWidth, m_iHeight);
	ReleaseDC(m_hWnd, hWindowDC);

	// Set old object as bitmap surface, create new brush and store old brush
	m_hOldObject = static_cast<HBITMAP>(SelectObject(m_hDC, m_hSurface));
	HBRUSH brushWhite = static_cast<HBRUSH>(GetStockObject(LTGRAY_BRUSH));
	HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(m_hDC, brushWhite));

	// Create rectangle
	Rectangle(m_hDC, 0, 0, m_iWidth, m_iHeight);
	SelectObject(m_hDC, oldBrush);
	return (true);
}

/***********************

 * Clear: Clear the backbuffer
 * @author: 

 ********************/
void CBackBuffer::Clear()
{
	// Set hOldBrush as current brush
	HBRUSH hOldBrush = static_cast<HBRUSH>(SelectObject(GetBFDC(), GetStockObject(BLACK_BRUSH)));
	// Get rectangle
	Rectangle(GetBFDC(), 0, 0, GetWidth(), GetHeight());
	// Clear rectangle
	SelectObject(GetBFDC(), hOldBrush);
}

/***********************

 * GetBFDC: Return m_hDC
 * @author: 
 * @return: HDC

 ********************/
HDC CBackBuffer::GetBFDC() const
{
	return (m_hDC);
}

/***********************

 * GetWidth: Return m_iWidth
 * @author: 
 * @return: int

 ********************/
int CBackBuffer::GetWidth() const
{
	return (m_iWidth);
}

/***********************

 * GetHeight: Return m_iHeight
 * @author: 
 * @return: int

 ********************/
int CBackBuffer::GetHeight() const
{
	return (m_iHeight);
}

/***********************

 * Present: Get current HDC and update present
 * @author: 
 * @return: int

 ********************/
void CBackBuffer::Present()
{
	// Get current HDC 
	HDC hWndDC = ::GetDC(m_hWnd);
	// Update to present
	BitBlt(hWndDC, 0, 0, m_iWidth, m_iHeight, m_hDC, 0, 0, SRCCOPY);
	// Release
	ReleaseDC(m_hWnd, hWndDC);
}