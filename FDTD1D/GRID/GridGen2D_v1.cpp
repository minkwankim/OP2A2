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

#include "GRID/GridV2.hpp"
#include "GRID/GridFunctions.hpp"


namespace OP2A {
namespace GRID {

/*

void GridGen2D_v1(const double X0, const unsigned int Nx, const double Xl,
				const double Y0, const unsigned int Ny, const double Yl,
				const double gridFactor, bool axysymmetric,
				c_Grid& grid2D)
{
	// Set the size of Node Locator
	vector<unsigned int>


	grid2D.DIM	= 2;

	// 1. Create Nodes
	double dX = (Xl - X0) / Nx;
	double dY = (Yl - Y0) / Ny;

	vector<double>	X(Nx+2, 0.0);
	vector<double>	Y(Ny+2, 0.0);

	for (int i_n = 1; i_n <= Nx+1; i_n++) X[i_n]	= X0 + dX*(i_n-1);
	for (int i_n = 1; i_n <= Ny+1; i_n++) Y[i_n]	= Y0 + dY*(i_n-1);

	int n = 0;
	int id = 1;

	for (int j = 1; j <= Ny+1; j++)
	{
		for (int i = 1; i <= Nx+1; i++)
		{
			grid2D.Node_Data.resize(n+1);

			grid2D.Node_Data[n].ID = id;
			grid2D.Node_Data[n].index.i = i;
			grid2D.Node_Data[n].index.j = j;
			grid2D.Node_Data[n].index.k = 0;

			grid2D.Node_Data[n].x[0]	= X[i];
			grid2D.Node_Data[n].x[1]	= Y[j];
			grid2D.Node_Data[n].x[2]	= 0.0;

			grid2D.Node_Data[n].BC = GridShapeFunctions(grid2D.Node_Data[n].x[0], grid2D.Node_Data[n].x[1], grid2D.Node_Data[n].x[2]);

			//grid2D.Node_Index_Map.insert(i, j, 0, n);

			if(grid2D.Node_Data[n].BC >= 0)	grid2D.Node_List.push_back(&grid2D.Node_Data[n]);
			else							grid2D.Node_Data[n].remove();

			n++;
			id++;
		}
	}

	grid2D.NNM = n;
	grid2D.whereisNode.resize(grid2D.NNM+1);
	for (n = 0; n <= grid2D.Node_Data.size()-1; n++)	grid2D.whereisNode[grid2D.Node_Data[n].ID]	= n;



	// 2. Create Faces
	int f = 0;
	id = 1;
	int direction;

	// A. X-direction
	direction = 1;
	for (int j = 1; j <= Ny; j++)
	{
		for (int i = 1; i <= Nx+1; i++)
		{
			grid2D.Face_Data.resize(f+1);

			grid2D.Face_Data[f].ID = id;
			grid2D.Face_Data[f].index.i = i;
			grid2D.Face_Data[f].index.j = j + 0.5;
			grid2D.Face_Data[f].index.k = 0;
			grid2D.Face_Data[f].index.lvl_refine = 0;
			grid2D.Face_Data[f].index.direction = direction;

			grid2D.Face_Data[f].N_List.resize(2);
			grid2D.Face_Data[f].N_List[0]	= grid2D.NODE(i, j);
			grid2D.Face_Data[f].N_List[1]	= grid2D.NODE(i, j+1);

			grid2D.Face_Data[f].Parent = NULL;
			grid2D.Face_Data[f].has_Child = false;

			//grid2D.Face_Index_Map.insert(i, j+0.5, 0, f);

			f++;
			id++;
		}
	}

	// B. Y-direction
	direction = 2;
	for (int j = 1; j <= Ny+1; j++)
	{
		for (int i = 1; i <= Nx; i++)
		{
			grid2D.Face_Data.resize(f+1);

			grid2D.Face_Data[f].ID = id;
			grid2D.Face_Data[f].index.i = i+0.5;
			grid2D.Face_Data[f].index.j = j;
			grid2D.Face_Data[f].index.k = 0;
			grid2D.Face_Data[f].index.lvl_refine = 0;
			grid2D.Face_Data[f].index.direction = direction;

			grid2D.Face_Data[f].N_List.resize(2);
			grid2D.Face_Data[f].N_List[0]	= grid2D.NODE(i,   j);
			grid2D.Face_Data[f].N_List[1]	= grid2D.NODE(i+1, j);

			grid2D.Face_Data[f].Parent = NULL;
			grid2D.Face_Data[f].has_Child = false;

			//grid2D.Face_Index_Map.insert(i+0.5, j, 0, f);

			f++;
			id++;
		}
	}
	grid2D.NFM = f;

	grid2D.whereisFace.resize(grid2D.NFM+1);
	for (f = 0; f <= grid2D.Face_Data.size()-1; f++)	grid2D.whereisFace[grid2D.Face_Data[f].ID]	= f;


	for (int i_f = 0; i_f <= grid2D.NFM-1; i_f++)
	{
		if (grid2D.Face_Data[i_f].N_List[0]->BC == -1 && grid2D.Face_Data[i_f].N_List[1]->BC == -1)
		{
			grid2D.Face_Data[i_f].BC 	= -1;
			grid2D.Face_Data[i_f].type 	= -1;
			grid2D.Face_Data[i_f].remove();
		}
		else if (grid2D.Face_Data[i_f].N_List[0]->BC == 1 && grid2D.Face_Data[i_f].N_List[1]->BC == 1)
		{
			grid2D.Face_Data[i_f].BC 	= 0;
			grid2D.Face_Data[i_f].type 	= 0;
			grid2D.Face_List.push_back(&grid2D.Face_Data[i_f]);
		}
		else
		{
			grid2D.Face_Data[i_f].BC 	= 1;
			grid2D.Face_Data[i_f].type 	= 1;
			grid2D.Face_List_Boundary.push_back(&grid2D.Face_Data[i_f]);
		}
	}


	// 3. Create Cells
	int c = 0;
	id = 1;
	grid2D.Cell_Index_Map	= Common::vector_3D<Cell_IJK>(Nx+1, Ny+1, 1);

	for (int j = 1; j <= Ny; j++)
	{
		for (int i = 1; i <= Nx; i++)
		{
			grid2D.Cell_Data.resize(c+1);

			grid2D.Cell_Data[c].ID = id;

			grid2D.Cell_Data[c].index.i = i;
			grid2D.Cell_Data[c].index.j = j;
			grid2D.Cell_Data[c].index.k = 0;
			grid2D.Cell_Data[c].index.location = 0;
			grid2D.Cell_Data[c].index.lvl_refine = 0;
			grid2D.Cell_Data[c].index.location_history.resize(1);
			grid2D.Cell_Data[c].index.location_history[0] = grid2D.Cell_Data[id].index.location;

			grid2D.Cell_Data[c].N_List.resize(4);
			grid2D.Cell_Data[c].N_List[0] = grid2D.NODE(i,   j);
			grid2D.Cell_Data[c].N_List[1] = grid2D.NODE(i+1, j);
			grid2D.Cell_Data[c].N_List[2] = grid2D.NODE(i+1, j+1);
			grid2D.Cell_Data[c].N_List[3] = grid2D.NODE(i,   j+1);

			grid2D.Cell_Data[c].F_List.resize(4);
			grid2D.Cell_Data[c].F_List[0] = grid2D.FACE(i+0.5, j);
			grid2D.Cell_Data[c].F_List[1] = grid2D.FACE(i+1, 	j+0.5);
			grid2D.Cell_Data[c].F_List[2] = grid2D.FACE(i+0.5, j+1);
			grid2D.Cell_Data[c].F_List[3] = grid2D.FACE(i, 	j+0.5);

			grid2D.Cell_Data[c].Parent = NULL;

			grid2D.Cell_Index_Map[i][j][0].resize(CONST_MAX_REFINEMENT_LEVEL, 4);
			grid2D.Cell_Index_Map[i][j][0](0, 0)	= c;

			c++;
			id++;
		}
	}

	grid2D.NCM = c;

	grid2D.whereisCell.resize(grid2D.NCM+1);
	for (c = 0; c <= grid2D.Cell_Data.size()-1; c++)	grid2D.whereisCell[grid2D.Cell_Data[c].ID]	= c;



	for (int i_c = 0; i_c <= grid2D.NCM-1; i_c++)
	{
		if (grid2D.Cell_Data[i_c].N_List[0]->BC == 1 &&
			grid2D.Cell_Data[i_c].N_List[1]->BC == 1 &&
			grid2D.Cell_Data[i_c].N_List[2]->BC == 1 &&
			grid2D.Cell_Data[i_c].N_List[3]->BC == 1 )
		{
			grid2D.Cell_Data[i_c].BC	= 0;
			grid2D.Cell_Data[i_c].type	= 0;

			grid2D.Cell_List.push_back(&grid2D.Cell_Data[i_c]);
		}
		else if (grid2D.Cell_Data[i_c].N_List[0]->BC <= 0 &&
			grid2D.Cell_Data[i_c].N_List[1]->BC <= 0 &&
			grid2D.Cell_Data[i_c].N_List[2]->BC <= 0 &&
			grid2D.Cell_Data[i_c].N_List[3]->BC <= 0 )
		{
			grid2D.Cell_Data[i_c].BC	= 1;
			grid2D.Cell_Data[i_c].type	= -1;

			grid2D.Cell_List_Ghost.push_back(&grid2D.Cell_Data[i_c]);
			grid2D.Cell_Data[i_c].remove();
		}
		else
		{
			grid2D.Cell_Data[i_c].BC	= -1;
			grid2D.Cell_Data[i_c].type	= 1;

			grid2D.Cell_List.push_back(&grid2D.Cell_Data[i_c]);
		}
	}


	// Assign Stencil for faces
	for (int itr_c = 0; itr_c <= grid2D.NCM-1; itr_c++)
	{
		if (grid2D.Cell_Data[itr_c].F_List[0]->CR == NULL)	grid2D.Cell_Data[itr_c].F_List[0]->CR = &grid2D.Cell_Data[itr_c];
		if (grid2D.Cell_Data[itr_c].F_List[1]->CL == NULL)	grid2D.Cell_Data[itr_c].F_List[1]->CL = &grid2D.Cell_Data[itr_c];
		if (grid2D.Cell_Data[itr_c].F_List[2]->CL == NULL)	grid2D.Cell_Data[itr_c].F_List[2]->CL = &grid2D.Cell_Data[itr_c];
		if (grid2D.Cell_Data[itr_c].F_List[3]->CR == NULL)	grid2D.Cell_Data[itr_c].F_List[3]->CR = &grid2D.Cell_Data[itr_c];
	}



	// Assign Neighboring cells on Node
	for (int i_c = 0; i_c <= grid2D.NCM-1; i_c++)
	{
		for (int i_n = 0; i_n <= grid2D.Cell_Data[i_c].N_List.size()-1; i_n++)
		{
			grid2D.Cell_Data[i_c].N_List[i_n]->C_List.push_back(&grid2D.Cell_Data[i_c]);
		}
	}

	for (int i_n = 0; i_n <= grid2D.NNM-1; i_n++)
	{
		Common::VectorPointer::removeNULL<c_Cell>(grid2D.Node_Data[i_n].C_List);
	}



	// Update grid list
	grid2D.Node_List.clear();
	for (int n = 0; n <= grid2D.NNM-1; n++)
	{
		if (grid2D.Node_Data[n].isInclude() == true)	grid2D.Node_List.push_back(&grid2D.Node_Data[n]);
	}

	GridProcessing_v2(gridFactor, axysymmetric, grid2D);






	// Error check
	for (int i_n = 0; i_n <= grid2D.NNM-1; i_n++)	grid2D.Node_Data[i_n].CheckError();
	for (int i_f = 0; i_f <= grid2D.NFM-1; i_f++)	grid2D.Face_Data[i_f].CheckError();
	for (int i_c = 0; i_c <= grid2D.NCM-1; i_c++)	grid2D.Cell_Data[i_c].CheckError();
}





*/





}
}
