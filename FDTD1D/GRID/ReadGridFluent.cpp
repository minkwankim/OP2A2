/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ReadGridFluent.cpp
 *
 *  Created on: Nov 16, 2015
 *      Author: minkwan
 */


#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>



#include "./GRID/ReadGrid.hpp"
#include "./GRID/GridReadIndex.hpp"


using namespace std;
namespace OP2A{

void ReadGridFluent(const  std::string& mesh_file_name, Grid<GRID::Node, GRID::Face, GRID::Cell, GRID::Cell>& grid)
{
	ReadGridInfoFluent(mesh_file_name, grid.config, grid.accessBCzone());

	ReadGridNodeFluent(mesh_file_name, grid.config, grid.nodes, grid.whereisNode);

	ReadGridCellFluent(mesh_file_name, grid.config, grid.cells, grid.whereisCell);

	ReadGridFaceFluent(mesh_file_name, grid.config, grid.nodes, grid.whereisNode, grid.faces, grid.whereisFace, grid.cells, grid.whereisCell, grid.accessBCzone());
}








}
