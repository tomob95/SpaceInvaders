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

	// Set the paddle's position to be centered on the x,
	// and a little bit up from the bottom of the window.
	//m_pPlayer->SetX(_iWidth / 2.0f);
	//m_pPlayer->SetY(_iHeight - ( 4 * m_pPlayer->GetHeight()));
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

	SetInvadersRemaining(kiNumInvaders);
	return (true);
}

void CLevel::Draw()
{
	for (unsigned int i = 0; i < m_vecInvaders.size(); ++i)
	{
		m_vecInvaders[i]->Draw();
	}
	m_pPlayer->Draw();
	
	if( m_pPlayerBullet != nullptr )
	{
		m_pPlayerBullet->Draw();
	}
	DrawScore();
}

void CLevel::Process(float _fDeltaTick)
{
	// Set time elapsed to current + delta tick
	m_fTimeElapsed += _fDeltaTick;

	// If it has been more than one tick since start of game
	if (m_fTimeElapsed > 1)
	{
		// Set time elapsed to 0
		m_fTimeElapsed = 0;

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

	}
	// If the bullet is not null
	if( m_pPlayerBullet != nullptr )
	{
		// Process bullet
		m_pPlayerBullet->Process( _fDeltaTick );
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
	// Create mew bullet object using input
	m_pPlayerBullet = new CBullet( _bDirection, _iPositionX, _iPositionY );
	// Debug string
	OutputDebugString( L"Totes workded " );
	// Validate initialisation
	VALIDATE( m_pPlayerBullet->Initialise() );
	// Draw the new bullet
	m_pPlayerBullet->Draw();
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
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	m_strScore = L"Bricks Remaining: ";
	m_strScore += converter.from_bytes(ToString(GetInvadersRemaining()));
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

 * IsMouseDraggingCards: Check if the mouse is dragging cards
 * @author: 
 * @return: bool

 ********************/
bool IsBulletExist()
{
	return( false );
}