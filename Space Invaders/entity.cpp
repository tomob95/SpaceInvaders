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

// Library Includes
// Local Includes
#include "resource.h"
#include "sprite.h"
#include "utils.h"
// This Include
#include "entity.h"
// Static Variables
// Static Function Prototypes
// Implementation
CEntity::CEntity()
{
}
CEntity::~CEntity()
{
	delete m_pSprite;
	m_pSprite = 0;
}

bool CEntity::Initialise(const int _kiSpriteID)
{
	m_pSprite = new CSprite();
	VALIDATE(m_pSprite->Initialise(_kiSpriteID));
	return (true);
}

void CEntity::Draw()
{
	m_pSprite->Draw();
}

void CEntity::Process(float _fDeltaTick)
{
	m_pSprite->Process(_fDeltaTick);
}

int CEntity::GetX() const
{
	return (m_pSprite->GetX());
}

int CEntity::GetY() const
{
	return (m_pSprite->GetY());
}

int CEntity::GetWidth() const
{
	return (m_pSprite->GetWidth());
}

int CEntity::GetHeight() const
{
	return (m_pSprite->GetHeight());
}

void CEntity::SetX(int _i)
{
	m_pSprite->SetX(_i);
}

void CEntity::SetY(int _i)
{
	m_pSprite->SetY(_i);
}