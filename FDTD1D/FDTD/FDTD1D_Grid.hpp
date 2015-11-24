/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FDTD1D.hpp
 *
 *  Created on: Nov 2, 2015
 *      Author: minkwan
 */

#ifndef FDTD1DGRID_HPP_
#define FDTD1DGRID_HPP_

#include "COMMON/Array1D.hpp"
#include "COMMON/Common.hpp"

#include "GRID/Grid.hpp"
#include "DATA/DataSamples.hpp"

using namespace std;

namespace OP2A{
namespace FDTD{
class FDTD1D_GRID
{
public:
	/*
	 * I. Constructor and Destructor
	 */
	FDTD1D_GRID();
	~FDTD1D_GRID();

	/*
	 * II. Member Variables
	 */
public:
	unsigned int NNM;
	unsigned int NCM;

	vector<double> Xn;
	vector<double> Xc;

	unsigned int BC_type_0;
	unsigned int BC_type_L;

protected:
	vector <double> m_dXn;
	vector <double> m_dXc;


	/*
	 * III. Member Functions
	 */
public:
	void Setup(unsigned int ncm, double x0, double xL);
	double dXn(unsigned int i);
	double dXc(unsigned int i);
};




class FDTD1D_GRIDv2 : public OP2A::Grid1D
{
public:
	/*
	 * I. Constructor and Destructor
	 */
	FDTD1D_GRIDv2();
	~FDTD1D_GRIDv2();

	/*
	 * II. Member Variables
	 */
protected:


	/*
	 * III. Member Functions
	 */
public:
	void Setup(unsigned int nfm, double x0, double xL);
};




}
}




#endif /* FDTD1D_HPP_ */
