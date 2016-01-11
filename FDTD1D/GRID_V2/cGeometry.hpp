/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cGeometry.hpp
 *
 *  Created on: Jan 5, 2016
 *      Author: minkwan
 */

#ifndef CGEOMETRY_HPP_
#define CGEOMETRY_HPP_

namespace GRID {

class c_Geometry {
public:
	c_Geometry():id(0), S(0.0), type(0)
	{
		x[0]	= 0.0;
		x[1]	= 0.0;
		x[2]	= 0.0;
	}

	~c_Geometry(){	};

	int 	id;
	double 	x[3];
	double	S;

	unsigned int type;
};

} /* namespace GRID */

#endif /* CGEOMETRY_HPP_ */
