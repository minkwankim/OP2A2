/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * TecplotHeader.cpp
 *
 *  Created on: Oct 30, 2015
 *      Author: minkwan
 */


#include "TecplotHeader.hpp"
#include "TECIO.h"

namespace OP2A{
namespace IO{


using namespace std;

/*
 * III. Member Functions
 */
// MF-PUB-01 - writeASCII
// @brief	Write Tecplot file in ASCII format
// @pre  	TecplotHeader class should be completed.
void TecplotHeader::writeASCII(const std::string& filename)
{
	ofstream		tecplot_file;

	// OPEN FILE TO WRITE
	tecplot_file.open(filename.c_str());

	tecplot_file << "TITLE = \""	<< title << "\"" << endl;
	tecplot_file << "FILETYPE = \"";

	switch (filetype)
	{
	case 0:
		tecplot_file << "FULL\"" << endl;
		break;

	case 1:
		tecplot_file << "GRID\"" << endl;
		break;

	case 2:
		tecplot_file << "SOLUTION\"" << endl;
		break;
	}

	tecplot_file << "VARIABLES = ";

	int var	= variables.size();
	for (int i = 0; i <= var-1; i++)
	{
		tecplot_file << "\"";
		tecplot_file << variables[i];
		tecplot_file << "\" ";
	}
	tecplot_file << endl;

	tecplot_file.close();
}


// MF-PUB-02 - writeBinary
// @brief	Write Tecplot file in Binary format
// @pre  	TecplotHeader class should be completed.
void TecplotHeader::writeBinary(const std::string& filename)
{
	int result;

	int var	= variables.size();
	std::ostringstream variables_str;

	variables_str << variables[0];
	for (int i = 1; i <= var-1; i++)
	{
		variables_str << " " << variables[i];
	}

	string scratchdir	= "./";

	char *Title;
	char *Variables;
	char *FName;
	char *ScratchDir;

	INTEGER4 Debug;
	INTEGER4 VIsDouble;


	Title		= const_cast<char *>(title.c_str());
	Variables	= const_cast<char *>(variables_str.str().c_str());
	FName		= const_cast<char *>(filename.c_str());
	ScratchDir	= const_cast<char *>(scratchdir.c_str());
	Debug 		= 0;
	VIsDouble 	= 1;

	//result = TECINI112(Title, Variables, FName, ScratchDir, &filetype, &Debug, &VIsDouble);
}


}
}

