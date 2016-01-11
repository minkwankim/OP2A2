/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cCellV2.hpp
 *
 *  Created on: Jan 5, 2016
 *      Author: minkwan
 */

#ifndef CCELLV2_HPP_
#define CCELLV2_HPP_

#include "cCommonElement.hpp"
#include "GridConfig.hpp"


namespace GRID {


class c_Node;
class c_Face;
class c_Cell;



enum CellType
{
	c_ghost			= 0,
	c_triangle		= 1,
	c_tetrahedron	= 2,
	c_quadrilateral	= 3,
	c_hexahedron	= 4,
	c_pyramid		= 5,
	c_prism			= 6
};


class c_CellSpecial
{
public:
	c_CellSpecial():charcteristic_lentgh(0.0), lineID(-1), distWall(0.0)
	{
		N_List.reserve(8);
		F_List.reserve(12);
	};

	~c_CellSpecial()
	{

	};

public:
	std::vector<c_Node*>	N_List;
	std::vector<c_Face*>	F_List;
	std::vector<c_Cell*>	Neighbor_List;
	double charcteristic_lentgh;
	double distWall;	// distance to wall
	int lineID;
};




class c_Cell_v2 : public c_CommonElement
{
public:
	c_Cell_v2();
	~c_Cell_v2();

public:
	c_CellSpecial Specialized;


public:
	void CheckError();

};

} /* namespace GRID */

#endif /* CCELLV2_HPP_ */
