/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GridGen1D.cpp
 *
 *  Created on: Nov 9, 2015
 *      Author: minkwan
 */

#include "Grid.hpp"
#include "GeometryCommon.hpp"
#include "./COMMON/TypeConversion.hpp"

namespace OP2A
{


Grid<GRID::Node, GRID::Face, GRID::Cell, GRID::Cell> GridGen1D(const double x0, const double xL, const int N, const int gridFlag)
{
	int ncm	= N;
	int nfm	= N+1;
	int nnm	= N+1;
	int ngm	= 2;


	Grid<GRID::Node, GRID::Face, GRID::Cell, GRID::Cell>	grid1D;
	grid1D.config.Configure(1, nnm, nfm, ncm, ngm, 1.0, false);
	grid1D.allocateGrid();

	// Nodes
	double dx	= (xL - x0) / N;
	for (int n = 1; n <= nnm; n++)
	{
		grid1D.nodes[n].geo.BC		= 0;
		grid1D.nodes[n].geo.ID		= n;
		grid1D.nodes[n].geo.type	= 0;
		grid1D.nodes[n].geo.x[0]	= x0 + dx*(n-1);
	}

	// Faces
	for (int f = 1; f <= nfm; f++)
	{

	}








	return (grid1D);
}












}


