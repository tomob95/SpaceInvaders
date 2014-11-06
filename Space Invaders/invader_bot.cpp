// Library Includes
// Local Includes
#include "resource.h"
#include "utils.h"
// This Include
#include "invader_bot.h"
// Static Variables
// Static Function Prototypes
// Implementation
CInvaderBot::CInvaderBot()
: m_bHit(false)
{
}
CInvaderBot::~CInvaderBot()
{
}

bool CInvaderBot::Initialise()
{
	VALIDATE(CEntity::Initialise(IDB_INVADER_TOP0));
	return (true);
}

void CInvaderBot::Draw()
{
	if (!m_bHit)
	{
		CEntity::Draw();
	}
}

void CInvaderBot::Process(float _fDeltaTick)
{
	if (!m_bHit)
	{
		CEntity::Process(_fDeltaTick);
	}
}

void CInvaderBot::SetHit(bool _b)
{
	m_bHit = _b;
}

bool CInvaderBot::IsHit() const
{
	return (m_bHit);
}