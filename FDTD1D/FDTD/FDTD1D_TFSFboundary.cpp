/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FDTD1D_TFSFboundary.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: minkwan
 */

#include <FDTD/FDTD1D.hpp>
#include "./PHYS/ConstantsEM.hpp"


double fn_incident(double m, double q)
{
	double ft;
	double aux1;

	aux1 = ((q-m) - 30 ) / 10;
	ft	 = exp(-aux1*aux1);
	return (ft);
}


namespace OP2A {
namespace FDTD {


void FDTD1D::applyTFSFboundaryH(unsigned int i_node, unsigned int n_time)
{
	double coeffHy	= setup.Sc / C / material.mu_c[i_node-1];

	data.H(i_node-1)	= data.H(i_node-1) - fn_incident(0.0, n_time) *coeffHy;
}

void FDTD1D::applyTFSFboundaryE(unsigned int i_node, unsigned int n_time)
{
	double coeffEy	= setup.Sc / C / material.eps_n[i_node];

	data.E(i_node)	= data.E(i_node) - fn_incident(-0.5, n_time+0.5) *coeffEy;
}





void FDTD1Dv2::applyTFSFboundary_H(GRID::Face &face)
{
	face.data(H,1)	-= face.data(CoeffH,2)*Einc.ezInc(setup.n, 0.0);
}


void FDTD1Dv2::applyTFSFboundary_E(GRID::Node &node)
{
	double coeff;
	int mat_ID	= node_material_ID[node.geo.ID];

	double eps_r = material[mat_ID].eps / EPS0;
	double mu_r  = material[mat_ID].mu  / MU0;

	coeff	= setup.Sc / sqrt(eps_r * mu_r);
	node.data(E,1)	+= coeff*Einc.ezInc(setup.n+0.5, -0.5);
}


void FDTD1Dv2::applyTFSFboundary_H()
{
	for (int f = 1; f <= grid.config.NFM; f++)
	{
		int BC_type	= grid.faces[f].geo.BC;

		if (BC_type == 3)
		{
			applyTFSFboundary_H(grid.faces[f]);
		}
	}
}


void FDTD1Dv2::applyTFSFboundary_E()
{
	for (int n = 1; n <= grid.config.NNM; n++)
	{
		int BC_type	= grid.nodes[n].geo.BC;

		if (BC_type == 3)
		{
			applyTFSFboundary_E(grid.nodes[n]);
		}
	}
}



}
}
