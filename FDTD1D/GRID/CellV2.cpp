/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * CellV2.cpp
 *
 *  Created on: Nov 30, 2015
 *      Author: minkwan
 */

#include <typeinfo>
#include <COMMON/ExceptionGeneral.hpp>
#include <COMMON/ErrorCode.hpp>

#include <GRID/NodeV2.hpp>
#include <GRID/FaceV2.hpp>
#include <GRID/CellV2.hpp>
#include <GRID/GridSetupParameter.hpp>

namespace OP2A {
namespace GRID {

Cell_V2::Cell_V2():
		ID(0), BC(-1), type(0), S(0),
		Parent(NULL), has_Child(false), m_include(true), m_needToRefine(false)

{

}

Cell_V2::Cell_V2(unsigned int size_data):
		ID(0), BC(-1), type(0), S(0),
		Parent(NULL), has_Child(false), m_include(true), m_needToRefine(false), data(size_data, 0.0)
{

}


Cell_V2::~Cell_V2()
{
	Parent = NULL;
}



/*
 * 1.1 Apply boundary and deciding type of face
 */
void Cell_V2::applyBoundary()
{
	type	= 1;
	BC		= 1;

	bool flag_type = true;
	for (int n = 1; n <= N_List.size()-1; n++)
	{
		if (N_List[n]->BC == 1)
		{
			if (flag_type != true)
			{
				flag_type = false;
				break;
			}
		}
		else
		{
			flag_type = false;
		}

		if (flag_type != true)	break;
	}

	if (flag_type == true)
	{
		type	= 0;
		BC		= 0;
	}


	flag_type = true;
	for (int n = 1; n <= N_List.size()-1; n++)
	{
		if (N_List[n]->BC == -1)
		{
			if (flag_type != true)
			{
				flag_type = false;
				break;
			}
		}
		else
		{
			flag_type = false;
		}

		if (flag_type != true)	break;
	}

	if (flag_type == true)
	{
		type	= -1;
		BC		= 1;
	}
}













void Cell_V2::CheckError()
{
	if (ID == 0)
	{
		Common::ExceptionGeneral(FromHere(),"This cell is not allocated yet.",Common::ErrorCode::NotAllocated());
	}


	for (int i_n = 0; i_n <= N_List.size()-1; i_n++)
	{
		if (typeid(N_List[i_n]) != typeid(c_Node*))
		{
			Common::ExceptionGeneral(FromHere(), "CELL::Pointer type of Node List is not c_Node. Need to check allocation of it.", Common::ErrorCode::NotMatchTypeofPointer());
		}
	}


	for (int i_f = 0; i_f <= F_List.size()-1; i_f++)
	{
		if (typeid(F_List[i_f]) != typeid(c_Face*))
		{
			Common::ExceptionGeneral(FromHere(), "CELL::Pointer type of Face List is not c_Face. Need to check allocation of it.", Common::ErrorCode::NotMatchTypeofPointer());
		}
	}


	if (S < 0.0)
	{
		Common::ExceptionGeneral(FromHere(), "CELL:: Area/Volume has negative value.", Common::ErrorCode::NegativeValue());
	}


	if (has_Child == true)
	{
		for (int i_c = 0; i_c <= Children.size()-1; i_c++)
		{
			if (typeid(Children[i_c]) != typeid(Cell_V2*))
			{
				Common::ExceptionGeneral(FromHere(), "CELL::Pointer type of children is not c_Cell. Need to check allocation of it.", Common::ErrorCode::NotMatchTypeofPointer());
			}
		}
	}

	if(Parent != NULL)
	{
		if (typeid(Parent) != typeid(Cell_V2*))
		{
			Common::ExceptionGeneral(FromHere(), "CELL::Pointer type of Parent is not c_Cell. Need to check allocation of it.", Common::ErrorCode::NotMatchTypeofPointer());
		}
	}
}

void Cell_V2::resizeData(unsigned int size_data)
{
	data.resize(size_data);
}

void Cell_V2::remove()
{
	m_include = false;
}


bool Cell_V2::isInclude()
{
	return (m_include);
}

bool Cell_V2::needToRefine()
{
	return (m_needToRefine);
}

void Cell_V2::setRefine(bool flag)
{
	m_needToRefine = flag;
}



} /* namespace FDTD */
} /* namespace OP2A */
