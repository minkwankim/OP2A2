/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GeometryCommon.hpp
 *
 *  Created on: Nov 4, 2015
 *      Author: minkwan
 */

#ifndef GEOMETRYCOMMON_HPP_
#define GEOMETRYCOMMON_HPP_

namespace OP2A{
namespace GRID{

enum CellTypeCart
{
	cc_flow		= 0,
	cc_surface	= 1,
	cc_solid	= 2
};

enum CellType
{
	c_ghost			= -1,
	c_mixed			= 0,
	c_line			= 1,
	c_triangle		= 2,
	c_tetrahedron	= 3,
	c_quadrilateral = 4,
	c_hexahedron	= 5,
	c_pyramid		= 6,
	c_wedge			= 7
};

enum FaceType
{
	f_ghost				= -1,
	f_mixed				= 0,
	f_point				= 1,
	f_line				= 2,
	f_triangle			= 3,
	f_quadrilateral 	= 4
};

enum BCType
{
	bc_interior			= 0,
	bc_wall				= 1,
	bc_inlet			= 2,
	bc_outlet			= 3,
	bc_freestream		= 4,
	bc_symmetric		= 5,
	bc_axis				= 6,
	bc_anode			= 7,
	bc_cathode			= 8,
	bc_dielectricwall	= 9
};



class GeometryCommon {
	/*
	 * I. Constructor and Destructor
	 */
public:
	GeometryCommon();
	~GeometryCommon();


	/*
	 * II. Member Variables
	 */
public:
	int	ID;			// id number (negative value means a ghost property)
	double x[3];	// position vector
	double S;		// Area or volume (for node, it is ZERO)
	int	type;		// type node/face/cell (for node, it is ZERO. Others use the defined type index)
	int	BC;			// Index of Boundary condition



	/*
	 * III. Member Functions
	 */
public:


};


}
}
#endif /* GEOMETRYCOMMON_HPP_ */
