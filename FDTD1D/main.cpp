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

#include "./COMMON/ExceptionGeneral.hpp"
#include "./COMMON/Map1D.hpp"
#include "./IO/TecplotHeader.hpp"
#include "./IO/TecplotZone.hpp"


int main(int argc, char *argv[])
{
	std::vector< std::string> temp(2);
	temp[0]	= "X";
	temp[1] = "Y";


	OP2A::IO::TecplotHeader	tecplotHeader("test", 0, temp);
	OP2A::IO::TecplotZone	tecplotzone;

	tecplotHeader.writeASCII("test.dat");


	tecplotzone.title = "cpu0";
	std::vector<int> test_int1(3);
	test_int1[0] = 1;
	test_int1[1] = 2;
	test_int1[2] = 4;

	std::vector<int> test_int2(4);
	test_int2[0] = 3;
	test_int2[1] = 5;
	test_int2[2] = 6;
	test_int2[3] = 7;


	tecplotzone.settingVarLocation(test_int1.size(), test_int1, test_int2.size(), test_int2);
	tecplotzone.writeASCII("test.dat");







	std::cout << "test" << std::endl;
	std::cout << "TEST:";
}
