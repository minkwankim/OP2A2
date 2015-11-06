/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FDTD1D.hpp
 *
 *  Created on: Nov 4, 2015
 *      Author: minkwan
 */

#ifndef FDTD1D_HPP_
#define FDTD1D_HPP_


//#include "GRID/Grid.hpp"
#include "FDTD/FDTDConfiguration.hpp"
#include "FDTD/ElectromagneticData.hpp"
#include "FDTD/ExtraData1D.hpp"



namespace OP2A{
namespace FDTD{

class FDTD1D
{
	/*
	 * I. Member Variables
	 */
public:
	//OP2A::GRID::Grid					grid;
	//OP2A::FDTD::Configuration			config;
	//OP2A::FDTD::ElectroMagneticData1D	data;
	//OP2A::FDTD::ExtraData1D				extradata;



	/*
	 * II. Constructor and Destructor
	 */
public:
	FDTD1D()
	{

	};

	~FDTD1D()
	{

	};



	/*
	 * III. Member Functions
	 */
	// MF-PUB-01 - initData
	// @return Void
	void initData();

	// MF-PUB-02 - UpdateElectricField1D
	// @return Void
	void UpdateE();





};




}
}


#endif /* FDTD1D_HPP_ */
