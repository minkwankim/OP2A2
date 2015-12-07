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
#include <mpi.h>
#include <iomanip>

#include "./FDTD/FDTD1D.hpp"
#include "./FDTD/GaussianPulse.hpp"


#include "./PHYS/ConstantsEM.hpp"

#include "./IO/TecplotV2.hpp"

#include "./GRID/GridV2.hpp"
#include "./GRID/GridSetupParameter.hpp"
#include "./GRID/GridFunctions.hpp"

#include "./COMMON/VectorPointer.hpp"

using namespace OP2A;

int main(int argc, char *argv[])
{
	int size, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);


	// Problem Setting Section
	string	simulation_title	= "Test_FDTD";
	int 	outputFileType		= 1;



	// Grid Generation/Read
	int Nx	= 30;
	int Ny  = 20;
	GRID::c_Grid grid(Nx, Ny);

	int aa;

	//GRID::GridGen2D_v1(-2.0, 100, 4.0, 0.0, 50, 3.0, 1.0, false, grid);


	/*
	for (int l = 0; l <= 2; l++)
	{
		GridSetRefiningFlagGeometry(grid);
		GridSetRefiniement(grid);
	}



	for (int i_n = 0; i_n <= grid.NNM; i_n++)
	{
		grid.Node_Data[i_n].data.resize(1);
		grid.Node_Data[i_n].data[0] = 0;
	}

	grid.Node_Data_Map.insert("test", 0);

	vector<unsigned int> variableFlag(1);
	variableFlag[0] = grid.Node_Data_Map.find("test");



	// Print Result
	IO::TecplotV2 outputTecplot;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	outputTecplot.setCpuNumber(rank);
	outputTecplot.outputFilename = simulation_title.c_str();
	outputTecplot.WriteFile(simulation_title, grid, variableFlag);

*/




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
	fdtd1D.Einc.cdtds 		= fdtd1D.setup.Sc;
	fdtd1D.Einc.delay		= 30.0;
	fdtd1D.Einc.width		= 10.0;


	// GRID Preparation
	fdtd1D.gridSetup(nfm, X0, XL);
	fdtd1D.CalculateTime();

	/*
	 * ==========================
	 * Customizable Section
	 * ==========================
	 */
	int NNM = fdtd1D.grid.config.NNM;
	int NFM = fdtd1D.grid.config.NFM;

	fdtd1D.grid.NODE(1).geo.BC 		= 2;
	fdtd1D.grid.NODE(NNM).geo.BC 	= 2;

	fdtd1D.grid.FACE(0).geo.BC		= 2;
	fdtd1D.grid.FACE(NFM+1).geo.BC	= 2;

	fdtd1D.grid.nodes[50].geo.BC = 3;
	fdtd1D.grid.faces[49].geo.BC = 3;


	// Material parameters
	fdtd1D.material.resize(3);

	int m_mat = 0;
	double mu_r;
	double eps_r;
	double mu;
	double eps;

	// Mat 1
	mu_r	= 1.0;
	eps_r	= 1.0;
	mu		= MU0 * mu_r;
	eps		= EPS0 * eps_r;
	fdtd1D.material[m_mat].eps 	 = eps;
	fdtd1D.material[m_mat].mu  	 = mu;
	fdtd1D.material[m_mat].sigma = 0.0;
	fdtd1D.material[m_mat].sigma_m = 0.0;
	m_mat++;

	// Mat 2
	mu_r	= 1.0;
	eps_r	= 9.0;
	mu		= MU0 * mu_r;
	eps		= EPS0 * eps_r;
	fdtd1D.material[m_mat].eps 	 = eps;
	fdtd1D.material[m_mat].mu  	 = mu;
	fdtd1D.material[m_mat].sigma = 0.0;
	fdtd1D.material[m_mat].sigma_m = 0.0;
	m_mat++;

	// Mat 3
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
	fdtd1D.Initialize();


	// OPEN FILE TO WRITE
	ofstream		tecplot_file;
	tecplot_file.open("test.plt");
	tecplot_file << "TITLE = \""	<< "TEST" << "\"" << std::endl;
	tecplot_file << "VARIABLES = \"time step\" \"Ez \" " << std::endl;

	ofstream		tecplot_file2;
	tecplot_file2.open("test_time.plt");
	tecplot_file2 << "TITLE = \""	<< "TEST" << "\"" << std::endl;
	tecplot_file2 << "VARIABLES = \"X\" \"Ez \" " << std::endl;


	for (int n = 1; n <= maxTimeStep; n++)
	{
		fdtd1D.setup.n = n;
		fdtd1D.CalculateTime();
		fdtd1D.CalculateUpdateCoefficient();

		// Update Magnetic field
		fdtd1D.UpdateH();

		// Update Electric Field
		fdtd1D.UpdateE();


		// Apply Source Term
		//fdtd1D.grid.nodes[50].data(E, 1) += fdtd1D.Einc.ezInc(n, 0.0);


		tecplot_file << n << " " << fdtd1D.grid.nodes[50].data(E, 1) << std::endl;

		if (n%10 == 0)
		{
			tecplot_file2 << "ZONE" << std::endl;
			tecplot_file2 << "T = \" timestep_" << n << "\" " << std::endl;
			tecplot_file2 << "StrandID = " << n << std::endl;
			tecplot_file2 << "SOLUTIONTIME = " << n << std::endl;
			for (int i = 1; i <= fdtd1D.grid.config.NNM; i++)
			{
				tecplot_file2 << fdtd1D.grid.nodes[i].geo.x[0] << "  " << fdtd1D.grid.nodes[i].data(E, 1) << std::endl;
			}
			tecplot_file2 <<std::endl;

		}

	}


	std::cout << "test grid: " << std::endl;
	std::cout << "TEST:";

}
