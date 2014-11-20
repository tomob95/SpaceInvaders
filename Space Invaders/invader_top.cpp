// Library Includes
// Local Includes
#include "resource.h"
#include "utils.h"
// This Include
#include "invader_top.h"
// Static Variables
// Static Function Prototypes
// Implementation
CInvaderTop::CInvaderTop()
: m_bHit(false)
{
}
CInvaderTop::~CInvaderTop()
{
}

bool CInvaderTop::Initialise()
{
	VALIDATE(CEntity::Initialise(IDB_INVADER_TOP0));
	return (true);
}

void CInvaderTop::Draw()
{
	if (!m_bHit)
	{
		CEntity::Draw();
	}
}

void CInvaderTop::Process(float _fDeltaTick)
{
	if (!m_bHit)
	{
		CEntity::Process(_fDeltaTick);
	}
}

void CInvaderTop::SetHit(bool _b)
{
	m_bHit = _b;
}

bool CInvaderTop::IsHit() const
{
	return (m_bHit);
}