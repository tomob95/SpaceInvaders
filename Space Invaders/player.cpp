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

// Library Includes
// Local Includes
#include "resource.h"
#include "utils.h"
// This Include
#include "player.h"
// Static Variables
// Static Function Prototypes
// Implementation
CPlayer::CPlayer()
{
}
CPlayer::~CPlayer()
{
}
bool
CPlayer::Initialise()
{
	VALIDATE(CEntity::Initialise(IDB_PLAYER));
	return (true);
}
void
CPlayer::Draw()
{
	CEntity::Draw();
}
void
CPlayer::Process(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);
}