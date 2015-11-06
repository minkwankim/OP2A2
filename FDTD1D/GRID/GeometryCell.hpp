/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GeometryCell.hpp
 *
 *  Created on: Nov 5, 2015
 *      Author: minkwan
 */

#ifndef GEOMETRYCELL_HPP_
#define GEOMETRYCELL_HPP_

#include "GeometryCommon.hpp"

namespace OP2A {
namespace GRID {



class GeometryCell : public GeometryCommon
{
	/*
	 * I. Constructor and Destructor
	 */
public:
	GeometryCell();
	~GeometryCell();


	/*
	 * II. Member Variables
	 */
public:
	double	distWall;				// distance to wall
	double	characteristicLength;	// characteristic length of a cell



	/*
	 * III. Member Functions
	 */
public:

};

} /* namespace GRID */
} /* namespace OP2A */

#endif /* GEOMETRYCELL_HPP_ */
