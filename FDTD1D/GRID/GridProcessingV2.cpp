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

/*
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
				grid.Node_Data[i_n].x[i_k]	/= gridFactor;
			}
		}
	}


	if (isAxisymmetric == true && grid.DIM == 2)
	{
#pragma ivdep
		for (int i_n = 0; i_n <= grid.NCM-1; i_n++)
		{
			grid.Node_Data[i_n].x[1]	+= CONST_GRID_AXISSYMMETRIC_ADD;
		}
	}



	// FACES
#pragma ivdep
	for (int i_f = 0; i_f <= grid.NFM-1; i_f++)
	{
		// 1. Calculate location of face center
		for (int i_k = 0; i_k <= grid.DIM-1; i_k++)
		{
			grid.Face_Data[i_f].x[i_k]	= 0.0;
			for (int i_n = 0; i_n <= grid.Face_Data[i_f].N_List.size()-1; i_n++)
			{
				grid.Face_Data[i_f].x[i_k] += grid.Face_Data[i_f].N_List[i_n]->x[i_k];
			}
			grid.Face_Data[i_f].x[i_k] /= grid.Face_Data[i_f].N_List.size();

			if (grid.Face_Data[i_f].x[i_k] != grid.Face_Data[i_f].x[i_k])
			{
				Common::ExceptionGeneral(FromHere(), "NaN value for face center location", Common::ErrorCode::NaNValue());
			}

			if (grid.Face_Data[i_f].x[i_k] == numeric_limits<double>::infinity())
			{
				Common::ExceptionGeneral(FromHere(), "Infinite value for face center location", Common::ErrorCode::InfValue());
			}
		}


		// 2. Calculate Area
		switch (grid.DIM)
		{
		case 1:
			grid.Face_Data[i_f].S =  MATH::CalLength(grid.Face_Data[i_f].N_List[0]->x, grid.Face_Data[i_f].N_List[1]->x);
			break;

		case 2:
			grid.Face_Data[i_f].S =  MATH::CalLength(grid.Face_Data[i_f].N_List[0]->x, grid.Face_Data[i_f].N_List[1]->x);
			break;

		case 3:
			grid.Face_Data[i_f].S = MATH::CalAreaQuadrilateral(grid.Face_Data[i_f].N_List[0]->x, grid.Face_Data[i_f].N_List[1]->x, grid.Face_Data[i_f].N_List[2]->x, grid.Face_Data[i_f].N_List[3]->x);
			break;
		}


		// 3. Find directional vectors
		switch (grid.DIM)
		{
			case 1:
				grid.Face_Data[i_f].n[0][0]	= 0.0;
				grid.Face_Data[i_f].n[0][1]	= 1.0;
				grid.Face_Data[i_f].n[0][1]	= 0.0;

				grid.Face_Data[i_f].n[1][0]	= 1.0;
				grid.Face_Data[i_f].n[1][1]	= 0.0;
				grid.Face_Data[i_f].n[1][1]	= 0.0;

				grid.Face_Data[i_f].n[1][0]	= 0.0;
				grid.Face_Data[i_f].n[1][1]	= 0.0;
				grid.Face_Data[i_f].n[1][1]	= 1.0;
				break;

			case 2:
				if (grid.Face_Data[i_f].index.direction == 1)
				{
					grid.Face_Data[i_f].n[0][0]	= 1.0;
					grid.Face_Data[i_f].n[0][1]	= 0.0;
					grid.Face_Data[i_f].n[0][1]	= 0.0;

					grid.Face_Data[i_f].n[1][0]	= 0.0;
					grid.Face_Data[i_f].n[1][1]	= 1.0;
					grid.Face_Data[i_f].n[1][1]	= 0.0;

					grid.Face_Data[i_f].n[1][0]	= 0.0;
					grid.Face_Data[i_f].n[1][1]	= 0.0;
					grid.Face_Data[i_f].n[1][1]	= 0.0;
				}
				else
				{
					grid.Face_Data[i_f].n[0][0]	= 0.0;
					grid.Face_Data[i_f].n[0][1]	= 1.0;
					grid.Face_Data[i_f].n[0][1]	= 0.0;

					grid.Face_Data[i_f].n[1][0]	= 0.0;
					grid.Face_Data[i_f].n[1][1]	= -1.0;
					grid.Face_Data[i_f].n[1][1]	= 0.0;

					grid.Face_Data[i_f].n[1][0]	= 0.0;
					grid.Face_Data[i_f].n[1][1]	= 0.0;
					grid.Face_Data[i_f].n[1][1]	= 0.0;
				}
				break;

			case 3:
				if (grid.Face_Data[i_f].index.direction == 1)
				{
					grid.Face_Data[i_f].n[0][0]	= 1.0;
					grid.Face_Data[i_f].n[0][1]	= 0.0;
					grid.Face_Data[i_f].n[0][1]	= 0.0;

					grid.Face_Data[i_f].n[1][0]	= 0.0;
					grid.Face_Data[i_f].n[1][1]	= 1.0;
					grid.Face_Data[i_f].n[1][1]	= 0.0;

					grid.Face_Data[i_f].n[1][0]	= 0.0;
					grid.Face_Data[i_f].n[1][1]	= 0.0;
					grid.Face_Data[i_f].n[1][1]	= 1.0;
				}
				else if (grid.Face_Data[i_f].index.direction == 2)
				{
					grid.Face_Data[i_f].n[0][0]	= 0.0;
					grid.Face_Data[i_f].n[0][1]	= 1.0;
					grid.Face_Data[i_f].n[0][1]	= 0.0;

					grid.Face_Data[i_f].n[1][0]	= -1.0;
					grid.Face_Data[i_f].n[1][1]	= 0.0;
					grid.Face_Data[i_f].n[1][1]	= 0.0;

					grid.Face_Data[i_f].n[1][0]	= 0.0;
					grid.Face_Data[i_f].n[1][1]	= 0.0;
					grid.Face_Data[i_f].n[1][1]	= 1.0;
				}
				else
				{
					grid.Face_Data[i_f].n[0][0]	= 0.0;
					grid.Face_Data[i_f].n[0][1]	= 0.0;
					grid.Face_Data[i_f].n[0][1]	= 1.0;

					grid.Face_Data[i_f].n[1][0]	= 0.0;
					grid.Face_Data[i_f].n[1][1]	= 1.0;
					grid.Face_Data[i_f].n[1][1]	= 0.0;

					grid.Face_Data[i_f].n[1][0]	= -1.0;
					grid.Face_Data[i_f].n[1][1]	= 0.0;
					grid.Face_Data[i_f].n[1][1]	= 0.0;
				}
				break;
		}
	}



	// Cell
#pragma ivdep
	for (int i_c = 0; i_c <= grid.NCM-1; i_c++)
	{
		// 1. Calculate location of face center
		for (int i_k = 0; i_k <= grid.DIM-1; i_k++)
		{
			grid.Cell_Data[i_c].x[i_k]	= 0.0;	// Initialize value

			for (int i_n = 0; i_n <= grid.Cell_Data[i_c].N_List.size()-1; i_n++)
			{
				grid.Cell_Data[i_c].x[i_k]	+= grid.Cell_Data[i_c].N_List[i_n]->x[i_k];
			}
			grid.Cell_Data[i_c].x[i_k]	/= grid.Cell_Data[i_c].N_List.size();

			if (grid.Cell_Data[i_c].x[i_k] != grid.Cell_Data[i_c].x[i_k])
			{
				Common::ExceptionGeneral(FromHere(), "NaN value for cell center location", Common::ErrorCode::NaNValue());
			}

			if (fabs(grid.Cell_Data[i_c].x[i_k]) == numeric_limits<double>::infinity())
			{
				Common::ExceptionGeneral(FromHere(), "Infinite cell for face center location", Common::ErrorCode::InfValue());
			}
		}


		// 2. Calculate Area
		switch (grid.DIM)
		{
		case 1:
			grid.Cell_Data[i_c].S = MATH::CalLength(grid.Cell_Data[i_c].N_List[0]->x, grid.Cell_Data[i_c].N_List[1]->x);
			break;

		case 2:
			grid.Cell_Data[i_c].S = MATH::CalAreaQuadrilateral(grid.Cell_Data[i_c].N_List[0]->x,
					grid.Cell_Data[i_c].N_List[1]->x,
					grid.Cell_Data[i_c].N_List[2]->x,
					grid.Cell_Data[i_c].N_List[3]->x);
			break;

		case 3:
			grid.Cell_Data[i_c].S	= MATH::CalVolumeHexahedron(grid.Cell_Data[i_c].N_List[0]->x,
					grid.Cell_Data[i_c].N_List[1]->x,
					grid.Cell_Data[i_c].N_List[2]->x,
					grid.Cell_Data[i_c].N_List[3]->x,
					grid.Cell_Data[i_c].N_List[4]->x,
					grid.Cell_Data[i_c].N_List[5]->x,
					grid.Cell_Data[i_c].N_List[6]->x,
					grid.Cell_Data[i_c].N_List[7]->x);
			break;
		}
	}


#pragma ivdep
	for (int i_n = 0; i_n <= grid.NCM-1; i_n++)
	{
		double S_sum = 0.0;
		for (int i_c = 0; i_c <= grid.Node_Data[i_n].C_List.size()-1; i_c++)
		{
			S_sum	+= grid.Node_Data[i_n].C_List[i_c]->S;
		}

		grid.Node_Data[i_n].Wc.resize(grid.Node_Data[i_n].C_List.size());
		for (int i_c = 0; i_c <= grid.Node_Data[i_n].C_List.size()-1; i_c++)
		{
			grid.Node_Data[i_n].Wc[i_c] = grid.Node_Data[i_n].C_List[i_c]->S / S_sum;
		}
	}
}






void GridProcessing_Face_v2(c_Grid& grid, int i_f)
{

	// 1. Calculate location of face center
	for (int i_k = 0; i_k <= grid.DIM-1; i_k++)
	{
		grid.Face_Data[i_f].x[i_k]	= 0.0;
		for (int i_n = 0; i_n <= grid.Face_Data[i_f].N_List.size()-1; i_n++)
		{
			grid.Face_Data[i_f].x[i_k] += grid.Face_Data[i_f].N_List[i_n]->x[i_k];
		}
		grid.Face_Data[i_f].x[i_k] /= grid.Face_Data[i_f].N_List.size();

		if (grid.Face_Data[i_f].x[i_k] != grid.Face_Data[i_f].x[i_k])
		{
			Common::ExceptionGeneral(FromHere(), "NaN value for face center location", Common::ErrorCode::NaNValue());
		}

		if (grid.Face_Data[i_f].x[i_k] == numeric_limits<double>::infinity())
		{
			Common::ExceptionGeneral(FromHere(), "Infinite value for face center location", Common::ErrorCode::InfValue());
		}
	}


	// 2. Calculate Area
	switch (grid.DIM)
	{
	case 1:
		grid.Face_Data[i_f].S =  MATH::CalLength(grid.Face_Data[i_f].N_List[0]->x, grid.Face_Data[i_f].N_List[1]->x);
		break;

	case 2:
		grid.Face_Data[i_f].S =  MATH::CalLength(grid.Face_Data[i_f].N_List[0]->x, grid.Face_Data[i_f].N_List[1]->x);
		break;

	case 3:
		grid.Face_Data[i_f].S = MATH::CalAreaQuadrilateral(grid.Face_Data[i_f].N_List[0]->x, grid.Face_Data[i_f].N_List[1]->x, grid.Face_Data[i_f].N_List[2]->x, grid.Face_Data[i_f].N_List[3]->x);
		break;
	}


	// 3. Find directional vectors
	switch (grid.DIM)
	{
		case 1:
			grid.Face_Data[i_f].n[0][0]	= 0.0;
			grid.Face_Data[i_f].n[0][1]	= 1.0;
			grid.Face_Data[i_f].n[0][1]	= 0.0;

			grid.Face_Data[i_f].n[1][0]	= 1.0;
			grid.Face_Data[i_f].n[1][1]	= 0.0;
			grid.Face_Data[i_f].n[1][1]	= 0.0;

			grid.Face_Data[i_f].n[1][0]	= 0.0;
			grid.Face_Data[i_f].n[1][1]	= 0.0;
			grid.Face_Data[i_f].n[1][1]	= 1.0;
			break;

		case 2:
			if (grid.Face_Data[i_f].index.direction == 1)
			{
				grid.Face_Data[i_f].n[0][0]	= 1.0;
				grid.Face_Data[i_f].n[0][1]	= 0.0;
				grid.Face_Data[i_f].n[0][1]	= 0.0;

				grid.Face_Data[i_f].n[1][0]	= 0.0;
				grid.Face_Data[i_f].n[1][1]	= 1.0;
				grid.Face_Data[i_f].n[1][1]	= 0.0;

				grid.Face_Data[i_f].n[1][0]	= 0.0;
				grid.Face_Data[i_f].n[1][1]	= 0.0;
				grid.Face_Data[i_f].n[1][1]	= 0.0;
			}
			else
			{
				grid.Face_Data[i_f].n[0][0]	= 0.0;
				grid.Face_Data[i_f].n[0][1]	= 1.0;
				grid.Face_Data[i_f].n[0][1]	= 0.0;

				grid.Face_Data[i_f].n[1][0]	= 0.0;
				grid.Face_Data[i_f].n[1][1]	= -1.0;
				grid.Face_Data[i_f].n[1][1]	= 0.0;

				grid.Face_Data[i_f].n[1][0]	= 0.0;
				grid.Face_Data[i_f].n[1][1]	= 0.0;
				grid.Face_Data[i_f].n[1][1]	= 0.0;
			}
			break;

		case 3:
			if (grid.Face_Data[i_f].index.direction == 1)
			{
				grid.Face_Data[i_f].n[0][0]	= 1.0;
				grid.Face_Data[i_f].n[0][1]	= 0.0;
				grid.Face_Data[i_f].n[0][1]	= 0.0;

				grid.Face_Data[i_f].n[1][0]	= 0.0;
				grid.Face_Data[i_f].n[1][1]	= 1.0;
				grid.Face_Data[i_f].n[1][1]	= 0.0;

				grid.Face_Data[i_f].n[1][0]	= 0.0;
				grid.Face_Data[i_f].n[1][1]	= 0.0;
				grid.Face_Data[i_f].n[1][1]	= 1.0;
			}
			else if (grid.Face_Data[i_f].index.direction == 2)
			{
				grid.Face_Data[i_f].n[0][0]	= 0.0;
				grid.Face_Data[i_f].n[0][1]	= 1.0;
				grid.Face_Data[i_f].n[0][1]	= 0.0;

				grid.Face_Data[i_f].n[1][0]	= -1.0;
				grid.Face_Data[i_f].n[1][1]	= 0.0;
				grid.Face_Data[i_f].n[1][1]	= 0.0;

				grid.Face_Data[i_f].n[1][0]	= 0.0;
				grid.Face_Data[i_f].n[1][1]	= 0.0;
				grid.Face_Data[i_f].n[1][1]	= 1.0;
			}
			else
			{
				grid.Face_Data[i_f].n[0][0]	= 0.0;
				grid.Face_Data[i_f].n[0][1]	= 0.0;
				grid.Face_Data[i_f].n[0][1]	= 1.0;

				grid.Face_Data[i_f].n[1][0]	= 0.0;
				grid.Face_Data[i_f].n[1][1]	= 1.0;
				grid.Face_Data[i_f].n[1][1]	= 0.0;

				grid.Face_Data[i_f].n[1][0]	= -1.0;
				grid.Face_Data[i_f].n[1][1]	= 0.0;
				grid.Face_Data[i_f].n[1][1]	= 0.0;
			}
			break;
	}
}




void GridProcessing_Cell_v2(c_Grid& grid, int i_c)
{
	// 1. Calculate location of face center
	for (int i_k = 0; i_k <= grid.DIM-1; i_k++)
	{
		grid.Cell_Data[i_c].x[i_k]	= 0.0;	// Initialize value

		for (int i_n = 0; i_n <= grid.Cell_Data[i_c].N_List.size()-1; i_n++)
		{
			grid.Cell_Data[i_c].x[i_k]	+= grid.Cell_Data[i_c].N_List[i_n]->x[i_k];
		}
		grid.Cell_Data[i_c].x[i_k]	/= grid.Cell_Data[i_c].N_List.size();

		if (grid.Cell_Data[i_c].x[i_k] != grid.Cell_Data[i_c].x[i_k])
		{
			Common::ExceptionGeneral(FromHere(), "NaN value for cell center location", Common::ErrorCode::NaNValue());
		}

		if (fabs(grid.Cell_Data[i_c].x[i_k]) == numeric_limits<double>::infinity())
		{
			Common::ExceptionGeneral(FromHere(), "Infinite cell for face center location", Common::ErrorCode::InfValue());
		}
	}


	// 2. Calculate Area
	switch (grid.DIM)
	{
	case 1:
		grid.Cell_Data[i_c].S = MATH::CalLength(grid.Cell_Data[i_c].N_List[0]->x, grid.Cell_Data[i_c].N_List[1]->x);
		break;

	case 2:
		grid.Cell_Data[i_c].S = MATH::CalAreaQuadrilateral(grid.Cell_Data[i_c].N_List[0]->x,
				grid.Cell_Data[i_c].N_List[1]->x,
				grid.Cell_Data[i_c].N_List[2]->x,
				grid.Cell_Data[i_c].N_List[3]->x);
		break;

	case 3:
		grid.Cell_Data[i_c].S	= MATH::CalVolumeHexahedron(grid.Cell_Data[i_c].N_List[0]->x,
				grid.Cell_Data[i_c].N_List[1]->x,
				grid.Cell_Data[i_c].N_List[2]->x,
				grid.Cell_Data[i_c].N_List[3]->x,
				grid.Cell_Data[i_c].N_List[4]->x,
				grid.Cell_Data[i_c].N_List[5]->x,
				grid.Cell_Data[i_c].N_List[6]->x,
				grid.Cell_Data[i_c].N_List[7]->x);
		break;
	}
}






*/


}
}
