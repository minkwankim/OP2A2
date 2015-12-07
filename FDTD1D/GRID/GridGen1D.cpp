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
	GridProcessingGeometryNode(grid1D.config, grid1D.nodes);


	grid1D.nodes[1].next 		= &grid1D.nodes[2];
	grid1D.nodes[1].previous 	= NULL;

	grid1D.nodes[nnm].next 		= NULL;
	grid1D.nodes[nnm].previous 	= &grid1D.nodes[nnm-1];


	// Faces
	for (int f = 1; f <= nfm; f++)
	{
		grid1D.faces[f].geo.BC		= 0;
		grid1D.faces[f].geo.ID		= f;
		grid1D.faces[f].geo.type	= GRID::f_point;

		grid1D.faces[f].conn.numNodes = 1;
		grid1D.faces[f].conn.listNodes.resize(grid1D.faces[f].conn.numNodes);
		grid1D.faces[f].conn.listNodes[0] = &grid1D.nodes[f];
	}
	GridProcessingGeometryFace(grid1D.config, grid1D.faces);


	grid1D.faces[1].next 		= &grid1D.faces[2];
	grid1D.faces[1].previous 	= NULL;

	grid1D.faces[nfm].next 		= NULL;
	grid1D.faces[nfm].previous 	= &grid1D.faces[nfm-1];



	// Cells
	for (int c = 1; c <= ncm; c++)
	{
		grid1D.cells[c].geo.BC		= 0;
		grid1D.cells[c].geo.ID		= c;
		grid1D.cells[c].geo.type	= GRID::c_line;

		grid1D.cells[c].conn.numNodes = 2;
		grid1D.cells[c].conn.listNodes.resize(grid1D.cells[c].conn.numNodes);
		grid1D.cells[c].conn.listNodes[0] = &grid1D.nodes[c];
		grid1D.cells[c].conn.listNodes[1] = &grid1D.nodes[c+1];

		grid1D.cells[c].conn.numFaces = 2;
		grid1D.cells[c].conn.listFaces.resize(grid1D.cells[c].conn.numFaces);
		grid1D.cells[c].conn.listFaces[0] = &grid1D.faces[c];
		grid1D.cells[c].conn.listFaces[1] = &grid1D.faces[c+1];
	}
	GridProcessingGeometryCell(grid1D.config, grid1D.cells);

	grid1D.cells[1].next 		= &grid1D.cells[2];
	grid1D.cells[1].previous 	= NULL;

	grid1D.cells[ncm].next 		= NULL;
	grid1D.cells[ncm].previous 	= &grid1D.cells[ncm-1];



	// Connectivity of Face
	for (int f = 2; f <= nfm-1; f++)
	{
		grid1D.faces[f].conn.cl[0]	= &grid1D.cells[f-1];
		grid1D.faces[f].conn.cr[0]	= &grid1D.cells[f];
	}

	grid1D.faces[1].conn.cl[0]	= NULL;
	grid1D.faces[1].conn.cr[0]	= &grid1D.cells[1];

	grid1D.faces[nfm].conn.cl[0]	= &grid1D.cells[nfm-1];
	grid1D.faces[nfm].conn.cr[0]	= NULL;

	//Ghost cells
	GridProcessingGeometryGhost(grid1D.config, grid1D.faces, grid1D.ghosts);



	return (grid1D);
}




