/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cNodeV2.hpp
 *
 *  Created on: Jan 5, 2016
 *      Author: minkwan
 */

#ifndef CNODEV2_HPP_
#define CNODEV2_HPP_

#include "cCommonElement.hpp"
#include "GridConfig.hpp"


namespace GRID {

class c_Cell;

class c_NodeSpecial
{
public:
	c_NodeSpecial()
	{
		Wc.reserve(8);
		C_List.reserve(8);
	};
	~c_NodeSpecial()	{	};

public:
	vector<double>			Wc;
	std::vector<c_Cell*>	C_List;
};



class c_Node_v2 : public c_CommonElement
{
public:
	c_Node_v2();
	~c_Node_v2();

public:
	c_NodeSpecial Specialized;


public:
	void CheckError();

};

} /* namespace GRID */

#endif /* CNODEV2_HPP_ */
