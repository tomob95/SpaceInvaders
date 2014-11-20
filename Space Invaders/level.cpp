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
#include "utils.h"
#include "backbuffer.h"
#include "Barrier.h"

//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: level.cpp
// Description	: Implementation of the level class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

// This Include
#include "Level.h"

// Static Variables
std::vector<CInvader*> CLevel::m_vecInvaders;

// Implementation
// TODO: rename this?
#define CHEAT_BOUNCE_ON_BACK_WALL

/***********************

 * CLevel: Constructor
 * @author:

 ********************/
CLevel::CLevel()
	: m_iInvadersRemaining(0)	// Default to 0
	, m_pPlayer(0)
	, m_iWidth(0)
	, m_iHeight(0)
{
}

/***********************

 * ~CLevel: Deconstructor
 * @author:

 ********************/
CLevel::~CLevel()
{
	// While there are still invaders
	while (m_vecInvaders.size() > 0)
	{
		// Get the invader
		CInvader* pInvader = m_vecInvaders[m_vecInvaders.size() - 1];
		// pop
		m_vecInvaders.pop_back();
		// Clean up pointer
		delete pInvader;
	}
	// Clean up memeber variable
	delete m_pPlayer;
	m_pPlayer = 0;
}

/***********************

 * Initialise: Initialise the level
 * @author:
 * @parameter: int _iWidth, level width
 *				int _iHeight, level height
 * @return: bool

 ********************/
bool CLevel::Initialise(int _iWidth, int _iHeight)
{
	// Initialise variables
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

	// Iniialise constants
	const int kiNumInvaders = 55;
	const int kiStartX = 20;
	const int kiGap = 15;

	// Set x and y
	int iCurrentX = kiStartX;
	int iCurrentY = kiStartX;

	// Loop through invaders
	for (int i = 0; i < kiNumInvaders; ++i)
	{
		// Create, validate and initialise
		CInvader* pInvader = new CInvader();
		VALIDATE(pInvader->Initialise());
		// Set x & y
		pInvader->SetX(iCurrentX);
		pInvader->SetY(iCurrentY);

		// Set current x
		iCurrentX += pInvader->GetWidth() + kiGap;
		// If is is greater than 500
		if (iCurrentX > 500)
		{
			// Reset x
			iCurrentX = kiStartX;
			// Increase y
			iCurrentY += 30;
		}
		// Push to vector
		m_vecInvaders.push_back(pInvader);
	}

	// Set the barrier x & y
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
			// Create, validate and initialise
			CBarrier* pBarrier = new CBarrier();
			VALIDATE(pBarrier->Initialise());
			// Set x & y
			pBarrier->SetX(_iBarrier1X + 10*j);
			pBarrier->SetY(_iBarrier1Y + 10*i);

			// Push to vector
			m_vecBarrier1.push_back(pBarrier);
		}
	}

	//Barrier 2
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<8; j++)
		{
			// Create, validate and initialise
			CBarrier* pBarrier = new CBarrier();
			VALIDATE(pBarrier->Initialise());
			// Set x & y
			pBarrier->SetX(_iBarrier2X + 10*j);
			pBarrier->SetY(_iBarrier2Y + 10*i);

			// Push to vector
			m_vecBarrier2.push_back(pBarrier);
		}
	}

	//Barrier 3
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<8; j++)
		{
			// Create, validate and initialise
			CBarrier* pBarrier = new CBarrier();
			VALIDATE(pBarrier->Initialise());
			// Set x & y
			pBarrier->SetX(_iBarrier3X + 10*j);
			pBarrier->SetY(_iBarrier3Y + 10*i);

			// Push to vector
			m_vecBarrier3.push_back(pBarrier);
		}
	}

	// Set the number of invaders still on screen
	SetInvadersRemaining(kiNumInvaders);
	return (true);
}

/***********************

 * Draw: Draw the level
 * @author:

 ********************/
void CLevel::Draw()
{
	// Draw each invader
	for (unsigned int i = 0; i < m_vecInvaders.size(); ++i)
	{
		m_vecInvaders[i]->Draw();
	}

	// Draw player
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

	// If the bullet exists
	if( m_pPlayerBullet != nullptr )
	{
		// Draw it
		m_pPlayerBullet->Draw();
	}

	// Draw the score
	DrawScore();
}

