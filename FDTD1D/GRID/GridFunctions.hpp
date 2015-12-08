/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GridFunctions.hpp
 *
 *  Created on: Dec 1, 2015
 *      Author: minkwan
 */

#ifndef GRIDFUNCTIONS_HPP_
#define GRIDFUNCTIONS_HPP_


#include "GRID/GridV2.hpp"

namespace OP2A {
namespace GRID {

int GridShapeFunctions(const double x, const double y, const double z);
int GridShapeFunctions(const double x, const double y);

void GridGen2D_v1(const double X0, const unsigned int Nx, const double Xl,
				const double Y0, const unsigned int Ny, const double Yl,
				const double gridFactor, bool axysymmetric,
				c_Grid& grid2D);


void GridProcessing_v2(const double gridFactor, bool isAxisymmetric, c_Grid& grid);
void GridProcessing_Node_v2(c_Node& node, unsigned int DIM);
void GridProcessing_Face_v2(c_Face& face, unsigned int DIM);
void GridProcessing_Cell_v2(c_Cell& cell, unsigned int DIM);


void CreateGhostCell(c_Grid& grid, c_Face& face, unsigned int direction);



void GridSetRefiningFlagGeometry(c_Grid& grid);
void GridSetRefiniement(c_Grid& grid);
void GridRefiner2D_v1(c_Grid& grid, int c);



}
}



#endif /* GRIDFUNCTIONS_HPP_ */
