/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GridProcessingV2.cpp
 *
 *  Created on: Dec 2, 2015
 *      Author: minkwan
 */


#include <omp.h>
#include <limits>

#include "COMMON/VectorPointer.hpp"
#include "COMMON/TypeConversion.hpp"
#include "COMMON/ErrorCode.hpp"


#include "GRID/GridV2.hpp"
#include "GRID/GridFunctions.hpp"

#include "MATH/Area.hpp"
#include "MATH/Vector.hpp"



namespace OP2A {
namespace GRID {


void GridProcessing_v2(const double gridFactor, bool isAxisymmetric, c_Grid& grid)
{
	// Nodes
	if (gridFactor != 1.0)
	{
#pragma ivdep
		for (int i_n = 0; i_n <= grid.NCM-1; i_n++)
		{
			for (int i_k = 0; i_k <= grid.DIM-1; i_k++)
			{
				grid.NODE_data(i_n).x[i_k]	/= gridFactor;
			}
		}
	}


	if (isAxisymmetric == true && grid.DIM == 2)
	{
#pragma ivdep
		for (int i_n = 0; i_n <= grid.NCM-1; i_n++)
		{
			grid.NODE_data(i_n).x[1]	+= CONST_GRID_AXISSYMMETRIC_ADD;
		}
	}



	// FACES
#pragma ivdep
	for (int i_f = 0; i_f <= grid.NFM-1; i_f++)
	{
		GRID::GridProcessing_Face_v2(grid.FACE_data(i_f), grid.DIM);
	}


	// Cell
#pragma ivdep
	for (int i_c = 0; i_c <= grid.NCM-1; i_c++)
	{
		GRID::GridProcessing_Cell_v2(grid.CELL_data(i_c), grid.DIM);
	}


#pragma ivdep
	for (int i_n = 0; i_n <= grid.NNM-1; i_n++)
	{
		GRID::GridProcessing_Node_v2(grid.NODE_data(i_n), grid.DIM);
	}
}


void GridProcessing_Node_v2(c_Node& node, unsigned int DIM)
{
	double S = 0.0;
	double x;
	for (int n = 0; n <= node.C_List.size()-1; n++)
	{
		x = MATH::CalLength(node.x, node.C_List[n]->x);

		if (node.C_List[n]->type != -2)	S	+= node.C_List[n]->S;
	}

	node.Wc.resize(node.C_List.size());
	for (int n = 0; n <= node.C_List.size()-1; n++)
	{
		if (node.C_List[n]->type != -2)	node.Wc[n] = node.C_List[n]->S / S;
		else							node.Wc[n] = 0.0;
	}
}




void GridProcessing_Face_v2(c_Face& face, unsigned int DIM)
{
	// 1. Calculate location of face center
	for (int i_k = 0; i_k <= DIM-1; i_k++)
	{
		face.x[i_k]	= 0.0;
		for (int i_n = 0; i_n <= face.N_List.size()-1; i_n++)
		{
			face.x[i_k] += face.N_List[i_n]->x[i_k];
		}
		face.x[i_k] /= face.N_List.size();

		if (face.x[i_k] != face.x[i_k])
		{
			Common::ExceptionGeneral(FromHere(), "NaN value for face center location", Common::ErrorCode::NaNValue());
		}

		if (face.x[i_k] == numeric_limits<double>::infinity())
		{
			Common::ExceptionGeneral(FromHere(), "Infinite value for face center location", Common::ErrorCode::InfValue());
		}
	}


	// 2. Calculate Area
	switch (DIM)
	{
	case 1:
		face.S = MATH::CalLength(face.N_List[0]->x, face.N_List[1]->x);
		break;

	case 2:
		face.S = MATH::CalLength(face.N_List[0]->x, face.N_List[1]->x);
		break;

	case 3:
		face.S = MATH::CalAreaQuadrilateral(face.N_List[0]->x, face.N_List[1]->x, face.N_List[2]->x, face.N_List[3]->x);
		break;
	}


	// 3. Find directional vectors
	switch (DIM)
	{
		case 1:
			face.n[0][0]	= 0.0;
			face.n[0][1]	= 1.0;
			face.n[0][1]	= 0.0;

			face.n[1][0]	= 1.0;
			face.n[1][1]	= 0.0;
			face.n[1][1]	= 0.0;

			face.n[1][0]	= 0.0;
			face.n[1][1]	= 0.0;
			face.n[1][1]	= 1.0;
			break;

		case 2:
			if (face.index.direction == 1)
			{
				face.n[0][0]	= 1.0;
				face.n[0][1]	= 0.0;
				face.n[0][1]	= 0.0;

				face.n[1][0]	= 0.0;
				face.n[1][1]	= 1.0;
				face.n[1][1]	= 0.0;

				face.n[1][0]	= 0.0;
				face.n[1][1]	= 0.0;
				face.n[1][1]	= 0.0;
			}
			else
			{
				face.n[0][0]	= 0.0;
				face.n[0][1]	= 1.0;
				face.n[0][1]	= 0.0;

				face.n[1][0]	= 0.0;
				face.n[1][1]	= -1.0;
				face.n[1][1]	= 0.0;

				face.n[1][0]	= 0.0;
				face.n[1][1]	= 0.0;
				face.n[1][1]	= 0.0;
			}
			break;

		case 3:
			if (face.index.direction == 1)
			{
				face.n[0][0]	= 1.0;
				face.n[0][1]	= 0.0;
				face.n[0][1]	= 0.0;

				face.n[1][0]	= 0.0;
				face.n[1][1]	= 1.0;
				face.n[1][1]	= 0.0;

				face.n[1][0]	= 0.0;
				face.n[1][1]	= 0.0;
				face.n[1][1]	= 1.0;
			}
			else if (face.index.direction == 2)
			{
				face.n[0][0]	= 0.0;
				face.n[0][1]	= 1.0;
				face.n[0][1]	= 0.0;

				face.n[1][0]	= -1.0;
				face.n[1][1]	= 0.0;
				face.n[1][1]	= 0.0;

				face.n[1][0]	= 0.0;
				face.n[1][1]	= 0.0;
				face.n[1][1]	= 1.0;
			}
			else
			{
				face.n[0][0]	= 0.0;
				face.n[0][1]	= 0.0;
				face.n[0][1]	= 1.0;

				face.n[1][0]	= 0.0;
				face.n[1][1]	= 1.0;
				face.n[1][1]	= 0.0;

				face.n[1][0]	= -1.0;
				face.n[1][1]	= 0.0;
				face.n[1][1]	= 0.0;
			}
			break;
	}
}




void GridProcessing_Cell_v2(c_Cell& cell, unsigned int DIM)
{
	// 1. Calculate location of face center
	for (int i_k = 0; i_k <= DIM-1; i_k++)
	{
		cell.x[i_k]	= 0.0;	// Initialize value

		for (int i_n = 0; i_n <= cell.N_List.size()-1; i_n++)
		{
			cell.x[i_k]	+= cell.N_List[i_n]->x[i_k];
		}
		cell.x[i_k]	/= cell.N_List.size();

		if (cell.x[i_k] != cell.x[i_k])
		{
			Common::ExceptionGeneral(FromHere(), "NaN value for cell center location", Common::ErrorCode::NaNValue());
		}

		if (fabs(cell.x[i_k]) == numeric_limits<double>::infinity())
		{
			Common::ExceptionGeneral(FromHere(), "Infinite cell for face center location", Common::ErrorCode::InfValue());
		}
	}


	// 2. Calculate Area
	switch (DIM)
	{
	case 1:
		cell.S = MATH::CalLength(cell.N_List[0]->x, cell.N_List[1]->x);
		break;

	case 2:
		cell.S = MATH::CalAreaQuadrilateral(cell.N_List[0]->x,
											cell.N_List[1]->x,
											cell.N_List[2]->x,
											cell.N_List[3]->x);
		break;

	case 3:
		cell.S	= MATH::CalVolumeHexahedron(cell.N_List[0]->x,
											cell.N_List[1]->x,
											cell.N_List[2]->x,
											cell.N_List[3]->x,
											cell.N_List[4]->x,
											cell.N_List[5]->x,
											cell.N_List[6]->x,
											cell.N_List[7]->x);
		break;
	}
}



}
}
