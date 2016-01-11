/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GridConfig.hpp
 *
 *  Created on: Jan 5, 2016
 *      Author: minkwan
 */

#ifndef GRIDCONFIG_HPP_
#define GRIDCONFIG_HPP_

/*
 * It set the required grid configuration for each simulation modules
 * [Abbreviation Note]
 * 	_FDTD	=> FDTD simulation
 * 	_CFD	=> CFD simulation
 * 	_PIC	=> PIC / DSMC simulation
 */

namespace GRID {

#define	CONST_GRID_AXISSYMMETRIC_ADD		1.0e-9
#define	CONST_GRID_MATH_ZERO				1.0e-20

#define	CONST_GRID_DEFAULT_DATA_SIZE		5
#define	CONST_GRID_MAX_NUM_PATH				1000


#define c_Node	c_Node_v2
#define c_Face	c_Face_v2
#define c_Cell	c_Cell_v2

#define c_GridMap	c_GridMap_v1
#define c_Grid		c_Grid_v2






}



#endif /* GRIDCONFIG_HPP_ */
