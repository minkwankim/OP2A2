/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GeometryFace.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: minkwan
 */

#include <GRID/GeometryFace.hpp>


namespace OP2A{
namespace GRID{

GeometryFace::GeometryFace()
{
	n[0][0]	= 0.0;
	n[0][1]	= 0.0;
	n[0][2]	= 0.0;

	n[1][0]	= 0.0;
	n[1][1]	= 0.0;
	n[1][2]	= 0.0;

	n[2][0]	= 0.0;
	n[2][1]	= 0.0;
	n[2][2]	= 0.0;

	distWall	= 0.0;
	nDotWall	= 0.0;
}

GeometryFace::~GeometryFace() {
	// TODO Auto-generated destructor stub
}



}
}
