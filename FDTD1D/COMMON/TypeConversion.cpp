/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * TypeConversion.cpp
 *
 *  Created on: Jan 11, 2016
 *      Author: minkwan
 */

#include "TypeConversion.hpp"



namespace OP2A{
namespace Common{


std::string intToString(int i)
{
	std::stringstream ss;
	ss << i;
	return(ss.str());
}

std::string intToString(unsigned int i)
{
	std::stringstream ss;
	ss << i;
	return(ss.str());
}




}
}
