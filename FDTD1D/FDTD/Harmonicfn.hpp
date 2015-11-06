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
	Harmonic(double the_amp, double the_phase):amp(the_amp), phase(the_phase){	};
	Harmonic():amp(0.0), phase(0.0){	};

	~Harmonic(){	};


public:
	/*
	 * II. Member Variables
	 */
	double amp;
	double phase;


	/*
	 * III. Member Functions
	 */
	double harminic_fn(double x);
};


}
}
#endif /* HARMONICFN_HPP_ */
