/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Face.hpp
 *
 *  Created on: Nov 24, 2015
 *      Author: minkwan
 */

#ifndef FACE_HPP_
#define FACE_HPP_

#include "./GRID/GeometryFace.hpp"
#include "./GRID/ConnectivityFace.hpp"
#include "./DATA/DataBasic.hpp"


namespace OP2A{
namespace GRID{

class Face_v2
{
public:
	Face_v2()
		:m_type(-1), next(NULL), previous(NULL)
	{

	};


	Face_v2(GRID::GeometryFace i_geo, GRID::ConnectivityFace i_conn, DATA::DataBasic i_data)
		: geo(i_geo), conn(i_conn), data(i_data), m_type(-1),  next(NULL), previous(NULL)
	{

	};

	~Face_v2()
	{

	};



public:
	GRID::GeometryFace		geo;
	GRID::ConnectivityFace	conn;
	DATA::DataBasic			data;

	Face&	next;
	Face&	previous;

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



#endif /* FACE_HPP_ */