/***********************

 * Process: Process the level
 * @author:
 * @parameter: float _fDeltaTick - delta time

 ********************/
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
			// Delete it
			delete m_pPlayerBullet;
			m_pPlayerBullet = nullptr;
		} 
		// If the the bullet is off the screen in the other direction
		else if (m_pPlayerBullet->GetY() > m_iHeight)
		{
			// Delete it
			delete m_pPlayerBullet;
			m_pPlayerBullet = nullptr;		
		}
		else
		{
			// Otherwise process & check for collisions
			m_pPlayerBullet->Process( _fDeltaTick );
			CheckPlayerBulletCollision();			
		};
	}

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

	//Process each barrier
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

/***********************

 * GetPlayer: GetPlayer the level
 * @author:
 * @return: CPlayer*

 ********************/
CPlayer* CLevel::GetPlayer() const
{
	// Return member variable
	return (m_pPlayer);
}

/***********************

 * ProcessInvaderWallCollision: Process collision with wall
 * @author:
 * @parameter: float _fDeltaTick - delta time
 * @return: bool

 ********************/
bool CLevel::ProcessInvaderWallCollision(float _fDeltaTick)
{
	// Loop through all invaders
	for (unsigned int i = 0; i < m_vecInvaders.size(); ++i)
	{
		// If it is within the bounds
		if ((m_vecInvaders[i]->GetX() + 30 > m_iWidth - m_vecInvaders[i]->GetWidth()  && CInvader::GetDirection()) ||  (m_vecInvaders[i]->GetX() -30 < 20 && !CInvader::GetDirection()))
		{
			// It collided
			return 1;
		}
	}
	// Else it didnt
	return 0;

}

/***********************

 * ProcessInvaderBulletCollision: Process collision with invader bullet
 * @author:

 ********************/
void CLevel::ProcessInvaderBulletCollision()
{
	// Loop through all the invaders
	for (unsigned int i = 0; i < m_vecInvaders.size(); ++i)
	{
		//TODO: this
	}
}

/***********************

 * GetInvadersRemaining: Get the remaining invaders
 * @author:
 * @return: int

 ********************/
int CLevel::GetInvadersRemaining() const
{
	// Return number of remaining invaders
	return (m_iInvadersRemaining);
}

/***********************

 * SetInvadersRemaining: Set the remaining invaders
 * @author:
 * @parameter: int _i, the number of invaders remaining

 ********************/
void CLevel::SetInvadersRemaining(int _i)
{
	// Set the number of invaders remaining
	m_iInvadersRemaining = _i;
	UpdateScoreText();
}

/***********************

 * MoveInvadersDown: Move the invaders down
 * @author:
 * @parameter: float _fDeltaTick, delta time

 ********************/
