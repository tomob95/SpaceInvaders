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

#define CHEAT_BOUNCE_ON_BACK_WALL

CLevel::CLevel()
: m_iInvadersRemaining(0)
, m_pPlayer(0)
//, m_pBall(0)
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
	m_pPlayer->SetY(400);

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
//	ProcessBallWallCollision();
//	ProcessBallPaddleCollision();
//	ProcessBallBrickCollision();
//	ProcessCheckForWin();
//	ProcessBallBounds();

	m_fTimeElapsed += _fDeltaTick;
	if (m_fTimeElapsed > 1)
	{
		m_fTimeElapsed = 0;
		if(ProcessInvaderWallCollision(_fDeltaTick))
		{
			CInvader::SwapDirection();
			MoveInvadersDown(_fDeltaTick);		
		}
		else
		{
			for (unsigned int i = 0; i < m_vecInvaders.size(); ++i)
			{
				m_vecInvaders[i]->Process(_fDeltaTick);
			}	
		};

	}
	if( m_pPlayerBullet != nullptr )
	{
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
			/*float fBallR = m_pBall->GetRadius();
			float fBallX = m_pBall->GetX();
			float fBallY = m_pBall->GetY();
			float fBrickX = m_vecBricks[i]->GetX();
			float fBrickY = m_vecBricks[i]->GetY();
			float fBrickH = m_vecBricks[i]->GetHeight();
			float fBrickW = m_vecBricks[i]->GetWidth();

			if ((fBallX + fBallR > fBrickX - fBrickW / 2) &&
			(fBallX - fBallR < fBrickX + fBrickW / 2) &&
			(fBallY + fBallR > fBrickY - fBrickH / 2) &&
			(fBallY - fBallR < fBrickY + fBrickH / 2))
			{
				//Hit the front side of the brick...
				m_pBall->SetY((fBrickY + fBrickH / 2.0f) + fBallR);
				m_pBall->SetVelocityY(m_pBall->GetVelocityY() * -1);
				m_vecBricks[i]->SetHit(true);
				SetBricksRemaining(GetBricksRemaining() - 1);
			}*/
		}
	}
}
/*
void CLevel::ProcessCheckForWin()
{
	for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
	{
		if (!m_vecBricks[i]->IsHit())
		{
			return;
		}
	}
	CGame::GetInstance().GameOverWon();
}

void CLevel::ProcessBallBounds()
{
	if (m_pBall->GetX() < 0)
	{
		m_pBall->SetX(0);
	}

	else if (m_pBall->GetX() > m_iWidth)
	{
		m_pBall->SetX(static_cast<float>(m_iWidth));
	}

	if (m_pBall->GetY() < 0)
	{
		m_pBall->SetY(0.0f);
	}

	else if (m_pBall->GetY() > m_iHeight)
	{
		CGame::GetInstance().GameOverLost();
	//m_pBall->SetY(m_iHeight);
	}
}
*/
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
	m_pPlayerBullet = new CBullet( _bDirection, _iPositionX, _iPositionY );
	OutputDebugString( L"Totes workded " );
	VALIDATE( m_pPlayerBullet->Initialise() );
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