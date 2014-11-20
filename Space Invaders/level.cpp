//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: level.cpp
// Description	: Implementation file for level class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

// Library Includes
#include <locale>
#include <codecvt>
// Local Includes
#include "Game.h"
#include "player.h"
#include "Bullet.h"
#include "invader.h"
//#include "Ball.h"
#include "utils.h"
#include "backbuffer.h"
#include "Barrier.h"
// This Include
#include "Level.h"
// Static Variables

std::vector<CInvader*> CLevel::m_vecInvaders;
// Static Function Prototypes

// Implementation
// TODO: rename this?
#define CHEAT_BOUNCE_ON_BACK_WALL

CLevel::CLevel()
: m_iInvadersRemaining(0)
, m_pPlayer(0)
, m_iWidth(0)
, m_iHeight(0){}

CLevel::~CLevel()
{
	while (m_vecInvaders.size() > 0)
	{
		CInvader* pInvader = m_vecInvaders[m_vecInvaders.size() - 1];
		m_vecInvaders.pop_back();
		delete pInvader;
	}
	delete m_pPlayer;
	m_pPlayer = 0;
}

bool CLevel::Initialise(int _iWidth, int _iHeight)
{
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;
	m_fTimeElapsed = 5;
	m_pPlayer = new CPlayer();
	m_pPlayerBullet = nullptr;
	VALIDATE(m_pPlayer->Initialise());

	// Set the player's position to be centered on the x,
	// and a little bit up from the bottom of the window.
	m_pPlayer->SetX((_iWidth/2) - (m_pPlayer->GetWidth()/2));
	m_pPlayer->SetY( kiYPos );

	const int kiNumInvaders = 55;
	const int kiStartX = 20;
	const int kiGap = 15;

	int iCurrentX = kiStartX;
	int iCurrentY = kiStartX;

	for (int i = 0; i < kiNumInvaders; ++i)
	{
		CInvader* pInvader = new CInvader();
		VALIDATE(pInvader->Initialise());
		pInvader->SetX(iCurrentX);
		pInvader->SetY(iCurrentY);
		iCurrentX += pInvader->GetWidth() + kiGap;
		if (iCurrentX > 500)
		{
			iCurrentX = kiStartX;
			iCurrentY += 30;
		}
		m_vecInvaders.push_back(pInvader);
	}

	int _iBarrier1X = 150;
	int _iBarrier1Y = 650;

	int _iBarrier2X = 350;
	int _iBarrier2Y = 650;

	int _iBarrier3X = 550;
	int _iBarrier3Y = 650;

	/**************************
	*  Initialise the barriers *
	***************************/
	//Barrier 1
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<8; j++)
		{
			CBarrier* pBarrier = new CBarrier();
			VALIDATE(pBarrier->Initialise());
			pBarrier->SetX(_iBarrier1X + 10*j);
			pBarrier->SetY(_iBarrier1Y + 10*i);

			m_vecBarrier1.push_back(pBarrier);
		}
	}

	//Barrier 2
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<8; j++)
		{
			CBarrier* pBarrier = new CBarrier();
			VALIDATE(pBarrier->Initialise());
			pBarrier->SetX(_iBarrier2X + 10*j);
			pBarrier->SetY(_iBarrier2Y + 10*i);

			m_vecBarrier2.push_back(pBarrier);
		}
	}

	//Barrier 3
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<8; j++)
		{
			CBarrier* pBarrier = new CBarrier();
			VALIDATE(pBarrier->Initialise());
			pBarrier->SetX(_iBarrier3X + 10*j);
			pBarrier->SetY(_iBarrier3Y + 10*i);

			m_vecBarrier3.push_back(pBarrier);
		}
	}

	SetInvadersRemaining(kiNumInvaders);
	return (true);
}

void CLevel::Draw()
{
	//Draw Invaders
	for (unsigned int i = 0; i < m_vecInvaders.size(); ++i)
	{
		m_vecInvaders[i]->Draw();
	}
	//Draw Player
	m_pPlayer->Draw();
	
	/*****************
	* Draw Barriers  *
	******************/
	//Barrier 1
	for (unsigned int i = 0; i < m_vecBarrier1.size(); ++i)
	{
		m_vecBarrier1[i]->Draw();
	}
	//Barrier 2
	for (unsigned int i = 0; i < m_vecBarrier1.size(); ++i)
	{
		m_vecBarrier2[i]->Draw();
	}
	//Barrier 3
	for (unsigned int i = 0; i < m_vecBarrier1.size(); ++i)
	{
		m_vecBarrier3[i]->Draw();
	}

	//Draw Bullet
	if( m_pPlayerBullet != nullptr )
	{
		m_pPlayerBullet->Draw();
	}

	//Draw Score
	DrawScore();
}

