//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: bullet.h
// Description	: Header file for bullet class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#pragma once

// Local Includes
#include "entity.h"

// Prototypes
class CBarrier :
	public CEntity
{
	// Member functions
	public:
		// Construtor/destructor
		CBarrier();
		virtual ~CBarrier();
		virtual bool Initialise();
		virtual void Draw();
		virtual void Process();
		void SetHealth(int _i);
		int GetHealth() const;

	protected:
		static CSprite* m_hSprite1;
		static CSprite* m_hSprite2;
		static CSprite* m_hSprite3;
		static CSprite* m_hSprite4;
		static CSprite* m_hSprite5;

	private:

	// Member Variables
	public:
	protected:
		int m_iHealth;

	private:
		
};

