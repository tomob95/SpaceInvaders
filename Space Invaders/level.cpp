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
#include "Special_Invader.h"
#include "utils.h"
#include "backbuffer.h"
#include "Barrier.h"

// This Include
#include "Level.h"

// Static Variables
std::vector<CInvader*> CLevel::m_vecInvaders;

// Implementation

/***********************

 * CLevel: Constructor
 * @author:

 ********************/
CLevel::CLevel()
	: m_iScore(0)	// Default to 0
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

	//Delete Barrier 1
	while (!m_vecBarrier1.empty())
	{
		CBarrier* pBarrier = m_vecBarrier1.back();
		m_vecBarrier1.pop_back();
		delete pBarrier;
		pBarrier = nullptr;
	}

	//Delete Barrier 2
	while (!m_vecBarrier2.empty())
	{
		CBarrier* pBarrier = m_vecBarrier2.back();
		m_vecBarrier2.pop_back();
		delete pBarrier;
		pBarrier = nullptr;
	}

	//Delete Barrier 3
	while (!m_vecBarrier3.empty())
	{
		CBarrier* pBarrier = m_vecBarrier3.back();
		m_vecBarrier3.pop_back();
		delete pBarrier;
		pBarrier = nullptr;
	}

	//Delete Invader Bullets
	while (!m_vecInvaderBullets.empty())
	{
		CBullet* pBullet = m_vecInvaderBullets.back();
		m_vecInvaderBullets.pop_back();
		delete pBullet;
		pBullet = nullptr;
	}

	// Clean up memeber variables
	delete m_pSpecialInvader;
	m_pSpecialInvader = 0;
	
	delete m_pPlayer;
	m_pPlayer = 0;

	delete m_pPlayerBullet;
	m_pPlayerBullet = nullptr;
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
	m_iLives = 3;
	m_pPlayer = new CPlayer();
	m_pPlayerBullet = nullptr;
	m_pSpecialInvader = nullptr;
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

	// If the special exists
	if( m_pSpecialInvader != nullptr )
	{
		// Draw it
		m_pSpecialInvader->Draw();
	}

	//Draw Invader Bullets
	for (unsigned int i = 0; i < m_vecInvaderBullets.size(); i++)
	{
		m_vecInvaderBullets[i]->Draw();
	}

	// Draw the score
	DrawScore();
	DrawLives();
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
	int iRandShoot;

	if(m_iLives <= 0)
	{
		CGame::GetInstance().GameOver();
	}

	if(m_vecInvaders.empty())
	{
		ResetInvaders();
		m_iLives += 1;
	}

	if( CheckBarrierInvaderCollision() )
	{
		CGame::GetInstance().GameOver();
	}

	// If there is not a special
	if( m_pSpecialInvader == nullptr )
	{
		// Generate random number
		int iRand = rand() % 500;
		// If it is 2
		if( iRand == 2 )
		{
			// Create a special
			CreateSpecialInvader();
		}
	}

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


	//Process Invader Bullets

	for(unsigned int i=0; i<m_vecInvaderBullets.size(); i++)
	{
		// If the bullet is off the screen
		if (m_vecInvaderBullets[i]->GetY() > m_iHeight || m_vecInvaderBullets[i]->IsHit())
		{
			// Delete it
			CBullet* _delBullet = m_vecInvaderBullets[i];
			m_vecInvaderBullets.erase(m_vecInvaderBullets.begin() + i, m_vecInvaderBullets.begin() + i + 1);
			delete _delBullet;
			_delBullet = nullptr;
		} 
		else
		{
			if(	ProcessInvaderBulletCollision(m_vecInvaderBullets[i]))
			{
				m_vecInvaderBullets[i]->SetHit( true );
			}
			m_vecInvaderBullets[i]->Process(_fDeltaTick);
		}
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
			//Detect if Invader should shoot
			iRandShoot = rand()%2000;
			if(iRandShoot < g_iInvaderShootRate && m_vecInvaderBullets.size() < g_iMaxInvaderBullets && !m_vecInvaders[i]->IsHit())
			{
					CBullet* pBullet = new CBullet(1, m_vecInvaders[i]->GetX(),m_vecInvaders[i]->GetY() + 2);
					pBullet->Initialise();
					m_vecInvaderBullets.push_back(pBullet);
					pBullet = nullptr;
			};
			m_vecInvaders[i]->Process(_fDeltaTick);
		}	
	};

	//Process special
	if( m_pSpecialInvader != nullptr )
	{
		// If invader collides with wall
		if( ProcessSpecialWallCollision( _fDeltaTick ) )
		{
			// delete special
			delete m_pSpecialInvader;
			m_pSpecialInvader = nullptr;
		}
		else
		{
			// Else move sideways
			m_pSpecialInvader->Process( _fDeltaTick );	
		}
	}

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

	// Update score
	UpdateScoreText();
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

 * ProcessInvaderWallCollision: Process collision with wall
 * @author:
 * @parameter: float _fDeltaTick - delta time
 * @return: bool

 ********************/
