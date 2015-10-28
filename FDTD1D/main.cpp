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
#include "./COMMON/Array1D.hpp"
#include "./COMMON/Array2D.hpp"


int main(int argc, char *argv[])
{
	unsigned int 	test_int;
	double	test_double;

	std::vector<std::vector <double> > test_vector2D	= OP2A::Common::vector_2D(2,4, 1.0);
	test_vector2D[0][0]	= 1.0;
	test_vector2D[0][1]	= 2.0;
	test_vector2D[0][2]	= 3.0;
	test_vector2D[0][3]	= 4.0;
	test_vector2D[1][0]	= 5.0;
	test_vector2D[1][1]	= 6.0;
	test_vector2D[1][2]	= 7.0;
	test_vector2D[1][3]	= 8.0;



	OP2A::Common::Array2D<double> test_array2D_1(test_vector2D);
	OP2A::Common::Array2D<double> test_array2D_2;
	test_array2D_2.assign(3,5, 1.5);
	test_array2D_1.resize_Row(3);
	test_array2D_1.insert(2, 3, 1.2);


	std::cout << "test" << std::endl;
	std::cout << "TEST:";
}
