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
#include "Special_Invader.h"

// Implementation
/***********************

 * CSPInvader: Constructor
 * @author:

 ********************/
CSPInvader::CSPInvader()
	: m_bHit(false) // Default to false
{
}

/***********************

 * ~CSPInvader: Deconstructor
 * @author:

 ********************/
CSPInvader::~CSPInvader()
{
}

/***********************

 * Initialise: Initialise the Invader bot
 * @author:
 * @return: bool

 ********************/
bool CSPInvader::Initialise()
{
	// Validate and initialise entity
	VALIDATE(CEntity::Initialise(IDB_SPECIAL));
	return (true);
}

/***********************

 * Draw: Draw the invader
 * @author:

 ********************/
void CSPInvader::Draw()
{
	// If the invader is not hit
	if (!m_bHit)
	{
		// Draw entity
		CEntity::Draw();
	}
}

/***********************

 * Process: Process the invader
 * @author:
 * @parameter: float _fDeltaTick, delta tick

 ********************/
void CSPInvader::Process(float _fDeltaTick)
{
	// If the invader is not hit
	if (!m_bHit)
	{
		// Go right
		SetX(GetX() + 2);
		// Process the entity
		CEntity::Process(_fDeltaTick);
	}
}

/***********************

 * ProcessSprite: Process the sprite
 * @author:
 * @parameter: float _fDeltaTick, delta tick

 ********************/
void CSPInvader::ProcessSprite(float _fDeltaTick)
{
	// Process the entity
	CEntity::Process(_fDeltaTick);
}

/***********************

 * SetHit: Set the invader to hit
 * @author:
 * @parameter: bool _b

 ********************/
void CSPInvader::SetHit(bool _b)
{
	m_bHit = _b;
}

/***********************

 * IsHit: Return if the invader is hit
 * @author:
 * @return: bool

 ********************/
bool CSPInvader::IsHit() const
{
	return (m_bHit);
}