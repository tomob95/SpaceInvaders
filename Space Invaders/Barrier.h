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
#include "windows.h"

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
		static HBITMAP s_hSprite1;
		static HBITMAP s_hSprite2;
		static HBITMAP s_hSprite3;
		static HBITMAP s_hSprite4;
		static HBITMAP s_hSprite5;

		static BITMAP s_bitmapSprite1;
		static BITMAP s_bitmapSprite2;
		static BITMAP s_bitmapSprite3;
		static BITMAP s_bitmapSprite4;
		static BITMAP s_bitmapSprite5;

	private:

	// Member Variables
	public:
	protected:
		int m_iHealth;

	private:
		
};

