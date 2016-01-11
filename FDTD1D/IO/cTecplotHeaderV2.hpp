/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cTecplotHeaderV2.hpp
 *
 *  Created on: Jan 8, 2016
 *      Author: minkwan
 */

#ifndef CTECPLOTHEADERV2_HPP_
#define CTECPLOTHEADERV2_HPP_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

#include "./COMMON/ErrorCode.hpp"
#include "./COMMON/ExceptionGeneral.hpp"

using namespace std;

namespace IO {


enum IO_Tecplot_Header
{
	enum_FULL		=	0,
	enum_GRID		=	1,
	enum_SOLUTION	=	2
};




/*
 * Class for Tecplot Header
 *
 * 	Initially written by:	Minkwan Kim
 * 	Last modified on	:	Jan/01/2016
 * 	Last modified by	:	Minkwan Kim
 */
class c_TecplotHeader_v2 {
	/*
	 * I. Constructor and Destructor
	 */
public:
	c_TecplotHeader_v2();
	c_TecplotHeader_v2(const std::string& tec_title, const std::vector<std::string>& tec_variables);



	~c_TecplotHeader_v2();

public:

	/*
	 * II. Member Variables
	 */
public:
	string			title;		// Title of Output
	vector<string>	variables;	// Name list of variables


private:
	unsigned int m_filetype;

	/*
	 * III. Member Functions
	 */
public:
	void writeASCII(const std::string& filename);
	void writeASCII();

	void setFileType(const unsigned int filetype);
	void setFileType(const IO_Tecplot_Header filetype);

};

} /* namespace IO */

#endif /* CTECPLOTHEADERV2_HPP_ */
