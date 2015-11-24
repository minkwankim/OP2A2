/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ConnectivityFaceCart.cpp
 *
 *  Created on: Nov 11, 2015
 *      Author: minkwan
 */


#include <GRID/ConnectivityFaceCart.hpp>

namespace OP2A {
namespace GRID {

ConnectivityFaceCart::ConnectivityFaceCart():cl(2), cr(2), numNeighborCells(0), numNodes(0), listNodes(2)
{

}

ConnectivityFaceCart::~ConnectivityFaceCart()
{
	cl.clear();
	cr.clear();

	weightNeighborCells.clear();
	listNeighborCells.clear();

	listNodes.clear();
}

/*
 * III. Member Functions
 */
// MF-PUB-01 - resizeNeighber
// @param newSize new size of vector
// @return Void
void ConnectivityFaceCart::resizeNeighber(int newSize)
{
	weightNeighborCells.resize(newSize);
	listNeighborCells.resize(newSize);
}





} /* namespace GRID */
} /* namespace OP2A */

