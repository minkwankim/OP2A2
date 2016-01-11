/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cGridData.hpp
 *
 *  Created on: Jan 6, 2016
 *      Author: minkwan
 */

#ifndef CGRIDDATA_HPP_
#define CGRIDDATA_HPP_

#include "GridConfig.hpp"
#include "cNodeV2.hpp"
#include "cFaceV2.hpp"
#include "cCellV2.hpp"


namespace GRID {

class c_GridData {
public:
	c_GridData();
	~c_GridData();


public:
	vector<c_Node>	nodes;
	vector<c_Face>	faces;
	vector<c_Cell>	cells;
	vector<c_Cell>	ghosts;

};

} /* namespace GRID */

#endif /* CGRIDDATA_HPP_ */
