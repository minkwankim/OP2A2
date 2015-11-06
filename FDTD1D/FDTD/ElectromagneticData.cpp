/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ElectromagneticData.cpp
 *
 *  Created on: Nov 4, 2015
 *      Author: minkwan
 */

#include "ElectromagneticData.hpp"

namespace OP2A{
namespace FDTD{


// MF-PUB-01 - allocate
// @param ncm number of cell in grid
// @return Void
void ElectroMagneticData1D::allocate(unsigned int ncm)
{
	mk_assert (m_isInitialized == false);

	E.resize(ncm+1);
	H.resize(ncm+1);
	m_isAllocated = true;
}


// MF-PUB-02 - resize
// @param ncm_new new number of cell in grid
// @return Void
void ElectroMagneticData1D::resize(unsigned int ncm_new)
{
	E.resize(ncm_new+1);
	H.resize(ncm_new+1);
	m_isAllocated = true;
}


// MF-PUB-03 - isInitialized
// @return bool
bool ElectroMagneticData1D::isInitialized()
{
	return (m_isInitialized);
}


// MF-PUB-04 - isAllocated
// @return bool
bool ElectroMagneticData1D::isAllocated()
{
	return (m_isAllocated);
}


}
}
