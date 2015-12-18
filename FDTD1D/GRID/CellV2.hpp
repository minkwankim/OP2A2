/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * CellV2.hpp
 *
 *  Created on: Nov 30, 2015
 *      Author: minkwan
 */

#ifndef CELLV2_HPP_
#define CELLV2_HPP_

#include <vector>
#include "GridSetupParameter.hpp"
#include "./GRID/Cell_IJK_Info.hpp"

namespace OP2A {
namespace GRID {

class c_Face;
class c_Node;

class Cell_V2 {
public:
	Cell_V2();
	Cell_V2(unsigned int size_data);

	~Cell_V2();

public:
	unsigned int 	ID;
	Cell_IJK_Info	index;

	double			x[3];
	int				BC;
	int				type;

	std::vector<c_Node*> N_List;
	std::vector<c_Face*> F_List;



	double S;

	bool has_Child;
	std::vector<Cell_V2*>	Children;
	Cell_V2*				Parent;

	std::vector<double>		data;

protected:
	bool m_include;
	bool m_needToRefine;

public:
	void applyBoundary();
	void dataUpdateFromChildren();

	/*
	c_Cell*	CS();
	c_Cell*	CE();
	c_Cell*	CN();
	c_Cell*	CW();
*/

	void CheckError();
	void resizeData(unsigned int size_data);

	void remove();
	void include();
	bool isInclude();

	void setRefine(bool flag);
	bool needToRefine();




};

} /* namespace FDTD */
} /* namespace OP2A */

#endif /* CELLV2_HPP_ */
