#pragma once
#if !defined(__PADDLE_H__)
#define __PADDLE_H__
// Library Includes
// Local Includes
#include "entity.h"
#include "sprite.h"
// Types
// Constants
// Prototypes
class CPlayer : public CEntity
{
// Member Functions
public:
CPlayer();
virtual ~CPlayer();
virtual bool Initialise();
virtual void Draw();
virtual void Process(float _fDeltaTick);
protected:
private:
CPlayer(const CPlayer& _kr);
CPlayer& operator= (const CPlayer& _kr);
// Member Variables
public:
protected:
private:
};
#endif // __PADDLE_H__