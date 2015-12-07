/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FaceV2.cpp
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

Face_V2::Face_V2() :
		ID(0), BC(-1), type(0), m_include(true), S(0), distWall(0.0), nDotWall(0.0),
		has_Child(false), Parent(NULL), CR(NULL), CL(NULL)
{

}

Face_V2::Face_V2(unsigned int size_data) :
		ID(0), BC(-1), type(0), m_include(true), S(0), distWall(0.0), nDotWall(0.0),
		has_Child(false), CR(NULL), Parent(NULL), CL(NULL), data(size_data, 0.0)
{

}

Face_V2::~Face_V2()
{
	CL = NULL;
	CR = NULL;
	Parent = NULL;
}


void Face_V2::CheckError()
{
	if (ID == 0)
		Common::ExceptionGeneral(FromHere(),"This face is not allocated yet.",Common::ErrorCode::NotAllocated());


	for (int i_n = 0; i_n <= N_List.size()-1; i_n++)
	{
		if (typeid(N_List[i_n]) != typeid(c_Node*))
		{
			Common::ExceptionGeneral(FromHere(), "FACE::Pointer type of Node List is not c_Node. Need to check allocation of it.", Common::ErrorCode::NotMatchTypeofPointer());
		}
	}

	if (typeid(CL) != typeid(c_Node*))
	{
		Common::ExceptionGeneral(FromHere(), "FACE::CL is not the pointer of c_Cell.", Common::ErrorCode::NotMatchTypeofPointer());
	}

	if (typeid(CR) != typeid(c_Node*))
	{
		Common::ExceptionGeneral(FromHere(), "FACE::CL is not the pointer of c_Cell.", Common::ErrorCode::NotMatchTypeofPointer());
	}


	if (S < 0.0)
	{
		Common::ExceptionGeneral(FromHere(), "FACE:: Area/Volume has negative value.", Common::ErrorCode::NegativeValue());
	}

	if (has_Child == true)
	{
		for (int i_f = 0; i_f <= Children.size()-1; i_f++)
		{
			if (typeid(Children[i_f]) != typeid(Face_V2*))
			{
				Common::ExceptionGeneral(FromHere(), "FACE::Pointer type of children is not c_Face. Need to check allocation of it.", Common::ErrorCode::NotMatchTypeofPointer());
			}
		}
	}

	if(Parent != NULL)
	{
		if (typeid(Parent) != typeid(Face_V2*))
		{
			Common::ExceptionGeneral(FromHere(), "FACE::Pointer type of Parent is not c_Face. Need to check allocation of it.", Common::ErrorCode::NotMatchTypeofPointer());
		}
	}
}


void Face_V2::resizeData(unsigned int size_data)
{
	data.resize(size_data);
}

void Face_V2::remove()
{
	m_include = false;
}


bool Face_V2::isInclude()
{
	return (m_include);
}




} /* namespace FDTD */
		} /* namespace OP2A */
