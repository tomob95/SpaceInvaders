#pragma once
#include "entity.h"
class CBullet :
	public CEntity
{
	public:
		CBullet(bool _bDirection, int _iXPos, int _iYPos);
		virtual ~CBullet();
		virtual bool Initialise();
		virtual void Draw();
		virtual void Process(float _fDeltaTick);
		void ProcessSprite(float _fDeltaTick);
		void SetHit(bool _b);
		bool IsHit() const;
		bool GetDirection();
		void SetDirection(bool _bDirection);
	protected:
	private:
		CBullet(const CBullet& _kr);
		CBullet& operator= (const CBullet& _kr);
	// Member Variables
	public:
	protected:
		bool m_bDirection; //_bDirection: 0=Down, 1=Up
		bool m_bHit;
	private:
		
};

