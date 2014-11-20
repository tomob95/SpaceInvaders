// Library Includes
// Local Includes
#include "resource.h"
#include "utils.h"
#include <Windows.h>
// This Include
#include "invader.h"
#include "level.h"
// Static Variables
bool CInvader::m_bDirection = 1;
bool CInvader::m_bMoveDown = 0;
// Static Function Prototypes
// Implementation
CInvader::CInvader()
: m_bHit(false)
{
}
CInvader::~CInvader()
{
}

bool CInvader::Initialise()
{
	VALIDATE(CEntity::Initialise(IDB_INVADER));

	return (true);
}

void CInvader::Draw()
{
	if (!m_bHit)
	{
		CEntity::Draw();
	}
}

void CInvader::SwapDirection()
{
	m_bDirection = !m_bDirection;
}

bool CInvader::GetDirection()
{
	return m_bDirection;
}

void CInvader::Process(float _fDeltaTick)
{
	if (!m_bHit)
	{
		if (m_bDirection)
		{
			SetX(GetX() + 1);
		}
		else
		{
			SetX(GetX() - 1);
		}
		
		CEntity::Process(_fDeltaTick);
	}
}

void CInvader::ProcessSprite(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);
}

void CInvader::SetHit(bool _b)
{
	m_bHit = _b;
}

bool CInvader::IsHit() const
{
	return (m_bHit);
}