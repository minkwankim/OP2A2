/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ReadGrid.hpp
 *
 *  Created on: Nov 16, 2015
 *      Author: minkwan
 */

#ifndef READGRID_HPP_
#define READGRID_HPP_



#include <typeinfo>
#include "./GRID/Grid.hpp"



namespace OP2A{

/*
 * ================================================================================
 * 		READ Basic grid information from grid file
 * ================================================================================
 */
void ReadGridInfo(const  std::string& mesh_file_name, OP2A::GRID::Configuration& config, std::vector<int>& bc_zone, int type);

void ReadGridInfoFluent(const std::string& mesh_file_name,		// Mesh file name
						OP2A::GRID::Configuration&	config,		// Grid Configuration
						std::vector<int>& bc_zone);				// BC Information

void ReadGridNode(const  std::string& mesh_file_name, const OP2A::GRID::Configuration&	config, vector<GRID::Node>& nodes,  vector<int>& whereis, int type);
void ReadGridNodeFluent(const  std::string& mesh_file_name, const OP2A::GRID::Configuration&	config, vector<GRID::Node>& nodes, vector<int>& whereis);


void ReadGridFace(const  std::string& mesh_file_name, const OP2A::GRID::Configuration& config,
				vector<GRID::Node>& nodes, const vector<int>& whereisNode,
				vector<GRID::Face>& faces, 	     vector<int>& whereisFace,
				vector<GRID::Cell>& cells, const vector<int>& whereisCell,
				const vector<int>& bc_zone, int type);
void ReadGridFaceFluent(const  std::string& mesh_file_name, const OP2A::GRID::Configuration& config,
						vector<GRID::Node>& nodes, const vector<int>& whereisNode,
						vector<GRID::Face>& faces, 	     vector<int>& whereisFace,
						vector<GRID::Cell>& cells, const vector<int>& whereisCell,
						const vector<int>& bc_zone);

void ReadGridCell(const  std::string& mesh_file_name, const OP2A::GRID::Configuration& config,
				vector<GRID::Cell>& cells, vector<int>& whereisCell, int type);
void ReadGridCellFluent(const  std::string& mesh_file_name, const OP2A::GRID::Configuration& config,
						vector<GRID::Cell>& cells, vector<int>& whereisCell);

void ReadGridFluent(const  std::string& mesh_file_name, Grid<GRID::Node, GRID::Face, GRID::Cell, GRID::Cell>& grid);


}

#endif /* READGRID_HPP_ */
