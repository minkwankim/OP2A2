/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * TecplotData.hpp
 *
 *  Created on: Oct 30, 2015
 *      Author: minkwan
 */

#ifndef TECPLOTDATA_HPP_
#define TECPLOTDATA_HPP_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

#include "./COMMON/Common.hpp"
#include "./COMMON/Array1D.hpp"


namespace OP2A{
namespace IO{

void TecplotDataWritePoint(std::vector <OP2A::Common::Array1D<double> > & data, int num, int var);
void TecplotDataWriteBlock(std::vector <OP2A::Common::Array1D<double> > & data, int num, int var);


}
}




#endif /* TECPLOTDATA_HPP_ */
