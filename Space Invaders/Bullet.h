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
class CBullet :
	public CEntity
{
	// Member functions
	public:
		// Construtor/destructor
		CBullet(bool _bDirection, int _iXPos, int _iYPos);
		virtual ~CBullet();

		virtual bool Initialise();
		virtual void Draw();
		virtual void Process(float _fDeltaTick);
		void ProcessSprite(float _fDeltaTick);
		void SetHit(bool _b);
		bool IsHit() const;
		bool GetDirection();
		void SetDirection(bool _bDirection);
		void UpdateSpritePos();

	protected:
	private:
		CBullet(const CBullet& _kr);
		// Operator overload
		CBullet& operator= (const CBullet& _kr);

	// Member Variables
	public:
	protected:
		bool m_bDirection; //_bDirection: 0=Down, 1=Up
		bool m_bHit;
	private:
		
};

