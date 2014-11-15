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
class CPlayer;
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
		int GetInvadersRemaining() const;
		static void MoveInvadersDown(float _fDeltaTick);

	protected:
		void ProcessInvaderBulletCollision();
		void UpdateScoreText();
		void CreateBullet(bool _bDirection, int _iPositionX,  int _iPositionY); //_bDirection: 0=Down, 1=Up
		void DrawScore();
		void SetInvadersRemaining(int _i);
		bool ProcessInvaderWallCollision(float _fDeltaTick);

	private:
		float m_fTimeElapsed;
		CLevel(const CLevel& _kr);
		CLevel& operator= (const CLevel& _kr);

	// Member Variables
	public:
	protected:
		CPlayer* m_pPlayer;
		static std::vector<CInvader*> m_vecInvaders;
		int m_iWidth;
		int m_iHeight;
		int m_iInvadersRemaining;
		std::wstring m_strScore;
		int m_iBulletSpeed;

	private:
};

#endif // __LEVEL_H__