/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Grid.hpp
 *
 *  Created on: Nov 5, 2015
 *      Author: minkwan
 */

#ifndef GRID_HPP_
#define GRID_HPP_


#include "./GRID/GridBasicElement.hpp"

#include "./GRID/GeometryNode.hpp"
#include "./GRID/GeometryFace.hpp"
#include "./GRID/GeometryCell.hpp"
#include "./GRID/GeometryCellCart.hpp"

#include "./GRID/ConnectivityNode.hpp"
#include "./GRID/ConnectivityFace.hpp"
#include "./GRID/ConnectivityCell.hpp"

#include "./GRID/Configuration.hpp"


namespace OP2A{

/*
class Cell: public OP2A::GridBasicElement<OP2A::GRID::GeometryCell, OP2A::GRID::ConnectivityCell, double>
{
public:
	Cell(){};
	~Cell(){};
};


class Face: public OP2A::GridBasicElement<OP2A::GRID::GeometryFace, OP2A::GRID::ConnectivityFace, double>
{
public:
	Face(){};
	~Face(){};
};


class Node: public OP2A::GridBasicElement<OP2A::GRID::GeometryNode, OP2A::GRID::ConnectivityNode, double>
{
public:
	Node(){};
	~Node(){};
};

*/


class Node;
class Face;
class Cell;









class Grid
{
	/*
	 * I. Member Variables
	 */
public:
	OP2A::GRID::Configuration	config;

	std::vector<OP2A::Node*>		nodes;
	std::vector<OP2A::Face*>		faces;
	std::vector<OP2A::Cell*>		cells;
	std::vector<OP2A::Cell*>		ghosts;

private:
	std::vector<int>	m_bc_zone;
	bool				m_isAllocated;


	/*
	 * II. Constructor and Destructor
	 */
public:
	Grid();
	~Grid();


	/*
	 * III. Member Functions
	 */
public:
	// MF-PUB-01 - allocateGrid
	// @param newSize new size of vector
	// @return Void
	void allocateGrid();

	// MF-PUB-02 - resizeNode
	// @param newSize new size of vector
	// @return Void
	void resizeNode(const int nnm);

	// MF-PUB-03 - resizeFace
	// @param newSize new size of vector
	// @return Void
	void resizeFace(const int nfm);

	// MF-PUB-04 - resizeCell
	// @param newSize new size of vector
	// @return Void
	void resizeCell(const int ncm);

	// MF-PUB-05 - resizeGhost
	// @param newSize new size of vector
	// @return Void
	void resizeGhost(const int ngm);


};




}


#endif /* GRID_HPP_ */
