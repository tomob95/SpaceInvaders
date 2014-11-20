//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: entity.cpp
// Description	: Header file for entity class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

// Local Includes
#include "resource.h"
#include "sprite.h"
#include "utils.h"

// This Include
#include "entity.h"

// Implementation
/***********************

 * CEntity: Constructor
 * @author:

 ********************/
CEntity::CEntity()
{
}

/***********************

 * ~CEntity: Deconstructor
 * @author:

 ********************/
CEntity::~CEntity()
{
	delete m_pSprite;
	m_pSprite = 0;
}

/***********************

 * Initialise: Initialise the entity
 * @author:
 * @parameter: const int _kiSpriteID, which sprite to use
 * @return: bool

 ********************/
bool CEntity::Initialise(const int _kiSpriteID)
{
	// Create new sprite
	m_pSprite = new CSprite();
	// Validate and initialise
	VALIDATE(m_pSprite->Initialise(_kiSpriteID));
	return (true);
}

/***********************

 * Initialise: Initialise the entity
 * @author:
 * @parameter: const int _kiSpriteID, which sprite to use
 *             const int _kiMaskID, which mask to use
 * @return: bool

 ********************/
bool CEntity::Initialise(const int _kiSpriteID, const int _kiMaskID)
{
	// Make a new sprite
	m_pSprite = new CSprite();
	// Validate and initialse
	VALIDATE(m_pSprite->Initialise(_kiSpriteID, _kiMaskID));
	return (true);
}

/***********************

 * Draw: Draw the entity
 * @author:

 ********************/
void CEntity::Draw()
{
	// Draw the sprite
	m_pSprite->Draw();
}

/***********************

 * Process: Process the entity
 * @author:
 * @parameter: float _fDeltaTick, delta tick

 ********************/
void CEntity::Process(float _fDeltaTick)
{
	// Process the sprite
	m_pSprite->Process(_fDeltaTick);
}

/***********************

 * GetX: Get the x of the sprite
 * @author:
 * @return: int

 ********************/
int CEntity::GetX() const
{
	// return sprite x pos
	return (m_pSprite->GetX());
}

/***********************

 * GetY: Get the y of the sprite
 * @author:
 * @return: int

 ********************/
int CEntity::GetY() const
{
	return (m_pSprite->GetY());
}

/***********************

 * GetWidth: Get the width of the sprite
 * @author:
 * @return: int

 ********************/
int CEntity::GetWidth() const
{
	// Return width
	return (m_pSprite->GetWidth());
}

/***********************

 * GetHeight: Get the height of the sprite
 * @author:
 * @return: int

 ********************/
int CEntity::GetHeight() const
{
	return (m_pSprite->GetHeight());
}

/***********************

 * SetX: Get the height of the sprite
 * @author:
 * @return: int

 ********************/
void CEntity::SetX(int _i)
{
	// Set x pos
	m_pSprite->SetX(_i);
}

/***********************

 * SetY: Get the height of the sprite
 * @author:
 * @parameter: int _i, 

 ********************/
void CEntity::SetY(int _i)
{
	m_pSprite->SetY(_i);
}