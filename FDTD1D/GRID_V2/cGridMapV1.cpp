/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cGridMapV1.cpp
 *
 *  Created on: Jan 6, 2016
 *      Author: minkwan
 */

#include <GRID_V2/cGridMapV1.hpp>

#include "./COMMON/Assert.hpp"
#include "./COMMON/ExceptionGeneral.hpp"
#include "./COMMON/ErrorCode.hpp"

namespace GRID {

c_GridMap_v1::c_GridMap_v1() {
	// TODO Auto-generated constructor stub

}

c_GridMap_v1::~c_GridMap_v1() {
	// TODO Auto-generated destructor stub
}





void c_GridMap_v1::c_assign_ID_to_pos(unsigned int id, unsigned int pos)
{
	if(c_ID_to_pos.size() < id + 1)	c_ID_to_pos.resize(id+1, -1);
	c_ID_to_pos[id]	= pos;
}

void c_GridMap_v1::f_assign_ID_to_pos(unsigned int id, unsigned int pos)
{
	if(f_ID_to_pos.size() < id + 1)	f_ID_to_pos.resize(id+1, -1);
	f_ID_to_pos[id]	= pos;
}

void c_GridMap_v1::n_assign_ID_to_pos(unsigned int id, unsigned int pos)
{
	if(n_ID_to_pos.size() < id + 1)	n_ID_to_pos.resize(id+1, -1);
	n_ID_to_pos[id]	= pos;
}

void c_GridMap_v1::g_assign_ID_to_pos(unsigned int id, unsigned int pos)
{
	if(g_ID_to_pos.size() < id + 1)	g_ID_to_pos.resize(id+1, -1);
	g_ID_to_pos[id]	= pos;
}


void c_GridMap_v1::n_assign_IJK_to_ID(unsigned int i, unsigned int j, unsigned int k, unsigned int id)
{
	if(n_IJK_to_ID.size() < i+1)			n_IJK_to_ID.resize(i+1);
	if(n_IJK_to_ID[i].size() < j+1)			n_IJK_to_ID[i].resize(j+1);
	if(n_IJK_to_ID[i][j].size() < k+1)		n_IJK_to_ID[i][j].resize(k+1);

	n_IJK_to_ID[i][j][k]	= id;
}

void c_GridMap_v1::f_assign_IJK_to_ID(unsigned int i, unsigned int j, unsigned int k, unsigned int id)
{
	if(f_IJK_to_ID.size() < i+1)			f_IJK_to_ID.resize(i+1);
	if(f_IJK_to_ID[i].size() < j+1)			f_IJK_to_ID[i].resize(j+1);
	if(f_IJK_to_ID[i][j].size() < k+1)		f_IJK_to_ID[i][j].resize(k+1);

	f_IJK_to_ID[i][j][k]	= id;
}

void c_GridMap_v1::c_assign_IJK_to_ID(unsigned int i, unsigned int j, unsigned int k, unsigned int id)
{
	if(c_IJK_to_ID.size() < i+1)			c_IJK_to_ID.resize(i+1);
	if(c_IJK_to_ID[i].size() < j+1)			c_IJK_to_ID[i].resize(j+1);
	if(c_IJK_to_ID[i][j].size() < k+1)		c_IJK_to_ID[i][j].resize(k+1);

	c_IJK_to_ID[i][j][k]	= id;
}


void c_GridMap_v1::n_assign_ID_to_IJK(unsigned int id, unsigned int i, unsigned int j, unsigned int k)
{
	if(n_ID_to_IJK.size() < id+1)	n_ID_to_IJK.resize(id+1);

	n_ID_to_IJK[id].resize(3);
	n_ID_to_IJK[id][0]	= i;
	n_ID_to_IJK[id][1]	= j;
	n_ID_to_IJK[id][2]	= k;
}

void c_GridMap_v1::f_assign_ID_to_IJK(unsigned int id, unsigned int i, unsigned int j, unsigned int k)
{
	if(f_ID_to_IJK.size() < id+1)	f_ID_to_IJK.resize(id+1);

	f_ID_to_IJK[id].resize(3);
	f_ID_to_IJK[id][0]	= i;
	f_ID_to_IJK[id][1]	= j;
	f_ID_to_IJK[id][2]	= k;
}

void c_GridMap_v1::c_assign_ID_to_IJK(unsigned int id, unsigned int i, unsigned int j, unsigned int k)
{
	if(c_ID_to_IJK.size() < id+1)	c_ID_to_IJK.resize(id+1);

	c_ID_to_IJK[id].resize(3);
	c_ID_to_IJK[id][0]	= i;
	c_ID_to_IJK[id][1]	= j;
	c_ID_to_IJK[id][2]	= k;
}

void c_GridMap_v1::n_assign_IJK_to_ID(unsigned int i, unsigned int j, unsigned int id)	{n_assign_IJK_to_ID(i,j,0, id);};
void c_GridMap_v1::f_assign_IJK_to_ID(unsigned int i, unsigned int j, unsigned int id)	{f_assign_IJK_to_ID(i,j,0, id);}
void c_GridMap_v1::c_assign_IJK_to_ID(unsigned int i, unsigned int j, unsigned int id)	{c_assign_IJK_to_ID(i,j,0, id);}

void c_GridMap_v1::n_assign_ID_to_IJK(unsigned int id, unsigned int i, unsigned int j)	{n_assign_ID_to_IJK(id, i,j,0);};
void c_GridMap_v1::f_assign_ID_to_IJK(unsigned int id, unsigned int i, unsigned int j)	{f_assign_ID_to_IJK(id, i,j,0);};
void c_GridMap_v1::c_assign_ID_to_IJK(unsigned int id, unsigned int i, unsigned int j)	{c_assign_ID_to_IJK(id, i,j,0);};




} /* namespace GRID */
