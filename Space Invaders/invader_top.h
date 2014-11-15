//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: invader_top.h
// Description	: Header file for invader_top class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#pragma once
#if !defined(__INVADER_TOP_H__)
#define __INVADER_TOP_H__

// Library Includes

// Local Includes
#include "entity.h"
#include "invader.h"

// Types
// Constants

// Prototypes
class CInvaderTop : public CInvader
{
// Member Functions
public:
	CInvaderTop();
	virtual ~CInvaderTop();
	virtual bool Initialise();
	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	void SetHit(bool _b);
	bool IsHit() const;

protected:
private:
	CInvaderTop(const CInvaderTop& _kr);
	CInvaderTop& operator= (const CInvaderTop& _kr);

// Member Variables
public:
protected:
	bool m_bHit;

private:
};
#endif // __INVADER_TOP_H__