#include "Barrier.h"
#include "sprite.h"
#include "utils.h"
#include "resource.h"
#include "game.h"

HBITMAP CBarrier::s_hSprite1 = nullptr;
HBITMAP CBarrier::s_hSprite2;
HBITMAP CBarrier::s_hSprite3;
HBITMAP CBarrier::s_hSprite4;
HBITMAP CBarrier::s_hSprite5;

BITMAP CBarrier::s_bitmapSprite1;
BITMAP CBarrier::s_bitmapSprite2;
BITMAP CBarrier::s_bitmapSprite3;
BITMAP CBarrier::s_bitmapSprite4;
BITMAP CBarrier::s_bitmapSprite5;

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
		GetObject(s_hSprite1, sizeof(BITMAP), &s_bitmapSprite1);
		
		s_hSprite2 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BARRIER2));
		VALIDATE(s_hSprite2);
		GetObject(s_hSprite2, sizeof(BITMAP), &s_bitmapSprite2);

		s_hSprite3 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BARRIER3));
		VALIDATE(s_hSprite3);
		GetObject(s_hSprite3, sizeof(BITMAP), &s_bitmapSprite3);

		s_hSprite4 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BARRIER4));
		VALIDATE(s_hSprite4);
		GetObject(s_hSprite4, sizeof(BITMAP), &s_bitmapSprite4);

		s_hSprite5 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BARRIER5));
		VALIDATE(s_hSprite5);
		GetObject(s_hSprite5, sizeof(BITMAP), &s_bitmapSprite5);
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