/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cGridMapV1.hpp
 *
 *  Created on: Jan 6, 2016
 *      Author: minkwan
 */

#ifndef CGRIDMAPV1_HPP_
#define CGRIDMAPV1_HPP_

#include <vector>
#include "./COMMON/Map1D.hpp"

using namespace std;

namespace GRID {

class c_GridMap_v1 {
public:
	c_GridMap_v1();
	~c_GridMap_v1();

public:
	vector<int>	c_ID_to_pos;
	vector<int>	f_ID_to_pos;
	vector<int>	n_ID_to_pos;
	vector<int>	g_ID_to_pos;

	vector< vector < vector<unsigned int > > > 	n_IJK_to_ID;
	vector< vector < vector<unsigned int > > > 	c_IJK_to_ID;
	vector< vector < vector<unsigned int > > > 	f_IJK_to_ID;

	vector< vector<unsigned int> >	n_ID_to_IJK;
	vector< vector<unsigned int> >	f_ID_to_IJK;
	vector< vector<unsigned int> >	c_ID_to_IJK;

	// Data Index Section
	OP2A::Common::Map1D<string, unsigned int>	n_Data_Map;
	OP2A::Common::Map1D<string, unsigned int>	f_Data_Map;
	OP2A::Common::Map1D<string, unsigned int>	c_Data_Map;



public:
	void c_assign_ID_to_pos(unsigned int id, unsigned int pos);
	void f_assign_ID_to_pos(unsigned int id, unsigned int pos);
	void n_assign_ID_to_pos(unsigned int id, unsigned int pos);
	void g_assign_ID_to_pos(unsigned int id, unsigned int pos);

	void n_assign_IJK_to_ID(unsigned int i, unsigned int j, unsigned int k, unsigned int id);
	void f_assign_IJK_to_ID(unsigned int i, unsigned int j, unsigned int k, unsigned int id);
	void c_assign_IJK_to_ID(unsigned int i, unsigned int j, unsigned int k, unsigned int id);

	void n_assign_ID_to_IJK(unsigned int id, unsigned int i, unsigned int j, unsigned int k);
	void f_assign_ID_to_IJK(unsigned int id, unsigned int i, unsigned int j, unsigned int k);
	void c_assign_ID_to_IJK(unsigned int id, unsigned int i, unsigned int j, unsigned int k);

	void n_assign_IJK_to_ID(unsigned int i, unsigned int j, unsigned int id);
	void f_assign_IJK_to_ID(unsigned int i, unsigned int j, unsigned int id);
	void c_assign_IJK_to_ID(unsigned int i, unsigned int j, unsigned int id);

	void n_assign_ID_to_IJK(unsigned int id, unsigned int i, unsigned int j);
	void f_assign_ID_to_IJK(unsigned int id, unsigned int i, unsigned int j);
	void c_assign_ID_to_IJK(unsigned int id, unsigned int i, unsigned int j);

};

} /* namespace GRID */

#endif /* CGRIDMAPV1_HPP_ */
