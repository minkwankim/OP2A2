/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ConnectivityNode.hpp
 *
 *  Created on: Nov 5, 2015
 *      Author: minkwan
 */

#ifndef CONNECTIVITYNODE_HPP_
#define CONNECTIVITYNODE_HPP_

#include <vector>

namespace OP2A {

class Cell;

namespace GRID {

class ConnectivityNode
{
public:
	/*
	 * I. Constructor and Destructor
	 */
	ConnectivityNode();
	~ConnectivityNode();


	/*
	 * II. Member Variables
	 */
public:
	int numShairedCells;
	std::vector<double>	weightShairedCells;
	std::vector<Cell*> 	listShairedCells;



	/*
	 * III. Member Functions
	 */
public:
	// MF-PUB-01 - resize
	// @param newSize new size of vector
	// @return Void
	void resize(int newSize);



};

} /* namespace GRID */
} /* namespace OP2A */

#endif /* CONNECTIVITYNODE_HPP_ */
