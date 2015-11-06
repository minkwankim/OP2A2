/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ConnectivityNode.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: minkwan
 */

#include <GRID/ConnectivityNode.hpp>

namespace OP2A {
namespace GRID {

ConnectivityNode::ConnectivityNode()
{
	numShairedCells	 = 0.0;
}

ConnectivityNode::~ConnectivityNode()
{
	weightShairedCells.clear();
	listShairedCells.clear();
}


/*
 * III. Member Functions
 */
// MF-PUB-01 - resize
// @param newSize new size of vector
// @return Void
void ConnectivityNode::resize(int newSize)
{
	weightShairedCells.resize(newSize);
	listShairedCells.resize(newSize);
}




} /* namespace GRID */
} /* namespace OP2A */
