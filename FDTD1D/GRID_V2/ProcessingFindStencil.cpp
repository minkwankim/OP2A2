/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ProcessingFindStencil.cpp
 *
 *  Created on: Jan 8, 2016
 *      Author: minkwan
 */


#include <omp.h>

#include "Gridv2.hpp"

#include "./COMMON/ExceptionGeneral.hpp"
#include "./COMMON/ErrorCode.hpp"
#include "./MATH/Vector.hpp"
#include "./MATH/Area.hpp"

namespace GRID
{

void Processing_Find_Stencil(c_Grid& grid)
{
	c_Cell* CL;
	c_Cell* CR;
	c_Cell* CLL;
	c_Cell* CRR;

	int dim	= grid.Info.DIM;
	double xfc[dim];
	double normal_vector[dim];


	double max_dot;
	double magnitude_xfc;
	double dot;


	for (int f = 0; f <= grid.Info.NFM-1; f++)
	{
		CL	= grid.Data.faces[f].Specialized.cl;
		CR	= grid.Data.faces[f].Specialized.cr;

		// 1: FIND CLL
		if (CL->geometry.id > 0)
		{
			CLL 	= NULL;
			max_dot = -1.0;

			// GET NORMAL VECTOR TOWARD TO CL
			for (int k = 0; k <= dim-1; k++)	normal_vector[k]	= -grid.Data.faces[f].Specialized.n[0][k];

			// CALCULATE DISTANCE TO CELL-CENTER OF EACH NEIGHBORING CELL
			c_Cell* trial_Cell;
			for (int j = 0; j <= CL->Specialized.Neighbor_List.size()-1; j++)
			{
				trial_Cell = CL->Specialized.Neighbor_List[j];;

				for (int k = 0; k <= dim-1; k++)	xfc[k] = trial_Cell->geometry.x[k] - grid.Data.faces[f].geometry.x[k];

				magnitude_xfc = 0.0;
				for (int k = 0; k <= dim-1; k++)	magnitude_xfc = pow(xfc[k], 2.0);
				magnitude_xfc = sqrt(magnitude_xfc);
				for (int k = 0; k <= dim-1; k++)	xfc[k] /= magnitude_xfc;


				dot = 0.0;
				for (int k = 0; k <= dim-1; k++) dot += normal_vector[k]*xfc[k];

				if (dot > max_dot)
				{
					max_dot = dot;
					CLL = trial_Cell;
				}
			}

			if (CLL == NULL)	CLL	= CL;
		}
		else
		{
			CLL = CL;
		}



		// 2: FIND CRR
		if (CR->geometry.id > 0)
		{
			CRR 	= NULL;
			max_dot = -1.0;

			// GET NORMAL VECTOR TOWARD TO CR
			for (int k = 0; k <= dim-1; k++)	normal_vector[k]	= grid.Data.faces[f].Specialized.n[0][k];

			// CALCULATE DISTANCE TO CELL-CENTER OF EACH NEIGHBORING CELL
			c_Cell* trial_Cell;
			for (int j = 0; j <= CR->Specialized.Neighbor_List.size()-1; j++)
			{
				trial_Cell = CR->Specialized.Neighbor_List[j];;

				for (int k = 0; k <= dim-1; k++)	xfc[k] = trial_Cell->geometry.x[k] - grid.Data.faces[f].geometry.x[k];

				magnitude_xfc = 0.0;
				for (int k = 0; k <= dim-1; k++)	magnitude_xfc = pow(xfc[k], 2.0);
				magnitude_xfc = sqrt(magnitude_xfc);
				for (int k = 0; k <= dim-1; k++)	xfc[k] /= magnitude_xfc;


				dot = 0.0;
				for (int k = 0; k <= dim-1; k++) dot += normal_vector[k]*xfc[k];

				if (dot > max_dot)
				{
					max_dot = dot;
					CRR = trial_Cell;
				}
			}

			if (CRR == NULL)	CRR	= CR;
		}
		else
		{
			CRR = CR;
		}


		grid.Data.faces[f].Specialized.cll	= CLL;
		grid.Data.faces[f].Specialized.crr	= CRR;
	}
}





















}

