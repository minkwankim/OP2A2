/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Node.hpp
 *
 *  Created on: Nov 24, 2015
 *      Author: minkwan
 */

#ifndef NODE_HPP_
#define NODE_HPP_


#include "./GRID/GeometryNode.hpp"
#include "./GRID/ConnectivityNode.hpp"
#include "./DATA/DataBasic.hpp"


namespace OP2A{
namespace GRID{

class Node_v2
{
public:
	Node_v2()
		:m_type(-1), next(NULL), previous(NULL)
	{

	};


	Node_v2(GRID::GeometryNode i_geo, GRID::ConnectivityNode i_conn, DATA::DataBasic i_data)
		: geo(i_geo), conn(i_conn), data(i_data), m_type(-1),  next(NULL), previous(NULL)
	{

	};

	~Node_v2()
	{

	};



public:
	GRID::GeometryNode		geo;
	GRID::ConnectivityNode	conn;
	DATA::DataBasic			data;

	Node&	next;
	Node&	previous;

protected:
	int m_type;


public:
	void setType(int i_type)
	{
		m_type	= i_type;
	}

	int showType()
	{
		return(m_type);
	}

};


}
}


#endif /* NODE_HPP_ */
