/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * main.cpp
 *
 *  Created on: Oct 26, 2015
 *      Author: minkwan
 */

#include <iostream>
#include <fstream>
#include <time.h>
#include <omp.h>
#include <iomanip>

#include "./GRID/Grid.hpp"
#include "./DATA/DataBasic.hpp"


#include "./COMMON/Array1D.hpp"
#include "./COMMON/TypeConversion.hpp"

using namespace OP2A;

int main(int argc, char *argv[])
{
	double testDouble1;


	DATA::DataBasic	testData(3, 10, 1);

	Common::Map1D<string, int>	testMapScalar;
	testMapScalar.insert("rho", 0);
	testMapScalar.insert("E", 1);
	testMapScalar.insert("H", 2);
	testData.dataMapScalar	= testMapScalar;
	testData.checkScalar();

	testData("rho")	= 1.0;
	testData("E")	= 1.5;

	testDouble1 = testData("E");





	std::cout << "test grid: " << std::endl;
	std::cout << "TEST:";


}
