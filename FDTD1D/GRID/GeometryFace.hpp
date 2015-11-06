/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GeometryFace.hpp
 *
 *  Created on: Nov 5, 2015
 *      Author: minkwan
 */

#ifndef GEOMETRYFACE_HPP_
#define GEOMETRYFACE_HPP_


#include "GeometryCommon.hpp"

namespace OP2A{
namespace GRID{

class GeometryFace:public GeometryCommon
{

	/*
	 * I. Constructor and Destructor
	 */
public:
	GeometryFace();
	~GeometryFace();


	/*
	 * II. Member Variables
	 */
public:
	double n[3][3];		// Normal vector [normal/tangential/tangential2][direction]
	double	distWall;	// distance to wall
	double	nDotWall;	// dot product between normal vector and wall vector



	/*
	 * III. Member Functions
	 */
public:


};

}
}

#endif /* GEOMETRYFACE_HPP_ */
