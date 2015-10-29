/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * DataRead.hpp
 *
 *  Created on: Oct 28, 2015
 *      Author: minkwan
 */

#ifndef DATAREAD_HPP_
#define DATAREAD_HPP_



#include "NonInstantiable.hpp"
#include "Common.hpp"
#include "CommonAPI.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>


namespace OP2A {
namespace Common {

class COMMON_API DataRead : public Common::NonInstantiable<DataRead>
{
public:
	static std::string get_data_from_string_string(std::string line, std::string TEXT);
	static std::string remove_space_front(std::string line);
	static std::string remove_space_end(std::string line);

	static void remove_comments(std::string& line, std::string comment_s, std::string comment_e);
	static void remove_comments(std::string& line, std::string comment_s);

	static void read_line(std::string& line);


	template<class T>
	static void get_data_from_string(std::string line, std::string TEXT, T default_value, T& data)
	{
		int num;
		T result;

		// REMOVE EMPTY SPACE AT FRONT AND END
		line = remove_space_front(line);
		line = remove_space_end(line);

		// REMOVE EMPTY SPACE AT FRONT AND END
		TEXT = remove_space_front(TEXT);
		TEXT = remove_space_end(TEXT);

		num = TEXT.size();
		if(line.compare(0, num, TEXT) == 0)
		{
			line.erase(0, num);
			line = remove_space_front(line);
			std::istringstream(line) >> result;

			if (line == "") result = default_value;

			data = result;
		}
	}
};


}
}

#endif /* DATAREAD_HPP_ */