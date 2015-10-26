/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * CodeLocation.cpp
 *
 *  Created on: Oct 26, 2015
 *      Author: minkwan
 */


#include "CodeLocation.hpp"

namespace OP2A{
namespace Common{



/*
 * This class stores the information about a location in the source code
 */
CodeLocation::CodeLocation(const char * file, int line, const char * function)
 : m_file(file), m_function(function), m_line (line)
{

}



std::string CodeLocation::str () const
{
	std::string place (m_file);
	place += ":";
	place += m_line;

	if (!m_function.empty()) // skip if compiler doees not set function
	{
		place += ":";
		place += m_function;
	}

	return place;
}





}
}