void CLevel::MoveInvadersDown(float _fDeltaTick)
{
	// Loop through all the invaders
	for (unsigned int i = 0; i < m_vecInvaders.size(); ++i)
	{
		// Move down
		m_vecInvaders[i]->SetY(m_vecInvaders[i]->GetY() + 30);
		// Process
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
bool CLevel::CreateBullet(bool _bDirection, int _iPositionX, int _iPositionY) //_bDirection: 0=Down, 1=Up
{
	// If the bullet does not already exist
	if(m_pPlayerBullet == nullptr)
	{
		// Create mew bullet object using input
		m_pPlayerBullet = new CBullet( _bDirection, _iPositionX, _iPositionY );
		// Validate initialisation
		VALIDATE( m_pPlayerBullet->Initialise() );
		// Draw the new bullet
		m_pPlayerBullet->Draw();
		return true;
	}
	// Otherwise no bullet for you
	return false;
}

/***********************

 * DrawScore: Draw the score to the screen
 * @author: 

 ********************/
void CLevel::DrawScore()
{
	// Get hdc
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

	// Set x 7 y
	const int kiX = 0;
	const int kiY = m_iHeight - 50;
	
	// Output text
	TextOut(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
}

/***********************

 * UpdateScoreText: Update the text
 * @author: 

 ********************/
void CLevel::UpdateScoreText()
{
	// Convert to string
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	m_strScore = L"Bricks Remaining: ";
	// Add to member variable
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
	int iInvaderX;
	int iInvaderY;
	int iInvaderW;
	int iInvaderH;
	int iBarrierX;
	int iBarrierY;
	int iBarrierHealth;

	// For each invader
	for( unsigned int i = 0; i < m_vecInvaders.size(); ++i )
	{
		// get x, y, width and height
		iInvaderX = m_vecInvaders[ i ]->GetX();
		iInvaderY = m_vecInvaders[ i ]->GetY();
		iInvaderW = m_vecInvaders[ i ]->GetWidth();
		iInvaderH = m_vecInvaders[ i ]->GetHeight();

		// Check if bullet collides
		if( (( iBulletX >= iInvaderX ) || ( iBulletX + 4 >= iInvaderX )) && 
			(( iBulletX <= iInvaderX + iInvaderW ) || ( iBulletX + 4 <= iInvaderX + iInvaderW )) &&
			( iBulletY >= iInvaderY ) &&
			( iBulletY <= iInvaderY + iInvaderH ) 
		  )
		{
			//Bullet has hit the invader. Destroy the invader and the bullet.
			m_vecInvaders.erase(m_vecInvaders.begin()+i,m_vecInvaders.begin()+i+1);
			delete m_pPlayerBullet;
			m_pPlayerBullet = nullptr;
			return( true );
		}
	}

	//Check Barrier 1 for collision
	for (unsigned int i=0; i < m_vecBarrier1.size(); i++)
	{
		//Get X, Y and Health
		iBarrierX = m_vecBarrier1[i]->GetX();
		iBarrierY = m_vecBarrier1[i]->GetY();
		iBarrierHealth = m_vecBarrier1[i]->GetHealth();
		//Check if collides
		if( (iBarrierHealth > 0) && 
			(( iBulletX >= iBarrierX ) || ( iBulletX + 4 >= iBarrierX )) && 
			(( iBulletX <= iBarrierX + 10 ) || ( iBulletX + 4 <= iBarrierX + 10 )) &&
			( iBulletY >= iBarrierY ) &&
			( iBulletY <= iBarrierY + 10 ) 
		  )
		{
			//Change health and destroy bullet
			m_vecBarrier1[i]->SetHealth(iBarrierHealth-1);
			delete m_pPlayerBullet;
			m_pPlayerBullet = nullptr;
			return( true );
		}
	}

	//Check Barrier 2 for collision
	for (unsigned int i=0; i < m_vecBarrier2.size(); i++)
	{
		//Get X, Y and Health
		iBarrierX = m_vecBarrier2[i]->GetX();
		iBarrierY = m_vecBarrier2[i]->GetY();
		iBarrierHealth = m_vecBarrier2[i]->GetHealth();
		//Check if collides
		if( (iBarrierHealth > 0) && 
			(( iBulletX >= iBarrierX ) || ( iBulletX + 4 >= iBarrierX )) && 
			(( iBulletX <= iBarrierX + 10 ) || ( iBulletX + 4 <= iBarrierX + 10 )) &&
			( iBulletY >= iBarrierY ) &&
			( iBulletY <= iBarrierY + 10 ) 
		  )
		{
			//Change health and destroy bullet
			m_vecBarrier2[i]->SetHealth(iBarrierHealth-1);
			delete m_pPlayerBullet;
			m_pPlayerBullet = nullptr;
			return( true );
		}
	}

	//Check Barrier 3 for collision
	for (unsigned int i=0; i < m_vecBarrier3.size(); i++)
	{
		//Get X, Y and Health
		iBarrierX = m_vecBarrier3[i]->GetX();
		iBarrierY = m_vecBarrier3[i]->GetY();
		iBarrierHealth = m_vecBarrier3[i]->GetHealth();
		//Check if collides
		if( (iBarrierHealth > 0) && 
			(( iBulletX >= iBarrierX ) || ( iBulletX + 4 >= iBarrierX )) && 
			(( iBulletX <= iBarrierX + 10 ) || ( iBulletX + 4 <= iBarrierX + 10 )) &&
			( iBulletY >= iBarrierY ) &&
			( iBulletY <= iBarrierY + 10 ) 
		  )
		{
			//Change health and destroy bullet
			m_vecBarrier3[i]->SetHealth(iBarrierHealth-1);
			delete m_pPlayerBullet;
			m_pPlayerBullet = nullptr;
			return( true );
		}
	}
	return( false );
}