void CLevel::Process(float _fDeltaTick)
{
	// Set time elapsed to current + delta tick
	m_fTimeElapsed += _fDeltaTick;

	// If the bullet is not null
	if( m_pPlayerBullet != nullptr )
	{
		// Process bullet
		
		// If the bullet is off the screen
		if (m_pPlayerBullet->GetY() <= 0)
		{
			delete m_pPlayerBullet;
			m_pPlayerBullet = nullptr;
		}
		else if (m_pPlayerBullet->GetY() > m_iHeight)
		{
			delete m_pPlayerBullet;
			m_pPlayerBullet = nullptr;		
		}
		else
		{
			m_pPlayerBullet->Process( _fDeltaTick );
			CheckPlayerBulletCollision();			
		};
	}

	// If it has been more than one tick since start of game
	//if (m_fTimeElapsed > 1)
	//{
	//	// Set time elapsed to 0
	//	m_fTimeElapsed = 0;

		// If invader collides with wall
		if(ProcessInvaderWallCollision(_fDeltaTick))
		{
			// Change direction and move down
			CInvader::SwapDirection();
			MoveInvadersDown(_fDeltaTick);		
		}
		else
		{
			// Else move sideways
			for (unsigned int i = 0; i < m_vecInvaders.size(); ++i)
			{
				m_vecInvaders[i]->Process(_fDeltaTick);
			}	
		};

	//}




	for(unsigned int i=0; i<m_vecBarrier1.size(); i++)
	{
		m_vecBarrier1[i]->Process();
		m_vecBarrier2[i]->Process();
		m_vecBarrier3[i]->Process();
	}


	// Update player position & process
	m_pPlayer->SetX( m_fMouseX );
	m_pPlayer->Process(_fDeltaTick);
}

CPlayer* CLevel::GetPlayer() const
{
	return (m_pPlayer);
}

bool CLevel::ProcessInvaderWallCollision(float _fDeltaTick)
{
	for (unsigned int i = 0; i < m_vecInvaders.size(); ++i)
	{
		if ((m_vecInvaders[i]->GetX() + 30 > m_iWidth - m_vecInvaders[i]->GetWidth()  && CInvader::GetDirection()) ||  (m_vecInvaders[i]->GetX() -30 < 20 && !CInvader::GetDirection()))
		{
			return 1;
		}
	}
	return 0;

}

void CLevel::ProcessInvaderBulletCollision()
{
	for (unsigned int i = 0; i < m_vecInvaders.size(); ++i)
	{
		if (!m_vecInvaders[i]->IsHit())
		{
			// TODO: this
		}
	}
}

int CLevel::GetInvadersRemaining() const
{
	return (m_iInvadersRemaining);
}

void CLevel::SetInvadersRemaining(int _i)
{
	m_iInvadersRemaining = _i;
	UpdateScoreText();
}

void CLevel::MoveInvadersDown(float _fDeltaTick)
{
	for (unsigned int i = 0; i < m_vecInvaders.size(); ++i)
	{
		m_vecInvaders[i]->SetY(m_vecInvaders[i]->GetY() + 30);
		m_vecInvaders[i]->ProcessSprite(_fDeltaTick);
	}
}

/***********************

 * CreateBullet: Create a new bullet
 * @author: 
 * @parameter:  bool _bDirection, direction of bullet
 *				int _x, x position
 *				int _y, y position

 ********************/
bool CLevel::CreateBullet(bool _bDirection, int _iPositionX, int _iPositionY)//_bDirection: 0=Down, 1=Up
{
	if(m_pPlayerBullet == nullptr)
	{
		// Create mew bullet object using input
		m_pPlayerBullet = new CBullet( _bDirection, _iPositionX, _iPositionY );
		// Debug string
		//
		
		// Validate initialisation
		VALIDATE( m_pPlayerBullet->Initialise() );
		// Draw the new bullet
		m_pPlayerBullet->Draw();
		return true;
	}
	return false;
}

void CLevel::DrawScore()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();
	const int kiX = 0;
	const int kiY = m_iHeight - 50;
	
	TextOut(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
}

void CLevel::UpdateScoreText()
{
	//std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	//m_strScore = L"Bricks Remaining: ";
	//m_strScore += converter.from_bytes(ToString(GetInvadersRemaining()));
}

/***********************

 * SetMouseCoords: Set the x & y pos of the mouse
 * @author: 
 * @parameter: int _x, x position
 *				int _y, y position

 ********************/
void CLevel::SetMouseCoords(int _iX, int _iY)
{
	// Set as member variables
	m_fMouseX = _iX;
	m_fMouseY = _iY;
}

