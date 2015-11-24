/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ConnectivityCellCart.cpp
 *
 *  Created on: Nov 11, 2015
 *      Author: minkwan
 */


#include <GRID/ConnectivityCellCart.hpp>

namespace OP2A {
namespace GRID {

ConnectivityCellCart::ConnectivityCellCart():listNodes(3), listFaces(3)
{
	numNeighborCells	 = 0;

	numNodes	= 0;
	numFaces	= 0;
}

ConnectivityCellCart::~ConnectivityCellCart()
{
	weightNeighborCells.clear();
	listNeighborCells.clear();

	listNodes.clear();
	listFaces.clear();
}


/*
 * III. Member Functions
 */
// MF-PUB-01 - resizeNeighber
// @param newSize new size of vector
// @return Void
void ConnectivityCellCart::resizeNeighber(int newSize)
{
	weightNeighborCells.resize(newSize);
	listNeighborCells.resize(newSize);
}






} /* namespace GRID */
} /* namespace OP2A */


