#pragma once
#include "entity.h"
class CInvader :
	public CEntity
{
	public:
		CInvader();
		virtual ~CInvader();
		virtual bool Initialise();
		virtual void Draw();
		virtual void Process(float _fDeltaTick);
		void ProcessSprite(float _fDeltaTick);
		void SetHit(bool _b);
		bool IsHit() const;
		static bool GetDirection();
		static void SwapDirection();
	protected:
	private:
		CInvader(const CInvader& _kr);
		CInvader& operator= (const CInvader& _kr);
	// Member Variables
	public:
	protected:
		
		bool m_bHit;
	private:
		static bool m_bDirection; //0 = Left, 1 = Right
		static bool m_bMoveDown;


};

