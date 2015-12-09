/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GridRefiner.cpp
 *
 *  Created on: Dec 2, 2015
 *      Author: minkwan
 */


#include "./COMMON/VectorPointer.hpp"
#include "./COMMON/ErrorCode.hpp"
#include "./COMMON/ExceptionGeneral.hpp"


#include "GRID/GridV2.hpp"
#include "GRID/GridFunctions.hpp"


namespace OP2A {
namespace GRID {


void GridSetRefiningFlagGeometry(c_Grid& grid)
{
	for (int c = 0; c <= grid.Cell_List.size()-1; c++)
	{
		grid.Cell_List[c]->setRefine(false);

		if (grid.Cell_List[c]->has_Child == false)
		{
			if (grid.Cell_List[c]->type == 1 && grid.Cell_List[c]->index.lvl_refine < CONST_MAX_REFINEMENT_LEVEL-1)
			{
				grid.Cell_List[c]->setRefine(true);
			}
		}
	}

	GridSetRefiningFlagNeighbors(grid);
}


void GridSetRefiningFlagNeighbors(c_Grid& grid)
{
	for (int ia = 0; ia <= CONST_MAX_REFINEMENT_LEVEL-1; ia++)
	{

		for (int f = 0; f <= grid.NFM-1; f++)
		{
			if (grid.FACE_data(f).has_Child == false)
			{
				c_Cell* CL	= grid.FACE_data(f).CL;
				c_Cell* CR	= grid.FACE_data(f).CR;

				if (CL != NULL && CL->isInclude() == true &&
					CR != NULL && CR->isInclude() == true)
				{
					if (CR->index.lvl_refine != CL->index.lvl_refine)
					{
						if (CL->needToRefine() == true && CR->needToRefine() != true)
						{
							if(CL->index.lvl_refine > CR->index.lvl_refine	&& CR->has_Child == false)
							{
								CR->setRefine(true);
							}
						}

						if (CL->needToRefine() != true && CR->needToRefine() == true)
						{
							if(CR->index.lvl_refine > CL->index.lvl_refine	&& CL->has_Child == false)
							{
								CL->setRefine(true);
							}
						}
					}
				}
			}
		}
	}
}



void GridSetRefiniement(c_Grid& grid)
{
	if (grid.DIM == 2)
	{
		for (int c = 0; c <= grid.Cell_List.size()-1; c++)
		{
			if (grid.Cell_List[c]->needToRefine() == true)
			{
				GridRefiner2D_v1(grid, grid.Cell_List[c]);
			}
		}
	}
	else
	{
		//@TODO Need to add 3D case
	}


	grid.NODE_ListUpdate();
	grid.FACE_ListUpdate();
	grid.CELL_ListUpdate();


	// CREATE GHOST CELLS
	for (unsigned int i_f = 0; i_f <= grid.NFM-1; i_f++)
	{
		if (grid.FACE_data(i_f).BC != 0)
		{
			if (grid.FACE_data(i_f).CL == NULL)	CreateGhostCell(grid, grid.FACE_data(i_f), 0);
			if (grid.FACE_data(i_f).CR == NULL)	CreateGhostCell(grid, grid.FACE_data(i_f), 1);
		}
	}
}



void GridRefiner2D_v1(c_Grid& grid, c_Cell* cell)
{
	// Getting Basic information of nodes and faces
	c_Node*	node1	= cell->N_List[0];
	c_Node*	node2	= cell->N_List[1];
	c_Node*	node3	= cell->N_List[2];
	c_Node*	node4	= cell->N_List[3];

	c_Face*	face1	= cell->F_List[0];
	c_Face*	face2	= cell->F_List[1];
	c_Face*	face3	= cell->F_List[2];
	c_Face*	face4	= cell->F_List[3];


	// Refinement information
	int lvl_refine	= cell->index.lvl_refine;
	double di, dj;
	lvl_refine++;


	// Create 4new cells
	double ic, jc, kc;
	ic	= cell->index.i;
	jc	= cell->index.j;
	kc	= cell->index.k;

	di	= 1.0 / pow(2.0, lvl_refine + 1.0);

	grid.CELL_add(ic-di, jc-di);
	grid.CELL_add(ic+di, jc-di);
	grid.CELL_add(ic+di, jc+di);
	grid.CELL_add(ic-di, jc+di);

	c_Cell* cell_new1	= grid.CELL(ic-di, jc-di);
	c_Cell* cell_new2	= grid.CELL(ic+di, jc-di);;
	c_Cell* cell_new3	= grid.CELL(ic+di, jc+di);;
	c_Cell* cell_new4	= grid.CELL(ic-di, jc+di);;

	cell_new1->index.i	= ic-di;
	cell_new1->index.j	= jc-di;
	cell_new1->index.k	= kc;

	cell_new2->index.i	= ic+di;
	cell_new2->index.j	= jc-di;
	cell_new2->index.k	= kc;

	cell_new3->index.i	= ic+di;
	cell_new3->index.j	= jc+di;
	cell_new3->index.k	= kc;

	cell_new4->index.i	= ic-di;
	cell_new4->index.j	= jc+di;
	cell_new4->index.k	= kc;




	// 1. Create nodes (1~ 5)
	c_Node	node;
	di	= 1.0 / pow(2.0, lvl_refine);
	dj	= di;
	double i  = node1->index.i;
	double j  = node1->index.j;
	double k  = node1->index.k;

	// Error check
	if  (di != (node2->index.i - node1->index.i) / 2.0)
	{
		Common::ExceptionGeneral(FromHere(), "CellRefinement:: Problem in refinement level in x-direction.", Common::ErrorCode::NotMatchDimention());
	}

	if  (dj != (node4->index.j - node1->index.j) / 2.0)
	{
		Common::ExceptionGeneral(FromHere(), "CellRefinement:: Problem in refinement level in y-direction.", Common::ErrorCode::NotMatchDimention());
	}


	// Node1
	node.x[0]	= cell->x[0];
	node.x[1]	= cell->x[1];
	node.x[2]	= cell->x[2];
	node.index.i = i + di;
	node.index.j = j + dj;
	node.index.k = 0.0;
	node.BC = GridShapeFunctions(node.x[0], node.x[1], node.x[2]);
	node.C_List.resize(4);
	node.C_List[0]	= cell_new1;
	node.C_List[1]	= cell_new2;
	node.C_List[2]	= cell_new3;
	node.C_List[3]	= cell_new4;
	grid.NODE_add(node.index.i, node.index.j, node.index.k, node);


	// Node2
	if (grid.NODE(i+di, j, k) == NULL)
	{
		node.x[0]	= face1->x[0];
		node.x[1]	= face1->x[1];
		node.x[2]	= face1->x[2];
		node.index.i = i+di;
		node.index.j = j;
		node.index.k = k;
		node.BC = GridShapeFunctions(node.x[0], node.x[1], node.x[2]);

		node.C_List.resize(3);
		node.C_List[0]	= face1->CL;
		node.C_List[1]	= cell_new1;
		node.C_List[2]	= cell_new2;
		grid.NODE_add(node.index.i, node.index.j, node.index.k, node);
	}
	else
	{
		int n_size	= grid.NODE(i+di, j, k)->C_List.size();
		for (int n = 0; n <= n_size-1; n++)
		{
			if (grid.NODE(i+di, j, k)->C_List[n] == cell)
			{
				grid.NODE(i+di, j, k)->C_List.resize(n_size+1);
				grid.NODE(i+di, j, k)->C_List[n]		= cell_new1;
				grid.NODE(i+di, j, k)->C_List[n_size]	= cell_new2;
				break;
			}
		}
	}


	// Node3
	if (grid.NODE(i+2.0*di, j+dj, k) == NULL)
	{
		node.x[0]	= face2->x[0];
		node.x[1]	= face2->x[1];
		node.x[2]	= face2->x[2];
		node.index.i = i+2.0*di;
		node.index.j = j+dj;
		node.index.k = k;
		node.BC = GridShapeFunctions(node.x[0], node.x[1], node.x[2]);

		node.C_List.resize(3);
		node.C_List[0]	= face2->CR;
		node.C_List[1]	= cell_new2;
		node.C_List[2]	= cell_new3;
		grid.NODE_add(node.index.i, node.index.j, node.index.k, node);

	}
	else
	{
		int n_size	=grid.NODE(i+2.0*di, j+dj, k)->C_List.size();
		for (int n = 0; n <= n_size-1; n++)
		{
			if (grid.NODE(i+2.0*di, j+dj, k)->C_List[n] == cell)
			{
				grid.NODE(i+2.0*di, j+dj, k)->C_List.resize(n_size+1);
				grid.NODE(i+2.0*di, j+dj, k)->C_List[n]		= cell_new2;
				grid.NODE(i+2.0*di, j+dj, k)->C_List[n_size]	= cell_new3;
				break;
			}
		}
	}


	// Node4
	if (grid.NODE(i+di, j+2.0*dj, k) == NULL)
	{
		node.x[0]	= face3->x[0];
		node.x[1]	= face3->x[1];
		node.x[2]	= face3->x[2];
		node.index.i = i+di;
		node.index.j = j+2.0*dj;
		node.index.k = k;
		node.BC = GridShapeFunctions(node.x[0], node.x[1], node.x[2]);

		node.C_List.resize(3);
		node.C_List[0]	= face3->CL;
		node.C_List[1]	= cell_new3;
		node.C_List[2]	= cell_new3;
		grid.NODE_add(node.index.i, node.index.j, node.index.k, node);
	}
	else
	{
		int n_size	= grid.NODE(i+di, j+2.0*dj, k)->C_List.size();
		for (int n = 0; n <= n_size-1; n++)
		{
			if (grid.NODE(i+di, j+2.0*dj, k)->C_List[n] == cell)
			{
				grid.NODE(i+di, j+2.0*dj, k)->C_List.resize(n_size+1);
				grid.NODE(i+di, j+2.0*dj, k)->C_List[n]		= cell_new3;
				grid.NODE(i+di, j+2.0*dj, k)->C_List[n_size]	= cell_new4;
				break;
			}
		}
	}



	// Node5
	if (grid.NODE(i, j+dj, k) == NULL)
	{
		node.x[0]	= face4->x[0];
		node.x[1]	= face4->x[1];
		node.x[2]	= face4->x[2];
		node.index.i = i;
		node.index.j = j+dj;
		node.index.k = k;
		node.BC = GridShapeFunctions(node.x[0], node.x[1], node.x[2]);

		node.C_List.resize(3);
		node.C_List[0]	= face4->CR;
		node.C_List[1]	= cell_new4;
		node.C_List[2]	= cell_new1;
		grid.NODE_add(node.index.i, node.index.j, node.index.k, node);

	}
	else
	{
		int n_size	= grid.NODE(i, j+dj, k)->C_List.size();
		for (int n = 0; n <= n_size-1; n++)
		{
			if (grid.NODE(i, j+dj, k)->C_List[n] == cell)
			{
				grid.NODE(i, j+dj, k)->C_List.resize(n_size+1);
				grid.NODE(i, j+dj, k)->C_List[n]		= cell_new4;
				grid.NODE(i, j+dj, k)->C_List[n_size]	= cell_new1;
				break;
			}
		}
	}

	c_Node* node5	= grid.NODE(i + 	di,	j +		dj, k);
	c_Node* node6	= grid.NODE(i + 	di, j 	  	  , k);
	c_Node* node7	= grid.NODE(i + 2.0*di, j + 	dj, k);
	c_Node* node8	= grid.NODE(i + 	di, j + 2.0*dj, k);
	c_Node* node9	= grid.NODE(i 		  , j + 	dj, k);


	// 2. FACE
	c_Face	face;
	di	= 1.0 / pow(2.0, lvl_refine + 1);
	dj	= di;
	double two_di, three_di;
	double two_dj, three_dj;

	two_di		= 2.0 * di;
	three_di	= 3.0 * di;

	two_dj		= 2.0 * dj;
	three_dj	= 3.0 * dj;

	// face5
	face.index.i 			= i + two_di;
	face.index.j 			= j + dj;
	face.index.k 			= k;
	face.index.lvl_refine 	= lvl_refine;
	face.index.direction 	= 1;
	face.N_List.resize(2);
	face.N_List[0]	= node6;
	face.N_List[1]	= node5;
	face.Parent = NULL;
	face.has_Child = false;
	face.CL	= cell_new1;
	face.CR	= cell_new2;
	grid.FACE_add(face.index.i, face.index.j, face.index.k, face);

	// face6
	face.index.i 			= i + three_di;
	face.index.j 			= j + two_dj;
	face.index.k 			= k;
	face.index.lvl_refine 	= lvl_refine;
	face.index.direction 	= 2;
	face.N_List.resize(2);
	face.N_List[0]	= node5;
	face.N_List[1]	= node7;
	face.Parent = NULL;
	face.has_Child = false;
	face.CL	= cell_new2;
	face.CR	= cell_new3;
	grid.FACE_add(face.index.i, face.index.j, face.index.k, face);

	// face7
	face.index.i 			= i + two_di;
	face.index.j 			= j + three_dj;
	face.index.k 			= k;
	face.index.lvl_refine 	= lvl_refine;
	face.index.direction 	= 1;
	face.N_List.resize(2);
	face.N_List[0]	= node5;
	face.N_List[1]	= node8;
	face.Parent = NULL;
	face.has_Child = false;
	face.CL	= cell_new4;
	face.CR	= cell_new3;
	grid.FACE_add(face.index.i, face.index.j, face.index.k, face);


	// face8
	face.index.i 			= i + di;
	face.index.j 			= j + two_dj;
	face.index.k 			= k;
	face.index.lvl_refine 	= lvl_refine;
	face.index.direction 	= 2;
	face.N_List.resize(2);
	face.N_List[0]	= node9;
	face.N_List[1]	= node5;
	face.Parent = NULL;
	face.has_Child = false;
	face.CL	= cell_new1;
	face.CR	= cell_new4;
	grid.FACE_add(face.index.i, face.index.j, face.index.k, face);


	// face9
	if (grid.FACE(i+di, j, k)	== NULL)
	{
		face.index.i 			= i + di;
		face.index.j 			= j;
		face.index.k 			= k;
		face.index.lvl_refine 	= lvl_refine;
		face.index.direction 	= 2;
		face.N_List.resize(2);
		face.N_List[0]	= node1;
		face.N_List[1]	= node6;
		face.Parent = face1;
		face.has_Child = false;
		face.CL	= face1->CL;
		face.CR	= cell_new1;
		grid.FACE_add(face.index.i, face.index.j, face.index.k, face);
	}
	else
	{
		if (grid.FACE(i+di, j, k)->CR != cell)
		{
			Common::ExceptionGeneral(FromHere(), "CellRefinement:: Problem in the stencil of Face9. CR of face 9 is not Mother Cell", Common::ErrorCode::NotMatchDimention());
		}
		grid.FACE(i+di, j, k)->CR = cell_new1;
	}

	// face10
	if (grid.FACE(i+three_di, j, k)	== NULL)
	{
		face.index.i 			= i + three_di;
		face.index.j 			= j;
		face.index.k 			= k;
		face.index.lvl_refine 	= lvl_refine;
		face.index.direction 	= 2;
		face.N_List.resize(2);
		face.N_List[0]	= node6;
		face.N_List[1]	= node2;
		face.Parent = face1;
		face.has_Child = false;
		face.CL	= face1->CL;
		face.CR	= cell_new2;
		grid.FACE_add(face.index.i, face.index.j, face.index.k, face);
	}
	else
	{
		if (grid.FACE(i+three_di, j, k)->CR != cell)
		{
			Common::ExceptionGeneral(FromHere(), "CellRefinement:: Problem in the stencil of Face10. CR of face10 is not Mother Cell", Common::ErrorCode::NotMatchDimention());
		}
		grid.FACE(i+three_di, j, k)->CR = cell_new2;
	}


	// face11
	if (grid.FACE(i+4.0*di, j + dj, k)	== NULL)
	{
		face.index.i 			= i + 4.0*di;
		face.index.j 			= j + dj;
		face.index.k 			= k;
		face.index.lvl_refine 	= lvl_refine;
		face.index.direction 	= 1;
		face.N_List.resize(2);
		face.N_List[0]	= node2;
		face.N_List[1]	= node7;
		face.Parent = face2;
		face.has_Child = false;
		face.CL	= cell_new2;
		face.CR	= face2->CR;
		grid.FACE_add(face.index.i, face.index.j, face.index.k, face);
	}
	else
	{
		if (grid.FACE(i+4.0*di, j+dj, k)->CL != cell)
		{
			Common::ExceptionGeneral(FromHere(), "CellRefinement:: Problem in the stencil of Face11. CL of face11 is not Mother Cell", Common::ErrorCode::NotMatchDimention());
		}
		grid.FACE(i+4.0*di, j+dj, k)->CL = cell_new2;
	}


	// face12
	ic	= i + 2.0*di;
	jc	= j + 1.5*dj;
	kc	= k;

	if (grid.FACE(i+4.0*di, j+three_dj, k)	== NULL)
	{
		face.index.i 			= i + 4.0*di;
		face.index.j 			= j + three_dj;
		face.index.k 			= k;
		face.index.lvl_refine 	= lvl_refine;
		face.index.direction 	= 1;
		face.N_List.resize(2);
		face.N_List[0]	= node7;
		face.N_List[1]	= node3;
		face.Parent = face2;
		face.has_Child = false;
		face.CL	= cell_new3;
		face.CR	= face2->CR;
		grid.FACE_add(face.index.i, face.index.j, face.index.k, face);
	}
	else
	{
		if (grid.FACE(i+4.0*di, j+three_dj, k)->CL != cell)
		{
			Common::ExceptionGeneral(FromHere(), "CellRefinement:: Problem in the stencil of Face12. CL of face 12 is not Mother Cell", Common::ErrorCode::NotMatchDimention());
		}
		grid.FACE(i+4.0*di, j+three_dj, k)->CL = cell_new3;
	}


	// face13
	if (grid.FACE(i+three_di, j+4.0*dj, k)	== NULL)
	{
		face.index.i 			= i + three_di;
		face.index.j 			= j + 4.0*dj;
		face.index.k 			= k;
		face.index.lvl_refine 	= lvl_refine;
		face.index.direction 	= 2;
		face.N_List.resize(2);
		face.N_List[0]	= node8;
		face.N_List[1]	= node3;
		face.Parent = face3;
		face.has_Child = false;
		face.CL	= cell_new3;
		face.CR	= face3->CR;
		grid.FACE_add(face.index.i, face.index.j, face.index.k, face);
	}
	else
	{
		if (grid.FACE(i+three_di, j+4.0*dj, k)->CL != cell)
		{
			Common::ExceptionGeneral(FromHere(), "CellRefinement:: Problem in the stencil of Face13. CL of face13 is not Mother Cell", Common::ErrorCode::NotMatchDimention());
		}
		grid.FACE(i+three_di, j+4.0*dj, k)->CL = cell_new3;
	}


	// face14
	if (grid.FACE(i+di, j+4.0*dj, k)	== NULL)
	{
		face.index.i 			= i + di;
		face.index.j 			= j + 4.0*dj;
		face.index.k 			= k;
		face.index.lvl_refine 	= lvl_refine;
		face.index.direction 	= 2;
		face.N_List.resize(2);
		face.N_List[0]	= node4;
		face.N_List[1]	= node8;
		face.Parent = face3;
		face.has_Child = false;
		face.CL	= cell_new4;
		face.CR	= face3->CR;
		grid.FACE_add(face.index.i, face.index.j, face.index.k, face);
	}
	else
	{
		if (grid.FACE(i+di, j+4.0*dj, k)->CL != cell)
		{
			Common::ExceptionGeneral(FromHere(), "CellRefinement:: Problem in the stencil of Face14. CL of face14 is not Mother Cell", Common::ErrorCode::NotMatchDimention());
		}
		grid.FACE(i+three_di, j+4.0*dj, k)->CL = cell_new4;
	}


	// face15
	if (grid.FACE(i, j+three_dj, k)	== NULL)
	{
		face.index.i 			= i;
		face.index.j 			= j + three_dj;
		face.index.k 			= k;
		face.index.lvl_refine 	= lvl_refine;
		face.index.direction 	= 1;
		face.N_List.resize(2);
		face.N_List[0]	= node4;
		face.N_List[1]	= node9;
		face.Parent = face4;
		face.has_Child = false;
		face.CL	= face4->CL;
		face.CR	= cell_new4;
		grid.FACE_add(face.index.i, face.index.j, face.index.k, face);
	}
	else
	{
		if (grid.FACE(i, j+three_dj, k)->CR != cell)
		{
			Common::ExceptionGeneral(FromHere(), "CellRefinement:: Problem in the stencil of Face15. CR of face15 is not Mother Cell", Common::ErrorCode::NotMatchDimention());
		}
		grid.FACE(i, j+three_dj, k)->CR = cell_new4;
	}


	// face16
	if (grid.FACE(i, j+dj, k)	== NULL)
	{
		face.index.i 			= i;
		face.index.j 			= j + dj;
		face.index.k 			= k;
		face.index.lvl_refine 	= lvl_refine;
		face.index.direction 	= 1;
		face.N_List.resize(2);
		face.N_List[0]	= node9;
		face.N_List[1]	= node1;
		face.Parent = face4;
		face.has_Child = false;
		face.CL	= face4->CL;
		face.CR	= cell_new1;
		grid.FACE_add(face.index.i, face.index.j, face.index.k, face);
	}
	else
	{
		if (grid.FACE(i, j+dj, k)->CR != cell)
		{
			Common::ExceptionGeneral(FromHere(), "CellRefinement:: Problem in the stencil of Face16. CR of face16 is not Mother Cell", Common::ErrorCode::NotMatchDimention());
		}
		grid.FACE(i, j+dj, k)->CR = cell_new1;
	}

	c_Face* face5	= grid.FACE(i+two_di,	j+dj, 		k);
	c_Face* face6	= grid.FACE(i+three_di,	j+two_dj, 	k);
	c_Face* face7	= grid.FACE(i+two_di,	j+three_dj, k);
	c_Face* face8	= grid.FACE(i+di,		j+two_dj,	k);
	c_Face* face9	= grid.FACE(i+di,		j, 			k);
	c_Face* face10	= grid.FACE(i+three_di,	j,			k);
	c_Face* face11	= grid.FACE(i+4.0*di,	j+dj, 		k);
	c_Face* face12	= grid.FACE(i+4.0*di,	j+three_dj, k);
	c_Face* face13	= grid.FACE(i+three_di,	j+4.0*dj, 	k);
	c_Face* face14	= grid.FACE(i+di,		j+4.0*dj, 	k);
	c_Face* face15	= grid.FACE(i,			j+three_dj, k);
	c_Face* face16	= grid.FACE(i,			j+dj, 		k);

	GridProcessing_Face_v2(*face5, grid.DIM);
	GridProcessing_Face_v2(*face6, grid.DIM);
	GridProcessing_Face_v2(*face7, grid.DIM);
	GridProcessing_Face_v2(*face8, grid.DIM);
	GridProcessing_Face_v2(*face9, grid.DIM);
	GridProcessing_Face_v2(*face10, grid.DIM);
	GridProcessing_Face_v2(*face11, grid.DIM);
	GridProcessing_Face_v2(*face12, grid.DIM);
	GridProcessing_Face_v2(*face13, grid.DIM);
	GridProcessing_Face_v2(*face14, grid.DIM);
	GridProcessing_Face_v2(*face15, grid.DIM);
	GridProcessing_Face_v2(*face16, grid.DIM);

	face5->applyBoundary();
	face6->applyBoundary();
	face7->applyBoundary();
	face8->applyBoundary();
	face9->applyBoundary();
	face10->applyBoundary();
	face11->applyBoundary();
	face12->applyBoundary();
	face13->applyBoundary();
	face14->applyBoundary();
	face15->applyBoundary();
	face16->applyBoundary();


	// 3. Create Cell

	// Cell1
	cell_new1->index.location	= 0;
	cell_new1->index.lvl_refine = lvl_refine;
	cell_new1->index.location_history = cell->index.location_history;
	cell_new1->index.location_history.push_back(1);
	cell_new1->N_List.resize(4);
	cell_new1->N_List[0]	= node1;
	cell_new1->N_List[1]	= node6;
	cell_new1->N_List[2]	= node5;
	cell_new1->N_List[3]	= node9;
	cell_new1->F_List.resize(4);
	cell_new1->F_List[0]	= face9;
	cell_new1->F_List[1]	= face5;
	cell_new1->F_List[2]	= face8;
	cell_new1->F_List[3]	= face16;
	cell_new1->Parent		= cell;


	// Cell2
	cell_new2->index.location	= 1;
	cell_new2->index.lvl_refine = lvl_refine;
	cell_new2->index.location_history = cell->index.location_history;
	cell_new2->index.location_history.push_back(1);
	cell_new2->N_List.resize(4);
	cell_new2->N_List[0]	= node6;
	cell_new2->N_List[1]	= node2;
	cell_new2->N_List[2]	= node7;
	cell_new2->N_List[3]	= node5;
	cell_new2->F_List.resize(4);
	cell_new2->F_List[0]	= face10;
	cell_new2->F_List[1]	= face11;
	cell_new2->F_List[2]	= face6;
	cell_new2->F_List[3]	= face5;
	cell_new2->Parent		= cell;


	// Cell3
	cell_new3->index.location	= 2;
	cell_new3->index.lvl_refine = lvl_refine;
	cell_new3->index.location_history = cell->index.location_history;
	cell_new3->index.location_history.push_back(1);
	cell_new3->N_List.resize(4);
	cell_new3->N_List[0]	= node5;
	cell_new3->N_List[1]	= node7;
	cell_new3->N_List[2]	= node3;
	cell_new3->N_List[3]	= node8;
	cell_new3->F_List.resize(4);
	cell_new3->F_List[0]	= face6;
	cell_new3->F_List[1]	= face12;
	cell_new3->F_List[2]	= face13;
	cell_new3->F_List[3]	= face7;
	cell_new3->Parent		= cell;


	// Cell4
	cell_new4->index.location	= 3;
	cell_new4->index.lvl_refine = lvl_refine;
	cell_new4->index.location_history = cell->index.location_history;
	cell_new4->index.location_history.push_back(1);
	cell_new4->N_List.resize(4);
	cell_new4->N_List[0]	= node9;
	cell_new4->N_List[1]	= node5;
	cell_new4->N_List[2]	= node8;
	cell_new4->N_List[3]	= node4;
	cell_new4->F_List.resize(4);
	cell_new4->F_List[0]	= face8;
	cell_new4->F_List[1]	= face7;
	cell_new4->F_List[2]	= face14;
	cell_new4->F_List[3]	= face15;
	cell_new4->Parent		= cell;

	GridProcessing_Cell_v2(*cell_new1, grid.DIM);
	GridProcessing_Cell_v2(*cell_new2, grid.DIM);
	GridProcessing_Cell_v2(*cell_new3, grid.DIM);
	GridProcessing_Cell_v2(*cell_new4, grid.DIM);

	cell->has_Child = true;
	cell->Children.resize(4);
	cell->Children[0]	= cell_new1;
	cell->Children[1]	= cell_new2;
	cell->Children[2]	= cell_new3;
	cell->Children[3]	= cell_new4;
	cell->setRefine(false);

	cell_new1->applyBoundary();
	cell_new2->applyBoundary();
	cell_new3->applyBoundary();
	cell_new4->applyBoundary();
}






}
}

