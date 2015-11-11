/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ConnectivityCell.hpp
 *
 *  Created on: Nov 5, 2015
 *      Author: minkwan
 */

#ifndef CONNECTIVITYCELL_HPP_
#define CONNECTIVITYCELL_HPP_

#include <vector>

namespace OP2A {
namespace GRID {

class Node;
class Face;
class Cell;




class ConnectivityCell {
public:
	ConnectivityCell();
	~ConnectivityCell();



	/*
	 * II. Member Variables
	 */
public:
	int numNeighborCells;
	std::vector<double>	weightNeighborCells;
	std::vector<Cell*> 	listNeighborCells;

	int numNodes;
	std::vector<Node*> 	listNodes;

	int numFaces;
	std::vector<Face*> 	listFaces;

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

#endif /* CONNECTIVITYCELL_HPP_ */
