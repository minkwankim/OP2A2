/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cCommomElement.cpp
 *
 *  Created on: Jan 5, 2016
 *      Author: minkwan
 */

#include <GRID_V2/cCommonElement.hpp>
#include <GRID_V2/GridConfig.hpp>


namespace GRID {

c_CommonElement::c_CommonElement()
{
	data.reserve(CONST_GRID_DEFAULT_DATA_SIZE);
}

c_CommonElement::c_CommonElement(unsigned int i_minDataSize):data(i_minDataSize)
{


}

c_CommonElement::~c_CommonElement()
{
	// TODO Auto-generated destructor stub
}

} /* namespace GRID */
