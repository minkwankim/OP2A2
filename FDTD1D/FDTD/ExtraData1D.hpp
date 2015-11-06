/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ExtraData.hpp
 *
 *  Created on: Nov 4, 2015
 *      Author: minkwan
 */

#ifndef EXTRADATA_HPP_
#define EXTRADATA_HPP_


#include "COMMON/Array1D.hpp"
#include "COMMON/Common.hpp"



namespace OP2A{
namespace FDTD{

class ExtraData1D
{
	/*
	 * I. Member Variables
	 */
public:
	std::vector<double>	Coeff1_E;
	std::vector<double>	Coeff2_E;
	std::vector<double>	Coeff1_H;
	std::vector<double>	Coeff2_H;

private:
	bool m_isInitialized;
	bool m_isAllocated;

	/*
	 * II. Constructor and Destructor
	 */
public:
	ExtraData1D():m_isInitialized(false), m_isAllocated(false){	};
	ExtraData1D(unsigned int ncm)
		:Coeff1_E(ncm+1, 0.0), Coeff2_E(ncm+1, 0.0),
		 Coeff1_H(ncm+1, 0.0), Coeff2_H(ncm+1, 0.0),
		 m_isInitialized(false), m_isAllocated(true)
	{

	};

	~ExtraData1D()
	{
		if (m_isAllocated == true)
		{
			Coeff1_E.clear();
			Coeff2_E.clear();
			Coeff1_H.clear();
			Coeff2_H.clear();
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


#endif /* EXTRADATA_HPP_ */
