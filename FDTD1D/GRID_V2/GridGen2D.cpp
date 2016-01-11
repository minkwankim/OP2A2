/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GridGen2D.cpp
 *
 *  Created on: Jan 5, 2016
 *      Author: minkwan
 */

#include "Gridv2.hpp"

#include "./COMMON/ExceptionGeneral.hpp"
#include "./COMMON/ErrorCode.hpp"


namespace GRID {



void GridGen2D_phaseI_simpleCart(const double X0, const unsigned int Nx, const double Xl,
								const double Y0, const unsigned int Ny, const double Yl,
								c_Grid& grid)
{
	grid.Info.DIM	= 2;

	int nnm	= (Nx+1) * (Ny+1);
	int nfm	= (Nx+1)*Ny	+ (Ny+1)*Nx;
	int ncm	= Nx * Ny;

	grid.Data.nodes.resize(nnm);
	grid.Data.faces.resize(nfm);
	grid.Data.cells.resize(ncm);

	// 1. Create Nodes
	double dX = (Xl - X0) / Nx;
	double dY = (Yl - Y0) / Ny;

	vector<double>	X(Nx+1, 0.0);
	vector<double>	Y(Ny+1, 0.0);

	for (int i_n = 0; i_n <= Nx; i_n++) X[i_n]	= X0 + dX*i_n;
	for (int i_n = 0; i_n <= Ny; i_n++) Y[i_n]	= Y0 + dY*i_n;

	int n = 0;
	for (int j = 0; j <= Ny; j++)
	{
		for (int i = 0; i <= Nx; i++)
		{
			grid.Data.nodes[n].geometry.id = n+1;
			grid.Data.nodes[n].geometry.x[0]	= X[i];
			grid.Data.nodes[n].geometry.x[1]	= Y[j];
			grid.Data.nodes[n].geometry.x[2]	= 0.0;

			grid.Map.n_assign_ID_to_pos(grid.Data.nodes[n].geometry.id, n);
			grid.Map.n_assign_IJK_to_ID(i,j, grid.Data.nodes[n].geometry.id);
			grid.Map.n_assign_ID_to_IJK(grid.Data.nodes[n].geometry.id, i,j);
			n++;
		}
	}

	if (n != nnm)	OP2A::Common::ExceptionGeneral(FromHere(), "Number of Created nodes does not match with calculated NCM", OP2A::Common::ErrorCode::NotMatchDimention());
	grid.Info.NNM	= nnm;



	// 2. Create Cells
	int c = 0;
	for (int j = 0; j <= Ny-1; j++)
	{
		for (int i = 0; i <= Nx-1; i++)
		{
			grid.Data.cells[c].geometry.id	= c + 1;
			grid.Data.cells[c].geometry.type 	= c_quadrilateral;

			grid.Data.cells[c].Specialized.N_List.resize(4);
			grid.Data.cells[c].Specialized.F_List.resize(4);

			grid.Map.c_assign_ID_to_pos(grid.Data.cells[c].geometry.id, c);
			grid.Map.c_assign_IJK_to_ID(i,j, grid.Data.cells[c].geometry.id);
			grid.Map.c_assign_ID_to_IJK(grid.Data.cells[c].geometry.id, i,j);
			c++;
		}
	}

	if (c != ncm)	OP2A::Common::ExceptionGeneral(FromHere(), "Number of Created cells does not match with calculated NCM", OP2A::Common::ErrorCode::NotMatchDimention());
	grid.Info.NCM	= ncm;


	// 3. Create Faces
	int f 	= 0;

	for (int j = 0; j <= Ny; j++)
	{
		for (int i = 0; i <= Nx-1; i++)
		{
			grid.Data.faces[f].geometry.id	= f+1;
			grid.Data.faces[f].geometry.type = f_line;

			grid.Data.faces[f].Specialized.N_List.resize(2);
			grid.Data.faces[f].Specialized.N_List[0]	= &grid.NODE_ijk(i, 	j);
			grid.Data.faces[f].Specialized.N_List[1]	= &grid.NODE_ijk(i+1,j);

			grid.Data.faces[f].Specialized.cl = NULL;
			if (j <= Ny-1)	grid.Data.faces[f].Specialized.cl	= &grid.CELL_ijk(i,j);

			grid.Data.faces[f].Specialized.cr = NULL;
			if (j >= 1)		grid.Data.faces[f].Specialized.cr	= &grid.CELL_ijk(i,j-1);

			grid.Data.faces[f].bc_type.bc 	= interior;
			grid.Data.faces[f].bc_type.type = inside_domain;

			grid.Map.f_assign_ID_to_pos(grid.Data.faces[f].geometry.id, f);
			grid.Map.f_assign_IJK_to_ID(2*i+1, 2*j, grid.Data.faces[f].geometry.id);
			grid.Map.f_assign_ID_to_IJK(grid.Data.faces[f].geometry.id, 2*i+1,2*j);
			f++;
		}
	}

	for (int j = 0; j <= Ny-1; j++)
	{
		for (int i = 0; i <= Nx; i++)
		{
			grid.Data.faces[f].geometry.id	= f+1;
			grid.Data.faces[f].geometry.type = f_line;

			grid.Data.faces[f].Specialized.N_List.resize(2);
			grid.Data.faces[f].Specialized.N_List[0]	= &grid.NODE_ijk(i, 	j);
			grid.Data.faces[f].Specialized.N_List[1]	= &grid.NODE_ijk(i,j+1);

			grid.Data.faces[f].Specialized.cl = NULL;
			if (i >= 1)		grid.Data.faces[f].Specialized.cl	= &grid.CELL_ijk(i-1,j);

			grid.Data.faces[f].Specialized.cr = NULL;
			if (i <= Nx-1)	grid.Data.faces[f].Specialized.cr	= &grid.CELL_ijk(i,j);

			grid.Data.faces[f].bc_type.bc 	= interior;
			grid.Data.faces[f].bc_type.type = inside_domain;

			grid.Map.f_assign_ID_to_pos(grid.Data.faces[f].geometry.id, f);
			grid.Map.f_assign_IJK_to_ID(2*i, 2*j+1, grid.Data.faces[f].geometry.id);
			grid.Map.f_assign_ID_to_IJK(grid.Data.faces[f].geometry.id, 2*i,2*j+1);
			f++;
		}
	}

	if (f != nfm)	OP2A::Common::ExceptionGeneral(FromHere(), "Number of Created faces does not match with calculated NFM", OP2A::Common::ErrorCode::NotMatchDimention());
	grid.Info.NFM	= nfm;
}



void GridGen2D_simpleCart(const double X0, const unsigned int Nx, const double Xl, const double Y0, const unsigned int Ny, const double Yl, c_Grid& grid,
						vector<unsigned int>& BCs, const double gridFactor, bool isAxiSymmetric)
{
	GRID::GridGen2D_phaseI_simpleCart(X0, Nx, Xl, Y0, Ny, Yl, grid);

	// Apply Boundary Conditions
	int i, j, k;
	int pos;
	unsigned int bcIndex;

	// Left
	i	= 0;
	k 	= 0;
	bcIndex = 0;
	for (j = 0; j <= Ny-1; j++)
	{
		grid.FACE_ijk(i,2*j+1,k).bc_type.bc		= BCs[bcIndex];
		grid.FACE_ijk(i,2*j+1,k).bc_type.type	= edge_domain;
	}

	// Right
	i	= 2*Nx;
	k 	= 0;
	bcIndex = 1;
	for (j = 0; j <= Ny-1; j++)
	{
		grid.FACE_ijk(i,2*j+1,k).bc_type.bc		= BCs[bcIndex];
		grid.FACE_ijk(i,2*j+1,k).bc_type.type	= edge_domain;
	}

	// Top
	j	= 2*Ny;
	k 	= 0;
	bcIndex = 2;
	for (i = 0; i <= Nx-1; i++)
	{
		grid.FACE_ijk(2*i+1,j,k).bc_type.bc		= BCs[bcIndex];
		grid.FACE_ijk(2*i+1,j,k).bc_type.type	= edge_domain;
	}

	// Bottom
	j	= 0;
	k 	= 0;
	bcIndex = 3;
	for (i = 0; i <= Nx-1; i++)
	{
		grid.FACE_ijk(2*i+1,j,k).bc_type.bc		= BCs[bcIndex];
		grid.FACE_ijk(2*i+1,j,k).bc_type.type	= edge_domain;
	}


	GRID::Processing_Node(grid, gridFactor, isAxiSymmetric);
	GRID::Processing_Face(grid);
	GRID::Processing_Cell(grid);
	GRID::Processing_Create_Ghost_Cells(grid);


	if (isWallType(BCs[0])|| isWallType(BCs[1]) || isWallType(BCs[2]) || isWallType(BCs[3]))
	{
		GRID::Processing_Calculate_Distance_To_Wall(grid);
	}

	GRID::Processing_Find_Stencil(grid);

}



}
