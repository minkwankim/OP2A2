/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * main.cpp
 *
 *  Created on: Oct 26, 2015
 *      Author: minkwan
 */

#include <iostream>
#include <fstream>
#include <time.h>
#include <omp.h>
#include <iomanip>

#include "./FDTD/FDTD1D.hpp"
#include "./FDTD/GaussianPulse.hpp"


#include "./PHYS/ConstantsEM.hpp"

#include "./IO/Tecplot.hpp"

using namespace OP2A;

int main(int argc, char *argv[])
{
	FDTD::FDTD1Dv2	fdtd1D;


	// Problem setup
	unsigned int maxTimeStep	= 1000;
	unsigned int nfm			= 200;
	double	X0 = 0.0;
	double	XL = 1.0;
	double 	Sc		= 1.0;		// Courant Number



	// Set Configuration
	fdtd1D.setup.maxTimeStep = maxTimeStep;
	fdtd1D.setup.Sc			= Sc;

	// GRID Preparation
	fdtd1D.gridSetup(nfm, X0, XL);
	/*
	fdtd1D.grid = GridGen1Dv2(X0, XL, nfm, 0);
	fdtd1D.face_IC_ID.resize(nfm+1);
	fdtd1D.node_IC_ID.resize(nfm+1+1);

	fdtd1D.face_material_ID.resize(nfm+1);
	fdtd1D.node_material_ID.resize(nfm+1+1);
	*/




	/*
	 * Customizable Section
	 */
	// Material parameters
	fdtd1D.material.resize(3);

	int m_mat = 0;
	double mu_r;
	double eps_r;
	double mu;
	double eps;

	mu_r	= 1.0;
	eps_r	= 1.0;
	mu		= MU0 * mu_r;
	eps		= EPS0 * eps_r;
	fdtd1D.material[m_mat].eps 	 = eps;
	fdtd1D.material[m_mat].mu  	 = mu;
	fdtd1D.material[m_mat].sigma = 0.0;
	fdtd1D.material[m_mat].sigma_m = 0.0;
	m_mat++;

	mu_r	= 1.0;
	eps_r	= 9.0;
	mu		= MU0 * mu_r;
	eps		= EPS0 * eps_r;
	fdtd1D.material[m_mat].eps 	 = eps;
	fdtd1D.material[m_mat].mu  	 = mu;
	fdtd1D.material[m_mat].sigma = 0.0;
	fdtd1D.material[m_mat].sigma_m = 0.0;
	m_mat++;

	mu_r	= 1.0;
	eps_r	= 9.0;
	mu		= MU0 * mu_r;
	eps		= EPS0 * eps_r;
	fdtd1D.material[m_mat].eps 	 	= eps;
	fdtd1D.material[m_mat].mu  	 	= mu;
	fdtd1D.material[m_mat].sigma 	= 0.02 * 2.0*eps/fdtd1D.setup.dt;
	fdtd1D.material[m_mat].sigma_m	= 0.02 * 2.0*mu/fdtd1D.setup.dt;
	m_mat++;

#pragma ivdep
	for (int n = 1; n <= fdtd1D.grid.config.NNM; n++)
	{
		if 		(fdtd1D.grid.nodes[n].geo.x[0] < 0.5)	fdtd1D.node_material_ID[n] = 0;
		else if (fdtd1D.grid.nodes[n].geo.x[0] < 0.9)	fdtd1D.node_material_ID[n] = 1;
		else											fdtd1D.node_material_ID[n] = 2;
	}

#pragma ivdep
	for (int f = 1; f <= fdtd1D.grid.config.NFM; f++)
	{
		if 		(fdtd1D.grid.faces[f].geo.x[0] < 0.5)	fdtd1D.face_material_ID[f] = 0;
		else if (fdtd1D.grid.faces[f].geo.x[0] < 0.9)	fdtd1D.face_material_ID[f] = 1;
		else											fdtd1D.face_material_ID[f] = 2;
	}

	// Initial conditions
	fdtd1D.IC_E0.resize(2);
	fdtd1D.IC_H0.resize(2);

	double E0 = 0.0;
	double H0 = 0.0;


	fdtd1D.IC_E0[0]	= E0;
	fdtd1D.IC_H0[0]	= H0;

#pragma ivdep
	for (int n = 1; n <= fdtd1D.grid.config.NNM; n++)
	{
		fdtd1D.node_IC_ID[n] = 0;
	}

#pragma ivdep
	for (int f = 1; f <= fdtd1D.grid.config.NFM; f++)
	{
		fdtd1D.face_IC_ID[f] = 0;
	}


	// Initializing DATA
	//fdtd1D.Initialize();



	// OPEN FILE TO WRITE
	ofstream		tecplot_file;
	tecplot_file.open("test.plt");
	tecplot_file << "TITLE = \""	<< "TEST" << "\"" << std::endl;
	tecplot_file << "VARIABLES = \"time step\" \"Ez \" " << std::endl;

	ofstream		tecplot_file2;
	tecplot_file2.open("test_time.plt");
	tecplot_file2 << "TITLE = \""	<< "TEST" << "\"" << std::endl;
	tecplot_file2 << "VARIABLES = \"X\" \"Ez \" " << std::endl;


	FDTD::GaussianPulse	sourceEz(30.0, 100.0, 1.0);

	for (int n = 1; n <= maxTimeStep; n++)
	{
		//fdtd1D.CalculateUpdateCoefficient();

		// Update Magnetic field
		//fdtd1D.UpdateH();

		// Update Electric Field
		//fdtd1D.UpdateE();

		// Apply BC
		//fdtd1D.applyBC();

		// Apply Source Term
		//fdtd1D.data.E(0)	= sourceEz.ezInc(n, 0.0);



		//tecplot_file << n << " " << fdtd1D_data.E(50) << std::endl;

		if (n%10 == 0)
		{
			tecplot_file2 << "ZONE" << std::endl;
			tecplot_file2 << "T = \" timestep_" << n << "\" " << std::endl;
			tecplot_file2 << "StrandID = " << n << std::endl;
			tecplot_file2 << "SOLUTIONTIME = " << n << std::endl;
			//for (int i = 0; i <= fdtd1D_grid.NNM+1; i++)
			//{
			//	tecplot_file2 << fdtd1D_grid.Xn[i] << "  " << fdtd1D_data.E(i) << std::endl;
			//}
			tecplot_file2 <<std::endl;

		}

	}


	std::cout << "test grid: " << std::endl;
	std::cout << "TEST:";

}