/***********************

 * SetMouseCoords: Set the x & y pos of the mouse
 * @author: 
 * @parameter: int _x, x position
 *				int _y, y position

 ********************/
bool CLevel::CheckPlayerBulletCollision()
{
	int iBulletX = m_pPlayerBullet->GetX();
	int iBulletY = m_pPlayerBullet->GetY();
	int iBulletW = m_pPlayerBullet->GetWidth();
	
	int iBarrierX;
	int iBarrierY;
	int iBarrierHealth;

	int iInvaderX;
	int iInvaderY;
	int iInvaderW;
	int iInvaderH;

	// For each invader
	// TODO: why does this need to be unsigned?
	// ANSWER .size returns an unsigned int (a vector can't be negative size)
	// Just has conversion warnings when it is a normal int
	for( unsigned int i = 0; i < m_vecInvaders.size(); ++i )
	{
		iInvaderX = m_vecInvaders[ i ]->GetX();
		iInvaderY = m_vecInvaders[ i ]->GetY();
		iInvaderW = m_vecInvaders[ i ]->GetWidth();
		iInvaderH = m_vecInvaders[ i ]->GetHeight();

		// Check if bullet collides
		// TODO: Fix, never fires for some reason
		if( (( iBulletX >= iInvaderX ) || ( iBulletX + 4 >= iInvaderX )) && 
			(( iBulletX <= iInvaderX + iInvaderW ) || ( iBulletX + 4 <= iInvaderX + iInvaderW )) &&
			( iBulletY >= iInvaderY ) &&
			( iBulletY <= iInvaderY + iInvaderH ) 
		  )
		{
			// TODO: this
			//OutputDebugString( L"Totes workded \n" );
			//Bullet has hit the invader. Destroy the invader and the bullet.
			m_vecInvaders.erase(m_vecInvaders.begin()+i,m_vecInvaders.begin()+i+1);
			delete m_pPlayerBullet;
			m_pPlayerBullet = nullptr;
			return( true );
		}
	}

	for (unsigned int i=0; i < m_vecBarrier1.size(); i++)
	{
		iBarrierX = m_vecBarrier1[i]->GetX();
		iBarrierY = m_vecBarrier1[i]->GetY();
		iBarrierHealth = m_vecBarrier1[i]->GetHealth();
		if( (iBarrierHealth > 0) && 
			(( iBulletX >= iBarrierX ) || ( iBulletX + 4 >= iBarrierX )) && 
			(( iBulletX <= iBarrierX + 10 ) || ( iBulletX + 4 <= iBarrierX + 10 )) &&
			( iBulletY >= iBarrierY ) &&
			( iBulletY <= iBarrierY + 10 ) 
		  )
		{
			m_vecBarrier1[i]->SetHealth(iBarrierHealth-1);
			delete m_pPlayerBullet;
			m_pPlayerBullet = nullptr;
			return( true );
		}
	}

	for (unsigned int i=0; i < m_vecBarrier2.size(); i++)
	{
		iBarrierX = m_vecBarrier2[i]->GetX();
		iBarrierY = m_vecBarrier2[i]->GetY();
		iBarrierHealth = m_vecBarrier2[i]->GetHealth();
		if( (iBarrierHealth > 0) && 
			(( iBulletX >= iBarrierX ) || ( iBulletX + 4 >= iBarrierX )) && 
			(( iBulletX <= iBarrierX + 10 ) || ( iBulletX + 4 <= iBarrierX + 10 )) &&
			( iBulletY >= iBarrierY ) &&
			( iBulletY <= iBarrierY + 10 ) 
		  )
		{
			m_vecBarrier2[i]->SetHealth(iBarrierHealth-1);
			delete m_pPlayerBullet;
			m_pPlayerBullet = nullptr;
			return( true );
		}
	}

	for (unsigned int i=0; i < m_vecBarrier3.size(); i++)
	{
		iBarrierX = m_vecBarrier3[i]->GetX();
		iBarrierY = m_vecBarrier3[i]->GetY();
		iBarrierHealth = m_vecBarrier3[i]->GetHealth();
		if( (iBarrierHealth > 0) && 
			(( iBulletX >= iBarrierX ) || ( iBulletX + 4 >= iBarrierX )) && 
			(( iBulletX <= iBarrierX + 10 ) || ( iBulletX + 4 <= iBarrierX + 10 )) &&
			( iBulletY >= iBarrierY ) &&
			( iBulletY <= iBarrierY + 10 ) 
		  )
		{
			m_vecBarrier3[i]->SetHealth(iBarrierHealth-1);
			delete m_pPlayerBullet;
			m_pPlayerBullet = nullptr;
			return( true );
		}
	}

	return( false );
}