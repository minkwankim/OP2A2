/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FileUtilities.hpp
 *
 *  Created on: Oct 28, 2015
 *      Author: minkwan
 */

#ifndef FILEUTILITIES_HPP_
#define FILEUTILITIES_HPP_


#include <fstream>

namespace OP2A{
namespace Common{

bool fileExist(const char *filename);
bool fileExist(const std::string &filename);



}
}




#endif /* FILEUTILITIES_HPP_ */
