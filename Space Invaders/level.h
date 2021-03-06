//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: level.h
// Description	: Header file for level class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#pragma once

#if !defined(__LEVEL_H__)
#define __LEVEL_H__

// Library Includes
#include <vector>
#include <string>

// Local Includes
// Types
// Constants

// Prototypes
class CInvader;
class CSPInvader;
class CPlayer;
class CBullet;
class CBarrier;
class CLevel
{
	// Member Functions
	public:
		// Constructor/destructor
		CLevel();
		virtual ~CLevel();

		virtual bool Initialise(int _iWidth, int _iHeight);
		virtual void Draw();
		virtual void Process(float _fDeltaTick);
		CPlayer* GetPlayer() const;
		static void MoveInvadersDown(float _fDeltaTick);
		void SetMouseCoords(int _iX, int _iY);
		bool CreateBullet(bool _bDirection, int _iPositionX,  int _iPositionY); //_bDirection: 0=Down, 1=Up
		bool CreateSpecialInvader();
		void ResetInvaders();
		void SetBulletSpeed( int _iSpeed );
		int GetBulletSpeed();
		void SetInvaderSpeed( int _iSpeed );
		int GetInvaderSpeed();
		void SetPlayerInvincible( int _iInv );
		int GetPlayerInvincible();
		void SetBulletPierce( int _iInv );
		int GetBulletPierce();
		int GetScore() const;



	protected:
		bool ProcessInvaderBulletCollision(CBullet* _pBullet);
		void UpdateScoreText();
		void DrawScore();
		void DrawLives();
		bool ProcessInvaderWallCollision(float _fDeltaTick);
		bool ProcessSpecialWallCollision(float _fDeltaTick);
		bool CheckPlayerBulletCollision();
		bool CheckBarrierInvaderCollision();

	private:
		float m_fTimeElapsed;
		CLevel(const CLevel& _kr);
		CLevel& operator= (const CLevel& _kr);

	// Member Variables
	public:
		CBullet* m_pPlayerBullet;
	protected:
		CPlayer* m_pPlayer;
		static std::vector<CInvader*> m_vecInvaders;

		std::vector<CBarrier*> m_vecBarrier1;
		std::vector<CBarrier*> m_vecBarrier2;
		std::vector<CBarrier*> m_vecBarrier3;

		std::vector<CBullet*> m_vecInvaderBullets;

		int m_iWidth;
		int m_iHeight;
		int m_iScore;
		std::string m_strScore;
		int m_iBulletSpeed;
		int m_iInvaderSpeed;
		int m_iBulletPierce;
		int m_iPlayerInv;
		int m_fMouseX;
		int m_fMouseY;
		CSPInvader* m_pSpecialInvader;
		int m_iLives;

	private:
};

#endif // __LEVEL_H__