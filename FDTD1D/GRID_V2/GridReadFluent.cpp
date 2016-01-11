/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GridReadFluent.cpp
 *
 *  Created on: Jan 11, 2016
 *      Author: minkwan
 */


#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string.h>

#include "Gridv2.hpp"
#include "GridReadConfig.hpp"

#include "./COMMON/ExceptionGeneral.hpp"
#include "./COMMON/ErrorCode.hpp"

using namespace std;

namespace GRID {

void GridRead_Fluent(const string& mesh_file_name, c_Grid& grid, const double gridFactor, bool isAxiSymmetric)
{
	vector<int> bc_zone;

	GridReadInfo_Fluent(mesh_file_name, grid, bc_zone);

	GridReadNodes_Fluent(mesh_file_name, grid);
	GridReadCells_Fluent(mesh_file_name, grid);
	GridReadFaces_Fluent(mesh_file_name, grid, bc_zone);


	GRID::Processing_Node(grid, gridFactor, isAxiSymmetric);
	GRID::Processing_Face(grid);
	GRID::Processing_Cell(grid);
	GRID::Processing_Create_Ghost_Cells(grid);
	GRID::Processing_Calculate_Distance_To_Wall(grid);
	GRID::Processing_Find_Stencil(grid);
}





}
