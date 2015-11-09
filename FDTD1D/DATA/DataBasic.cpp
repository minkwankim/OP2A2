/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * DataBasic.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: minkwan
 */

#include <DATA/DataBasic.hpp>

namespace OP2A {
namespace DATA {

DataBasic::DataBasic():m_hasScalar(false), m_hasVector(false), m_hasMatrix(false)
{

}

DataBasic::DataBasic(int nScalar, int nVector, int nMatrix)
	:dataScalar(nScalar), dataVector(nVector), dataMatrix(nMatrix)//, m_hasScalar(false), m_hasVector(false), m_hasMatrix(false)
{
	if (nScalar > 0)	m_hasScalar = true;
	if (nVector > 0)	m_hasVector = true;
	if (nMatrix > 0)	m_hasMatrix = true;
}

DataBasic::DataBasic(std::vector<double> i_dataScalar, std::vector<Common::Array1D<double> >	i_dataVector, std::vector<Common::Array2D<double> >	i_dataMatrix)
	:dataScalar(i_dataScalar), dataVector(i_dataVector), dataMatrix(i_dataMatrix),  m_hasScalar(false), m_hasVector(false), m_hasMatrix(false)
{
	if (dataScalar.size() > 0)	m_hasScalar = true;
	if (dataVector.size() > 0)	m_hasVector = true;
	if (dataMatrix.size() > 0)	m_hasMatrix = true;
}


DataBasic::~DataBasic()
{


}


/*
 * III. Member Functions
 */
// MF-PUB-01 - sizeScalar / sizeVector / sizeMatrix
// @return Void
int DataBasic::sizeScalar()
{
	return (dataScalar.size());
}

int DataBasic::sizeVector()
{
	return (dataVector.size());
}

int DataBasic::sizeMatrix()
{
	return (dataMatrix.size());
}


// MF-PUB-02 - check
// @brief check error in the allocated size of data and dataMap
// @return Void
void DataBasic::checkScalar()
{
	if (dataScalar.size() != dataMapScalar.size())
	{
		Common::ExceptionGeneral(FromHere(), "The size of scalar data does not match with the dataMap size:", "MismatchDataSize:Scalar");
	}
}


void DataBasic::checkVector()
{
	if (dataVector.size() != dataMapVector.size())
	{
		Common::ExceptionGeneral(FromHere(), "The size of vector data does not match with the dataMap size:", "MismatchDataSize:Vector");
	}
}


void DataBasic::checkMatrix()
{
	if (dataMatrix.size() != dataMapMatrix.size())
	{
		Common::ExceptionGeneral(FromHere(), "The size of matrix data does not match with the dataMap size:", "MismatchDataSize:Matrix");
	}
}

void DataBasic::check()
{
	checkScalar();
	checkVector();
	checkMatrix();
}


// MF-PUB-03 - operator ()
double& DataBasic::operator() (const string varName)
{
	int index	= dataMapScalar.find(varName);
	return (dataScalar[index]);
}

double& DataBasic::operator() (const string varName, unsigned int i)
{
	int index	= dataMapVector.find(varName);
	return (dataVector[index](i));
}

double& DataBasic::operator() (const string varName, unsigned int i, unsigned int j)
{
	int index	= dataMapMatrix.find(varName);
	return (dataMatrix[index](i, j));
}


// MF-PUB-04 - Alloc
void DataBasic::dataVectorAlloc(const string varName, unsigned int iSize)
{
	dataVector[dataMapVector.find(varName)].resize(iSize);
}

void DataBasic::dataMatrixAlloc(const string varName, unsigned int iSize, unsigned int jSize)
{
	dataMatrix[dataMapMatrix.find(varName)].resize(iSize, jSize);
}



} /* namespace DATA */
} /* namespace OP2A */
