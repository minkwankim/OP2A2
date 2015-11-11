/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Configuration.cpp
 *
 *  Created on: Nov 3, 2015
 *      Author: minkwan
 */

#include "Configuration.hpp"


namespace OP2A{
namespace GRID{

bool Configuration::isConfigured()
{
	return (m_isConfigured);
}


void Configuration::Configure(const int dim, const int nnm, const int nfm, const int ncm, const int ngm, const double mesh_factor, bool is_axisymmetric)
{
	DIM	= dim;
	NNM	= nnm;
	NFM	= nfm;
	NCM	= ncm;
	NGM	= ngm;

	gridFactor = mesh_factor;
	isAxisymmetric = is_axisymmetric;

	if (DIM == 3 || DIM == 1)
	{
		if (isAxisymmetric == true)
		{
			std::cout <<"[Warning!!] Axisymmetric is only applicable for 2D case. The Axisymmetric option is automatically turned off!!" << std::endl;
		}
	}


	m_isConfigured = true;
}



}
}
