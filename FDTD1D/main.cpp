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

/*
#include "./FDTD/FDTD1D.hpp"
#include "./FDTD/GaussianPulse.hpp"


#include "./PHYS/ConstantsEM.hpp"

#include "./IO/TecplotV2.hpp"

#include "./GRID/GridV2.hpp"
#include "./GRID/GridSetupParameter.hpp"
#include "./GRID/GridFunctions.hpp"

#include "./DATA/Variables.hpp"

#include "./NUMERICAL/NumericalMethodUtilities.hpp"
*/

//using namespace OP2A;


/*
 * TEST
 */
#include "./COMMON/Map1D.hpp"

#include "./GRID_V2/Gridv2.hpp"
#include "./IO/TecplotOutput.hpp"
#include "./DATA/Data.hpp"


int main(int argc, char *argv[])
{
	int size, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// Problem Setting Section
	string	simulation_title	= "Test";
	string	mesh_file_name		= "PlasmaGun_ver1.cas";

	int 	outputFileType		= 1;


	// Setup Data Variables
	OP2A::Common::Map1D<string, unsigned int> data_map_face;
	OP2A::Common::Map1D<string, unsigned int> data_map_node;
	OP2A::Common::Map1D<string, unsigned int> data_map_cell;
	std::vector<double> 				data_storage_face;
	std::vector<double> 				data_storage_node;
	std::vector<double> 				data_storage_cell;


	// Grid Generation/Read
	bool useGridFileInput = false;
	int Nx	= 40;	double X0 = -2.0;	double XL = 4.0;
	int Ny  = 20;	double Y0 = 0.0;	double YL = 3.0;
	vector<unsigned int> BCs(4);
	BCs[0]	= 5;
	BCs[1]	= 3;
	BCs[2]	= 3;
	BCs[3]	= GRID::wall;

	GRID::c_Grid	testgrid;
	if (useGridFileInput == true)	GridRead_Fluent(mesh_file_name, testgrid, 1.0, false);
	else							GridGen2D_simpleCart(X0, Nx, XL, Y0, Ny, YL, testgrid, BCs, 1.0, false);



	DATA::c_Data testData = DATA::NONEQ_CFD::dataSampleCell(10, 2, 3);





	for (int n = 0; n <= testgrid.Info.NNM-1; n++)	testgrid.Data.nodes[n].data.resize(2);
	vector<unsigned int> variableFlag(1, 0);
	testgrid.Map.n_Data_Map.insert("temp", 0);



	// Print Result
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	IO::c_Tecplot outputTecplot;
	outputTecplot.setCpuNumber(rank);
	outputTecplot.outputFilename = simulation_title.c_str();
	outputTecplot.WriteFile(simulation_title, testgrid, variableFlag);
	//
	//


	//	GRID::c_Grid grid(Nx, Ny);
	//	GRID::GridGen2D_v1(-2.0, Nx, 4.0, 0.0, Ny, 3.0, 1.0, false, BCs, grid);
	//	GRID::AssignDataNode(grid, data_map_node, data_storage_node);
	//	GRID::AssignDataFace(grid, data_map_face, data_storage_face);
	//	GRID::AssignDataCell(grid, data_map_cell, data_storage_cell);
	//	GRID::GridGen2D_v1_CreateGhostCell(-2.0, Nx, 4.0, 0.0, Ny, 3.0, 1.0, false, BCs, grid);
	//	GRID::GridRefineGeometry(grid, 3);



//	DATA::VariableTMz_face(data_map_face, data_storage_face);
//	DATA::VariableTMz_node(data_map_node, data_storage_node);
//	DATA::VariableTMz_cell(data_map_cell, data_storage_cell);
//
//
//	// Grid Generation/Read
//	int Nx	= 40;
//	int Ny  = 20;
//	vector<unsigned int> BCs(4);
//	BCs[0]	= 5;
//	BCs[1]	= 3;
//	BCs[2]	= 3;
//	BCs[3]	= 2;
//
//	GRID::c_Grid grid(Nx, Ny);
//	GRID::GridGen2D_v1(-2.0, Nx, 4.0, 0.0, Ny, 3.0, 1.0, false, BCs, grid);
//	GRID::AssignDataNode(grid, data_map_node, data_storage_node);
//	GRID::AssignDataFace(grid, data_map_face, data_storage_face);
//	GRID::AssignDataCell(grid, data_map_cell, data_storage_cell);
//	GRID::GridGen2D_v1_CreateGhostCell(-2.0, Nx, 4.0, 0.0, Ny, 3.0, 1.0, false, BCs, grid);
//	GRID::GridRefineGeometry(grid, 3);
//
//
//	//[TEST] Assign value
//	int iv = grid.Cell_Data_Map.find(E);
//	for (int c = 0; c <= grid.Cell_List.size()-1; c++)
//	{
//		double x = grid.Cell_List[c]->x[0];
//		double y = grid.Cell_List[c]->x[1];
//
//		grid.Cell_List[c]->data[iv] = pow(x-1.0, 2.0) + y*y;
//	}
//
//	for (int c = 0; c <= grid.NCM-1; c++)	grid.CELL_data(c).dataUpdateFromChildren();
//
//
//	vector<unsigned int> variableFlagCell(1); variableFlagCell[0] = iv;
//	vector<unsigned int> variableFlagNode(1); variableFlagNode[0] = grid.Node_Data_Map.find(E);
//	GetNodeVariables(grid, variableFlagCell, variableFlagNode, 1);
//
//
//	vector<unsigned int> variableFlag(2);
//	variableFlag[0] = grid.Node_Data_Map.find(E);
//	variableFlag[1] = grid.Node_Data_Map.find(sigma);
//
//
//	// Print Result
//	IO::TecplotV2 outputTecplot;
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//	outputTecplot.setCpuNumber(rank);
//	outputTecplot.outputFilename = simulation_title.c_str();
//	outputTecplot.WriteFile(simulation_title, grid, variableFlag);
//
//
//
//
//
//	FDTD::FDTD1Dv2	fdtd1D;
//	// Problem setup
//	unsigned int maxTimeStep	= 1000;
//	unsigned int nfm			= 200;
//	double	X0 = 0.0;
//	double	XL = 1.0;
//	double 	Sc		= 1.0;		// Courant Number
//
//	// Set Configuration
//	fdtd1D.setup.maxTimeStep = maxTimeStep;
//	fdtd1D.setup.Sc			= Sc;
//	fdtd1D.Einc.cdtds 		= fdtd1D.setup.Sc;
//	fdtd1D.Einc.delay		= 30.0;
//	fdtd1D.Einc.width		= 10.0;
//
//
//	// GRID Preparation
//	fdtd1D.gridSetup(nfm, X0, XL);
//	fdtd1D.CalculateTime();
//
//	/*
//	 * ==========================
//	 * Customizable Section
//	 * ==========================
//	 */
//	int NNM = fdtd1D.grid.config.NNM;
//	int NFM = fdtd1D.grid.config.NFM;
//
//	fdtd1D.grid.NODE(1).geo.BC 		= 2;
//	fdtd1D.grid.NODE(NNM).geo.BC 	= 2;
//
//	fdtd1D.grid.FACE(0).geo.BC		= 2;
//	fdtd1D.grid.FACE(NFM+1).geo.BC	= 2;
//
//	fdtd1D.grid.nodes[50].geo.BC = 3;
//	fdtd1D.grid.faces[49].geo.BC = 3;
//
//
//	// Material parameters
//	fdtd1D.material.resize(3);
//
//	int m_mat = 0;
//	double mu_r;
//	double eps_r;
//	double mu;
//	double eps;
//
//	// Mat 1
//	mu_r	= 1.0;
//	eps_r	= 1.0;
//	mu		= MU0 * mu_r;
//	eps		= EPS0 * eps_r;
//	fdtd1D.material[m_mat].eps 	 = eps;
//	fdtd1D.material[m_mat].mu  	 = mu;
//	fdtd1D.material[m_mat].sigma = 0.0;
//	fdtd1D.material[m_mat].sigma_m = 0.0;
//	m_mat++;
//
//	// Mat 2
//	mu_r	= 1.0;
//	eps_r	= 9.0;
//	mu		= MU0 * mu_r;
//	eps		= EPS0 * eps_r;
//	fdtd1D.material[m_mat].eps 	 = eps;
//	fdtd1D.material[m_mat].mu  	 = mu;
//	fdtd1D.material[m_mat].sigma = 0.0;
//	fdtd1D.material[m_mat].sigma_m = 0.0;
//	m_mat++;
//
//	// Mat 3
//	mu_r	= 1.0;
//	eps_r	= 9.0;
//	mu		= MU0 * mu_r;
//	eps		= EPS0 * eps_r;
//	fdtd1D.material[m_mat].eps 	 	= eps;
//	fdtd1D.material[m_mat].mu  	 	= mu;
//	fdtd1D.material[m_mat].sigma 	= 0.02 * 2.0*eps/fdtd1D.setup.dt;
//	fdtd1D.material[m_mat].sigma_m	= 0.02 * 2.0*mu/fdtd1D.setup.dt;
//	m_mat++;
//
//#pragma ivdep
//	for (int n = 1; n <= fdtd1D.grid.config.NNM; n++)
//	{
//		if 		(fdtd1D.grid.nodes[n].geo.x[0] < 0.5)	fdtd1D.node_material_ID[n] = 0;
//		else if (fdtd1D.grid.nodes[n].geo.x[0] < 0.9)	fdtd1D.node_material_ID[n] = 1;
//		else											fdtd1D.node_material_ID[n] = 2;
//	}
//
//#pragma ivdep
//	for (int f = 1; f <= fdtd1D.grid.config.NFM; f++)
//	{
//		if 		(fdtd1D.grid.faces[f].geo.x[0] < 0.5)	fdtd1D.face_material_ID[f] = 0;
//		else if (fdtd1D.grid.faces[f].geo.x[0] < 0.9)	fdtd1D.face_material_ID[f] = 1;
//		else											fdtd1D.face_material_ID[f] = 2;
//	}
//
//	// Initial conditions
//	fdtd1D.IC_E0.resize(2);
//	fdtd1D.IC_H0.resize(2);
//
//	double E0 = 0.0;
//	double H0 = 0.0;
//
//
//	fdtd1D.IC_E0[0]	= E0;
//	fdtd1D.IC_H0[0]	= H0;
//
//#pragma ivdep
//	for (int n = 1; n <= fdtd1D.grid.config.NNM; n++)
//	{
//		fdtd1D.node_IC_ID[n] = 0;
//	}
//
//#pragma ivdep
//	for (int f = 1; f <= fdtd1D.grid.config.NFM; f++)
//	{
//		fdtd1D.face_IC_ID[f] = 0;
//	}
//
//
//
//	// Initializing DATA
//	fdtd1D.Initialize();
//
//
//	// OPEN FILE TO WRITE
//	ofstream		tecplot_file;
//	tecplot_file.open("test.plt");
//	tecplot_file << "TITLE = \""	<< "TEST" << "\"" << std::endl;
//	tecplot_file << "VARIABLES = \"time step\" \"Ez \" " << std::endl;
//
//	ofstream		tecplot_file2;
//	tecplot_file2.open("test_time.plt");
//	tecplot_file2 << "TITLE = \""	<< "TEST" << "\"" << std::endl;
//	tecplot_file2 << "VARIABLES = \"X\" \"Ez \" " << std::endl;
//
//
//	for (int n = 1; n <= maxTimeStep; n++)
//	{
//		fdtd1D.setup.n = n;
//		fdtd1D.CalculateTime();
//		fdtd1D.CalculateUpdateCoefficient();
//
//		// Update Magnetic field
//		fdtd1D.UpdateH();
//
//		// Update Electric Field
//		fdtd1D.UpdateE();
//
//
//		// Apply Source Term
//		//fdtd1D.grid.nodes[50].data(E, 1) += fdtd1D.Einc.ezInc(n, 0.0);
//
//
//		tecplot_file << n << " " << fdtd1D.grid.nodes[50].data(E, 1) << std::endl;
//
//		if (n%10 == 0)
//		{
//			tecplot_file2 << "ZONE" << std::endl;
//			tecplot_file2 << "T = \" timestep_" << n << "\" " << std::endl;
//			tecplot_file2 << "StrandID = " << n << std::endl;
//			tecplot_file2 << "SOLUTIONTIME = " << n << std::endl;
//			for (int i = 1; i <= fdtd1D.grid.config.NNM; i++)
//			{
//				tecplot_file2 << fdtd1D.grid.nodes[i].geo.x[0] << "  " << fdtd1D.grid.nodes[i].data(E, 1) << std::endl;
//			}
//			tecplot_file2 <<std::endl;
//
//		}
//
//	}



	std::cout << "test grid: " << std::endl;
	std::cout << "TEST:";

}
