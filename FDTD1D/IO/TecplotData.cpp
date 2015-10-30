/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * TecplotData.cpp
 *
 *  Created on: Oct 30, 2015
 *      Author: minkwan
 */

#include "./COMMON/CodeLocation.hpp"
#include "./COMMON/ExceptionGeneral.hpp"
#include "TecplotData.hpp"


namespace OP2A{
namespace IO{

using namespace std;

void TecplotDataWritePoint(const std::string& filename, std::vector <OP2A::Common::Array1D<double> > & data, int num, int var)
{
	ofstream		tecplot_file;

	// OPEN FILE TO APPEND
	tecplot_file.open(filename.c_str(), std::fstream::app);

	if(!tecplot_file)
	{
		throw Common::ExceptionGeneral (FromHere(), "Could not open file: " + filename + "==> Need to run TecplotHeader first", "FileSystem");
	}

	for (int c = 1; c <= num; c++)
	{
		for (int v = 1; v <= var; v++)
		{
			tecplot_file << data[c](v) << " ";
		}
		tecplot_file << endl;
	}
}


void TecplotDataWriteBlock(const std::string& filename, std::vector <OP2A::Common::Array1D<double> > & data, int num, int var)
{
	ofstream		tecplot_file;

	// OPEN FILE TO APPEND
	tecplot_file.open(filename.c_str(), std::fstream::app);

	if(!tecplot_file)
	{
		throw Common::ExceptionGeneral (FromHere(), "Could not open file: " + filename + "==> Need to run TecplotHeader first", "FileSystem");
	}

	for (int v = 1; v <= var; v++)
	{
		for (int c = 1; c <= num; c++)
		{

			tecplot_file << data[c](v) << endl;
		}
	}
}


}
}
