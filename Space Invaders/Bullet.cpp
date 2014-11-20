//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: bullet.cpp
// Description	: Implementation file for bullet class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

// Library Includes
#include <Windows.h>

// Local Includes
#include "resource.h"
#include "utils.h"
#include "level.h"
#include "game.h"

// This Include
#include "bullet.h"

// Static Variables
// Static Function Prototypes

// Implementation
/***********************

 * CBackBuffer: Constructor
 * @author: 
 * @parameter: bool _bDirection, direction of bullet
 *				int _iXPos, x position
 *				int _iYPos, y position

 ********************/
CBullet::CBullet(bool _bDirection, int _iXPos, int _iYPos)
	: m_bHit(false),
	  m_bDirection(_bDirection)
	  // Set direction as parameter
{
	// Set x & y position
	m_fX = _iXPos; 
	m_fY = _iYPos;
}

/***********************

 * ~CBackBuffer: Destructor
 * @author: 

 ********************/
CBullet::~CBullet()
{
}

/***********************

 * Initialise: Destructor
 * @author:
 * @return: bool

 ********************/
bool CBullet::Initialise()
{
	// TODO: need sprite
	// Validate and initialise entity
	VALIDATE(CEntity::Initialise( IDB_BULLET ));
	// Update sprite position
	UpdateSpritePos();

	return (true);
}

/***********************

 * Draw: Draw the bullet
 * @author:

 ********************/
void CBullet::Draw()
{
	// If the bullet is not hit
	if (!m_bHit)
	{
		// Draw the bullet
		CEntity::Draw();
	}
}

/***********************

 * SetDirection: Set direction of bullet
 * @author:
 * @parameter: bool _bDirection, direction bullet is travelling

 ********************/
void CBullet::SetDirection(bool _bDirection)
{
	// Set member variable
	m_bDirection = _bDirection;
}

/***********************

 * GetDirection: Get direction of bullet
 * @author:
 * @return: bool

 ********************/
bool CBullet::GetDirection()
{
	return( m_bDirection );
}

/***********************

 * Process: Process bullet
 * @author:
 * @parameter: float _fDeltaTick, delta time

 ********************/
void CBullet::Process(float _fDeltaTick)
{
	// If bullet is not hit	
	if (!m_bHit)
	{
		// If direction is up ( true )
		if (m_bDirection)
		{
			// Change y position adding current & speed
			m_fY = m_fY + kiBulletSpeed;
		}
		else
		{
			// Change y position subtracting current & speed
			m_fY = m_fY - kiBulletSpeed;
		}
		// Process entity
		UpdateSpritePos();
		CEntity::Process(_fDeltaTick);
		Draw();
	}
}

/***********************

 * ProcessSprite: Process bullet sprite
 * @author:
 * @parameter: float _fDeltaTick, delta time

 ********************/
void CBullet::ProcessSprite(float _fDeltaTick)
{
	// Call process for entity
	CEntity::Process(_fDeltaTick);
}

/***********************

 * SetHit: set bullet hit
 * @author:
 * @parameter: bool _b, whether bullet is hit

 ********************/
void CBullet::SetHit(bool _b)
{
	m_bHit = _b;
}

/***********************

 * GetHit: Get bullet hit
 * @author:
 * @return: bool

 ********************/
bool CBullet::IsHit() const
{
	return( m_bHit );
}

/***********************

 * UpdateSpritePos: Update the sprites xy position to match objects
 * @author:

 ********************/
void CBullet::UpdateSpritePos()
{
	CEntity::SetX( m_fX );
	CEntity::SetY( m_fY );
}