/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cBc.cpp
 *
 *  Created on: Jan 8, 2016
 *      Author: minkwan
 */



#include "./COMMON/ErrorCode.hpp"
#include "./COMMON/ExceptionGeneral.hpp"

#include <GRID_V2/cBC.hpp>

namespace GRID {



bool isWallType(int bctype)
{
	if (bctype == wall ||
		bctype == anode ||
		bctype == cathode ||
		bctype == dielectricwall)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}





}
