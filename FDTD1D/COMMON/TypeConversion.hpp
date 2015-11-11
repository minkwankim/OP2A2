/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * TypeConversion.hpp
 *
 *  Created on: Nov 5, 2015
 *      Author: minkwan
 */

#ifndef TYPECONVERSION_HPP_
#define TYPECONVERSION_HPP_


#include "Common.hpp"
#include "ExceptionGeneral.hpp"
#include "CodeLocation.hpp"
#include <algorithm>


namespace OP2A{
namespace Common{


template<typename T>
T IntToEnum(int v)
{
	return(static_cast<T>(v));
}

template<typename T>
int EnumToInt(T v)
{
	return(static_cast<int>(v));
}


}
}


#endif /* TYPECONVERSION_HPP_ */
