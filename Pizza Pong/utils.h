//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: utils.h
// Description	: header for utils
// Author		: Pizza Party - Aimee Constable, Chloe Cantwell, Joseph Maton, Nick Lacy
// Mail			: aimee.con6886@mediadesign.school.nz, chloe.can6956@mediadesign.school.nz, joseph.mat3620@mediadesign.school.nz, darcy.lac6935@mediadesign.school.nz
//

#pragma once

#if !defined(__UTILS_H__)
#define __UTILS_H__

// Library Includes
#include <strstream>
#define VALIDATE(a) if (!a) return (false)

template<typename T>
std::string ToString(const T& _value)
{
    std::strstream theStream;
    theStream << _value << std::ends;
    return (theStream.str());
}


#endif    // __UTILS_H__

