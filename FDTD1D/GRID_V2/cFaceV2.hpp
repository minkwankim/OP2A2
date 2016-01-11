/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cFacev2.hpp
 *
 *  Created on: Jan 5, 2016
 *      Author: minkwan
 */

#ifndef CFACEV2_HPP_
#define CFACEV2_HPP_

#include "cCommonElement.hpp"
#include "GridConfig.hpp"

namespace GRID {


class c_Node;
class c_Cell;


enum FaceType
{
	f_ghost			= 0,
	f_line			= 2,
	f_triangle		= 3,
	f_quadrilateral	= 4
};



class c_FaceSpecial
{
public:
	c_FaceSpecial() : distWall(0.0), nDotWall(0.0)
	{
		N_List.reserve(4);

		cl	= NULL;
		cll	= NULL;
		cr	= NULL;
		crr	= NULL;
	};

	~c_FaceSpecial()
	{

	};

public:
	std::vector<c_Node*>	N_List;

	c_Cell*	cl;
	c_Cell*	cll;

	c_Cell*	cr;
	c_Cell*	crr;

	double n[3][3];
	double distWall;	// distance to wall
	double nDotWall;	// dot product between normal vector and wall vector
};







class c_Face_v2 : public c_CommonElement
{
public:
	c_Face_v2();
	~c_Face_v2();

public:
	c_FaceSpecial Specialized;

public:
	void CheckError();
};

} /* namespace GRID */

#endif /* CFACEV2_HPP_ */
