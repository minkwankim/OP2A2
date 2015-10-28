/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Assert.cpp
 *
 *  Created on: Oct 27, 2015
 *      Author: minkwan
 */




#include "Common.hpp"
#include "CodeLocation.hpp"
#include "Assert.hpp"
#include "ExceptionGeneral.hpp"


using namespace std;
using namespace OP2A::Common;

namespace OP2A {

// Constructor
AssertionManager::AssertionManager() : DoAssertions(true), AssertionDumps(true), AssertionThrows(true)
{

}


/*
 * Class functions
 */

// [CF-01] Gets the instance of the manager
AssertionManager& AssertionManager::getInstance()
{
	static AssertionManager assertion_manager;
	return assertion_manager;
}


// [CF-03] Forward declaration of the function that implements the always present assert
void AssertionManager::do_assert ( bool condition,			// Conditions
                                   const char * cond_str,	// Condition name
                                   const char * file,		// File name
                                   int line,				// Location
                                   const char * func,		// Function name
                                   const char * desc)		// Description
{
	if ((!condition) && AssertionManager::getInstance().DoAssertions)
	{
		std::ostringstream out;
		out << "Assertion failed: [" << cond_str << "] ";

		if (desc)	out << "'" << desc << "' ";
		out << "in " << file << ":" << line;

		if (func)	out << " [function " << func << "]";

		//if ( AssertionManager::getInstance().AssertionDumps )	out << "\n" << OSystem::getInstance().getProcessInfo()->getBackTrace();

		if ( AssertionManager::getInstance().AssertionThrows )
		{
			throw ExceptionGeneral (FromHere(),out.str(), "Failed Assertion");
		}
		else
		{
			std::cerr << out << std::endl;
			std::cerr.flush();
			abort ();
		}
	}
}

}
