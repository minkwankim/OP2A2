/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FDTD1D_applyBC.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: minkwan
 */




#include <FDTD/FDTD1D.hpp>

namespace OP2A {
namespace FDTD {



void FDTD1D::applyBC()
{
	switch (grid.BC_type_0)
	{
	case 1:	// PCM BC
		data.H(0)	= 0.0;
		data.E(0)	= 0.0;
		break;

	case 2: // ABC BC
		data.H(0)	= data.H(1);
		data.E(0)	= data.H(1);
		break;
	}

	switch (grid.BC_type_L)
	{
	case 1:	// PCM BC
		data.H(grid.NNM)	= 0.0;
		data.E(grid.NCM)	= 0.0;
		break;

	case 2: // ABC BC
		data.H(grid.NNM)	= data.H(1);
		data.E(grid.NCM)	= data.H(1);
		break;
	}
}



void FDTD1Dv2::applyBC_H(GRID::Face& ghost)
{
	switch(ghost.geo.BC)
	{
	case 1:	// PCM BC
		ghost.data(H, 1)	= 0.0;
		break;

	case 2: // ABC BC
		ghost.data(H, 1) = ghost.previous->data(H, 1);
		break;
	}
}


void FDTD1Dv2::applyBC_H()
{
	applyBC_H(grid.FACE(0));
	applyBC_H(grid.FACE(grid.config.NFM+1));
}



void FDTD1Dv2::applyBC_E(GRID::Node& node)
{
	switch(node.geo.BC)
	{
	case 1:	// PCE BC
		node.data(E, 1)	= 0.0;
		break;

	case 2: // ABC BC
		if (node.previous != NULL)								node.data(E, 1)	= node.previous->data(E, 1);
		else if (node.previous == NULL && node.next != NULL )	node.data(E, 1)	= node.next->data(E, 1);
		break;
	}
}


void FDTD1Dv2::applyBC_E()
{
	applyBC_E(grid.NODE(1));
	applyBC_E(grid.NODE(grid.config.NNM));
}



}
}
