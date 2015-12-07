/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FDTD1D_Init.cpp
 *
 *  Created on: Nov 2, 2015
 *      Author: minkwan
 */

#include "FDTD1D_Grid.hpp"


namespace OP2A{
namespace FDTD{


FDTD1D_GRID::FDTD1D_GRID():
		NCM(0), NNM(0), BC_type_0(0), BC_type_L(0)
{

}


FDTD1D_GRID::~FDTD1D_GRID()
{

}


void FDTD1D_GRID::Setup(unsigned int ncm, double x0, double xL)
{
	NCM = ncm;
	NNM = NCM;


	Xn.resize(NNM+1);
	Xc.resize(NCM+1);

	// Node positions
	double dX = fabs(xL - x0) / ncm;

	Xn[0]	= x0;
	for (int i = 1; i <= NNM; i++)
	{
		Xn[i] = Xn[i-1] + dX;
	}

	Xc[0] = Xn[0] - 0.5*(Xn[1] - Xn[0]);
	for (int i = 1; i <= NCM; i++)
	{
		Xc[i] = Xc[i-1] + dX;
	}

	m_dXn.resize(NNM+1);
	m_dXc.resize(NCM+1);

	for (int i = 1; i <= NNM; i++)	m_dXn[i] = Xn[i] - Xn[i-1];
	for (int i = 1; i <= NCM; i++)	m_dXc[i] = Xc[i] - Xc[i-1];
}


double FDTD1D_GRID::dXn(unsigned int i)
{
	return (m_dXn[i]);
}

double FDTD1D_GRID::dXc(unsigned int i)
{
	return (m_dXc[i]);
}




/*
 * FDTD1D_GRIDv2 class
 */
FDTD1D_GRIDv2::FDTD1D_GRIDv2()
{

}

FDTD1D_GRIDv2::~FDTD1D_GRIDv2()
{

}



void FDTD1D_GRIDv2::Setup(unsigned int nfm, double x0, double xL)
{
	config.Configure(1, nfm+1, nfm, 0, 2, 1.0, false);
	allocateGrid();

	DATA::dataSampleFDTD1D	datasample;
	GRID::Node	nodesample;
	GRID::Face	facesample;

	nodesample.data	= datasample;
	facesample.data = datasample;

	initializeNode(nodesample);
	initializeFace(facesample);
	ghosts[0]	= facesample;
	ghosts[1]	= facesample;
	ghosts[2]	= facesample;


	GridGen1Dv2(x0, xL, nfm, *this);

	/*// Node positions
	double dX = fabs(xL - x0) / nfm;
	for (int n = 1; n <= config.NNM; n++)
	{
		nodes[n].geo.ID 	= n;
		nodes[n].geo.type 	= 0;
		nodes[n].geo.x[0]	= x0 + dX*(n-1);
		nodes[n].geo.S		= 0.0;

		if (n != 1 && n != config.NNM)	nodes[n].geo.BC		= 0;

		whereisNode[n]	= n;


		if (n > 1)	nodes[n].previous	= &nodes[n-1];
		else		nodes[n].previous	= NULL;

		if (n < config.NNM)	nodes[n].next = &nodes[n+1];
		else				nodes[n].next = NULL;

	}

	// Faces
	for (int f = 1; f <= config.NFM; f++)
	{
		faces[f].geo.ID 	= f;
		faces[f].geo.type 	= 2;
		faces[f].geo.BC		= 0;

		faces[f].conn.numNodes	= 2;
		faces[f].conn.listNodes.resize(faces[f].conn.numNodes);
		faces[f].conn.listNodes[0]	= &nodes[f];
		faces[f].conn.listNodes[1]	= &nodes[f+1];

		whereisFace[f]	= f;


		if (f > 1)	faces[f].previous	= &faces[f-1];
		else		faces[f].previous	= NULL;

		if (f < config.NFM)	faces[f].next = &faces[f+1];
		else				faces[f].next = NULL;
	}

	GridProcessingGeometryFace(config, faces);*/
}



}
}
