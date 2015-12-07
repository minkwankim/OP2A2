/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GridCreateGhost.cpp
 *
 *  Created on: Dec 4, 2015
 *      Author: minkwan
 */

#include "./COMMON/VectorPointer.hpp"
#include "GRID/GridV2.hpp"
#include "GRID/GridFunctions.hpp"


namespace OP2A {
namespace GRID {

/*
void GridCreatGhost2D_v1(c_Grid& grid, int Nx, int Ny, const vector<int>& BC_index)
{

	int ngm = 0;
	int pos;
	for (int f = 0; f <= grid.NFM-1; f++)
	{
		//Left
		if (grid.Face_Data[f].index.i == 1 && grid.Face_Data[f].index.direction == 1)
		{
			grid.Face_Data[f].BC = BC_index[0];

			ngm++;
			grid.Ghost_Data.resize(ngm);
			pos	= grid.Ghost_Data.size()-1;

			grid.Ghost_Data[pos].ID = -ngm;
			grid.Ghost_Data[pos].index.i = 0;
			grid.Ghost_Data[pos].index.j = grid.Face_Data[f].CR->index.j;
			grid.Ghost_Data[pos].index.k = grid.Face_Data[f].CR->index.j;
			grid.Ghost_Data[pos].index.location = 0;

			grid.Ghost_Data[pos].N_List.resize(2);
			grid.Ghost_Data[pos].N_List[0]	= grid.Face_Data[f].N_List[0];
			grid.Ghost_Data[pos].N_List[1]	= grid.Face_Data[f].N_List[1];

			grid.Ghost_Data[pos].F_List.resize(1);
			grid.Ghost_Data[pos].F_List[0]	= &grid.Face_Data[f];






		}

		//Right
		if (grid.Face_Data[f].index.i == Nx+1 && grid.Face_Data[f].index.direction == 1)
		{
			grid.Face_Data[f].BC = BC_index[2];
		}

		if (grid.Face_Data[f].index.i == 1 && grid.Face_Data[f].index.direction == 1)	grid.Face_Data[f].BC = BC_index[0];
		if (grid.Face_Data[f].index.i == 1 && grid.Face_Data[f].index.direction == 1)	grid.Face_Data[f].BC = BC_index[0];
		if (grid.Face_Data[f].index.i == 1 && grid.Face_Data[f].index.direction == 1)	grid.Face_Data[f].BC = BC_index[0];

	}















}
*/


}
}
