/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * CELLIJKINFO.hpp
 *
 *  Created on: Nov 30, 2015
 *      Author: minkwan
 */

#ifndef CELLIJKINFO_HPP_
#define CELLIJKINFO_HPP_


#include "GridSetupParameter.hpp"

namespace OP2A {
namespace GRID {



class Cell_IJK_Info {
public:
	Cell_IJK_Info();
	~Cell_IJK_Info();

public:
	double i;
	double j;
	double k;

	unsigned int lvl_refine;
	unsigned int location;
	std::vector<unsigned int> location_history;

public:

};




class Cell_IJK
{
public:
	Cell_IJK();
	Cell_IJK(unsigned int size_max_lvl, unsigned int dim);

	~Cell_IJK();

protected:
	std::vector< std::vector<unsigned int> > m_subIndex;

public:
	void resize(unsigned int size_max_lvl, unsigned int dim);
	unsigned int& operator()(const unsigned i, const unsigned j);


public:

};

} /* namespace FDTD */
} /* namespace OP2A */

#endif /* CELLIJKINFO_HPP_ */
