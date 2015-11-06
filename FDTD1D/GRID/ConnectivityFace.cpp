/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ConnectivityFace.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: minkwan
 */

#include <GRID/ConnectivityFace.hpp>

namespace OP2A {
namespace GRID {

ConnectivityFace::ConnectivityFace():cl(2), cr(2), numNeighborCells(0), numNodes(0), listNodes(2)
{

}

ConnectivityFace::~ConnectivityFace()
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
void ConnectivityFace::resizeNeighber(int newSize)
{
	weightNeighborCells.resize(newSize);
	listNeighborCells.resize(newSize);
}





} /* namespace GRID */
} /* namespace OP2A */
