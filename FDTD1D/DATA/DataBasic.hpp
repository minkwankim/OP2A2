/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * DataBasic.hpp
 *
 *  Created on: Nov 5, 2015
 *      Author: minkwan
 */

#ifndef DATABASIC_HPP_
#define DATABASIC_HPP_

#include "COMMON/Array1D.hpp"
#include "COMMON/Array2D.hpp"
#include "COMMON/Map1D.hpp"
#include "COMMON/ExceptionGeneral.hpp"



namespace OP2A {
namespace DATA {

class DataBasic {

	/*
	 * I. Constructor and Destructor
	 */
public:
	DataBasic();
	DataBasic(int nScalar, int nVector, int mMatrix);
	DataBasic(std::vector<double> i_dataScalar, std::vector<Common::Array1D<double> >	i_dataVector, std::vector<Common::Array2D<double> >	i_dataMatrix);

	~DataBasic();


	/*
	 * II. Member Variables
	 */
public:
	std::vector<double>						dataScalar;
	std::vector<Common::Array1D<double> >	dataVector;
	std::vector<Common::Array2D<double> >	dataMatrix;

	Common::Map1D<string, int>				dataMapScalar;
	Common::Map1D<string, int>				dataMapVector;
	Common::Map1D<string, int>				dataMapMatrix;

protected:
	bool m_hasScalar;
	bool m_hasVector;
	bool m_hasMatrix;


	/*
	 * III. Member Functions
	 */
public:
	// MF-PUB-01 - sizeScalar / sizeVector / sizeMatrix
	// @return Void
	int sizeScalar();
	int sizeVector();
	int sizeMatrix();


	// MF-PUB-02 - check
	// @brief check error in the allocated size of data and dataMap
	// @return Void
	void checkScalar();
	void checkVector();
	void checkMatrix();
	void check();


	// MF-PUB-03 - operator ()
	double& operator() (const string varName);									// For scalar variable
	double& operator() (const string varName, unsigned int i);					// For vector variable
	double& operator() (const string varName, unsigned int i, unsigned int j);	// For matrix variable


	// MF-PUB-04






};

} /* namespace DATA */
} /* namespace OP2A */

#endif /* DATABASIC_HPP_ */
