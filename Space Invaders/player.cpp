//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: player.cpp
// Description	: Implementation file for player class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

// Local Includes
#include "resource.h"
#include "utils.h"

// This Include
#include "player.h"

// Implementation
/***********************

 * CPlayer: Constructor
 * @author:

 ********************/
CPlayer::CPlayer()
{
}

/***********************

 * ~CPlayer: Deconstructor
 * @author:

 ********************/
CPlayer::~CPlayer()
{
}

/***********************

 * Initialise: Initialise the player
 * @author:
 * @return: bool

 ********************/
bool CPlayer::Initialise()
{
	// Validate and initialise entity
	VALIDATE(CEntity::Initialise(IDB_PLAYER));
	return (true);
}

/***********************

 * Draw: Draw the player
 * @author:

 ********************/
void CPlayer::Draw()
{
	// Call entity draw
	CEntity::Draw();
}

/***********************

 * Process: Process the player
 * @author:
 * @parameter: float _fDeltaTick, delta tick

 ********************/
void CPlayer::Process(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);
}