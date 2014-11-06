// Library Includes
// Local Includes
#include "resource.h"
#include "utils.h"
// This Include
#include "player.h"
// Static Variables
// Static Function Prototypes
// Implementation
CPlayer::CPlayer()
{
}
CPlayer::~CPlayer()
{
}
bool
CPlayer::Initialise()
{
	VALIDATE(CEntity::Initialise(IDB_PLAYER));
	return (true);
}
void
CPlayer::Draw()
{
	CEntity::Draw();
}
void
CPlayer::Process(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);
}