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
#include "./DATA/DataSamples.hpp"

#include "./COMMON/Array1D.hpp"
#include "./COMMON/TypeConversion.hpp"

using namespace OP2A;

int main(int argc, char *argv[])
{
	double testInt1;
	double testDouble1;


	Grid<GRID::Node, GRID::Face, GRID::Cell, GRID::Cell>	testGrid;


	DATA::dataSampleFDTD1D	testData;

	std::cout << "test grid: " << std::endl;
	std::cout << "TEST:";

}
