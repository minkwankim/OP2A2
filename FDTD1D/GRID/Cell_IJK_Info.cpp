/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * CELLIJKINFO.cpp
 *
 *  Created on: Nov 30, 2015
 *      Author: minkwan
 */

#include "COMMON/ErrorCode.hpp"
#include "COMMON/ExceptionGeneral.hpp"

#include <GRID/Cell_IJK_Info.hpp>

namespace OP2A {
namespace GRID {



Cell_IJK_Info::Cell_IJK_Info()
:i(0), j(0), k(0), lvl_refine(0), location(0)
{
	// TODO Auto-generated constructor stub
}

Cell_IJK_Info::~Cell_IJK_Info() {
	// TODO Auto-generated destructor stub
}










Cell_IJK::Cell_IJK()
{

}

Cell_IJK::Cell_IJK(unsigned int size_max_lvl, unsigned int dim)
:m_subIndex(size_max_lvl, std::vector<unsigned int>(4*(dim-1), 0))
{

}

Cell_IJK::~Cell_IJK()
{

}


void Cell_IJK::resize(unsigned int size_max_lvl, unsigned int pos)
{
	m_subIndex.resize(size_max_lvl);
	for (int l = 0; l <= size_max_lvl-1; l++)	m_subIndex[l].resize(pos);
}


unsigned int& Cell_IJK::operator()(const unsigned i, const unsigned j)
{
	return (m_subIndex[i][j]);
}







} /* namespace FDTD */
} /* namespace OP2A */
