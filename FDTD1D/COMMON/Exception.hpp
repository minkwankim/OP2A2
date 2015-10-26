/*
 * Exception.hpp
 *
 *  Created on: Oct 26, 2015
 *      Author: minkwan
 */

#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include "CodeLocation.hpp"
#include "NonCopyable.hpp"


namespace OP2A{
namespace Common{

class COMMON_API ExceptionManager : public Common::NonCopyable<ExceptionManager>
{
public:
	ExceptionManager();

	static ExceptionManager& getInstance ();

	bool	ExceptionOutputs;
	bool	ExceptionDumps;
	bool	ExceptionAborts;
};



/* Exception class
 *
 * @author	Minkwan Kim
 * @version 1.0 20/05/2015
 */
class COMMON_API Exception : public std::exception
{
public:
	virtual ~Exception () throw ();

	void append (const std::string& add) throw ();			// Append additional description into m_what
	const std::string& str () const throw ();				// Get contents of description (m_what)
	const char* what () const throw (); 					// Get contents of description (m_what) [char]

	std::string full_description ()	const throw ();			// Show full description of exception

	virtual std::string getClassName () throw ()
	{
		return m_class_name;
	}



protected:
	Exception (CodeLocation where, std::string message, std::string className) throw ();

	CodeLocation	m_where;
	std::string		m_msg;
	std::string		m_class_name;
	std::string		m_what;
};



//class Exception_Type :public Common::Exception
//{
//public:
//	Exception_Type (const Common::CodeLocation& where, const std::string& what)
//		:Common::Exception(where, what, "Test_Class")
//	{
//
//	}
//
//	Exception_Type (const Exception_Type& e) throw()	:Common::Exception(e)
//	{
//	}
//};



}
}


#endif /* EXCEPTION_HPP_ */
