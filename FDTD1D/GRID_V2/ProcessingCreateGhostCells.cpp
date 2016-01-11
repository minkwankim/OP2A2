/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ProcessingCreateGhostCells.cpp
 *
 *  Created on: Jan 7, 2016
 *      Author: minkwan
 */

#include <omp.h>

#include "Gridv2.hpp"
#include "./COMMON/ExceptionGeneral.hpp"
#include "./COMMON/ErrorCode.hpp"

namespace GRID
{


void Processing_Create_Ghost_Cells(c_Grid& grid)
{
	// 1. Find number of required ghost cells
	int ngm = 0;
	for (int f = 0; f <= grid.Info.NFM-1; f++)
	{
		if (grid.Data.faces[f].bc_type.bc != notInclude)
		{
			if(grid.Data.faces[f].bc_type.bc != interior)
			{
				ngm++;
			}
			else
			{
				if (grid.Data.faces[f].Specialized.cl == NULL)	ngm++;
				if (grid.Data.faces[f].Specialized.cr == NULL)	ngm++;
			}
		}
	}

	grid.Data.ghosts.resize(ngm);

	int counter = 0;
	for (int f = 0; f <= grid.Info.NFM-1; f++)
	{
		if(grid.Data.faces[f].Specialized.cr == NULL)	// Boundary face: ghost cell
		{
			grid.Data.faces[f].Specialized.cr = &grid.Data.ghosts[counter];


			// Create Ghost cell
			// 1. Geometry data
			grid.Data.ghosts[counter].geometry.id	= -(counter + 1);


			grid.Data.ghosts[counter].Specialized.N_List.resize(grid.Data.faces[f].Specialized.N_List.size());

			for (int n = 0; n <= grid.Data.faces[f].Specialized.N_List.size()-1; n++)
			{
				grid.Data.ghosts[counter].Specialized.N_List[n]	= grid.Data.faces[f].Specialized.N_List[n];
			}

			grid.Data.ghosts[counter].Specialized.F_List.resize(1);
			grid.Data.ghosts[counter].Specialized.F_List[0]	= &grid.Data.faces[f];


			for (int d = 0; d <= grid.Info.DIM-1; d++)
			{
				grid.Data.ghosts[counter].geometry.x[d]	= 2.0*grid.Data.faces[f].geometry.x[d]	- grid.Data.faces[f].Specialized.cl->geometry.x[d];
			}

			grid.Data.ghosts[counter].geometry.S = grid.Data.faces[f].geometry.S;
			grid.Data.ghosts[counter].Specialized.charcteristic_lentgh = grid.Data.ghosts[counter].geometry.S;

			grid.Data.ghosts[counter].geometry.type	= 0;
			grid.Data.ghosts[counter].bc_type.bc	= grid.Data.faces[f].bc_type.bc;
			grid.Data.ghosts[counter].bc_type.type  = -1;

			grid.Map.g_assign_ID_to_pos(counter + 1, counter);

			counter++;
		}
		else if (grid.Data.faces[f].Specialized.cl == NULL)	// Need to swap left and right cell
		{
			grid.Data.faces[f].Specialized.cl = grid.Data.faces[f].Specialized.cr;
			grid.Data.faces[f].Specialized.cr = &grid.Data.ghosts[counter];

			// Create Ghost cell
			// 1. Geometry data
			grid.Data.ghosts[counter].geometry.id	= -(counter + 1);


			grid.Data.ghosts[counter].Specialized.N_List.resize(grid.Data.faces[f].Specialized.N_List.size());

			for (int n = 0; n <= grid.Data.faces[f].Specialized.N_List.size()-1; n++)
			{
				grid.Data.ghosts[counter].Specialized.N_List[n]	= grid.Data.faces[f].Specialized.N_List[n];
			}

			grid.Data.ghosts[counter].Specialized.F_List.resize(1);
			grid.Data.ghosts[counter].Specialized.F_List[0]	= &grid.Data.faces[f];


			for (int d = 0; d <= grid.Info.DIM-1; d++)
			{
				grid.Data.ghosts[counter].geometry.x[d]	= 2.0*grid.Data.faces[f].geometry.x[d]	- grid.Data.faces[f].Specialized.cl->geometry.x[d];
			}

			grid.Data.ghosts[counter].geometry.S = grid.Data.faces[f].geometry.S;
			grid.Data.ghosts[counter].Specialized.charcteristic_lentgh = grid.Data.ghosts[counter].geometry.S;

			grid.Data.ghosts[counter].geometry.type	= 0;
			grid.Data.ghosts[counter].bc_type.bc	= grid.Data.faces[f].bc_type.bc;
			grid.Data.ghosts[counter].bc_type.type  = -1;

			grid.Map.g_assign_ID_to_pos(counter + 1, counter);
			counter++;
		}
	}

	// Error check
	if (counter != ngm)
	{
		OP2A::Common::ExceptionGeneral(FromHere(), "Number of Created ghost-cells does not match with calculated NGM", OP2A::Common::ErrorCode::NotMatchDimention());
	}
	else
	{
		grid.Info.NGM = ngm;
	}
}







}






