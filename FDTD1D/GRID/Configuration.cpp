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


void Configuration::Configure(const int dim, const int nnm, const int nfm, const int ncm, const int ngm)
{
	DIM	= dim;
	NNM	= nnm;
	NFM	= nfm;
	NCM	= ncm;
	NGM	= ngm;

	m_isConfigured = true;
}



}
}
