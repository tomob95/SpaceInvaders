#pragma once
#if !defined(__BRICK_H__)
#define __BRICK_H__
// Library Includes
// Local Includes
#include "entity.h"
#include "invader.h"
// Types
// Constants
// Prototypes
class CInvaderBot : public CInvader
{
// Member Functions
public:
CInvaderBot();
virtual ~CInvaderBot();
virtual bool Initialise();
virtual void Draw();
virtual void Process(float _fDeltaTick);
void SetHit(bool _b);
bool IsHit() const;
protected:
private:
CInvaderBot(const CInvaderBot& _kr);
CInvaderBot& operator= (const CInvaderBot& _kr);
// Member Variables
public:
protected:
bool m_bHit;
private:
};
#endif // __BRICK_H__