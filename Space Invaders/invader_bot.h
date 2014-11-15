//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: invader_bot.h
// Description	: Header file for invader_bot class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#pragma once

#if !defined(__INVADER_BOT_H__)
#define __INVADER_BOT_H__

// Library Includes

// Local Includes
#include "entity.h"
#include "invader.h"

// Types
// Constants

// Prototypes
class CInvaderBot : public CInvader
{
// Member Functions
public:
	// Constructor/destructor
	CInvaderBot();
	virtual ~CInvaderBot();

	virtual bool Initialise();
	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	void SetHit(bool _b);
	bool IsHit() const;

protected:
private:
	CInvaderBot(const CInvaderBot& _kr);
	CInvaderBot& operator= (const CInvaderBot& _kr);

// Member Variables
public:
protected:
	bool m_bHit;

private:
};
#endif // __INVADER_BOT_H__