/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cBC.hpp
 *
 *  Created on: Jan 5, 2016
 *      Author: minkwan
 */

#ifndef CBC_HPP_
#define CBC_HPP_

namespace GRID {

enum BCType
{
	notInclude		= -1,
	interior		= 0,
	wall			= 1,
	inlet			= 2,
	outlet			= 3,
	freestream		= 4,
	symmetric		= 5,
	axis			= 6,
	anode			= 7,
	cathode			= 8,
	dielectricwall	= 9
};

enum GridType
{
	outside_domain = -1,
	edge_domain	   = 0,
	inside_domain  = 1,
	partial_inside_domain = 2
};

bool isWallType(int bctype);









class c_BC {
public:
	c_BC():bc(-1), type(-1)	{	};
	~c_BC()	{	};

public:
	int bc;
	int type;
};

} /* namespace GRID */

#endif /* CBC_HPP_ */
