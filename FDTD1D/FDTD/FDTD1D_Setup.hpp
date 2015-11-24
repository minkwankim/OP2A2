/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Configuration.hpp
 *
 *  Created on: Nov 3, 2015
 *      Author: minkwan
 */

#ifndef FDTDCONFIGURATION_HPP_
#define FDTDCONFIGURATION_HPP_


#include "COMMON/Array1D.hpp"
#include "COMMON/Common.hpp"


namespace OP2A{
namespace FDTD{

class FDTD1D_SETUP
{
	/*
	 * I. Member Variables
	 */
public:
	unsigned int maxTimeStep;
	double 	Sc;					// Courant Number

	double	dt;			// Time step
	int 	n;		// Current iteration number
	double	t;	// Current simulation time

private:


	/*
	 * II. Constructor and Destructor
	 */
public:
	FDTD1D_SETUP();
	~FDTD1D_SETUP();



	/*
	 * III. Member Functions
	 */




};






}
}


#endif /* CONFIGURATION_HPP_ */
