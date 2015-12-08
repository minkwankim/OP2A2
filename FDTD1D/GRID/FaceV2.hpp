/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FaceV2.hpp
 *
 *  Created on: Nov 30, 2015
 *      Author: minkwan
 */

#ifndef FACEV2_HPP_
#define FACEV2_HPP_

#include <vector>
#include "GridSetupParameter.hpp"
#include "./GRID/Face_IJK_Info.hpp"

namespace OP2A {
namespace GRID {

class c_Cell;
class c_Node;

class Face_V2 {
public:
	Face_V2();
	Face_V2(unsigned int size_data);
	~Face_V2();

public:
	unsigned int 	ID;
	Face_IJK_Info	index;

	double			x[3];
	int				BC;
	int				type;

	std::vector<c_Node*> N_List;
	c_Cell* CL;
	c_Cell* CR;

	double n[3][3];
	double S;
	double distWall;	// distance to wall
	double nDotWall;	// dot product between normal vector and wall vector

	bool has_Child;
	std::vector<Face_V2*>	Children;
	Face_V2*				Parent;

	std::vector<double>		data;

protected:
	bool m_include;

public:
	void applyBoundary();


	void CheckError();
	void resizeData(unsigned int size_data);
	void remove();
	bool isInclude();





};

} /* namespace FDTD */
} /* namespace OP2A */

#endif /* FACEV2_HPP_ */
