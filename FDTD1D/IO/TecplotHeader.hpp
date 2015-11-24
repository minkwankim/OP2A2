/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * TecplotHeader.hpp
 *
 *  Created on: Oct 29, 2015
 *      Author: minkwan
 */

#ifndef TECPLOTHEADER_HPP_
#define TECPLOTHEADER_HPP_


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

#include "./COMMON/Common.hpp"
#include "./COMMON/Array1D.hpp"


namespace OP2A{
namespace IO{


enum IO_Tecplot_Header
{
	FULL		=	0,
	GRID		=	1,
	SOLUTION	=	2
};


/*
 * Class for Tecplot Header
 *
 * 	Initially written by:	Minkwan Kim
 * 	Last modified on	:	Oct/29/2015
 * 	Last modified by	:	Minkwan Kim
 */
class TecplotHeader
{
	/*
	 * I. Constructor and Destructor
	 */
public:
	TecplotHeader():filetype(0), m_filled(false), startVar(0), endVar(0){	};
	TecplotHeader(const std::string& tec_title, int tec_filetype, const std::vector<std::string>& tec_variables)	:title(tec_title), filetype(tec_filetype), variables(tec_variables), m_filled(true), startVar(0), endVar(0){	};

	~TecplotHeader(){	};


	/*
	 * II. Member Variables
	 */
public:
	std::string					title;
	int							filetype;
	std::vector<std::string>	variables;
	int  						startVar;
	int  						endVar;

private:
	bool m_filled;


	/*
	 * III. Member Functions
	 */
public:
	void writeASCII(const std::string& filename);
	void writeBinary(const std::string& filename);


};





}
}



#endif /* TECPLOTHEADER_HPP_ */
