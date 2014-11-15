//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: invader.h
// Description	: Header file for invader class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#pragma once

// Local includes
#include "entity.h"

class CInvader :
	public CEntity
{
	// Member functions
	public:
		// Constructor/destructor
		CInvader();
		virtual ~CInvader();

		virtual bool Initialise();
		virtual void Draw();
		virtual void Process(float _fDeltaTick);

		void ProcessSprite(float _fDeltaTick);
		void SetHit(bool _b);
		bool IsHit() const;

		static bool GetDirection();
		static void SwapDirection();

	protected:
	private:
		CInvader(const CInvader& _kr);
		// Operator overload
		CInvader& operator= (const CInvader& _kr);

	// Member Variables
	public:
	protected:
		bool m_bHit;

	private:
		static bool m_bDirection; //0 = Left, 1 = Right
		static bool m_bMoveDown;

};

