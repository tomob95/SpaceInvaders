//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: Invader_mid.cpp
// Description	: Implementation file for Invader_mid class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

// Local Includes
#include "resource.h"
#include "utils.h"

// This Include
#include "invader_mid.h"

// Implementation
/***********************

 * CInvaderMid: Constructor
 * @author:

 ********************/
CInvaderMid::CInvaderMid()
	: m_bHit(false) // Default to false
{
}

/***********************

 * ~CInvaderMid: Deconstructor
 * @author:

 ********************/
CInvaderMid::~CInvaderMid()
{
}

/***********************

 * Initialise: Initialise the Invader Mid
 * @author:
 * @return: bool

 ********************/
bool CInvaderMid::Initialise()
{
	// Validate and initialise entity
	VALIDATE(CEntity::Initialise(IDB_INVADER_MID0));
	return (true);
}

/***********************

 * Draw: Draw the invader-mid
 * @author:

 ********************/
void CInvaderMid::Draw()
{
	// If invader is not hit
	if (!m_bHit)
	{
		// Draw entity
		CEntity::Draw();
	}
}

/***********************

 * Process: Process the invader-mid
 * @author:
 * @parameter: float _fDeltaTick, delta tick

 ********************/
void CInvaderMid::Process(float _fDeltaTick)
{
	// If invader is not hit
	if (!m_bHit)
	{
		// Process entity
		CEntity::Process(_fDeltaTick);
	}
}

/***********************

 * SetHit: Set the invader to hit
 * @author:
 * @parameter: bool _b

 ********************/
void CInvaderMid::SetHit(bool _b)
{
	m_bHit = _b;
}

/***********************

 * IsHit: Return if the invader is hit
 * @author:
 * @return: bool

 ********************/
bool CInvaderMid::IsHit() const
{
	return (m_bHit);
}