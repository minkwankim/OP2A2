/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GridTypeDefinitions.hpp
 *
 *  Created on: Nov 6, 2015
 *      Author: minkwan
 */

#ifndef GRIDTYPEDEFINITIONS_HPP_
#define GRIDTYPEDEFINITIONS_HPP_


#include "./GRID/GridBasicElement.hpp"

#include "./GRID/GeometryNode.hpp"
#include "./GRID/GeometryFace.hpp"
#include "./GRID/GeometryCell.hpp"
#include "./GRID/GeometryCellCart.hpp"

#include "./GRID/ConnectivityNode.hpp"
#include "./GRID/ConnectivityFace.hpp"
#include "./GRID/ConnectivityCell.hpp"

#include "./GRID/Configuration.hpp"

#include "./DATA/DataBasic.hpp"


namespace OP2A{
namespace GRID{

class Cell:public OP2A::GridBasicElement<OP2A::GRID::GeometryCell,	OP2A::GRID::ConnectivityCell, OP2A::DATA::DataBasic>
{

};

class CellCart: public OP2A::GridBasicElement<OP2A::GRID::GeometryCellCart, 	OP2A::GRID::ConnectivityCell, OP2A::DATA::DataBasic>
{

};


class Face: public OP2A::GridBasicElement<OP2A::GRID::GeometryFace, 		OP2A::GRID::ConnectivityFace, OP2A::DATA::DataBasic>
{

};


class Node: public OP2A::GridBasicElement<OP2A::GRID::GeometryNode, 		OP2A::GRID::ConnectivityNode, OP2A::DATA::DataBasic>
{

};


//typedef	OP2A::GridBasicElement<OP2A::GRID::GeometryCell, 		OP2A::GRID::ConnectivityCell, OP2A::DATA::DataBasic>	Cell;
//typedef	OP2A::GridBasicElement<OP2A::GRID::GeometryCellCart, 	OP2A::GRID::ConnectivityCell, OP2A::DATA::DataBasic>	CellCart;
//typedef OP2A::GridBasicElement<OP2A::GRID::GeometryFace, 		OP2A::GRID::ConnectivityFace, OP2A::DATA::DataBasic>	Face;
//typedef OP2A::GridBasicElement<OP2A::GRID::GeometryNode, 		OP2A::GRID::ConnectivityNode, OP2A::DATA::DataBasic>	Node;



}
}


#endif /* GRIDTYPEDEFINITIONS_HPP_ */
