/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cNodeV2.cpp
 *
 *  Created on: Jan 5, 2016
 *      Author: minkwan
 */

#include "./COMMON/ErrorCode.hpp"
#include "./COMMON/ExceptionGeneral.hpp"

#include <GRID_V2/cNodeV2.hpp>

namespace GRID {

c_Node_v2::c_Node_v2()
{
	// TODO Auto-generated constructor stub

}

c_Node_v2::~c_Node_v2()
{
	// TODO Auto-generated destructor stub
}


/*
 * Internal functions
 */
void c_Node_v2::CheckError()
{
	if (Specialized.C_List.size() >= 1)
	{
		for (int i_c = 0; i_c <= Specialized.C_List.size()-1; i_c++)
		{
			if (typeid(Specialized.C_List[i_c]) != typeid(c_Cell*))
			{
				OP2A::Common::ExceptionGeneral(FromHere(), "Pointer type of Cell List is not c_Cell. Need to check allocation of it.", OP2A::Common::ErrorCode::NotMatchTypeofPointer());
			}
		}
	}
	else
	{
		OP2A::Common::ExceptionGeneral(FromHere(), "NODE: Neighboring Cells are not allocated.", OP2A::Common::ErrorCode::NotAllocated());
	}


	if (Specialized.C_List.size() != Specialized.Wc.size())
	{
		OP2A::Common::ExceptionGeneral(FromHere(), "Size of Cell_List does not match with the size of weighting value.", OP2A::Common::ErrorCode::NotMatchDimention());
	}
}





}
