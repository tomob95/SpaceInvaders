//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: barrier.cpp
// Description	: Implementation file for barrier class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

// Local includes
#include "Barrier.h"
#include "sprite.h"
#include "utils.h"
#include "resource.h"
#include "game.h"

// Static variables
HBITMAP CBarrier::s_hSprite1 = nullptr;
HBITMAP CBarrier::s_hSprite2 = nullptr;
HBITMAP CBarrier::s_hSprite3 = nullptr;
HBITMAP CBarrier::s_hSprite4 = nullptr;
HBITMAP CBarrier::s_hSprite5 = nullptr;

// Implementation
/***********************

 * CBarrier: Constructor
 * @author:

 ********************/
CBarrier::CBarrier(void)
{
}

/***********************

 * ~CBarrier: Destructor
 * @author:

 ********************/
CBarrier::~CBarrier(void)
{
}

/***********************

 * Initialise: Initialise the barrier
 * @author:
 * @return: bool

 ********************/
bool CBarrier::Initialise()
{
	// Get instnace
	HINSTANCE hInstance = CGame::GetInstance().GetAppInstance();
	// If no barrier has been initialised before
	if(s_hSprite1 == nullptr)
	{
		// Load bitmap for barrier 1 & validate
		s_hSprite1 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BARRIER1));
		VALIDATE(s_hSprite1);
		
		// Load bitmap for barrier 2 & validate
		s_hSprite2 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BARRIER2));
		VALIDATE(s_hSprite2);

		// Load bitmap for barrier 3 & validate
		s_hSprite3 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BARRIER3));
		VALIDATE(s_hSprite3);

		// Load bitmap for barrier 4 & validate
		s_hSprite4 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BARRIER4));
		VALIDATE(s_hSprite4);

		// Load bitmap for barrier 5 & validate
		s_hSprite5 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BARRIER5));
		VALIDATE(s_hSprite5);
	}

	// Set variables
	m_iHealth = 4;
	m_pSprite = new CSprite();
	m_pSprite->ReplaceSprite(s_hSprite5);
	return 1;
}

/***********************

 * Draw: Draw the barrier
 * @author:

 ********************/
void CBarrier::Draw()
{
	// Draw entitiy
	CEntity::Draw();
}

/***********************

 * Process: Process the barrier
 * @author:

 ********************/
void CBarrier::Process()
{
	// Switch health to get appropriate sprite
	switch(m_iHealth)
	{
	case 4:
		{
			//Barrier is full health
			m_pSprite->ReplaceSprite(s_hSprite5);
			return;
		}
		break;
	case 3:
		{
			// replace sprite with damaged
			m_pSprite->ReplaceSprite(s_hSprite4);
			return;
		}
		break;
	case 2:
		{
			// replace sprite with more damaged
			m_pSprite->ReplaceSprite(s_hSprite3);
			return;
		}
		break;
	case 1:
		{
			// replace sprite with even more damaged
			m_pSprite->ReplaceSprite(s_hSprite2);
			return;
		}
		break;
	case 0:
		{
			//Barrier is dead
			m_pSprite->ReplaceSprite(s_hSprite1);
			return;
		}
		break;
	default:
		{
			return;
		}
		break;
	}
}

/***********************

 * SetHealth: Set the health of the barrier
 * @author:
 * @parameter: int _i, health to set

 ********************/
void CBarrier::SetHealth(int _i)
{
	// Set memeber variable
	m_iHealth = _i;
}

/***********************

 * GetHealth: Get the health of the barrier
 * @author:
 * @return: int

 ********************/
int CBarrier::GetHealth() const
{
	// Return member variable
	return (m_iHealth);
}