bool CLevel::ProcessSpecialWallCollision(float _fDeltaTick)
{
	// Loop through all invaders
	if( m_pSpecialInvader != nullptr )
	{
		// If it is within the bounds
		if (m_pSpecialInvader->GetX() > m_iWidth - m_pSpecialInvader->GetWidth())
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
bool CLevel::ProcessInvaderBulletCollision(CBullet* _pBullet)
{
	// Get x, y, width, height
	int iBulletX = _pBullet->GetX();
	int iBulletY = _pBullet->GetY();
	int iBulletW = _pBullet->GetWidth();

	// initialise x, y 
	int iPlayerX = m_pPlayer->GetX();
	int iPlayerY = m_pPlayer->GetY();
	int iPlayerW = m_pPlayer->GetWidth();
	int iPlayerH = m_pPlayer->GetHeight();

	int iBarrierX;
	int iBarrierY;
	int iBarrierHealth;

	// check player for collision
	
	// Check if bullet collides with player
	if( (( iBulletX >= iPlayerX - iPlayerW/2 ) || ( iBulletX + 4 >= iPlayerX - iPlayerW/2 )) && 
		(( iBulletX <= iPlayerX + iPlayerW/2 ) || ( iBulletX + 4 <= iPlayerX + iPlayerW/2 )) &&
		( iBulletY >= iPlayerY ) &&
		( iBulletY <= iPlayerY + iPlayerH )
		)
	{
		//Bullet has hit the Player. Destroy the bullet and remove a life.
		m_iLives -= 1;
		return true;
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
			return true;
				
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
			return true;
				
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
			return true;
				
		}
	}
	return ( false );
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
	//Change bg color
	SetBkColor(hdc, COLORREF RGB(0, 0, 0));
	// Change text color
	SetTextColor(hdc, COLORREF RGB(255, 255, 255));
	// Set x & y
	const int kiX = 10;
	const int kiY = m_iHeight - 50;
	
	// Output text
	TextOut(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
}

/***********************

 * DrawLives: Draw the lives to the screen
 * @author: 

 ********************/
void CLevel::DrawLives()
{
	// Get HDC
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

	// Set x & y
	const int kiX = m_iWidth - 70;
	const int kiY = m_iHeight - 50;
	std::string Caption = "Lives: ";
	std::string sLives = ToString(m_iLives);

	std::string sOutput = Caption + sLives;
	// Output text
	TextOut(hdc, kiX, kiY, sOutput.c_str(), sOutput.size());
}

/***********************

 * UpdateScoreText: Update the text
 * @author: 

 ********************/
void CLevel::UpdateScoreText()
{
	// Convert to string
	m_strScore = "Score: ";
	// Add to member variable
	m_strScore += ToString(m_iScore);
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

 * CheckPlayerBulletCollision: Check if the player bullet is colliding with anything
 * @author: 
 * @return: bool

 ********************/
bool CLevel::CheckPlayerBulletCollision()
{
	// Get x, y, width, height
	int iBulletX = m_pPlayerBullet->GetX();
	int iBulletY = m_pPlayerBullet->GetY();
	int iBulletW = m_pPlayerBullet->GetWidth();
	// initialise x, y 
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
		if( (( iBulletX >= iInvaderX - iInvaderW/2 ) || ( iBulletX + 4 >= iInvaderX - iInvaderW/2 )) && 
			(( iBulletX <= iInvaderX + iInvaderW/2 ) || ( iBulletX + 4 <= iInvaderX + iInvaderW/2 )) &&
			( iBulletY >= iInvaderY ) &&
			( iBulletY <= iInvaderY + iInvaderH ) &&
			(!m_vecInvaders[i]->IsHit())
		  )
		{
			//Bullet has hit the invader. Destroy the invader and the bullet.
			m_vecInvaders[i]->SetHit( true );
			delete m_pPlayerBullet;
			m_pPlayerBullet = nullptr;
			// Increase score
			m_iScore += 10;
			return( true );
		}
	}

	// Check for special collision
	if( m_pSpecialInvader != nullptr )
	{
		iInvaderX = m_pSpecialInvader->GetX();
		iInvaderY = m_pSpecialInvader->GetY();
		iInvaderW = m_pSpecialInvader->GetWidth();
		iInvaderH = m_pSpecialInvader->GetHeight();

		// Check if bullet collides
		if( (( iBulletX >= iInvaderX - iInvaderW/2 ) || ( iBulletX + 4 >= iInvaderX - iInvaderW/2 )) && 
			(( iBulletX <= iInvaderX + iInvaderW/2 ) || ( iBulletX + 4 <= iInvaderX + iInvaderW/2 )) &&
			( iBulletY >= iInvaderY ) &&
			( iBulletY <= iInvaderY + iInvaderH ) 
		  )
		{
			//Bullet has hit the invader. Destroy the invader and the bullet.
			delete m_pSpecialInvader;
			m_pSpecialInvader = nullptr;
			// Increase score
			m_iScore += 100;
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

/***********************

 * CreateSpecialInvader: Create special ship
 * @author: 
 * @parameter: int _x, x position
 *				int _y, y position

 ********************/
bool CLevel::CreateSpecialInvader()
{
	// If the special does not already exist
	if(m_pSpecialInvader == nullptr)
	{
		// Create mew special object using input
		m_pSpecialInvader = new CSPInvader();
		// Validate initialisation
		VALIDATE( m_pSpecialInvader->Initialise() );
		m_pSpecialInvader->SetX( 20 );
		m_pSpecialInvader->SetY( 20 );
		// Draw the new bullet
		m_pSpecialInvader->Draw();
		return true;
	}
	// Otherwise no specail for you
	return false;
}

/***********************

 * ResetInvaders: Spawn moar invaders
 * @author: 
 * @return: void

 ********************/
void CLevel::ResetInvaders()
{
	while(!m_vecInvaders.empty())
	{
		CInvader* _pDelInvader = m_vecInvaders.back();
		m_vecInvaders.pop_back();
		delete _pDelInvader;
		_pDelInvader = nullptr;
	}

	while(!m_vecInvaderBullets.empty())
	{
		CBullet* _pDelInvaderBullet = m_vecInvaderBullets.back();
		m_vecInvaderBullets.pop_back();
		delete _pDelInvaderBullet;
		_pDelInvaderBullet = nullptr;
	}

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
		pInvader->Initialise();
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

}

/***********************

 * SetBulletSpeed: Set the bullet speed
 * @author: 
 * @parameter: int _iSpeed, speed to set

 ********************/
void CLevel::SetBulletSpeed( int _iSpeed )
{
	m_iBulletSpeed = _iSpeed;
}

/***********************

 * SetInvaderSpeed: Set the invader speed
 * @author: 
 * @parameter: int _iSpeed, speed to set

 ********************/
void CLevel::SetInvaderSpeed( int _iSpeed )
{
	// For each invader
	for( unsigned int i = 0; i < m_vecInvaders.size(); ++i )
	{
		// Set speed
		m_vecInvaders[ i ]->m_iSpeed = _iSpeed;
	}
}

/***********************

 * CheckBarrierInvaderCollision: Check if the invaders are colliding with barriers
 * @author: 
 * @return: bool

 ********************/
bool CLevel::CheckBarrierInvaderCollision()
{
	// initialise x, y 
	int iInvaderX;
	int iInvaderY;
	int iInvaderW;
	int iInvaderH;
	int iBarrierX;
	int iBarrierY;
	int iBarrierHealth;

	//Check Barrier 1 for collision
	for (unsigned int i=0; i < m_vecBarrier1.size(); i++)
	{
		//Get X, Y and Health
		iBarrierX = m_vecBarrier1[i]->GetX();
		iBarrierY = m_vecBarrier1[i]->GetY();
		iBarrierHealth = m_vecBarrier1[i]->GetHealth();

		for( unsigned int j = 0; j < m_vecInvaders.size(); ++j )
		{
			iInvaderX = m_vecInvaders[ j ]->GetX();
			iInvaderY = m_vecInvaders[ j ]->GetY();
			//Check if collides
			if( (iBarrierHealth > 0) && 
				(( iInvaderX >= iBarrierX ) || ( iInvaderX + 4 >= iBarrierX )) && 
				(( iInvaderX <= iBarrierX + 10 ) || ( iInvaderX + 4 <= iBarrierX + 10 )) &&
				( iInvaderY >= iBarrierY ) &&
				( iInvaderY <= iBarrierY + 10 ) 
			  )
			{
				//Change health 
				m_vecBarrier1[i]->SetHealth(iBarrierHealth-1);
				return( true );
			}
		}
	}

	//Check Barrier 2 for collision
	for (unsigned int i=0; i < m_vecBarrier2.size(); i++)
	{
		//Get X, Y and Health
		iBarrierX = m_vecBarrier2[i]->GetX();
		iBarrierY = m_vecBarrier2[i]->GetY();
		iBarrierHealth = m_vecBarrier2[i]->GetHealth();
		for( unsigned int j = 0; j < m_vecInvaders.size(); ++j )
		{
			iInvaderX = m_vecInvaders[ j ]->GetX();
			iInvaderY = m_vecInvaders[ j ]->GetY();
			//Check if collides
			if( (iBarrierHealth > 0) && 
				(( iInvaderX >= iBarrierX ) || ( iInvaderX + 4 >= iBarrierX )) && 
				(( iInvaderX <= iBarrierX + 10 ) || ( iInvaderX + 4 <= iBarrierX + 10 )) &&
				( iInvaderY >= iBarrierY ) &&
				( iInvaderY <= iBarrierY + 10 ) 
			  )
			{
				//Change health 
				m_vecBarrier2[i]->SetHealth(iBarrierHealth-1);
				return( true );
			}
		}
	}

	//Check Barrier 3 for collision
	for (unsigned int i=0; i < m_vecBarrier3.size(); i++)
	{
		//Get X, Y and Health
		iBarrierX = m_vecBarrier3[i]->GetX();
		iBarrierY = m_vecBarrier3[i]->GetY();
		iBarrierHealth = m_vecBarrier3[i]->GetHealth();
		for( unsigned int j = 0; j < m_vecInvaders.size(); ++j )
		{
			iInvaderX = m_vecInvaders[ j ]->GetX();
			iInvaderY = m_vecInvaders[ j ]->GetY();
			//Check if collides
			if( (iBarrierHealth > 0) && 
				(( iInvaderX >= iBarrierX ) || ( iInvaderX + 4 >= iBarrierX )) && 
				(( iInvaderX <= iBarrierX + 10 ) || ( iInvaderX + 4 <= iBarrierX + 10 )) &&
				( iInvaderY >= iBarrierY ) &&
				( iInvaderY <= iBarrierY + 10 ) 
			  )
			{
				//Change health 
				m_vecBarrier3[i]->SetHealth(iBarrierHealth-1);
				return( true );
			}
		}
	}

	return( false );
}