/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GridGen2D_v1.cpp
 *
 *  Created on: Dec 1, 2015
 *      Author: minkwan
 */

#include "./COMMON/VectorPointer.hpp"
#include "./COMMON/ExceptionGeneral.hpp"
#include "./COMMON/ErrorCode.hpp"

#include "GRID/GridV2.hpp"
#include "GRID/GridFunctions.hpp"


namespace OP2A {
namespace GRID {

void GridGen2D_v1(const double X0, const unsigned int Nx, const double Xl,
				const double Y0, const unsigned int Ny, const double Yl,
				const double gridFactor, bool axysymmetric,
				c_Grid& grid2D)
{
	grid2D.DIM	= 2;
	GRID::c_Node	node;
	GRID::c_Face	face;
	GRID::c_Cell	cell;


	// 1. Create Nodes
	int nnm	= (Nx+1) * (Ny+1);
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
			node.index.i	= i;
			node.index.j 	= j;
			node.index.k 	= 0;
			node.x[0]	= X[i];
			node.x[1]	= Y[j];
			node.x[2]	= 0.0;
			node.BC = GridShapeFunctions(X[i], Y[j], 0.0);

			grid2D.NODE_add(i, j, node);
			n++;
		}
	}

	if (n == nnm)	grid2D.NNM = n;
	else			Common::ExceptionGeneral(FromHere(), "Number of Created nodes does not match with calculated NCM", Common::ErrorCode::NotMatchDimention());






	// 2. Create Faces
	int nfm	= (Nx+1)*Ny	+ (Ny+1)*Nx;
	int f 	= 0;
	int direction;

	// A. X-direction
	direction = 1;
	for (int j = 0; j <= Ny-1; j++)
	{
		for (int i = 0; i <= Nx; i++)
		{
			face.index.i = i;
			face.index.j = j + 0.5;
			face.index.k = 0;
			face.index.lvl_refine = 0;
			face.index.direction = direction;

			face.N_List.resize(2);
			face.N_List[0]	= grid2D.NODE(i, j);
			face.N_List[1]	= grid2D.NODE(i, j + 1);
			if (face.N_List[0] == NULL)	Common::ExceptionGeneral(FromHere(), "Problem(NODE0) in x-direction face creation. Please check nodes", Common::ErrorCode::NotAllocated());
			if (face.N_List[1] == NULL)	Common::ExceptionGeneral(FromHere(), "Problem(NODE1) in x-direction face creation. Please check nodes", Common::ErrorCode::NotAllocated());

			face.Parent = NULL;
			face.has_Child = false;
			face.applyBoundary();

			grid2D.FACE_add(face.index.i, face.index.j, face);
			f++;
		}
	}

	// B. Y-direction
	direction = 2;
	for (int j = 0; j <= Ny; j++)
	{
		for (int i = 0; i <= Nx-1; i++)
		{
			face.index.i = i + 0.5;
			face.index.j = j;
			face.index.k = 0;
			face.index.lvl_refine = 0;
			face.index.direction = direction;

			face.N_List.resize(2);
			face.N_List[0] = grid2D.NODE(i,   j);
			face.N_List[1] = grid2D.NODE(i+1, j);
			if (face.N_List[0] == NULL)	Common::ExceptionGeneral(FromHere(), "Problem(NODE0) in y-direction face creation. Please check nodes", Common::ErrorCode::NotAllocated());
			if (face.N_List[1] == NULL)	Common::ExceptionGeneral(FromHere(), "Problem(NODE1) in y-direction face creation. Please check nodes", Common::ErrorCode::NotAllocated());

			face.Parent = NULL;
			face.has_Child = false;
			face.applyBoundary();

			grid2D.FACE_add(face.index.i, face.index.j, face);
			f++;
		}
	}

	if (f == nfm)	grid2D.NFM = f;
	else			Common::ExceptionGeneral(FromHere(), "Number of Created faces does not match with calculated NFM", Common::ErrorCode::NotMatchDimention());


