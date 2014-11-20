//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: clock.cpp
// Description	: Header file for clock class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

// Library Includes
#include <windows.h>

// Local Includes
#include "Clock.h"

// Implementation
/***********************

 * CClock: Constructor
 * @author:

 ********************/
CClock::CClock()
		: m_fTimeElapsed(0.0f), // Default to 0
			m_fDeltaTime(0.0f),
			m_fLastTime(0.0f), 
			m_fCurrentTime(0.0f)
{
}

/***********************

 * ~CClock: Deconstructor
 * @author:

 ********************/
CClock::~CClock()
{
}

/***********************

 * Initialise: Initialise the CClock
 * @author:
 * @return: bool

 ********************/
bool CClock::Initialise()
{
	return (true);
}

/***********************

 * Process: Process the clock
 * @author:

 ********************/
void CClock::Process()
{
	// Set last time as current time
	m_fLastTime = m_fCurrentTime;
	// Set current time as time
	m_fCurrentTime = static_cast<float>(timeGetTime());

	// If last time is 0
	if (m_fLastTime == 0.0f)
	{
		// last time is current time
		m_fLastTime = m_fCurrentTime;
	}

	// Set delta time to current time - last time
	m_fDeltaTime = m_fCurrentTime - m_fLastTime;
	// add elapsed time to delta time
	m_fTimeElapsed += m_fDeltaTime;
}

/***********************

 * GetDeltaTick: Get the tick
 * @author:

 ********************/
float CClock::GetDeltaTick()
{
	// Calc and return
	return (m_fDeltaTime / 1000.0f);
}