/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ConnectivityFaceCart.hpp
 *
 *  Created on: Nov 11, 2015
 *      Author: minkwan
 */

#ifndef CONNECTIVITYFACECART_HPP_
#define CONNECTIVITYFACECART_HPP_

#include <vector>

namespace OP2A {
namespace GRID {

class Node;
class CellCart;

class ConnectivityFaceCart {
public:
	ConnectivityFaceCart();
	~ConnectivityFaceCart();


	/*
	 * II. Member Variables
	 */
public:
	std::vector<CellCart*> 	cl;
	std::vector<CellCart*> 	cr;

	int numNeighborCells;
	std::vector<double>	weightNeighborCells;
	std::vector<CellCart*> 	listNeighborCells;

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



#endif /* CONNECTIVITYFACECART_HPP_ */
