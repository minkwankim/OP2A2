/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * NodeV2.hpp
 *
 *  Created on: Nov 30, 2015
 *      Author: minkwan
 */

#ifndef NODEV2_HPP_
#define NODEV2_HPP_

#include <vector>

#include "./GRID/Node_IJK_Info.hpp"
#include <GRID/GridSetupParameter.hpp>

namespace OP2A {
namespace GRID {

class c_Cell;

class Node_V2 {
public:
	Node_V2();
	Node_V2(unsigned int size_data);

	~Node_V2();

public:
	unsigned int 	ID;
	Node_IJK_Info	index;
	double			x[3];
	int				BC;

	std::vector<double>		Wc;
	std::vector<c_Cell*>	C_List;


	std::vector<double>		data;

protected:
	bool m_include;

public:
	void CheckError();
	void resizeData(unsigned int size_data);
	void remove();
	bool isInclude();

};

} /* namespace FDTD */
} /* namespace OP2A */

#endif /* NODEV2_HPP_ */
