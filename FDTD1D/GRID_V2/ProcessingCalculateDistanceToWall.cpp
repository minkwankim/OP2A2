/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ProcessingCalculateDistanceToWall.cpp
 *
 *  Created on: Jan 7, 2016
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


void Processing_Calculate_Distance_To_Wall(c_Grid& grid)
{
	// 1. Initizlize variables
	vector<unsigned int> walkBound(grid.Map.c_ID_to_pos.size(), 0);			// Walk bound of cell ID
	vector<c_Face*>		nearWallFace(grid.Map.c_ID_to_pos.size(), NULL);	// Near wall face of cell ID
	for (int c = 0; c <= grid.Info.NCM-1; c++) grid.Data.cells[c].Specialized.distWall	= 1.E10;


	// 2. Calculate distance of 1st Wall layer
	int	num_WallFaces	= 0;
	int	num_WalkCells	= 0;

	for (int g = 0; g <= grid.Info.NGM-1; g++)
	{
		if (isWallType(grid.Data.ghosts[g].bc_type.bc))
		{
			num_WallFaces++;

			c_Face* wallFace = grid.Data.ghosts[g].Specialized.F_List[0];
			c_Cell*	firstLayerCell = wallFace->Specialized.cl;

			if (firstLayerCell->geometry.id > 0)
			{
				walkBound[firstLayerCell->geometry.id] = 1;
				nearWallFace[firstLayerCell->geometry.id] = wallFace;
				num_WalkCells++;

				firstLayerCell->Specialized.distWall = OP2A::MATH::CalLength(firstLayerCell->geometry.x, wallFace->geometry.x);
			}
			else
			{
				std::ostringstream error_message;
				error_message << "Face ID:" << wallFace->geometry.id << " has problem in stencil. CL cannot be ghost";
				OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NotSupportedType());
			}
		}
	}



	// 2. Calculate path
	int num_Pass = 0;
	c_Face* curr_Face;
	c_Cell*	test_Cell;

	while (num_WalkCells > 0 && num_Pass <= CONST_GRID_MAX_NUM_PATH)
	{
		num_Pass++;
		num_WalkCells	= 0;	// Initialize number of walk cells

		for (int c = 0; c <= grid.Info.NCM-1; c++)
		{
			if (walkBound[grid.Data.cells[c].geometry.id] == num_Pass)
			{
				for (int f = 0; f <= grid.Data.cells[c].Specialized.F_List.size()-1; f++)
				{
					curr_Face = grid.Data.cells[c].Specialized.F_List[f];

					// Find test cell
					if (curr_Face->Specialized.cl != &grid.Data.cells[c])	test_Cell = curr_Face->Specialized.cl;
					else													test_Cell = curr_Face->Specialized.cr;

					// Only for inner cell(Not ghost cells)
					if (test_Cell->geometry.id > 0)
					{
						if (walkBound[test_Cell->geometry.id] != 1)	// Not for the first laye of walls
						{
							if (nearWallFace[test_Cell->geometry.id] == NULL)	// Case: Near wall face is not allocated
							{
								nearWallFace[test_Cell->geometry.id]	= curr_Face;
								walkBound[test_Cell->geometry.id]		= num_Pass + 1;
								num_WalkCells++;

								test_Cell->Specialized.distWall = OP2A::MATH::CalLength(test_Cell->geometry.x, curr_Face->geometry.x);
							}
							else if (nearWallFace[test_Cell->geometry.id] != nearWallFace[grid.Data.cells[c].geometry.id])
							{
								double dist = OP2A::MATH::CalLength(test_Cell->geometry.x, nearWallFace[grid.Data.cells[c].geometry.id]->geometry.x);

								if (dist < test_Cell->Specialized.distWall)
								{
									nearWallFace[test_Cell->geometry.id] 	= nearWallFace[grid.Data.cells[c].geometry.id];
									walkBound[test_Cell->geometry.id]		= num_Pass + 1;
									num_WalkCells++;

									test_Cell->Specialized.distWall	= dist;
								}
							}
						}
					}
				}
			}
		}
	}


	// Treatment for ghost cells
	for (int g = 0; g <= grid.Info.NGM-1; g++)
	{
		curr_Face	= grid.Data.ghosts[g].Specialized.F_List[0];
		grid.Data.ghosts[g].Specialized.distWall = -curr_Face->Specialized.cl->Specialized.distWall;
	}


	// Calculate distance and n_dot_wallVector for each faces
	c_Cell* CL;
	c_Cell* CR;
	c_Face*	wall_Face;
	for (int f = 0; f <= grid.Info.NFM-1; f++)
	{
		CL = grid.Data.faces[f].Specialized.cl;
		CR = grid.Data.faces[f].Specialized.cr;


		grid.Data.faces[f].Specialized.distWall	= 0.5 * (CL->Specialized.distWall + CR->Specialized.distWall);
		wall_Face = nearWallFace[CL->geometry.id];

		double n_dot_wall = OP2A::MATH::VectorDotProduct(grid.Data.faces[f].geometry.x, wall_Face->geometry.x);
		grid.Data.faces[f].Specialized.nDotWall = 1.0 - fabs(n_dot_wall);
	}
}








}
