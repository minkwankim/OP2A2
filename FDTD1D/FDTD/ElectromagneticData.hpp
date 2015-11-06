/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ElectromagneticData.hpp
 *
 *  Created on: Nov 4, 2015
 *      Author: minkwan
 */

#ifndef ELECTROMAGNETICDATA_HPP_
#define ELECTROMAGNETICDATA_HPP_



#include "COMMON/Array1D.hpp"
#include "COMMON/Common.hpp"



namespace OP2A{
namespace FDTD{

class ElectroMagneticData1D
{
	/*
	 * I. Member Variables
	 */
public:
	std::vector<double>	E;
	std::vector<double>	H;

private:
	bool m_isInitialized;
	bool m_isAllocated;


	/*
	 * II. Constructor and Destructor
	 */
public:
	ElectroMagneticData1D():m_isInitialized(false), m_isAllocated(false){	};
	ElectroMagneticData1D(unsigned int ncm):E(ncm+1, 0.0), H(ncm+1, 0.0), m_isInitialized(false), m_isAllocated(true){	};

	~ElectroMagneticData1D()
	{
		if ( m_isAllocated == true)
		{
			E.clear();
			H.clear();
		}
	}




	/*
	 * III. Member Functions
	 */
public:
	// MF-PUB-01 - allocated
	// @param ncm number of cell in grid
	// @return Void
	void allocate(unsigned int ncm);

	// MF-PUB-02 - resize
	// @param ncm_new new number of cell in grid
	// @return Void
	void resize(unsigned int ncm_new);

	// MF-PUB-03 - isInitialized
	// @return bool
	bool isInitialized();

	// MF-PUB-04 - isAllocated
	// @return bool
	bool isAllocated();

};





}
}


#endif /* ELECTROMAGNETICDATA_HPP_ */
