/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FDTD1D.hpp
 *
 *  Created on: Nov 18, 2015
 *      Author: minkwan
 */

#ifndef FDTD1D_HPP_
#define FDTD1D_HPP_

#include "./FDTD/FDTD1DDATA.hpp"
#include "./FDTD/FDTD1D_Grid.hpp"
#include "./FDTD/FDTD1D_Setup.hpp"
#include "./FDTD/FDTD1D_MATERIAL.hpp"


namespace OP2A {
namespace FDTD {

class FDTD1D {
public:
	FDTD1D();
	~FDTD1D();


public:
	string	title;
	string	filename_out;


	FDTD1D_SETUP 	setup;
	//
	FDTD1D_GRID  	grid;
	FDTD1D_DATA  	data;
	FDTD1D_MATERIAL material;


public:
	void SetDataSize();
	void Initialize();

	void UpdateE();
	void UpdateH();
	void CalculateUpdateCoefficient();



	void applyBC();
	void applyTFSFboundaryH(unsigned int i_node, unsigned int n_time);
	void applyTFSFboundaryE(unsigned int i_node, unsigned int n_time);
};


class FDTD1Dv2 {
public:
	FDTD1Dv2();
	~FDTD1Dv2();


public:
	string	title;
	string	filename_out;

	FDTD1D_SETUP 				setup;
	//FDTD1D_GRIDv2  			grid;
	Grid1D						grid;


	vector<FDTD1D_MATERIALv2>	material;
	vector<double>				IC_E0;
	vector<double>				IC_H0;

	vector<int>	face_material_ID;
	vector<int>	node_material_ID;
	vector<int>	face_IC_ID;
	vector<int>	node_IC_ID;




public:
	void gridSetup(unsigned int nfm, double x0, double xL);
	void Initialize();

	void UpdateE();
	void UpdateH();
	void CalculateUpdateCoefficient();



	void applyBC();
	void applyTFSFboundaryH(unsigned int i_node, unsigned int n_time);
	void applyTFSFboundaryE(unsigned int i_node, unsigned int n_time);
};



} /* namespace FDTD */
} /* namespace OP2A */

#endif /* FDTD1D_HPP_ */
