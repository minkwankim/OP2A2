/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * CodeLocation.hpp
 *
 *  Created on: Oct 26, 2015
 *      Author: minkwan
 */

#ifndef CODELOCATION_HPP_
#define CODELOCATION_HPP_


#include "./Common.hpp"

namespace OP2A{
namespace Common{


/*
 * This class stores the information about a location in the source code
 */

class COMMON_API	CodeLocation
{
public:
	explicit CodeLocation (const char *file, int line, const char *function);
	std::string str () const;

private:
	  std::string	m_file;
	  std::string	m_function;
	  int			m_line;
};



#define FromHere() OP2A::Common::CodeLocation( __FILE__ , __LINE__ , __FUNCTION__ )


}
}


#endif /* CODELOCATION_HPP_ */