	// 3. Create Cells
	int ncm	= Nx * Ny;
	int c = 0;
	for (int j = 0; j <= Ny-1; j++)
	{
		for (int i = 0; i <= Nx-1; i++)
		{
			cell.index.i = i + 0.5;
			cell.index.j = j + 0.5;
			cell.index.k = 0;
			cell.index.location = 0;
			cell.index.lvl_refine = 0;
			cell.index.location_history.resize(1);
			cell.index.location_history[0] = 0;

			cell.N_List.resize(4);
			cell.N_List[0] = grid2D.NODE(i,   j);
			cell.N_List[1] = grid2D.NODE(i+1, j);
			cell.N_List[2] = grid2D.NODE(i+1, j+1);
			cell.N_List[3] = grid2D.NODE(i,   j+1);
			if (cell.N_List[0] == NULL)	Common::ExceptionGeneral(FromHere(), "Problem(NODE0) in cell creation. Please check nodes", Common::ErrorCode::NotAllocated());
			if (cell.N_List[1] == NULL)	Common::ExceptionGeneral(FromHere(), "Problem(NODE1) in cell creation. Please check nodes", Common::ErrorCode::NotAllocated());
			if (cell.N_List[2] == NULL)	Common::ExceptionGeneral(FromHere(), "Problem(NODE2) in cell creation. Please check nodes", Common::ErrorCode::NotAllocated());
			if (cell.N_List[3] == NULL)	Common::ExceptionGeneral(FromHere(), "Problem(NODE3) in cell creation. Please check nodes", Common::ErrorCode::NotAllocated());


			cell.F_List.resize(4);
			cell.F_List[0] = grid2D.FACE(i+0.5, j);
			cell.F_List[1] = grid2D.FACE(i+1, 	j+0.5);
			cell.F_List[2] = grid2D.FACE(i+0.5, j+1);
			cell.F_List[3] = grid2D.FACE(i, 	j+0.5);
			if (cell.F_List[0] == NULL)	Common::ExceptionGeneral(FromHere(), "Problem(FACE0) in cell creation. Please check nodes", Common::ErrorCode::NotAllocated());
			if (cell.F_List[1] == NULL)	Common::ExceptionGeneral(FromHere(), "Problem(FACE1) in cell creation. Please check nodes", Common::ErrorCode::NotAllocated());
			if (cell.F_List[2] == NULL)	Common::ExceptionGeneral(FromHere(), "Problem(FACE2) in cell creation. Please check nodes", Common::ErrorCode::NotAllocated());
			if (cell.F_List[3] == NULL)	Common::ExceptionGeneral(FromHere(), "Problem(FACE3) in cell creation. Please check nodes", Common::ErrorCode::NotAllocated());

			cell.Parent = NULL;
			cell.has_Child = false;
			cell.applyBoundary();

			grid2D.CELL_add(cell.index.i, cell.index.j, cell);
			c++;
		}
	}

	if (c == ncm)	grid2D.NCM = c;
	else			Common::ExceptionGeneral(FromHere(), "Number of Created cells does not match with calculated NCM", Common::ErrorCode::NotMatchDimention());




	// Assign Stencil for faces	& Neighboring cells on Node
	double c_i, c_j, c_k;
	c_Cell* cell_ptr;
	for (int j = 0; j <= Ny-1; j++)
	{
		for (int i = 0; i <= Nx-1; i++)
		{
			c_i = i + 0.5;
			c_j = j + 0.5;
			c_k = 0;
			cell_ptr	= grid2D.CELL(c_i, c_j, c_k);

			if (cell_ptr != NULL)
			{
				if (cell_ptr->F_List[0]->CR == NULL)	cell_ptr->F_List[0]->CR = cell_ptr;
				if (cell_ptr->F_List[1]->CL == NULL)	cell_ptr->F_List[1]->CL = cell_ptr;
				if (cell_ptr->F_List[2]->CL == NULL)	cell_ptr->F_List[2]->CL = cell_ptr;
				if (cell_ptr->F_List[3]->CR == NULL)	cell_ptr->F_List[3]->CR = cell_ptr;

				for (int i_n = 0; i_n <= cell_ptr->N_List.size()-1; i_n++)	cell_ptr->N_List[i_n]->C_List.push_back(cell_ptr);
			}
		}
	}


	grid2D.NODE_ListUpdate();
	grid2D.FACE_ListUpdate();
	grid2D.CELL_ListUpdate();


	for (unsigned int i_n = 0; i_n <= grid2D.NNM-1; i_n++)
	{
		Common::VectorPointer::removeNULL<c_Cell>(grid2D.NODE_data(i_n).C_List);
	}



	// CREATE GHOST CELLS
	for (unsigned int i_f = 0; i_f <= grid2D.NFM-1; i_f++)
	{
		if (grid2D.FACE_data(i_f).BC != 0)
		{
			if (grid2D.FACE_data(i_f).CL == NULL)	CreateGhostCell(grid2D, grid2D.FACE_data(i_f), 0);
			if (grid2D.FACE_data(i_f).CR == NULL)	CreateGhostCell(grid2D, grid2D.FACE_data(i_f), 1);
		}
	}


	GridProcessing_v2(gridFactor, axysymmetric, grid2D);


	// Error check
	for (int i_n = 0; i_n <= grid2D.NNM-1; i_n++)	grid2D.NODE_data(i_n).CheckError();
	for (int i_f = 0; i_f <= grid2D.NFM-1; i_f++)	grid2D.FACE_data(i_f).CheckError();
	for (int i_c = 0; i_c <= grid2D.NCM-1; i_c++)	grid2D.CELL_data(i_c).CheckError();
}





}
}
