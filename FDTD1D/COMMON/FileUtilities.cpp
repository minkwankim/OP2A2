/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FileUtilities.cpp
 *
 *  Created on: Oct 28, 2015
 *      Author: minkwan
 */


#include "FileUtilities.hpp"

namespace OP2A{
namespace Common{


bool fileExist(const char *filename)
{
	std::ifstream ifile(filename);
	return ifile;
}

bool fileExist(const std::string& filename)
{
  std::ifstream ifile(filename.c_str());
  return ifile;
}

}
}


