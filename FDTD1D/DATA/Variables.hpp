/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Variables.hpp
 *
 *  Created on: Dec 10, 2015
 *      Author: minkwan
 */

#ifndef VARIABLES_HPP_
#define VARIABLES_HPP_



#include "COMMON/Map1D.hpp"
#include "COMMON/Common.hpp"
#include "DATA/Nomenclatures.hpp"

namespace OP2A{
namespace DATA{

// FDTD Simulation
void VariableTMz_face(Common::Map1D<std::string, unsigned int>& data_map, std::vector<double>& data_storage);
void VariableTMz_node(Common::Map1D<std::string, unsigned int>& data_map, std::vector<double>& data_storage);
void VariableTMz_cell(Common::Map1D<std::string, unsigned int>& data_map, std::vector<double>& data_storage);



}
}



#endif /* VARIABLES_HPP_ */
