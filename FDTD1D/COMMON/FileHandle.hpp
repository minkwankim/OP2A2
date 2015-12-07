/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FileHandle.hpp
 *
 *  Created on: Dec 2, 2015
 *      Author: minkwan
 */

#ifndef FILEHANDLE_HPP_
#define FILEHANDLE_HPP_

#include <iostream>
#include <fstream>

#include "NonInstantiable.hpp"
#include "Common.hpp"



namespace OP2A {
namespace Common {


class COMMON_API FileHandle : public Common::NonInstantiable<FileHandle>
{
public:
	static void merge (const std::string& file1, const std::string& file2, const std::string& file3);
	static void merge (const std::string& file1, const std::string& file2, const std::string& file3, const std::string& file4);
	static void Xmerge (const std::string& file1, const std::string& file2, const std::string& file3);
	static void Xmerge (const std::string& file1, const std::string& file2, const std::string& file3, const std::string& file4);


};

} /* namespace Common */
} /* namespace OP2A */

#endif /* FILEHANDLE_HPP_ */
