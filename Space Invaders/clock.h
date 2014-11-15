//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: clock.h
// Description	: Header file for clock class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#pragma once

#if !defined(__CLOCK_H__)
#define __CLOCK_H__

// Library Includes
// Local Includes
// Types
// Constants

// Prototypes
class CClock
{
// Member Functions
public:
	// Constructor/destructor
	CClock();
	~CClock();

	bool Initialise();
	void Process();
	float GetDeltaTick();

protected:
private:
	CClock(const CClock& _kr);
	// Operator overload
	CClock& operator= (const CClock& _kr);

// Member Variables
public:
protected:
	float m_fTimeElapsed;
	float m_fDeltaTime;
	float m_fLastTime;
	float m_fCurrentTime;

private:
};
#endif // __CLOCK_H__