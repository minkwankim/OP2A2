/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * CreateGhostCell.cpp
 *
 *  Created on: Dec 8, 2015
 *      Author: minkwan
 */



#include "./COMMON/VectorPointer.hpp"
#include "./COMMON/ExceptionGeneral.hpp"
#include "./COMMON/ErrorCode.hpp"

#include "GRID/GridV2.hpp"
#include "GRID/GridFunctions.hpp"


namespace OP2A {
namespace GRID {



// Direction:	0 - LEFT
//				1 - RIGHT

void CreateGhostCell(c_Grid& grid, c_Face& face, unsigned int direction)
{
	GRID::c_Cell	ghost;
	GRID::c_Cell*	cell;

	if (direction == 0)	cell	= face.CR;
	if (direction == 1) cell	= face.CL;

	if (cell == NULL)
	{
		Common::ExceptionGeneral(FromHere(), "[CreateGhost]: Problem in stencil. Please check stencil of face", Common::ErrorCode::NotAllocated());
	}

	ghost.index.i	= 2.0*face.index.i - cell->index.i;
	ghost.index.j	= 2.0*face.index.j - cell->index.j;
	ghost.index.k	= 2.0*face.index.k - cell->index.k;
	ghost.index.location = cell->index.location;
	ghost.index.lvl_refine = face.index.lvl_refine;

	ghost.N_List.resize(face.N_List.size());
	for (int n = 0; n <= face.N_List.size()-1; n++)
	{
		ghost.N_List[n]	= face.N_List[n];
	}

	ghost.F_List.resize(1);
	ghost.F_List[0]	= &face;

	ghost.Parent	= NULL;
	ghost.has_Child	= false;
	ghost.type		= -2;
	ghost.BC		= face.BC;

	ghost.x[0]	= 2.0*face.x[0] - cell->x[0];
	ghost.x[1]	= 2.0*face.x[1] - cell->x[1];
	ghost.x[2]	= 2.0*face.x[2] - cell->x[2];

	ghost.S	= face.S;

	grid.GHOST_add(ghost);
	if (direction == 0)	face.CL	= &grid.GHOST_data(grid.NGM-1);
	if (direction == 1) face.CR	= &grid.GHOST_data(grid.NGM-1);
}

}
}

