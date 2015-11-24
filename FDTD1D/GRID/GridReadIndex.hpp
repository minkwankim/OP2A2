/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GridReadIndex.hpp
 *
 *  Created on: Nov 16, 2015
 *      Author: minkwan
 */

#ifndef GRIDREADINDEX_HPP_
#define GRIDREADINDEX_HPP_


namespace OP2A{

/*
 * =============================================
 * 	A. Grid Date reading
 * =============================================
 */
// 1. FLUENT grid
#define FLUENT							0

#define FLU_INDEX_COMMENT 					0
#define FLU_INDEX_DIMENSIONS 				2
#define FLU_INDEX_NODE 						10
#define FLU_INDEX_PERIODIC_SHADOW_FACES 	18
#define FLU_INDEX_CELL 						12
#define FLU_INDEX_FACE 						13
#define FLU_INDEX_BC 						45
#define FLU_INDEX_FACE_TREE 				59
#define FLU_INDEX_CELL_TREE 				58
#define FLU_INDEX_INTERFACE_FACE_PARENTS 	61





}


#endif /* GRIDREADINDEX_HPP_ */
