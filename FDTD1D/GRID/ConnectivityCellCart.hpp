/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ConnectivityCellCart.hpp
 *
 *  Created on: Nov 11, 2015
 *      Author: minkwan
 */

#ifndef CONNECTIVITYCELLCART_HPP_
#define CONNECTIVITYCELLCART_HPP_

#include <vector>

namespace OP2A {
namespace GRID {

class Node;
class FaceCart;
class CellCart;




class ConnectivityCellCart {
public:
	ConnectivityCellCart();
	~ConnectivityCellCart();



	/*
	 * II. Member Variables
	 */
public:
	int numNeighborCells;
	std::vector<double>	weightNeighborCells;
	std::vector<CellCart*> 	listNeighborCells;

	int numNodes;
	std::vector<Node*> 	listNodes;

	int numFaces;
	std::vector<FaceCart*> 	listFaces;

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



#endif /* CONNECTIVITYCELLCART_HPP_ */
