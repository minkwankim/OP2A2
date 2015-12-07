/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FDTD1DUpdate.cpp
 *
 *  Created on: Nov 23, 2015
 *      Author: minkwan
 */



#include <FDTD/FDTD1D.hpp>
#include "./PHYS/ConstantsEM.hpp"

namespace OP2A {
namespace FDTD {


void FDTD1D::UpdateH()
{
	// Update Magnetic field
#pragma ivdep
	for (int c = 1; c <= grid.NCM; c++)
	{
		data.H(c)	= 	data.m_CoeffH1(c)*data.H(c) + 	data.m_CoeffH2(c)*(data.E(c) - data.E(c-1));
	}
}


void FDTD1D::UpdateE()
{
#pragma ivdep
	for (int n = 1; n <= grid.NNM; n++)
	{
		data.E(n)	= 	data.m_CoeffE1(n)*data.E(n) + data.m_CoeffE2(n)*(data.H(n+1) - data.H(n));
	}
}






void FDTD1Dv2::UpdateH()
{
	// Update Magnetic field
	int v_H 		= grid.faces[0].data.dataMapVector.find(H);
	int v_CoeffH 	= grid.faces[0].data.dataMapVector.find(CoeffH);
	int v_E 		= grid.nodes[0].data.dataMapVector.find(E);


	// Apply BC of H
	applyBC_H();

	// Update H
#pragma ivdep
	for (int f = 1; f <= grid.config.NFM; f++)
	{
		grid.faces[f].data.dataVector[v_H](1)	= grid.faces[f].data.dataVector[v_CoeffH](1)*grid.faces[f].data.dataVector[v_H](1);
		grid.faces[f].data.dataVector[v_H](1)  += grid.faces[f].data.dataVector[v_CoeffH](2)*(grid.faces[f].conn.listNodes[1]->data.dataVector[v_E](1)
																							- grid.faces[f].conn.listNodes[0]->data.dataVector[v_E](1));
	}

	//Apply TFSFboundary
	applyTFSFboundary_H();


	// Assign node value of H
	int v_Hn 		= grid.nodes[0].data.dataMapVector.find(H);

#pragma ivdep
	for (int n = 2; n <= grid.config.NNM-1; n++)
	{
		grid.nodes[n].data.dataVector[v_Hn](1)	= 0.5*(grid.faces[n-1].data.dataVector[v_Hn](1) + grid.faces[n].data.dataVector[v_Hn](1));
	}

}


void FDTD1Dv2::UpdateE()
{
	// Update Magnetic field
	int v_CoeffE 	= grid.nodes[0].data.dataMapVector.find(CoeffE);
	int v_E 		= grid.nodes[0].data.dataMapVector.find(E);
	int v_H 		= grid.faces[0].data.dataMapVector.find(H);

	// Assign Boundary Conditions
	applyBC_E();

	// Update E
#pragma ivdep
	for (int n = 2; n <= grid.config.NNM; n++)
	{
		grid.NODE(n).data.dataVector[v_E](1)  = grid.NODE(n).data.dataVector[v_CoeffE](1)*grid.NODE(n).data.dataVector[v_E](1);

		grid.NODE(n).data.dataVector[v_E](1)  += grid.NODE(n).data.dataVector[v_CoeffE](2) * (grid.FACE(n).data.dataVector[v_H](1)
																							- grid.FACE(n-1).data.dataVector[v_H](1));
	}

	//Apply TFSFboundary
	applyTFSFboundary_E();

	// Assign face value of E
	int v_Ef 		= grid.faces[0].data.dataMapVector.find(E);
#pragma ivdep
	for (int f = 1; f <= grid.config.NFM-1; f++)
	{
		grid.faces[f].data.dataVector[v_Ef](1)	= 0.0;

		for (int n = 0; n <= grid.faces[f].conn.numNodes-1; n++)
		{
			grid.faces[f].data.dataVector[v_Ef](1) += grid.faces[f].conn.listNodes[n]->data.dataVector[v_E](1);
		}

		grid.faces[f].data.dataVector[v_Ef](1)	= grid.faces[f].data.dataVector[v_Ef](1) / grid.faces[f].conn.numNodes;
	}
}







}
}
