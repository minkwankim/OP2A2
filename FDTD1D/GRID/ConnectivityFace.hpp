/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ConnectivityFace.hpp
 *
 *  Created on: Nov 5, 2015
 *      Author: minkwan
 */

#ifndef CONNECTIVITYFACE_HPP_
#define CONNECTIVITYFACE_HPP_

#include <vector>

namespace OP2A {
class Node;
class Cell;


namespace GRID {

class ConnectivityFace {
public:
	ConnectivityFace();
	~ConnectivityFace();


	/*
	 * II. Member Variables
	 */
public:
	std::vector<Cell*> 	cl;
	std::vector<Cell*> 	cr;

	int numNeighborCells;
	std::vector<double>	weightNeighborCells;
	std::vector<Cell*> 	listNeighborCells;

	int numNodes;
	std::vector<Node*> 	listNodes;



	/*
	 * III. Member Functions
	 */
public:
	// MF-PUB-01 - resizeNeighber
	// @param newSize new size of vector
	// @return Void
	void resizeNeighber(int newSize);



};

} /* namespace GRID */
} /* namespace OP2A */

#endif /* CONNECTIVITYFACE_HPP_ */
