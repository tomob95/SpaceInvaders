//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: Invader_bot.cpp
// Description	: Implementation file for Invader_bot class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

// Local Includes
#include "resource.h"
#include "utils.h"

// This Include
#include "invader_bot.h"

// Implementation
/***********************

 * CInvaderBot: Constructor
 * @author:

 ********************/
CInvaderBot::CInvaderBot()
	: m_bHit(false) // Default to false
{
}

/***********************

 * ~CInvaderBot: Deconstructor
 * @author:

 ********************/
CInvaderBot::~CInvaderBot()
{
}

/***********************

 * Initialise: Initialise the Invader bot
 * @author:
 * @return: bool

 ********************/
bool CInvaderBot::Initialise()
{
	// Validate and initialise
	VALIDATE(CEntity::Initialise(IDB_INVADER_TOP0));
	return (true);
}

/***********************

 * Draw: Draw the invader-bot
 * @author:

 ********************/
void CInvaderBot::Draw()
{
	// If the invader is nto hit
	if (!m_bHit)
	{
		// Draw entitys
		CEntity::Draw();
	}
}

/***********************

 * Process: Process the invader-top
 * @author:
 * @parameter: float _fDeltaTick, delta tick

 ********************/
void CInvaderBot::Process(float _fDeltaTick)
{
	// If the invader is not hit
	if (!m_bHit)
	{
		// process the entity
		CEntity::Process(_fDeltaTick);
	}
}

/***********************

 * SetHit: Set the invader to hit
 * @author:
 * @parameter: bool _b

 ********************/
void CInvaderBot::SetHit(bool _b)
{
	m_bHit = _b;
}

/***********************

 * IsHit: Return if the invader is hit
 * @author:
 * @return: bool

 ********************/
bool CInvaderBot::IsHit() const
{
	return (m_bHit);
}