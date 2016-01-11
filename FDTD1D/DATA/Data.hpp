/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Data.hpp
 *
 *  Created on: Jan 11, 2016
 *      Author: minkwan
 */

#ifndef DATA_HPP_
#define DATA_HPP_


#include "cDataV2.hpp"

namespace DATA
{
#define c_Data		c_Data_v2


namespace NONEQ_CFD
{
	c_Data	dataSampleCell(unsigned int NS, unsigned int DIM, unsigned NE);

}

namespace FDTD
{

}


namespace NONEQ_PIC
{

}




}




#endif /* DATA_HPP_ */
