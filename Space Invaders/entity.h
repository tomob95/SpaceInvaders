//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: entitiy.h
// Description	: Header file for enitity class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#pragma once

#if !defined(__ENTITY_H__)
#define __ENTITY_H__

// Library Includes
// Local Includes
// Types
// Constants

// Prototypes
class CSprite;
class CEntity
{
// Member Functions
public:
	// Constructor/destructor
	CEntity();
	virtual ~CEntity();

	virtual bool Initialise(const int _kiSpriteID);
	//virtual bool Initialise(const int _kiSpriteID, const int _kiMaskID);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	void SetX(int _i);
	void SetY(int _i);
	int GetX() const;
	int GetY() const;
	int GetHeight() const;
	int GetWidth() const;

protected:
private:
	CEntity(const CEntity& _kr);
	// Operator overload
	CEntity& operator= (const CEntity& _kr);

// Member Variables
public:
protected:
	CSprite* m_pSprite;
	int m_fX;
	int m_fY;

private:
};
#endif // __ENTITY_H__