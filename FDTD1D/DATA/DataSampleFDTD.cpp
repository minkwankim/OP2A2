/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * DataSampleFDTD.cpp
 *
 *  Created on: Nov 6, 2015
 *      Author: minkwan
 */


#include "DataSamples.hpp"
#include "Nomenclatures.hpp"

namespace OP2A{
namespace DATA{
/*
 * Sample Data for FDTD1D simulation
 */

dataSampleFDTD1D::dataSampleFDTD1D()
{
	int i;

	// Scalar variables
	i = 0;
	dataMapVector.insert(epsilon_EM, i);	i++;
	dataMapVector.insert(mu_EM, i);			i++;
	dataMapVector.insert(sigma, i);			i++;
	dataMapVector.insert(sigma_m, i);		i++;
	if (i > 0)	dataScalar.resize(i);


	// Vector variables
	i = 0;
	dataMapVector.insert(E, i);			i++;
	dataMapVector.insert(H, i);			i++;
	dataMapVector.insert(CoeffE, i);	i++;
	dataMapVector.insert(CoeffH, i);	i++;

	if (i > 0)	dataVector.resize(i);
	dataVectorAlloc(E, 1);
	dataVectorAlloc(H, 1);
	dataVectorAlloc(CoeffE, 2);
	dataVectorAlloc(CoeffH, 2);



	// Matrix variables
	i = 0;
	if (i > 0)	dataMatrix.resize(i);
}

dataSampleFDTD1D::~dataSampleFDTD1D()
{

}




}
}
