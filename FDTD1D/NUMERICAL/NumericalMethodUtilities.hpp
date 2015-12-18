/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * NumericalMethodUtilities.hpp
 *
 *  Created on: Dec 10, 2015
 *      Author: minkwan
 */

#ifndef NUMERICALMETHODUTILITIES_HPP_
#define NUMERICALMETHODUTILITIES_HPP_


#include "GRID/GridV2.hpp"

using namespace std;

namespace OP2A {


void GetNodeVariables(GRID::c_Grid& grid, const std::vector<unsigned int>& variableFlagCell, const std::vector<unsigned int>& variableFlagNode, unsigned int method);

}





#endif /* NUMERICALMETHODUTILITIES_HPP_ */
