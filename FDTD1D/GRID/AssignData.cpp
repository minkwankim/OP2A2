/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * AssignData.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: minkwan
 */


#include "./COMMON/Map1D.hpp"
#include "./COMMON/ExceptionGeneral.hpp"
#include "./COMMON/ErrorCode.hpp"

#include "GRID/GridV2.hpp"
#include "GRID/GridFunctions.hpp"


namespace OP2A {
namespace GRID {

void AssignDataNode(c_Grid& grid, const Common::Map1D<std::string, unsigned int>& data_map, const std::vector<double>& data_storage)
{
	grid.Node_Data_Map	= data_map;

	for (int i_n = 0; i_n <= grid.NNM-1; i_n++)	grid.NODE_data(i_n).data	= data_storage;
}


void AssignDataFace(c_Grid& grid, const Common::Map1D<std::string, unsigned int>& data_map, const std::vector<double>& data_storage)
{
	grid.Face_Data_Map	= data_map;

	for (int i_n = 0; i_n <= grid.NFM-1; i_n++)	grid.FACE_data(i_n).data	= data_storage;
}


void AssignDataCell(c_Grid& grid, const Common::Map1D<std::string, unsigned int>& data_map, const std::vector<double>& data_storage)
{
	grid.Cell_Data_Map	= data_map;

	for (int i_n = 0; i_n <= grid.NCM-1; i_n++)	grid.CELL_data(i_n).data	= data_storage;
}






}
}

