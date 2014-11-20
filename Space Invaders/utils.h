//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: utils.h
// Description	: Header file for utils class
// Author		: Kelsey Scheurich, Thomas O'Brien
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#pragma once
#if !defined(__UTILS_H__)
#define __UTILS_H__

// Library Includes
#include <strstream>

// Local Includes
// Types
// Constants
// Prototypes

#define VALIDATE(a) if (!a) return (false)

template<typename T>
std::string ToString(const T& _value)
{
	std::strstream theStream;
	theStream << _value << std::ends;
	return (theStream.str());
}

template<typename T>
std::wstring ToWString(const T& _value)
{
	std::wostringstream theStream;
	theStream << _value;
	return (theStream.str());
}

const int kiBulletSpeed = 7;
const int kiYPos = 740;
static int g_iGameSpeed = 15;
static int g_iInvaderShootRate = 1;
static unsigned int g_iMaxInvaderBullets = 8;

#endif // __UTILS_H__