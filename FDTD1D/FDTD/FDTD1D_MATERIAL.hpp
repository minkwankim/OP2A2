/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FDTD1DMATERIAL.hpp
 *
 *  Created on: Nov 18, 2015
 *      Author: minkwan
 */

#ifndef FDTD1DMATERIAL_HPP_
#define FDTD1DMATERIAL_HPP_

#include "COMMON/Array1D.hpp"
#include "COMMON/Common.hpp"

using namespace std;

namespace OP2A {
namespace FDTD {

class FDTD1D_MATERIAL {
public:
	FDTD1D_MATERIAL();
	~FDTD1D_MATERIAL();

public:
	vector<double> mu_n;
	vector<double> mu_c;

	vector<double> eps_n;
	vector<double> eps_c;

	vector<double> sigma_n;
	vector<double> sigma_c;

	vector<double> sigma_m_n;
	vector<double> sigma_m_c;

public:
	void allocateSize(unsigned int nnm, unsigned int ncm);
};


class FDTD1D_MATERIALv2 {
public:
	FDTD1D_MATERIALv2();
	~FDTD1D_MATERIALv2();

public:
	double mu;
	double eps;
	double sigma;
	double sigma_m;

public:
};

} /* namespace FDTD */
} /* namespace OP2A */

#endif /* FDTD1DMATERIAL_HPP_ */
