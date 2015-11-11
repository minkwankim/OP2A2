/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GeometryCellCart.hpp
 *
 *  Created on: Nov 5, 2015
 *      Author: minkwan
 */

#ifndef GEOMETRYCELLCART_HPP_
#define GEOMETRYCELLCART_HPP_

#include <vector>

#include "GridBasicElement.hpp"
#include "GeometryCell.hpp"

namespace OP2A {
namespace GRID {

class CellCart;

class GeometryCellCart: public GeometryCell
{
	/*
	 * I. Constructor and Destructor
	 */
public:
	GeometryCellCart();
	~GeometryCellCart();

	/*
	 * II. Member Variables
	 */
public:
	int typeCart;				// cell type in cartesian grid
	int	typeCutInCell;
	int levelGrid;

	bool needRefine;
	bool hasChildren;
	int	numChildren;

	std::vector<CellCart* >	listChildren;


	/*
	 * III. Member Functions
	 */
public:


};

} /* namespace GRID */
} /* namespace OP2A */

#endif /* GEOMETRYCELLCART_HPP_ */
