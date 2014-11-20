// Library Includes
// Local Includes
#include "resource.h"
#include "utils.h"
// This Include
#include "invader_mid.h"
// Static Variables
// Static Function Prototypes
// Implementation
CInvaderMid::CInvaderMid()
: m_bHit(false)
{
}
CInvaderMid::~CInvaderMid()
{
}

bool CInvaderMid::Initialise()
{
	VALIDATE(CEntity::Initialise(IDB_INVADER_MID0));
	return (true);
}

void CInvaderMid::Draw()
{
	if (!m_bHit)
	{
		CEntity::Draw();
	}
}

void CInvaderMid::Process(float _fDeltaTick)
{
	if (!m_bHit)
	{
		CEntity::Process(_fDeltaTick);
	}
}

void CInvaderMid::SetHit(bool _b)
{
	m_bHit = _b;
}

bool CInvaderMid::IsHit() const
{
	return (m_bHit);
}