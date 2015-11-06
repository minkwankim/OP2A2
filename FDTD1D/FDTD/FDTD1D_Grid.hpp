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


namespace OP2A{
namespace FDTD1D{


class Grid
{
public:
	/*
	 * I. Constructor and Destructor
	 */
	Grid():NX(0), time(0), maxTime(0), cdtds(0.0){	};
	Grid(int nx, int t, int max_t, double courant_number):
		ez(nx), hy(nx-1),
		NX(nx),	time(t), maxTime(max_t), cdtds(courant_number),
		ceze(nx), cezh(nx),
		chyh(nx-1), chye(nx-1)
	{

	};

	~Grid()	{ };

	/*
	 * II. Member Variables
	 */
public:
	OP2A::Common::Array1D<double>	ez;		// electric field array
	OP2A::Common::Array1D<double>	hy;		// magnetic field array

	OP2A::Common::Array1D<double>	ceze;	// Coefficient for updating Ez
	OP2A::Common::Array1D<double>	cezh;	// Coefficient for updating Ez
	OP2A::Common::Array1D<double>	chyh;	// Coefficient for updating Hy
	OP2A::Common::Array1D<double>	chye;	// Coeffifienc for updating Hy

	int NX;
	int time;
	int	maxTime;

	double	cdtds;


	/*
	 * III. Member Functions
	 */
public:
	void init();
};








}
}




#endif /* FDTD1D_HPP_ */
