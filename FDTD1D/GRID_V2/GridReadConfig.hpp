/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GridReadConfigure.hpp
 *
 *  Created on: Jan 11, 2016
 *      Author: minkwan
 */

#ifndef GRIDREADCONFIGURE_HPP_
#define GRIDREADCONFIGURE_HPP_


namespace GRID {


#define CONST_MAX_ZONE_READ_MESH	1000

enum GridFluent
{
	FLU_INDEX_COMMENT 					= 0,
	FLU_INDEX_DIMENSIONS				= 2,
	FLU_INDEX_NODE  					= 10,
	FLU_INDEX_PERIODIC_SHADOW_FACES 	= 18,
	FLU_INDEX_CELL 						= 12,
	FLU_INDEX_FACE 						= 13,
	FLU_INDEX_BC 						= 45,
	FLU_INDEX_FACE_TREE 				= 59,
	FLU_INDEX_CELL_TREE 				= 58,
	FLU_INDEX_INTERFACE_FACE_PARENTS	= 61,

	FLU_F_MIXED							= 0,
	FLU_F_LINE							= 2,
	FLU_F_TRIANGLE						= 3,
	FLU_F_QUADRILATERAL					= 4,

	FLU_C_GHOST							= -1,
	FLU_C_MIXED							= 0,
	FLU_C_TRIANGLE						= 1,
	FLU_C_TETRAHEDRON					= 2,
	FLU_C_QUADRILATERAL					= 3,
	FLU_C_HEXAHEDRON					= 4,
	FLU_C_PYRAMID						= 5,
	FLU_C_PRISM							= 6,
	FLU_C_WEDGE 						= 6
};




}




#endif /* GRIDREADCONFIGURE_HPP_ */
