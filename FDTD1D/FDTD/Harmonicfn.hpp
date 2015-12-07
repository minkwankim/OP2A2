/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * harmonicfn.hpp
 *
 *  Created on: Nov 2, 2015
 *      Author: minkwan
 */

#ifndef HARMONICFN_HPP_
#define HARMONICFN_HPP_


#include "COMMON/Array1D.hpp"
#include "COMMON/Common.hpp"


namespace OP2A{
namespace FDTD1D{

class Harmonic
{
public:
	/*
	 * I. Constructor and Destructor
	 */
	Harmonic(double i_Nlambda, double i_Sc, double i_mu_r, double i_eps_r)
	:N_lambda(i_Nlambda), Sc(i_Sc), mu_r(i_mu_r), eps_r(i_eps_r)
	{

	};

	Harmonic()
	:N_lambda(0), Sc(1), mu_r(1), eps_r(1)
	{

	};

	~Harmonic()
	{

	};


public:
	/*
	 * II. Member Variables
	 */
	double N_lambda;
	double Sc;
	double mu_r;
	double eps_r;



	/*
	 * III. Member Functions
	 */
public:
	double ezInc(double time, double location);

};


}
}
#endif /* HARMONICFN_HPP_ */