void GridGen1Dv2(const double x0, const double xL, const int nfm, Grid1D& grid1D)
{
	int ncm	= 0;
	int nnm	= nfm+1;

	grid1D.allocateGrid(nfm);


	// Node positions
	double dX = fabs(xL - x0) / nfm;

	for (int n = 1; n <= grid1D.config.NNM; n++)
	{
		grid1D.nodes[n].geo.ID 	= n;
		grid1D.nodes[n].geo.type 	= 0;
		grid1D.nodes[n].geo.x[0]	= x0 + dX*(n-1);
		grid1D.nodes[n].geo.S		= 0.0;

		if (n != 1 && n != grid1D.config.NNM)	grid1D.nodes[n].geo.BC		= 0;
		grid1D.mapNode.insert(n, n);


		if (n > 1)	grid1D.nodes[n].previous	= &grid1D.nodes[n-1];
		else		grid1D.nodes[n].previous	= NULL;

		if (n < grid1D.config.NNM)	grid1D.nodes[n].next = &grid1D.nodes[n+1];
		else						grid1D.nodes[n].next = NULL;
	}

	// Check error in Node Mapping
	if (grid1D.mapNode.size() != grid1D.config.NNM)
	{
		Common::ExceptionGeneral(FromHere(), "Number of element in NodeMap does not match with NNM. Please check Node Mapping", "NotMatchSize:");
	}



	// Faces
	for (int f = 1; f <= grid1D.config.NFM; f++)
	{
		grid1D.faces[f].geo.ID 	= f;
		grid1D.faces[f].geo.type 	= 2;
		grid1D.faces[f].geo.BC		= 0;

		grid1D.faces[f].conn.numNodes	= 2;
		grid1D.faces[f].conn.listNodes.resize(grid1D.faces[f].conn.numNodes);
		grid1D.faces[f].conn.listNodes[0]	= &grid1D.nodes[f];
		grid1D.faces[f].conn.listNodes[1]	= &grid1D.nodes[f+1];

		grid1D.mapFace.insert(f, f);

		if (f > 1)	grid1D.faces[f].previous	= &grid1D.faces[f-1];
		else		grid1D.faces[f].previous	= NULL;

		if (f < grid1D.config.NFM)	grid1D.faces[f].next = &grid1D.faces[f+1];
		else						grid1D.faces[f].next = NULL;
	}

	GridProcessingGeometryFace(grid1D.config, grid1D.faces);

	// Ghost faces
	grid1D.ghosts[1].geo.ID 	= -1;
	grid1D.ghosts[1].geo.type 	= -1;
	grid1D.ghosts[1].geo.BC		= -1;
	grid1D.ghosts[1].geo.S		= 2.0*fabs(grid1D.faces[1].geo.x[0] - grid1D.nodes[1].geo.x[0]);
	grid1D.ghosts[1].geo.x[0]	= grid1D.nodes[1].geo.x[0] - fabs(grid1D.faces[1].geo.x[0] - grid1D.nodes[1].geo.x[0]);

	grid1D.ghosts[1].conn.numNodes	= 1;
	grid1D.ghosts[1].conn.listNodes.resize(grid1D.ghosts[1].conn.numNodes);
	grid1D.ghosts[1].conn.listNodes[0]	= &grid1D.nodes[1];
	grid1D.ghosts[1].previous	= &grid1D.faces[1];
	grid1D.ghosts[1].next		= NULL;

	grid1D.mapFace.insert(0, -1);


	grid1D.ghosts[2].geo.ID 	= -2;
	grid1D.ghosts[2].geo.type 	= -1;
	grid1D.ghosts[2].geo.BC		= -1;
	grid1D.ghosts[2].geo.S		= 2.0*fabs(grid1D.nodes[nnm].geo.x[0] - grid1D.faces[nfm].geo.x[0]);
	grid1D.ghosts[2].geo.x[0]	= grid1D.nodes[nnm].geo.x[0] + fabs(grid1D.nodes[nnm].geo.x[0] - grid1D.faces[nfm].geo.x[0]);

	grid1D.ghosts[2].conn.numNodes	= 1;
	grid1D.ghosts[2].conn.listNodes.resize(grid1D.ghosts[2].conn.numNodes);
	grid1D.ghosts[2].conn.listNodes[0]	= &grid1D.nodes[nnm];
	grid1D.ghosts[2].previous	= &grid1D.faces[nfm];
	grid1D.ghosts[2].next		= NULL;

	grid1D.mapFace.insert(nfm+1, -2);

	// Check error in Node Mapping
	if (grid1D.mapFace.size() != grid1D.config.NFM + grid1D.config.NGM)
	{
		Common::ExceptionGeneral(FromHere(), "Number of element in NodeMap does not match with NNM. Please check Node Mapping", "NotMatchSize:");
	}




	// Node connectivity
	for (int n = 2; n <= grid1D.config.NNM; n++)
	{
		double Si = fabs(grid1D.faces[n].geo.x[0] - grid1D.faces[n-1].geo.x[0]);
		grid1D.nodes[n].geo.S = Si;
	}
	grid1D.nodes[1].geo.S = 2.0*fabs(grid1D.faces[1].geo.x[0] - grid1D.nodes[1].geo.x[0]);

}







}


