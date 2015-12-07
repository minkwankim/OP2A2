/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FDTD1D_CalCoefficient.cpp
 *
 *  Created on: Nov 24, 2015
 *      Author: minkwan
 */



#include <FDTD/FDTD1D.hpp>

namespace OP2A {
namespace FDTD {


void FDTD1D::CalculateUpdateCoefficient()
{
#pragma ivdep
	for (int n = 1; n <= grid.NNM; n++)
	{
		double dx	= grid.dXn(n);
		double aux1 = material.sigma_n[n] * setup.dt / (2.0*material.eps_n[n]);
		double aux2 = setup.dt / (material.eps_n[n]*dx);

		data.m_CoeffE1(n)	= (1-aux1) / (1+aux1);
		data.m_CoeffE2(n)	= aux2 / (1+aux1);

	}

#pragma ivdep
	for (int c = 1; c <= grid.NCM; c++)
	{
		double dx	= grid.dXc(c);
		double aux1 = material.sigma_m_c[c] * setup.dt / (2.0*material.mu_c[c]);
		double aux2 = setup.dt / (material.mu_c[c]*dx);

		data.m_CoeffH1(c)	= (1-aux1) / (1+aux1);
		data.m_CoeffH2(c)	= aux2 / (1+aux1);
	}
}


void FDTD1Dv2::CalculateUpdateCoefficient()
{
	int v_CoeffE;
	int v_CoeffH;

	v_CoeffE = grid.faces[0].data.dataMapVector.find(CoeffE);
	v_CoeffH = grid.faces[0].data.dataMapVector.find(CoeffH);
//#pragma ivdep
	for (int f = 1; f <= grid.config.NFM; f++)
	{
		double aux1 = setup.dt * material[face_material_ID[f]].sigma / (2.0*material[face_material_ID[f]].eps);
		double aux2 = setup.dt / (material[face_material_ID[f]].eps*grid.faces[f].geo.S);

		grid.faces[f].data.dataVector[v_CoeffE](1)	= (1-aux1) / (1+aux1);
		grid.faces[f].data.dataVector[v_CoeffE](2)	= aux2 / (1+aux1);

		double aux3 = setup.dt * material[face_material_ID[f]].sigma_m / (2.0*material[face_material_ID[f]].mu);
		double aux4 = setup.dt / (material[face_material_ID[f]].mu*grid.faces[f].geo.S);

		grid.faces[f].data.dataVector[v_CoeffH](1)	= (1-aux3) / (1+aux3);
		grid.faces[f].data.dataVector[v_CoeffH](2)	= aux4 / (1+aux3);

		if (aux1 != aux1)
		{
			int a =0;
		}
	}


	v_CoeffE = grid.nodes[0].data.dataMapVector.find(CoeffE);
	v_CoeffH = grid.nodes[0].data.dataMapVector.find(CoeffH);
#pragma ivdep
	for (int n = 1; n <= grid.config.NNM; n++)
	{
		double aux1 = setup.dt * material[node_material_ID[n]].sigma / (2.0*material[node_material_ID[n]].eps);
		double aux2 = setup.dt / (material[node_material_ID[n]].eps*grid.nodes[n].geo.S);

		grid.nodes[n].data.dataVector[v_CoeffE](1)	= (1-aux1) / (1+aux1);
		grid.nodes[n].data.dataVector[v_CoeffE](2)	= aux2 / (1+aux1);

		double aux3 = setup.dt * material[node_material_ID[n]].sigma_m / (2.0*material[node_material_ID[n]].mu);
		double aux4 = setup.dt / (material[node_material_ID[n]].mu*grid.nodes[n].geo.S);

		grid.nodes[n].data.dataVector[v_CoeffH](1)	= (1-aux3) / (1+aux3);
		grid.nodes[n].data.dataVector[v_CoeffH](2)	= aux4 / (1+aux3);
	}
}



}
}

