/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Exception_General.hpp
 *
 *  Created on: Oct 27, 2015
 *      Author: minkwan
 */

#ifndef EXCEPTION_GENERAL_HPP_
#define EXCEPTION_GENERAL_HPP_

#include "Exception.hpp"


namespace OP2A{
namespace Common{


class COMMON_API	ExceptionGeneral : public Common::Exception
{
public:
	ExceptionGeneral (const Common::CodeLocation& where, const std::string& what, const std::string& type): Common::Exception(where, what, type)
	{

	}

	ExceptionGeneral (const ExceptionGeneral& e) throw(): Common::Exception(e)
	{

	}
};



}
}




#endif /* EXCEPTION_GENERAL_HPP_ */
