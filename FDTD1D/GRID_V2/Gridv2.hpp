/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Gridv2.hpp
 *
 *  Created on: Jan 5, 2016
 *      Author: minkwan
 */

#ifndef GRIDV2_HPP_
#define GRIDV2_HPP_

#include "cCommonElement.hpp"

#include "cNodeV2.hpp"
#include "cFaceV2.hpp"
#include "cCellV2.hpp"
#include "cGridV2.hpp"
#include "GridConfig.hpp"


namespace GRID
{
	void GridGen2D_phaseI_simpleCart(const double X0, const unsigned int Nx, const double Xl, const double Y0, const unsigned int Ny, const double Yl, c_Grid& grid);
	void GridGen2D_simpleCart(const double X0, const unsigned int Nx, const double Xl, const double Y0, const unsigned int Ny, const double Yl, c_Grid& grid, vector<unsigned int>& BCs, const double gridFactor, bool isAxiSymmetric);


	void Processing_Node(c_Grid& grid, double meshFactor, bool isAxisymmetric);
	void Processing_Face(c_Grid& grid);
	void Processing_Cell(c_Grid& grid);
	void Processing_Create_Ghost_Cells(c_Grid& grid);

	void Processing_Calculate_Distance_To_Wall(c_Grid& grid);
	void Processing_Find_Stencil(c_Grid& grid);

	int ShapeFunctionsCircle(const double x, const double y, const double z);


	void GridReadInfo_Fluent(const string& mesh_file_name, c_Grid& grid, vector<int>& bc_zone);
	void GridReadNodes_Fluent(const string& mesh_file_name, c_Grid& grid);
	void GridReadFaces_Fluent(const string& mesh_file_name, c_Grid& grid, vector<int>& bc_zone);
	void GridReadCells_Fluent(const string& mesh_file_name, c_Grid& grid);
	void GridRead_Fluent(const string& mesh_file_name, c_Grid& grid, const double gridFactor, bool isAxiSymmetric);



}


#endif /* GRIDV2_HPP_ */
