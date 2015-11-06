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

class Configuration
{
	/*
	 * I. Member Variables
	 */
public:
	int 	maxIter;	// Maximum number of iteration;
	double	maxTime;	// Maximum simulation simulation time
	double	dt;			// Time step
	double 	Sc;			// Courant number

	int 	n;		// Current iteration number
	double	t;	// Current simulation time

private:
	bool m_isCompleted;


	/*
	 * II. Constructor and Destructor
	 */
public:
	Configuration()
	{
		maxIter	= 0;	// Maximum number of iteration;
		maxTime	= 0.0;	// Maximum simulation simulation time
		dt		= 0.0;			// Time step
		Sc		= 0.0;			// Courant number

		n		= 0;		// Current iteration number
		t		= 0.0;	// Current simulation time


		 m_isCompleted = false;
	}


	/*
	 * III. Member Functions
	 */




};






}
}


#endif /* CONFIGURATION_HPP_ */
