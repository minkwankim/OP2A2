/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cCellV2.cpp
 *
 *  Created on: Jan 5, 2016
 *      Author: minkwan
 */
#include "./COMMON/ErrorCode.hpp"
#include "./COMMON/ExceptionGeneral.hpp"

#include <GRID_V2/cCellV2.hpp>

namespace GRID {

c_Cell_v2::c_Cell_v2() {
	// TODO Auto-generated constructor stub

}

c_Cell_v2::~c_Cell_v2() {
	// TODO Auto-generated destructor stub
}




/*
 * Internal Functions
 */
void c_Cell_v2::CheckError()
{
	if (geometry.id == 0)
	{
		OP2A::Common::ExceptionGeneral(FromHere(),"This cell is not allocated yet.", OP2A::Common::ErrorCode::NotAllocated());
	}


	for (int i_n = 0; i_n <= Specialized.N_List.size()-1; i_n++)
	{
		if (typeid(Specialized.N_List[i_n]) != typeid(c_Node*))
		{
			OP2A::Common::ExceptionGeneral(FromHere(), "CELL::Pointer type of Node List is not c_Node. Need to check allocation of it.", OP2A::Common::ErrorCode::NotMatchTypeofPointer());
		}
	}


	for (int i_f = 0; i_f <= Specialized.F_List.size()-1; i_f++)
	{
		if (typeid(Specialized.F_List[i_f]) != typeid(c_Face*))
		{
			OP2A::Common::ExceptionGeneral(FromHere(), "CELL::Pointer type of Face List is not c_Face. Need to check allocation of it.", OP2A::Common::ErrorCode::NotMatchTypeofPointer());
		}
	}


	if (geometry.S < 0.0)
	{
		OP2A::Common::ExceptionGeneral(FromHere(), "CELL:: Area/Volume has negative value.", OP2A::Common::ErrorCode::NegativeValue());
	}
}







} /* namespace GRID */
