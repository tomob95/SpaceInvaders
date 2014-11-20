//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: bullet.cpp
// Description	: Implementation file for bullet class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

// Local includes
#include "Barrier.h"
#include "sprite.h"
#include "utils.h"
#include "resource.h"

// Static variables
CSprite* CBarrier::m_hSprite1;
CSprite* CBarrier::m_hSprite2;
CSprite* CBarrier::m_hSprite3;
CSprite* CBarrier::m_hSprite4;
CSprite* CBarrier::m_hSprite5;


CBarrier::CBarrier(void)
{
}


CBarrier::~CBarrier(void)
{
}

bool CBarrier::Initialise()
{
	if(m_hSprite1 == nullptr)
	{
		//No barrier has been initialised before
		m_hSprite1 = new CSprite();
		VALIDATE(m_hSprite1->Initialise(IDB_BARRIER1));

		m_hSprite2 = new CSprite();
		VALIDATE(m_hSprite2->Initialise(IDB_BARRIER2));

		m_hSprite3 = new CSprite();
		VALIDATE(m_hSprite3->Initialise(IDB_BARRIER3));

		m_hSprite4 = new CSprite();
		VALIDATE(m_hSprite4->Initialise(IDB_BARRIER4));

		m_hSprite5 = new CSprite();
		VALIDATE(m_hSprite5->Initialise(IDB_BARRIER5));
	}

	m_iHealth = 4;
	m_pSprite = m_hSprite5;
	return 1;
}

void CBarrier::Draw()
{
	CEntity::Draw();
}

void CBarrier::Process()
{
	switch(m_iHealth)
	{
	case 4:
		{
			//Barrier is full health
			m_pSprite = m_hSprite5;
		}
	case 3:
		{
			m_pSprite = m_hSprite4;
		}
	case 2:
		{
			m_pSprite = m_hSprite3;
		}
	case 1:
		{
			m_pSprite = m_hSprite2;
		}
	case 0:
		{
			//Barrier is dead
			m_pSprite = m_hSprite5;
		}
	}
}

void CBarrier::SetHealth(int _i)
{
	m_iHealth = _i;
}

int CBarrier::GetHealth() const
{
	return (m_iHealth);
}