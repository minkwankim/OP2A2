/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FDTD1D.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: minkwan
 */

#include <FDTD/FDTD1D.hpp>

namespace OP2A {
namespace FDTD {

FDTD1D::FDTD1D() {
	// TODO Auto-generated constructor stub

}

FDTD1D::~FDTD1D() {
	// TODO Auto-generated destructor stub
}


void FDTD1D::SetDataSize()
{
	data.SetDataSize(grid.NNM, grid.NCM);
}


void FDTD1D::Initialize()
{
	data.InitE(0.0);
	data.InitH(0.0);
}





/*
 * FDTD1Dv2 class
 */
FDTD1Dv2::FDTD1Dv2()
: material(1), IC_E0(1), IC_H0(1), face_material_ID(1), node_material_ID(1), face_IC_ID(1), node_IC_ID(1)
{

}

FDTD1Dv2::~FDTD1Dv2()
{

}


void FDTD1Dv2::gridSetup(unsigned int nfm, double x0, double xL)
{
	face_IC_ID.resize(nfm+1);
	node_IC_ID.resize(nfm+1+1);

	face_material_ID.resize(nfm+1);
	node_material_ID.resize(nfm+1+1);

	grid = GridGen1Dv2(x0, xL, nfm, 0);
}


void FDTD1Dv2::Initialize()
{
	int v_epsilon_EM;
	int v_mu_EM;
	int v_sigma;
	int v_sigma_m;
	int v_E;
	int v_H;


	v_epsilon_EM	= grid.faces[0].data.dataMapScalar.find(epsilon_EM);
	v_mu_EM 		= grid.faces[0].data.dataMapScalar.find(mu_EM);
	v_sigma			= grid.faces[0].data.dataMapScalar.find(sigma);
	v_sigma_m 		= grid.faces[0].data.dataMapScalar.find(sigma_m);
	v_E 			= grid.faces[0].data.dataMapScalar.find(E);
	v_H 			= grid.faces[0].data.dataMapScalar.find(H);

#pragma ivdep
	for (int f = 1; f <= grid.config.NFM; f++)
	{
		int m_index	= face_material_ID[f];
		grid.faces[f].data.dataScalar[v_epsilon_EM]	= material[m_index].eps;
		grid.faces[f].data.dataScalar[v_mu_EM]			= material[m_index].mu;
		grid.faces[f].data.dataScalar[v_sigma]			= material[m_index].sigma;
		grid.faces[f].data.dataScalar[v_sigma_m]		= material[m_index].sigma_m;

		int i_index	= face_IC_ID[f];
		grid.faces[f].data.dataVector[v_E](1)	= IC_E0[i_index];
		grid.faces[f].data.dataVector[v_H](1)	= IC_H0[i_index];
	}



	v_epsilon_EM	= grid.nodes[0].data.dataMapScalar.find(epsilon_EM);
	v_mu_EM 		= grid.nodes[0].data.dataMapScalar.find(mu_EM);
	v_sigma			= grid.nodes[0].data.dataMapScalar.find(sigma);
	v_sigma_m 		= grid.nodes[0].data.dataMapScalar.find(sigma_m);
	v_E 			= grid.nodes[0].data.dataMapScalar.find(E);
	v_H 			= grid.nodes[0].data.dataMapScalar.find(H);

#pragma ivdep
	for (int n = 1; n <= grid.config.NNM; n++)
	{
		int m_index	= node_material_ID[n];
		grid.nodes[n].data.dataScalar[v_epsilon_EM]		= material[m_index].eps;
		grid.nodes[n].data.dataScalar[v_mu_EM]			= material[m_index].mu;
		grid.nodes[n].data.dataScalar[v_sigma]			= material[m_index].sigma;
		grid.nodes[n].data.dataScalar[v_sigma_m]		= material[m_index].sigma_m;

		int i_index	= node_IC_ID[n];
		grid.nodes[n].data.dataVector[v_E](1)	= IC_E0[i_index];
		grid.nodes[n].data.dataVector[v_H](1)	= IC_H0[i_index];
	}
}


} /* namespace FDTD */
} /* namespace OP2A */
