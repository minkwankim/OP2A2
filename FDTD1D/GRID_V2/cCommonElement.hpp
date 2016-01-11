/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cCommomElement.hpp
 *
 *  Created on: Jan 5, 2016
 *      Author: minkwan
 */

#ifndef CCOMMOMELEMENT_HPP_
#define CCOMMOMELEMENT_HPP_


#include "./COMMON/Common.hpp"
#include "cBC.hpp"
#include "cGeometry.hpp"

using namespace std;


namespace GRID {

class c_CommonElement {
public:
	c_CommonElement();
	explicit c_CommonElement(unsigned int i_minDataSize);

	~c_CommonElement();

public:
	c_Geometry		geometry;
	c_BC			bc_type;
	vector<double>	data;
};

} /* namespace GRID */

#endif /* CCOMMOMELEMENT_HPP_ */
