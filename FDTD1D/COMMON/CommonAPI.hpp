/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * CommonAPI.hpp
 *
 *  Created on: Oct 26, 2015
 *      Author: minkwan
 */

#ifndef COMMONAPI_HPP_
#define COMMONAPI_HPP_

#include "./ExportAPI.hpp"

/**
 * Define the macro CommonAPI
 *
 */


#ifdef COMMON_EXPORT
	#define COMMON_API	MK_EXPORT_API
#else
	#define COMMON_API	MK_IMPORT_API
#endif

#endif /* COMMONAPI_HPP_ */
