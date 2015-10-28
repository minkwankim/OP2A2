/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Assert.hpp
 *
 *  Created on: Oct 27, 2015
 *      Author: minkwan
 */

#ifndef ASSERT_HPP_
#define ASSERT_HPP_

#include <cassert>
#include "NonCopyable.hpp"
#include "CommonAPI.hpp"


namespace OP2A{


/// Manager of behavior of assertions
class COMMON_API AssertionManager : public Common::NonCopyable <AssertionManager>
{
public:
	  bool DoAssertions;		// Flag to dynamically turn off assertions
	  bool AssertionDumps;		// Flag for Assertion Dumps backtraces
	  bool AssertionThrows;		// Flag for Assettion Throws exceptions

	  /// Constructor
	  AssertionManager();

	  /*
	   * Class functions
	   */

	  // [CF-01] Gets the instance of the manager
	  static	AssertionManager&	getInstance ();

	  // [CF-02] If AssertionManager is not handling assertions and those are passed to the standard assert function
	  // Controlled by the build option ENABLE_STDASSERT
	  static bool notHandlingAssertions ()
	  {
	  	  #ifdef ENABLE_STDASSERT
		  	  return true;
	  	  #else
		  	  return false;
	  	  #endif
	  }

	  // [CF-03] Forward declaration of the function that implements the always present assert
	  static void do_assert (bool condition, const char * cond_str, const char * file, int line, const char * func, const char * desc = 0 );
};



#ifndef ENABLE_STDASSERT
#define mk_always_assert(a) \
     { if (!(a)) { ::OP2A::AssertionManager::do_assert((a), #a, __FILE__, __LINE__, __FUNCTION__); } }

#define mk_always_assert_desc(msg, a) \
     { if (!(a)) { ::OP2A::AssertionManager::do_assert((a), #a, __FILE__, __LINE__, __FUNCTION__, msg); } }


/// Assertions are off if compiled with DNDEBUG
#ifndef NDEBUG
	#define mk_assert(a)       		mk_always_assert((a))
	#define mk_assert_desc(m,a) 	mk_always_assert_desc(m,(a))
#else
	#define mk_assert(a)
	#define mk_assert_desc(m,a)
#endif
#else
//ENABLE_STDASSERT
#ifndef NDEBUG
	#define mk_assert(a)              	 assert(a)
	#define mk_assert_desc(m,a)          assert(a)
	#define mk_always_assert(a)          assert(a)
	#define mk_always_assert_desc(msg,a) assert(a)
#else
	#define mk_assert(a)
	#define mk_assert_desc(m,a)
	#define mk_always_assert(a)
	#define mk_always_assert_desc(msg,a)
#endif

#endif // CF_ENABLE_STDASSERT


}


#endif /* ASSERT_HPP_ */
