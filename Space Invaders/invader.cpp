//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: invader.cpp
// Description	: Implementation file for invader class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

// Library Includes
#include <Windows.h>

// Local Includes
#include "resource.h"
#include "utils.h"
#include "level.h"

// This Include
#include "invader.h"

// Static Variables
bool CInvader::m_bDirection = 1;
bool CInvader::m_bMoveDown = 0;

// Implementation
/***********************

 * CInvader: Constructor
 * @author:

 ********************/
CInvader::CInvader()
	: m_bHit(false) // Default to false
{
}

/***********************

 * ~CInvaderBot: Deconstructor
 * @author:

 ********************/
CInvader::~CInvader()
{
}

/***********************

 * Initialise: Initialise the Invader bot
 * @author:
 * @return: bool

 ********************/
bool CInvader::Initialise()
{
	// Validate and initialise entity
	VALIDATE(CEntity::Initialise(IDB_INVADER));
	m_iSpeed = 1;
	return (true);
}

/***********************

 * Draw: Draw the invader
 * @author:

 ********************/
void CInvader::Draw()
{
	// If the invader is not hit
	if (!m_bHit)
	{
		// Draw entity
		CEntity::Draw();
	}
}

/***********************

 * SwapDirection: Swap the direction of the invader
 * @author:

 ********************/
void CInvader::SwapDirection()
{
	// Set it to opposite
	m_bDirection = !m_bDirection;
}

/***********************

 * SwapDirection: Swap the direction of the invader
 * @author:
 * @return: bool

 ********************/
bool CInvader::GetDirection()
{
	return m_bDirection;
}

/***********************

 * Process: Process the invader
 * @author:
 * @parameter: float _fDeltaTick, delta tick

 ********************/
void CInvader::Process(float _fDeltaTick)
{
	// If the invader is not hit
	if (!m_bHit)
	{
		// If the direction is true
		if (m_bDirection)
		{
			// Go right
			SetX(GetX() + m_iSpeed);
		}
		else
		{
			// Go left
			SetX(GetX() - m_iSpeed);
		}
		// Process the entity
		CEntity::Process(_fDeltaTick);
	}
}

/***********************

 * ProcessSprite: Process the sprite
 * @author:
 * @parameter: float _fDeltaTick, delta tick

 ********************/
void CInvader::ProcessSprite(float _fDeltaTick)
{
	// Process the entity
	CEntity::Process(_fDeltaTick);
}

/***********************

 * SetHit: Set the invader to hit
 * @author:
 * @parameter: bool _b

 ********************/
void CInvader::SetHit(bool _b)
{
	m_bHit = _b;
}

/***********************

 * IsHit: Return if the invader is hit
 * @author:
 * @return: bool

 ********************/
bool CInvader::IsHit() const
{
	return (m_bHit);
}