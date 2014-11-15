//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: player.h
// Description	: Header file for player class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#pragma once

#if !defined(__PLAYER_H__)
#define __PLAYER_H__

// Library Includes

// Local Includes
#include "entity.h"
#include "sprite.h"

// Types
// Constants

// Prototypes
class CPlayer : public CEntity
{
// Member Functions
public:
	// Constructor/destructor
	CPlayer();
	virtual ~CPlayer();

	virtual bool Initialise();
	virtual void Draw();
	virtual void Process(float _fDeltaTick);

protected:
private:
	CPlayer(const CPlayer& _kr);
	CPlayer& operator= (const CPlayer& _kr);

// Member Variables
public:
protected:
private:
};
#endif // __PLAYER_H__