/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cGridv2.cpp
 *
 *  Created on: Jan 6, 2016
 *      Author: minkwan
 */
#include <cstddef>

#include "./COMMON/ErrorCode.hpp"
#include "./COMMON/ExceptionGeneral.hpp"

#include <GRID_V2/cGridV2.hpp>

namespace GRID {

c_Grid_v2::c_Grid_v2() {
	// TODO Auto-generated constructor stub

}

c_Grid_v2::~c_Grid_v2() {
	// TODO Auto-generated destructor stub
}




c_Node& c_Grid_v2::NODE_id(unsigned int id)
{
	int pos	= Map.n_ID_to_pos[id];
	if (pos < 0)
	{
		std::ostringstream error_message;
		error_message << "Node ID:" << id << "  is not allocated yet. Please check node data";
		OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NotAllocated());
	}

	return (Data.nodes[pos]);
}

c_Face& c_Grid_v2::FACE_id(unsigned int id)
{
	int pos	= Map.f_ID_to_pos[id];
	if (pos < 0)
	{
		std::ostringstream error_message;
		error_message << "Face ID:" << id << "  is not allocated yet. Please check node data";
		OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NotAllocated());
	}

	return (Data.faces[pos]);
}


c_Cell& c_Grid_v2::CELL_id(int id)
{
	if (id > 0)
	{
		int pos	= Map.c_ID_to_pos[id];

		if (pos < 0)
		{
			std::ostringstream error_message;
			error_message << "Cell ID:" << id << "  is not allocated yet. Please check node data";
			OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NotAllocated());
		}

		return (Data.cells[pos]);
	}
	else
	{
		int pos	= Map.g_ID_to_pos[-id];

		if (pos < 0)
		{
			std::ostringstream error_message;
			error_message << "Ghost Cell ID:" << id << "  is not allocated yet. Please check node data";
			OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NotAllocated());
		}

		return (Data.ghosts[pos]);
	}
}



c_Node& c_Grid_v2::NODE_ijk(unsigned int i, unsigned int j, unsigned int k)
{
	return(NODE_id(Map.n_IJK_to_ID[i][j][k]));
}

c_Face& c_Grid_v2::FACE_ijk(unsigned int i, unsigned int j, unsigned int k)
{
	return(FACE_id(Map.f_IJK_to_ID[i][j][k]));
}

c_Cell& c_Grid_v2::CELL_ijk(unsigned int i, unsigned int j, unsigned int k)
{
	return(CELL_id(Map.c_IJK_to_ID[i][j][k]));
}


c_Node& c_Grid_v2::NODE_ijk(unsigned int i, unsigned int j)
{
	return(NODE_ijk(i,j,0));
}

c_Face& c_Grid_v2::FACE_ijk(unsigned int i, unsigned int j)
{
	return(FACE_ijk(i,j,0));
}

c_Cell& c_Grid_v2::CELL_ijk(unsigned int i, unsigned int j)
{
	return(CELL_ijk(i,j,0));
}




} /* namespace GRID */
