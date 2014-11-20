//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: Special_Invader.h
// Description	: Header file for special invader class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#pragma once

// Local includes
#include "entity.h"

class CSPInvader :
	public CEntity
{
	// Member functions
	public:
		// Constructor/destructor
		CSPInvader();
		virtual ~CSPInvader();

		virtual bool Initialise();
		virtual void Draw();
		virtual void Process(float _fDeltaTick);

		void ProcessSprite(float _fDeltaTick);
		void SetHit(bool _b);
		bool IsHit() const;

	protected:
	private:
		CSPInvader(const CSPInvader& _kr);
		// Operator overload
		CSPInvader& operator= (const CSPInvader& _kr);

	// Member Variables
	public:
	protected:
		bool m_bHit;

};