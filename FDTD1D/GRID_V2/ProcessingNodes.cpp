/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ProcessingNodes.cpp
 *
 *  Created on: Jan 6, 2016
 *      Author: minkwan
 */
#include <omp.h>

#include "Gridv2.hpp"
#include "./COMMON/ExceptionGeneral.hpp"
#include "./COMMON/ErrorCode.hpp"

namespace GRID
{
	void Processing_Node(c_Grid& grid, double meshFactor, bool isAxisymmetric)
	{
		if (meshFactor != 1.0)
		{
#pragma ivdep
			for (int n = 0; n <= grid.Info.NNM-1; n++)
			{
				for (int d = 0; d <= grid.Info.DIM-1; d++)
				{
					grid.Data.nodes[n].geometry.x[d] /= meshFactor;
				}
			}
		}


		if (isAxisymmetric == true && grid.Info.DIM == 2)
		{
#pragma ivdep
			for (int n = 0; n <= grid.Info.NNM-1; n++)
			{
				grid.Data.nodes[n].geometry.x[1]	+= CONST_GRID_AXISSYMMETRIC_ADD;
			}
		}
	}
}
