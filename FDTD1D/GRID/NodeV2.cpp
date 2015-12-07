/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * NodeV2.cpp
 *
 *  Created on: Nov 30, 2015
 *      Author: minkwan
 */

#include <typeinfo>
#include <COMMON/ExceptionGeneral.hpp>
#include <COMMON/ErrorCode.hpp>

#include <GRID/NodeV2.hpp>
#include <GRID/CellV2.hpp>
#include <GRID/GridSetupParameter.hpp>


namespace OP2A {
namespace GRID {

Node_V2::Node_V2()
:ID(0), BC(0), m_include(true)
{

}

Node_V2::Node_V2(unsigned int size_data)
:ID(0), BC(0), data(size_data, 0.0), m_include(true)
{

}


Node_V2::~Node_V2()
{
	// TODO Auto-generated destructor stub
}



void Node_V2::CheckError()
{
	if (C_List.size() > 1)
	{
		for (int i_c = 0; i_c <= C_List.size()-1; i_c++)
		{
			if (typeid(C_List[i_c]) != typeid(c_Cell*))
			{
				Common::ExceptionGeneral(FromHere(), "Pointer type of Cell List is not c_Cell. Need to check allocation of it.", Common::ErrorCode::NotMatchTypeofPointer());
			}
		}
	}
	else
	{
		Common::ExceptionGeneral(FromHere(), "NODE: Neighboring Cells are not allocated.", Common::ErrorCode::NotAllocated());
	}


	if (C_List.size() != Wc.size())
	{
		Common::ExceptionGeneral(FromHere(), "Size of Cell_List does not match with the size of weighting value.", Common::ErrorCode::NotMatchDimention());
	}

}


void Node_V2::resizeData(unsigned int size_data)
{
	data.resize(size_data);
}

void Node_V2::remove()
{
	m_include = false;
}

bool Node_V2::isInclude()
{
	return (m_include);
}


} /* namespace FDTD */
} /* namespace OP2A */
