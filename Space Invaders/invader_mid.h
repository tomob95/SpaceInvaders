//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: invader_mid.h
// Description	: Header file for invader_mid class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#pragma once

#if !defined(__INVADER_MID_H__)
#define __INVADER_MID_H__

// Library Includes

// Local Includes
#include "entity.h"
#include "invader.h"

// Types
// Constants

// Prototypes
class CInvaderMid : public CInvader
{
// Member Functions
public:
	// COnstructor/destructor
	CInvaderMid();
	virtual ~CInvaderMid();

	virtual bool Initialise();
	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	void SetHit(bool _b);
	bool IsHit() const;

protected:
private:
	CInvaderMid(const CInvaderMid& _kr);
	CInvaderMid& operator= (const CInvaderMid& _kr);

// Member Variables
public:
protected:
	bool m_bHit;

private:
};
#endif // __INVADER_MID_H__