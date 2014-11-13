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
		CLevel();
		virtual ~CLevel();
		virtual bool Initialise(int _iWidth, int _iHeight);
		virtual void Draw();
		virtual void Process(float _fDeltaTick);
		CPlayer* GetPlayer() const;
		int GetInvadersRemaining() const;
		static void MoveInvadersDown(float _fDeltaTick);
	protected:
		/*void ProcessBallWallCollision();
		void ProcessBallPaddleCollision();*/
		void ProcessInvaderBulletCollision();
		/*void ProcessCheckForWin();
		void ProcessBallBounds(); */
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
		//CBall* m_pBall;
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