/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GeometryCellCart.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: minkwan
 */

#include <GRID/GeometryCellCart.hpp>

namespace OP2A {
namespace GRID {


GeometryCellCart::GeometryCellCart()
{
	typeCart		= 0;				// cell type in cartesian grid
	typeCutInCell	= -1;
	levelGrid		= 0;

	needRefine	= false;
	hasChildren	= false;
	numChildren	= 0;
}

GeometryCellCart::~GeometryCellCart()
{
	listChildren.clear();
}

} /* namespace GRID */
} /* namespace OP2A */
