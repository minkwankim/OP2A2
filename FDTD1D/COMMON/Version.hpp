/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Version.hpp
 *
 *  Created on: Oct 28, 2015
 *      Author: minkwan
 */

#ifndef VERSION_HPP_
#define VERSION_HPP_


#include "Common.hpp"
#include "CommonAPI.hpp"


namespace OP2A {
namespace Common {
	/*
	 * Version information.
	 */

	class COMMON_API Version
	{
		public:
		  explicit Version (int ver_main, int ver_sub, int date_year, int date_month, int date_day, const char * type_info);

		  void info() const;

		private:
			int primary;       		/* Primary version number   (i.e. 2 for V2.0) */
			int secondary;    	 	/* Secondary version number (i.e. 0 for V2.0) */
			int year;          		/* Most recent date of update */
			int month;
			int date;

			std::string type;     	/* "Type" of version */
	};
}
}

#endif /* VERSION_HPP_ */
