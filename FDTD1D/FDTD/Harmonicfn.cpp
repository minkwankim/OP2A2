/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * harmonicfn.cpp
 *
 *  Created on: Nov 2, 2015
 *      Author: minkwan
 */



#include "Harmonicfn.hpp"


namespace OP2A{
namespace FDTD1D{

double Harmonic::ezInc(double n, double m)
{
	double result;

	result	= cos(2.0*M_PI/ N_lambda*(Sc*n - sqrt(mu_r*eps_r)*m));
	return (result);
}






}
}
