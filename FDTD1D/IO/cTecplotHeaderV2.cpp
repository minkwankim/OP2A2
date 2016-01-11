/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cTecplotHeaderv2.cpp
 *
 *  Created on: Jan 8, 2016
 *      Author: minkwan
 */

#include <IO/cTecplotHeaderV2.hpp>
#include "./COMMON/TypeConversion.hpp"

namespace IO {

c_TecplotHeader_v2::c_TecplotHeader_v2()
	:m_filetype(0)
{

}

c_TecplotHeader_v2::c_TecplotHeader_v2(const std::string& tec_title, const std::vector<std::string>& tec_variables)
	:title(tec_title), variables(tec_variables), m_filetype(0)
{

}


c_TecplotHeader_v2::~c_TecplotHeader_v2()
{


}












/*
 * III. Member Functions
 */
// MF-PUB-01 - writeASCII
// @brief	Write Tecplot file in ASCII format
// @pre  	TecplotHeader class should be completed.
void c_TecplotHeader_v2::writeASCII(const std::string& filename)
{
	ofstream		tecplot_file;

	// OPEN FILE TO WRITE
	tecplot_file.open(filename.c_str());

	tecplot_file << "TITLE = \""	<< title << "\"" << endl;

	tecplot_file << "FILETYPE = \"";
	switch (m_filetype)
	{
	case enum_FULL:
		tecplot_file << "FULL\"" << endl;
		break;

	case enum_GRID:
		tecplot_file << "GRID\"" << endl;
		break;

	case enum_SOLUTION:
		tecplot_file << "SOLUTION\"" << endl;
		break;
	}

	tecplot_file << "VARIABLES = ";
	if (variables.size() > 0)
	{
		for (int i = 0; i <= variables.size()-1; i++)
		{
			tecplot_file << "\"";
			tecplot_file << variables[i];
			tecplot_file << "\" ";
		}
	}
	tecplot_file << endl;

	tecplot_file.close();
}

void c_TecplotHeader_v2::writeASCII()
{
	std::ostringstream filename;

	if (title =="")	title	= "OP2A_default";

	filename << title << ".plt";

	writeASCII(filename.str());
}


void c_TecplotHeader_v2::setFileType(const unsigned int filetype)
{
	m_filetype	= filetype;
}

void c_TecplotHeader_v2::setFileType(const IO_Tecplot_Header filetype)
{
	m_filetype	= OP2A::Common::EnumToInt<IO_Tecplot_Header>(filetype);
}




} /* namespace IO */
