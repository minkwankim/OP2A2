/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * NonCopyable.hpp
 *
 *  Created on: Oct 26, 2015
 *      Author: minkwan
 */

#ifndef NONCOPYABLE_HPP_
#define NONCOPYABLE_HPP_

namespace OP2A{
namespace Common{


template < typename TYPE >
class NonCopyable {
public:
	/// Default inline constructor
	NonCopyable () {}

	/// Default inline destructor
	virtual ~NonCopyable () {}

private:
	/// private (non defined) copy constructor to prevent
	/// copying of the object
	NonCopyable (const NonCopyable & Source);

	/// private (non defined) assignment operator to prevent
	/// copy assignment of the object
	const NonCopyable & operator = (const NonCopyable & Source);
}; // end class NonCopyable


}
}




#endif /* NONCOPYABLE_HPP_ */
