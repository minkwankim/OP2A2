/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GridCommon.hpp
 *
 *  Created on: Nov 4, 2015
 *      Author: minkwan
 */

#ifndef GRIDBASICELEMENT_HPP_
#define GRIDBASICELEMENT_HPP_

#include "COMMON/Common.hpp"

namespace OP2A{


template <class Geometry, class Connectivity, class DataType>
class GridBasicElement
{
	/*
	 * I. Constructor and Destructor
	 */
public:
	GridBasicElement():m_type(-1), next(NULL), previous(NULL){	};
	GridBasicElement(Geometry i_geo, Connectivity i_conn, DataType i_data): geo(i_geo), conn(i_conn), data(i_data), m_type(-1),  next(NULL), previous(NULL){		};

	~GridBasicElement() { };



	/*
	 * II. Member Variables
	 */
public:
	Geometry		geo;
	Connectivity	conn;
	DataType		data;

	GridBasicElement*	next;
	GridBasicElement*	previous;

protected:
	int m_type;

	/*
	 * III. Member Functions
	 */
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
#endif /* GRIDCOMMON_HPP_ */
