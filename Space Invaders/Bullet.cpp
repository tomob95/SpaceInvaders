// Library Includes
// Local Includes
#include "resource.h"
#include "utils.h"
#include <Windows.h>
// This Include
#include "bullet.h"
#include "level.h"
// Static Variables
// Static Function Prototypes

// Implementation
CBullet::CBullet(bool _bDirection, int _iXPos, int _iYPos)
: m_bHit(false),
m_bDirection(_bDirection)
{
	m_fX =_iXPos;
	m_fY = _iYPos;
}
CBullet::~CBullet()
{
}

bool CBullet::Initialise()
{

	VALIDATE(CEntity::Initialise(IDB_INVADER));

	return (true);
}

void CBullet::Draw()
{
	if (!m_bHit)
	{
		CEntity::Draw();
	}
}

void CBullet::SetDirection(bool _bDirection)
{
	m_bDirection = _bDirection;
}

bool CBullet::GetDirection()
{
	return m_bDirection;
}

void CBullet::Process(float _fDeltaTick)
{
	if (!m_bHit)
	{
		if (m_bDirection)
		{
			m_fY = m_fY + kiBulletSpeed;
		}
		else
		{
			m_fY = m_fY - kiBulletSpeed;
		}
		CEntity::Process(_fDeltaTick);
	}
}

void CBullet::ProcessSprite(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);
}

void CBullet::SetHit(bool _b)
{
	m_bHit = _b;
}

bool CBullet::IsHit() const
{
	return (m_bHit);
}