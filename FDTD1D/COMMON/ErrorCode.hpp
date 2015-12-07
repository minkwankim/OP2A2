/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ErrorCode.hpp
 *
 *  Created on: Nov 30, 2015
 *      Author: minkwan
 */

#ifndef ERRORCODE_HPP_
#define ERRORCODE_HPP_

#include "NonInstantiable.hpp"
#include "Common.hpp"

namespace OP2A {
namespace Common {


class COMMON_API ErrorCode : public Common::NonInstantiable<ErrorCode>
{
public:
	static std::string NotMatchDimention()		{ return ("NotMatchDimension:");	};
	static std::string NotSupportedType()		{ return ("NotSupportedType:");	};
	static std::string NotMatchTypeofPointer()	{ return ("NotMatchTypeofPointer:");	};
	static std::string NotAllocated()			{ return ("NotAllocated:");	};
	static std::string NegativeValue()			{ return ("NegativeValue:");	};
	static std::string NaNValue()				{ return ("NaNValue:");	};
	static std::string InfValue()				{ return ("InfValue:");	};
	static std::string ExceedLimit()			{ return ("ExceedLimit:");	};






};

} /* namespace COMMON */
} /* namespace OP2A */

#endif /* ERRORCODE_HPP_ */
