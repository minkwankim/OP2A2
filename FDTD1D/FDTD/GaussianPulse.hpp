/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GaussianPulse.hpp
 *
 *  Created on: Nov 2, 2015
 *      Author: minkwan
 */

#ifndef GAUSSIANPULSE_HPP_
#define GAUSSIANPULSE_HPP_


#include "COMMON/Array1D.hpp"
#include "COMMON/Common.hpp"


namespace OP2A{
namespace FDTD{

class GaussianPulse{
	/*
	 * I. Constructor and Destructor
	 */
public:
	GaussianPulse(): delay(0.0), width(0.0), cdtds(0.0){	};
	GaussianPulse(double the_delay, double the_width, double the_cdtds): delay(the_delay), width(the_width), cdtds(the_cdtds){	};
	~GaussianPulse(){	}


public:
	/*
	 * II. Member Variables
	 */
public:
	double delay;
	double width;
	double cdtds;

	/*
	 * III. Member Functions
	 */
public:
	double ezInc(double time, double location);


};


}
}


#endif /* GAUSSIANPULSE_HPP_ */
