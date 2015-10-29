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



int main(int argc, char *argv[])
{
	bool			test_bool = false;
	unsigned int 	test_int;
	double	test_double;

	OP2A::Common::Map1D<std::string, int> test_map1D(4);
	test_map1D.resize(10);
	test_map1D.insert("test1", 1);
	test_map1D.insert("test3", 3);
	test_map1D.insert("test2", 7);
	test_map1D.insert("test6", 9);
	test_map1D.insert(0, "test5", 4);




	std::cout << "test" << std::endl;
	std::cout << "TEST:";
}
