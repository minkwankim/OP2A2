/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cFacev2.cpp
 *
 *  Created on: Jan 5, 2016
 *      Author: minkwan
 */
#include "./COMMON/ErrorCode.hpp"
#include "./COMMON/ExceptionGeneral.hpp"

#include <GRID_V2/cFaceV2.hpp>

namespace GRID {

c_Face_v2::c_Face_v2() {
	// TODO Auto-generated constructor stub

}

c_Face_v2::~c_Face_v2() {
	// TODO Auto-generated destructor stub
}






/*
 * Internal functions
 */
void c_Face_v2::CheckError()
{
	if (geometry.id == 0)
	{
		OP2A::Common::ExceptionGeneral(FromHere(),"This face is not allocated yet.", OP2A::Common::ErrorCode::NotAllocated());
	}

	for (int i_n = 0; i_n <= Specialized.N_List.size()-1; i_n++)
	{
		if (typeid(Specialized.N_List[i_n]) != typeid(c_Node*))
		{
			OP2A::Common::ExceptionGeneral(FromHere(), "FACE::Pointer type of Node List is not c_Node. Need to check allocation of it.", OP2A::Common::ErrorCode::NotMatchTypeofPointer());
		}
	}

	if (typeid(Specialized.cl) != typeid(c_Cell*))	OP2A::Common::ExceptionGeneral(FromHere(), "FACE::CL is not the pointer of c_Cell.", OP2A::Common::ErrorCode::NotMatchTypeofPointer());
	if (typeid(Specialized.cr) != typeid(c_Cell*))	OP2A::Common::ExceptionGeneral(FromHere(), "FACE::CL is not the pointer of c_Cell.", OP2A::Common::ErrorCode::NotMatchTypeofPointer());

	if (Specialized.cll != NULL && typeid(Specialized.cll) != typeid(c_Cell*) )	OP2A::Common::ExceptionGeneral(FromHere(), "FACE::CLL is not the pointer of c_Cell.", OP2A::Common::ErrorCode::NotMatchTypeofPointer());
	if (Specialized.crr != NULL && typeid(Specialized.crr) != typeid(c_Cell*))	OP2A::Common::ExceptionGeneral(FromHere(), "FACE::CRR is not the pointer of c_Cell.", OP2A::Common::ErrorCode::NotMatchTypeofPointer());

	if (geometry.S < 0.0)	OP2A::Common::ExceptionGeneral(FromHere(), "FACE:: Area/Volume has negative value.", OP2A::Common::ErrorCode::NegativeValue());
}



} /* namespace GRID */
