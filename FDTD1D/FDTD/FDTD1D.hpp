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
#include "./FDTD/GaussianPulse.hpp"

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

	GaussianPulse	Einc;

public:
	void SetDataSize();
	void Initialize();

	void CalculateUpdateCoefficient();



	void UpdateE();
	void UpdateH();



	void applyBC();
	void applyTFSFboundaryH(unsigned int i_node, unsigned int n_time);
	void applyTFSFboundaryE(unsigned int i_node, unsigned int n_time);
};




// Ver2
class FDTD1Dv2
{
public:
	FDTD1Dv2();
	~FDTD1Dv2();


public:
	string	title;			// Simulation title
	string	filename_out;	// Results file name

	FDTD1D_SETUP 				setup;		// Simulation Setup Data
	//FDTD1D_GRIDv2  			grid;
	Grid1D						grid;		// Grid Data (including flow data_

	vector<FDTD1D_MATERIALv2>	material;	// Material Data
	vector<double>				IC_E0;		// Initial Condition
	vector<double>				IC_H0;		// Initial Condition

	vector<int>	face_material_ID;			// Material info of faces
	vector<int>	node_material_ID;			// Material info of nodes
	vector<int>	face_IC_ID;					// IC info of face
	vector<int>	node_IC_ID;					// IN info of node

	GaussianPulse	Einc;


public:
	void gridSetup(unsigned int nfm, double x0, double xL);
	void Initialize();
	void CalculateTime();

	void CalculateUpdateCoefficient();
	void UpdateH();
	void applyBC_H();
	void applyBC_H(GRID::Face& ghost);


	void UpdateE();
	void applyBC_E();
	void applyBC_E(GRID::Node& node);


	void applyTFSFboundary_H();
	void applyTFSFboundary_H(GRID::Face &face);

	void applyTFSFboundary_E();
	void applyTFSFboundary_E(GRID::Node &node);

};



} /* namespace FDTD */
} /* namespace OP2A */

#endif /* FDTD1D_HPP_ */
