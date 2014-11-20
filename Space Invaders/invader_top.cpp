//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: Invader_top.cpp
// Description	: Implementation file for Invader_top class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

// Local Includes
#include "resource.h"
#include "utils.h"

// This Include
#include "invader_top.h"

// Implementation
/***********************

 * CInvaderTop: Constructor
 * @author:

 ********************/
CInvaderTop::CInvaderTop()
	: m_bHit(false) // Default to false
{
}

/***********************

 * ~CInvaderTop: Deconstructor
 * @author:

 ********************/
CInvaderTop::~CInvaderTop()
{
}

/***********************

 * Initialise: Initialise the invader-top
 * @author:
 * @return: bool

 ********************/
bool CInvaderTop::Initialise()
{
	// Validate & initialise
	VALIDATE(CEntity::Initialise(IDB_INVADER_TOP0));
	return (true);
}

/***********************

 * Draw: Draw the invader-top
 * @author:

 ********************/
void CInvaderTop::Draw()
{
	// If the invader is not hit 
	if (!m_bHit)
	{
		// Draw the entity
		CEntity::Draw();
	}
}

/***********************

 * Process: Process the invader-top
 * @author:
 * @parameter: float _fDeltaTick, delta tick

 ********************/
void CInvaderTop::Process(float _fDeltaTick)
{
	// If the invader_top is not hit
	if (!m_bHit)
	{
		// Draw the entity
		CEntity::Process(_fDeltaTick);
	}
}

/***********************

 * SetHit: Set the invader to hit
 * @author:
 * @parameter: bool _b

 ********************/
void CInvaderTop::SetHit(bool _b)
{
	// Set hit to _b
	m_bHit = _b;
}

/***********************

 * IsHit: Return if the invader is hit
 * @author:
 * @return: bool

 ********************/
bool CInvaderTop::IsHit() const
{
	return (m_bHit);
}