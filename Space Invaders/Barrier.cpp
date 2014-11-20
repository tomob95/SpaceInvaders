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
#include "game.h"

// Static variables
HBITMAP CBarrier::s_hSprite1 = nullptr;
HBITMAP CBarrier::s_hSprite2 = nullptr;
HBITMAP CBarrier::s_hSprite3 = nullptr;
HBITMAP CBarrier::s_hSprite4 = nullptr;
HBITMAP CBarrier::s_hSprite5 = nullptr;


CBarrier::CBarrier(void)
{
}


CBarrier::~CBarrier(void)
{
}

bool CBarrier::Initialise()
{
	HINSTANCE hInstance = CGame::GetInstance().GetAppInstance();
	if(s_hSprite1 == nullptr)
	{
		//No barrier has been initialised before
		s_hSprite1 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BARRIER1));
		VALIDATE(s_hSprite1);
		
		s_hSprite2 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BARRIER2));
		VALIDATE(s_hSprite2);

		s_hSprite3 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BARRIER3));
		VALIDATE(s_hSprite3);

		s_hSprite4 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BARRIER4));
		VALIDATE(s_hSprite4);

		s_hSprite5 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BARRIER5));
		VALIDATE(s_hSprite5);
	}

	m_iHealth = 4;
	m_pSprite = new CSprite();
	m_pSprite->ReplaceSprite(s_hSprite5);
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
			m_pSprite->ReplaceSprite(s_hSprite5);
			return;
		}
		break;
	case 3:
		{
			m_pSprite->ReplaceSprite(s_hSprite4);
			return;
		}
		break;
	case 2:
		{
			m_pSprite->ReplaceSprite(s_hSprite3);
			return;
		}
		break;
	case 1:
		{
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

void CBarrier::SetHealth(int _i)
{
	m_iHealth = _i;
}

int CBarrier::GetHealth() const
{
	return (m_iHealth);
}