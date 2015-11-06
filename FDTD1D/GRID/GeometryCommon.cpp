/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GeometryCommon.cpp
 *
 *  Created on: Nov 4, 2015
 *      Author: minkwan
 */

#include <GRID/GeometryCommon.hpp>


namespace OP2A{
namespace GRID{


/*
 * I. Constructor and Destructor
 */
GeometryCommon::GeometryCommon():ID(-1), S(0), type(-1), BC(-1)
{
	x[0]	= 0.0;
	x[1]	= 0.0;
	x[2]	= 0.0;
}

GeometryCommon::~GeometryCommon()
{

}



/*
 * III. Member Functions
 */

}
}
