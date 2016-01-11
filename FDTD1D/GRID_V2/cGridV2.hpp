/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cGridV2.h
 *
 *  Created on: Jan 6, 2016
 *      Author: minkwan
 */

#ifndef CGRIDV2_H_
#define CGRIDV2_H_


#include "cGridData.hpp"
#include "cGridInfo.hpp"
#include "cGridMapV1.hpp"



namespace GRID {


class c_Grid_v2 {
public:
	c_Grid_v2();
	~c_Grid_v2();


public:
	c_GridData	Data;
	c_GridInfo	Info;
	c_GridMap	Map;


public:
	c_Node& NODE_id(unsigned int id);
	c_Face& FACE_id(unsigned int id);
	c_Cell& CELL_id(int id);

	c_Node& NODE_ijk(unsigned int i, unsigned int j, unsigned int k);
	c_Face& FACE_ijk(unsigned int i, unsigned int j, unsigned int k);
	c_Cell& CELL_ijk(unsigned int i, unsigned int j, unsigned int k);

	c_Node& NODE_ijk(unsigned int i, unsigned int j);
	c_Face& FACE_ijk(unsigned int i, unsigned int j);
	c_Cell& CELL_ijk(unsigned int i, unsigned int j);
};

} /* namespace GRID */

#endif /* CGRIDV2_H_ */
