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


/*

void GridSetRefiningFlagGeometry(c_Grid& grid)
{
	for (int c = 0; c <= grid.NCM-1; c++)
	{
		grid.Cell_Data[c].setRefine(false);

		if (grid.Cell_Data[c].has_Child == false)
		{
			if (grid.Cell_Data[c].type == 1 && grid.Cell_Data[c].isInclude() == true)
			{
				grid.Cell_Data[c].setRefine(true);
			}
		}
	}

	for (int f = 0; f <= grid.NFM-1; f++)
	{

		if (grid.Face_Data[f].CL != NULL && grid.Face_Data[f].CR != NULL)
		{
			if (grid.Face_Data[f].CL->index.lvl_refine > grid.Face_Data[f].CR->index.lvl_refine &&	grid.Face_Data[f].CL->needToRefine() == true)
			{
				grid.Face_Data[f].CR->setRefine(true);
			}

			if (grid.Face_Data[f].CR->index.lvl_refine > grid.Face_Data[f].CL->index.lvl_refine &&	grid.Face_Data[f].CR->needToRefine() == true)
			{
				grid.Face_Data[f].CL->setRefine(true);
			}
		}
	}
}


void GridSetRefiniement(c_Grid& grid)
{

	if (grid.DIM == 2)
	{
		for (int c = 0; c <= grid.NCM-1; c++)
		{
			if (grid.Cell_Data[c].needToRefine() == true)
			{
				GridRefiner2D_v1(grid, c);
			}
		}
	}


	for (int c = 0; c <= grid.NCM-1; c++)
	{
		if (grid.Cell_Data[c].has_Child == true)
		{
			grid.Cell_Data[c].remove();
		}
	}



}



void GridRefiner2D_v1(c_Grid& grid, int c)
{

	// Getting Basic information of nodes and faces
	c_Node*	node1	= grid.Cell_Data[c].N_List[0];
	c_Node*	node2	= grid.Cell_Data[c].N_List[1];
	c_Node*	node3	= grid.Cell_Data[c].N_List[2];
	c_Node*	node4	= grid.Cell_Data[c].N_List[3];

	c_Face*	face1	= grid.Cell_Data[c].F_List[0];
	c_Face*	face2	= grid.Cell_Data[c].F_List[1];
	c_Face*	face3	= grid.Cell_Data[c].F_List[2];
	c_Face*	face4	= grid.Cell_Data[c].F_List[3];

	c_Cell*	cell	= &grid.Cell_Data[c];



	// Refinement information
	int lvl_refine	= grid.Cell_Data[c].index.lvl_refine;
	lvl_refine++;


	// Create 4new cells
	int last_location_cell	= grid.Cell_Data.size()-1;
	grid.Cell_Data.resize(grid.NCM + 4);
	grid.whereisCell.resize(grid.NCM + 5);

	c_Cell* cell_new1	= &grid.Cell_Data[last_location_cell+1];
	c_Cell* cell_new2	= &grid.Cell_Data[last_location_cell+2];
	c_Cell* cell_new3	= &grid.Cell_Data[last_location_cell+3];
	c_Cell* cell_new4	= &grid.Cell_Data[last_location_cell+4];



	// 1. Create nodes (1~ 5)
	double i  = node1->index.i;
	double j  = node1->index.j;
	double k  = node1->index.k;

	double di = (node2->index.i - node1->index.i) / 2.0;
	double dj = (node4->index.j - node1->index.j) / 2.0;
	double ic, jc, kc;

	// Error check
	if (di != 1.0/pow(2.0, lvl_refine))
	{
		Common::ExceptionGeneral(FromHere(), "CellRefinement:: Problem in refinement level in x-direction.", Common::ErrorCode::NotMatchDimention());
	}

	if (dj != 1.0/pow(2.0, lvl_refine))
	{
		Common::ExceptionGeneral(FromHere(), "CellRefinement:: Problem in refinement level in y-direction.", Common::ErrorCode::NotMatchDimention());
	}


	int last_location_node;
	int nnm	= grid.NNM;

	c_Node*	node_new1;
	c_Node*	node_new2;
	c_Node*	node_new3;
	c_Node*	node_new4;
	c_Node*	node_new5;

	// Node1
	nnm++;
	grid.Node_Data.resize(nnm);
	grid.whereisNode.resize(nnm + 1);
	last_location_node	= grid.Node_Data.size() - 1;
	node_new1	= &grid.Node_Data[last_location_node];

	node_new1->ID	= nnm;
	node_new1->x[0]	= grid.Cell_Data[c].x[0];
	node_new1->x[1]	= grid.Cell_Data[c].x[1];
	node_new1->x[2]	= grid.Cell_Data[c].x[2];
	node_new1->index.i = i + di;
	node_new1->index.j = j + dj;
	node_new1->index.k = 0.0;
	node_new1->BC = GridShapeFunctions(node_new1->x[0], node_new1->x[1], node_new1->x[2]);
	node_new1->C_List.resize(4);
	node_new1->C_List[0]	= cell_new1;
	node_new1->C_List[1]	= cell_new2;
	node_new1->C_List[2]	= cell_new3;
	node_new1->C_List[3]	= cell_new4;
	grid.whereisNode[node_new1->ID]	= last_location_node;
	//grid.Node_Index_Map.insert(node_new1->index.i, node_new1->index.j, node_new1->index.k, last_location_node);


	// Node2
	ic	= i + di;
	jc	= j;
	kc  = k;

	if (grid.NODE(ic, jc, kc) == NULL)
	{
		nnm++;
		grid.Node_Data.resize(nnm);
		grid.whereisNode.resize(nnm + 1);
		last_location_node	= grid.Node_Data.size() - 1;
		node_new2	= &grid.Node_Data[last_location_node];

		node_new2->ID	= nnm;
		node_new2->x[0]	= face1->x[0];
		node_new2->x[1]	= face1->x[1];
		node_new2->x[2]	= face1->x[2];
		node_new2->index.i = ic;
		node_new2->index.j = jc;
		node_new2->index.k = kc;
		node_new2->BC = GridShapeFunctions(node_new2->x[0], node_new2->x[1], node_new2->x[2]);

		if (face1->CL!= NULL && face1->CL->has_Child == true)
		{
			node_new2->C_List.resize(4);
			node_new2->C_List[0]	= face1->CL->Children[2];
			node_new2->C_List[1]	= face1->CL->Children[3];
			node_new2->C_List[2]	= cell_new1;
			node_new2->C_List[3]	= cell_new2;
		}
		else
		{
			node_new2->C_List.resize(4);
			node_new2->C_List[0]	= face1->CL;
			node_new2->C_List[1]	= cell_new1;
			node_new2->C_List[2]	= cell_new2;
		}

		grid.whereisNode[node_new2->ID]	= last_location_node;
		//grid.Node_Index_Map.insert(ic, jc, kc, last_location_node);
	}
	else
	{
		node_new2 = grid.NODE(ic, jc, kc);
	}


	// Node3
	ic	= i + 2.0*di;
	jc	= j + dj;
	kc  = k;

	if (grid.NODE(ic, jc, kc) == NULL)
	{
		nnm++;
		grid.Node_Data.resize(nnm);
		grid.whereisNode.resize(nnm + 1);
		last_location_node	= grid.Node_Data.size() - 1;
		node_new3	= &grid.Node_Data[last_location_node];

		node_new3->ID	= nnm;
		node_new3->x[0]	= face2->x[0];
		node_new3->x[1]	= face2->x[1];
		node_new3->x[2]	= face2->x[2];
		node_new3->index.i = ic;
		node_new3->index.j = jc;
		node_new3->index.k = kc;
		node_new3->BC = GridShapeFunctions(node_new3->x[0], node_new3->x[1], node_new3->x[2]);

		if (face2->CR!= NULL && face2->CR->has_Child == true)
		{
			node_new3->C_List.resize(4);
			node_new3->C_List[0]	= face2->CR->Children[0];
			node_new3->C_List[1]	= face2->CR->Children[3];
			node_new3->C_List[2]	= cell_new2;
			node_new3->C_List[3]	= cell_new3;
		}
		else
		{
			node_new3->C_List.resize(3);
			node_new3->C_List[0]	= face2->CR;
			node_new3->C_List[1]	= cell_new2;
			node_new3->C_List[2]	= cell_new3;
		}

		grid.whereisNode[node_new3->ID]	= last_location_node;
		//grid.Node_Index_Map.insert(ic, jc, kc, last_location_node);
	}
	else
	{
		node_new3 = grid.NODE(ic, jc, kc);
	}


	// Node4
	ic	= i + di;
	jc	= j + 2.0*dj;
	kc  = k;

	if (grid.NODE(ic, jc, kc) == NULL)
	{
		nnm++;
		grid.Node_Data.resize(nnm);
		grid.whereisNode.resize(nnm + 1);
		last_location_node	= grid.Node_Data.size() - 1;
		node_new4	= &grid.Node_Data[last_location_node];

		node_new4->ID	= nnm;
		node_new4->x[0]	= face3->x[0];
		node_new4->x[1]	= face3->x[1];
		node_new4->x[2]	= face3->x[2];
		node_new4->index.i = ic;
		node_new4->index.j = jc;
		node_new4->index.k = kc;
		node_new4->BC = GridShapeFunctions(node_new4->x[0], node_new4->x[1], node_new4->x[2]);

		if (face3->CR != NULL && face3->CR->has_Child == true)
		{
			node_new4->C_List.resize(4);
			node_new4->C_List[0]	= face3->CR->Children[0];
			node_new4->C_List[1]	= face3->CR->Children[1];
			node_new4->C_List[2]	= cell_new3;
			node_new4->C_List[3]	= cell_new4;
		}
		else
		{
			node_new4->C_List.resize(3);
			node_new4->C_List[0]	= face3->CR;
			node_new4->C_List[1]	= cell_new3;
			node_new4->C_List[2]	= cell_new4;
		}

		grid.whereisNode[node_new4->ID]	= last_location_node;
	//	grid.Node_Index_Map.insert(ic, jc, kc, last_location_node);
	}
	else
	{
		node_new4 = grid.NODE(ic, jc, kc);
	}


	// Node5
	ic	= i;
	jc	= j + dj;
	kc  = k;

	if (grid.NODE(ic, jc, kc) == NULL)
	{
		nnm++;
		grid.Node_Data.resize(nnm);
		grid.whereisNode.resize(nnm + 1);
		last_location_node	= grid.Node_Data.size() - 1;
		node_new5	= &grid.Node_Data[last_location_node];

		node_new5->ID	= nnm;
		node_new5->x[0]	= face4->x[0];
		node_new5->x[1]	= face4->x[1];
		node_new5->x[2]	= face4->x[2];
		node_new5->index.i = ic;
		node_new5->index.j = jc;
		node_new5->index.k = kc;
		node_new5->BC = GridShapeFunctions(node_new5->x[0], node_new5->x[1], node_new5->x[2]);

		if (face4->CL != NULL && face4->CL->has_Child == true)
		{
			node_new5->C_List.resize(4);
			node_new5->C_List[0]	= face4->CL->Children[1];
			node_new5->C_List[1]	= face4->CL->Children[2];
			node_new5->C_List[2]	= cell_new4;
			node_new5->C_List[3]	= cell_new1;
		}
		else
		{
			node_new5->C_List.resize(3);
			node_new5->C_List[0]	= face4->CL;
			node_new5->C_List[1]	= cell_new4;
			node_new5->C_List[2]	= cell_new1;
		}

		grid.whereisNode[node_new5->ID]	= last_location_node;
	//	grid.Node_Index_Map.insert(ic, jc, kc, last_location_node);
	}
	else
	{
		node_new5 = grid.NODE(ic, jc, kc);
	}


	// Update in Grid
	for (int i_n = grid.NNM-1; i_n <= nnm-1; i_n++)
	{
		if(grid.Node_Data[i_n].BC >= 0)	grid.Node_List.push_back(&grid.Node_Data[i_n]);
		else							grid.Node_Data[i_n].remove();
	}

	grid.NNM = nnm;







	// 2. FACE
	c_Face*	face_new1;
	c_Face*	face_new2;
	c_Face*	face_new3;
	c_Face*	face_new4;
	c_Face*	face_new5;
	c_Face*	face_new6;
	c_Face*	face_new7;
	c_Face*	face_new8;
	c_Face*	face_new9;
	c_Face*	face_new10;
	c_Face*	face_new11;
	c_Face*	face_new12;

	int last_location_face;
	int nfm	= grid.NFM;

	// face1
	ic	= i + di;
	jc	= j + 0.5*dj;
	kc	= k;

	nfm++;
	grid.Face_Data.resize(nfm);
	grid.whereisFace.resize(nfm+1);
	last_location_face	= grid.Face_Data.size() - 1;
	face_new1	= &grid.Face_Data[last_location_face];

	face_new1->ID		= nfm;
	face_new1->index.i 	= ic;
	face_new1->index.j 	= jc;
	face_new1->index.k 	= kc;
	face_new1->index.lvl_refine = lvl_refine;
	face_new1->index.direction = 1;
	face_new1->N_List.resize(2);
	face_new1->N_List[0]	= node_new2;
	face_new1->N_List[1]	= node_new1;
	face_new1->Parent = NULL;
	face_new1->has_Child = false;
	face_new1->CL	= cell_new1;
	face_new1->CR	= cell_new2;
	grid.whereisFace[face_new1->ID]	= last_location_face;
	//grid.Face_Index_Map.insert(ic, jc, kc, last_location_face);
	GridProcessing_Face_v2(grid, last_location_face);



	// face2
	ic	= i + 1.5*di;
	jc	= j + dj;
	kc	= k;

	nfm++;
	grid.Face_Data.resize(nfm);
	grid.whereisFace.resize(nfm+1);
	last_location_face	= grid.Face_Data.size() - 1;
	face_new2	= &grid.Face_Data[last_location_face];

	face_new2->ID	= nfm;
	face_new2->index.i = ic;
	face_new2->index.j = jc;
	face_new2->index.k = kc;
	face_new2->index.lvl_refine = lvl_refine;
	face_new2->index.direction = 2;
	face_new2->N_List.resize(2);
	face_new2->N_List[0]	= node_new1;
	face_new2->N_List[1]	= node_new3;
	face_new2->Parent = NULL;
	face_new2->has_Child = false;
	face_new2->CL	= cell_new2;
	face_new2->CR	= cell_new3;
	grid.whereisFace[face_new2->ID]	= last_location_face;
	//grid.Face_Index_Map.insert(ic, jc, kc, last_location_face);
	GridProcessing_Face_v2(grid, last_location_face);


	// face3
	ic	= i + di;
	jc	= j + 1.5*dj;
	kc	= k;

	nfm++;
	grid.Face_Data.resize(nfm);
	grid.whereisFace.resize(nfm+1);
	last_location_face	= grid.Face_Data.size() - 1;
	face_new3	= &grid.Face_Data[last_location_face];

	face_new3->ID	= nfm;
	face_new3->index.i = ic;
	face_new3->index.j = jc;
	face_new3->index.k = kc;
	face_new3->index.lvl_refine = lvl_refine;
	face_new3->index.direction = 1;
	face_new3->N_List.resize(2);
	face_new3->N_List[0]	= node_new1;
	face_new3->N_List[1]	= node_new4;
	face_new3->Parent = NULL;
	face_new3->has_Child = false;
	face_new3->CL	= cell_new4;
	face_new3->CR	= cell_new3;
	grid.whereisFace[face_new3->ID]	= last_location_face;
	//grid.Face_Index_Map.insert(ic, jc, kc, last_location_face);
	GridProcessing_Face_v2(grid, last_location_face);


	// face4
	ic	= i + 0.5*di;
	jc	= j + dj;
	kc	= k;

	nfm++;
	grid.Face_Data.resize(nfm);
	grid.whereisFace.resize(nfm+1);
	last_location_face	= grid.Face_Data.size() - 1;
	face_new4	= &grid.Face_Data[last_location_face];

	face_new4->ID	= nfm;
	face_new4->index.i = ic;
	face_new4->index.j = jc;
	face_new4->index.k = kc;
	face_new4->index.lvl_refine = lvl_refine;
	face_new4->index.direction = 2;
	face_new4->N_List.resize(2);
	face_new4->N_List[0]	= node_new5;
	face_new4->N_List[1]	= node_new1;
	face_new4->Parent = NULL;
	face_new4->has_Child = false;
	face_new4->CL	= cell_new1;
	face_new4->CR	= cell_new4;
	grid.whereisFace[face_new4->ID]	= last_location_face;
	//grid.Face_Index_Map.insert(ic, jc, kc, last_location_face);
	GridProcessing_Face_v2(grid, last_location_face);


	// face5
	ic	= i + 0.5*di;
	jc	= j;
	kc	= k;

	if (grid.FACE(ic, jc, kc) == NULL)
	{
		nfm++;
		grid.Face_Data.resize(nfm);
		grid.whereisFace.resize(nfm+1);
		last_location_face	= grid.Face_Data.size() - 1;
		face_new5	= &grid.Face_Data[last_location_face];

		face_new5->ID	= nfm;
		face_new5->index.i = ic;
		face_new5->index.j = jc;
		face_new5->index.k = kc;
		face_new5->index.lvl_refine = lvl_refine;
		face_new5->index.direction = 1;
		face_new5->N_List.resize(2);
		face_new5->N_List[0]	= node1;
		face_new5->N_List[1]	= node_new2;
		face_new5->Parent = face1;
		face_new5->has_Child = false;

		if (face1->CL != NULL && face1->CL->has_Child == true)	face_new5->CL	= face1->CL->Children[3];
		else													face_new5->CL	= face1->CL;
		face_new5->CR	= cell_new1;

		grid.whereisFace[face_new5->ID]	= last_location_face;
	//	grid.Face_Index_Map.insert(ic, jc, kc, last_location_face);
		GridProcessing_Face_v2(grid, last_location_face);
	}
	else
	{
		face_new5	= grid.FACE(ic, jc, kc);
	}


	// face6
	ic	= i + 1.5*di;
	jc	= j;
	kc	= k;

	if (grid.FACE(ic, jc, kc) == NULL)
	{
		nfm++;
		grid.Face_Data.resize(nfm);
		grid.whereisFace.resize(nfm+1);
		last_location_face	= grid.Face_Data.size() - 1;
		face_new6	= &grid.Face_Data[last_location_face];

		face_new6->ID	= nfm;
		face_new6->index.i = ic;
		face_new6->index.j = jc;
		face_new6->index.k = kc;
		face_new6->index.lvl_refine = lvl_refine;
		face_new6->index.direction = 1;
		face_new6->N_List.resize(2);
		face_new6->N_List[0]	= node_new2;
		face_new6->N_List[1]	= node2;
		face_new6->Parent = face1;
		face_new6->has_Child = false;

		if (face1->CL != NULL && face1->CL->has_Child == true)	face_new6->CL	= face1->CL->Children[2];
		else													face_new6->CL	= face1->CL;
		face_new6->CR	= cell_new2;

		grid.whereisFace[face_new6->ID]	= last_location_face;
	//	grid.Face_Index_Map.insert(ic, jc, kc, last_location_face);
		GridProcessing_Face_v2(grid, last_location_face);
	}
	else
	{
		face_new6	= grid.FACE(ic, jc, kc);
	}


	// face7
	ic	= i + 2.0*di;
	jc	= j + 0.5*dj;
	kc	= k;

	if (grid.FACE(ic, jc, kc) == NULL)
	{
		nfm++;
		grid.Face_Data.resize(nfm);
		grid.whereisFace.resize(nfm+1);
		last_location_face	= grid.Face_Data.size() - 1;
		face_new7	= &grid.Face_Data[last_location_face];

		face_new7->ID	= nfm;
		face_new7->index.i = ic;
		face_new7->index.j = jc;
		face_new7->index.k = kc;
		face_new7->index.lvl_refine = lvl_refine;
		face_new7->index.direction = 2;
		face_new7->N_List.resize(2);
		face_new7->N_List[0]	= node2;
		face_new7->N_List[1]	= node_new3;
		face_new7->Parent = face2;
		face_new7->has_Child = false;

		face_new7->CL	= cell_new2;
		if (face2->CR != NULL && face2->CR->has_Child == true)	face_new7->CR	= face2->CR->Children[0];
		else													face_new7->CR	= face2->CR;

		grid.whereisFace[face_new7->ID]	= last_location_face;
	//	grid.Face_Index_Map.insert(ic, jc, kc, last_location_face);
		GridProcessing_Face_v2(grid, last_location_face);
	}
	else
	{
		face_new7	= grid.FACE(ic, jc, kc);
	}


	// face8
	ic	= i + 2.0*di;
	jc	= j + 1.5*dj;
	kc	= k;

	if (grid.FACE(ic, jc, kc) == NULL)
	{
		nfm++;
		grid.Face_Data.resize(nfm);
		grid.whereisFace.resize(nfm+1);
		last_location_face	= grid.Face_Data.size() - 1;
		face_new8	= &grid.Face_Data[last_location_face];

		face_new8->ID	= nfm;
		face_new8->index.i = ic;
		face_new8->index.j = jc;
		face_new8->index.k = kc;
		face_new8->index.lvl_refine = lvl_refine;
		face_new8->index.direction = 2;
		face_new8->N_List.resize(2);
		face_new8->N_List[0]	= node_new3;
		face_new8->N_List[1]	= node3;
		face_new8->Parent = face2;
		face_new8->has_Child = false;

		face_new8->CL	= cell_new3;
		if (face2->CR != NULL && face2->CR->has_Child == true)	face_new8->CR = face2->CR->Children[3];
		else													face_new8->CR	= face2->CR;

		grid.whereisFace[face_new8->ID]	= last_location_face;
	//	grid.Face_Index_Map.insert(ic, jc, kc, last_location_face);
		GridProcessing_Face_v2(grid, last_location_face);
	}
	else
	{
		face_new8	= grid.FACE(ic, jc, kc);
	}


	// face9
	ic	= i + 1.5*di;
	jc	= j + 2.0*dj;
	kc	= k;

	if (grid.FACE(ic, jc, kc) == NULL)
	{
		nfm++;
		grid.Face_Data.resize(nfm);
		grid.whereisFace.resize(nfm+1);
		last_location_face	= grid.Face_Data.size() - 1;
		face_new9	= &grid.Face_Data[last_location_face];

		face_new9->ID	= nfm;
		face_new9->index.i = ic;
		face_new9->index.j = jc;
		face_new9->index.k = kc;
		face_new9->index.lvl_refine = lvl_refine;
		face_new9->index.direction = 1;
		face_new9->N_List.resize(2);
		face_new9->N_List[0]	= node_new4;
		face_new9->N_List[1]	= node3;
		face_new9->Parent = face3;
		face_new9->has_Child = false;
		face_new9->CL	= cell_new3;
		if (face3->CR != NULL && face3->CR->has_Child == true)	face_new9->CR	= face3->CR->Children[1];
		else													face_new9->CR	= face3->CR;

		grid.whereisFace[face_new9->ID]	= last_location_face;
	//	grid.Face_Index_Map.insert(ic, jc, kc, last_location_face);
		GridProcessing_Face_v2(grid, last_location_face);
	}
	else
	{
		face_new9	= grid.FACE(ic, jc, kc);
	}



	// face10
	ic	= i + 0.5*di;
	jc	= j + 2.0*dj;
	kc	= k;

	if (grid.FACE(ic, jc, kc) == NULL)
	{
		nfm++;
		grid.Face_Data.resize(nfm);
		grid.whereisFace.resize(nfm+1);
		last_location_face	= grid.Face_Data.size() - 1;
		face_new10	= &grid.Face_Data[last_location_face];

		face_new10->ID	= nfm;
		face_new10->index.i = ic;
		face_new10->index.j = jc;
		face_new10->index.k = kc;
		face_new10->index.lvl_refine = lvl_refine;
		face_new10->index.direction = 1;
		face_new10->N_List.resize(2);
		face_new10->N_List[0]	= node4;
		face_new10->N_List[1]	= node_new4;
		face_new10->Parent = face3;
		face_new10->has_Child = false;

		face_new10->CL	= cell_new4;
		if (face3->CR != NULL && face3->CR->has_Child == true)	face_new10->CR	= face3->CR->Children[0];
		else													face_new10->CR	= face3->CR;

		grid.whereisFace[face_new10->ID]	= last_location_face;
	//	grid.Face_Index_Map.insert(ic, jc, kc, last_location_face);
		GridProcessing_Face_v2(grid, last_location_face);
	}
	else
	{
		face_new10	= grid.FACE(ic, jc, kc);
	}


	// face11
	ic	= i;
	jc	= j + 1.5*dj;
	kc	= k;

	if (grid.FACE(ic, jc, kc) == NULL)
	{
		nfm++;
		grid.Face_Data.resize(nfm);
		grid.whereisFace.resize(nfm+1);
		last_location_face	= grid.Face_Data.size() - 1;
		face_new11	= &grid.Face_Data[last_location_face];

		face_new11->ID	= nfm;
		face_new11->index.i = ic;
		face_new11->index.j = jc;
		face_new11->index.k = kc;
		face_new11->index.lvl_refine = lvl_refine;
		face_new11->index.direction = 2;
		face_new11->N_List.resize(2);
		face_new11->N_List[0]	= node_new5;
		face_new11->N_List[1]	= node4;
		face_new11->Parent = face4;
		face_new11->has_Child = false;

		if (face4->CL != NULL && face4->CL->has_Child == true)	face_new11->CL	= face4->CL->Children[2];
		else													face_new11->CL	= face4->CL;
		face_new11->CR	= cell_new4;

		grid.whereisFace[face_new11->ID]	= last_location_face;
	//	grid.Face_Index_Map.insert(ic, jc, kc, last_location_face);
		GridProcessing_Face_v2(grid, last_location_face);
	}
	else
	{
		face_new11	= grid.FACE(ic, jc, kc);
	}


	// face12
	ic	= i;
	jc	= j + 0.5*dj;
	kc	= k;

	if (grid.FACE(ic, jc, kc) == NULL)
	{
		nfm++;
		grid.Face_Data.resize(nfm);
		grid.whereisFace.resize(nfm+1);
		last_location_face	= grid.Face_Data.size() - 1;
		face_new12	= &grid.Face_Data[last_location_face];

		face_new12->ID	= nfm;
		face_new12->index.i = ic;
		face_new12->index.j = jc;
		face_new12->index.k = kc;
		face_new12->index.lvl_refine = lvl_refine;
		face_new12->index.direction = 2;
		face_new12->N_List.resize(2);
		face_new12->N_List[0]	= node1;
		face_new12->N_List[1]	= node_new5;
		face_new12->Parent = face4;
		face_new12->has_Child = false;

		if (face4->CL != NULL && face4->CL->has_Child == true)	face_new12->CL	= face4->CL->Children[1];
		else													face_new12->CL	= face4->CL;
		face_new12->CR	= cell_new1;

		grid.whereisFace[face_new12->ID]	= last_location_face;
	//	grid.Face_Index_Map.insert(ic, jc, kc, last_location_face);
		GridProcessing_Face_v2(grid, last_location_face);
	}
	else
	{
		face_new12	= grid.FACE(ic, jc, kc);
	}


	if (face1->has_Child == false)
	{
		face1->has_Child	= true;
		face1->Children.resize(2);
		face1->Children[0]	= face_new5;
		face1->Children[1]	= face_new6;
	}

	if (face2->has_Child == false)
	{
		face2->has_Child	= true;
		face2->Children.resize(2);
		face2->Children[0]	= face_new7;
		face2->Children[1]	= face_new8;
	}

	if (face3->has_Child == false)
	{

		face3->has_Child	= true;
		face3->Children.resize(2);
		face3->Children[0]	= face_new9;
		face3->Children[1]	= face_new10;
	}

	if (face4->has_Child == false)
	{

		face4->has_Child	= true;
		face4->Children.resize(2);
		face4->Children[0]	= face_new11;
		face4->Children[1]	= face_new12;
	}



	for (int i_f = grid.NFM-1; i_f <= nfm-1; i_f++)
	{
		if (grid.Face_Data[i_f].N_List[0]->BC == -1 && grid.Face_Data[i_f].N_List[1]->BC == -1)
		{
			grid.Face_Data[i_f].BC 	= -1;
			grid.Face_Data[i_f].type 	= -1;
			grid.Face_Data[i_f].remove();
		}
		else if (grid.Face_Data[i_f].N_List[0]->BC == 1 && grid.Face_Data[i_f].N_List[1]->BC == 1)
		{
			grid.Face_Data[i_f].BC 	= 0;
			grid.Face_Data[i_f].type 	= 0;
			grid.Face_List.push_back(&grid.Face_Data[i_f]);
		}
		else
		{
			grid.Face_Data[i_f].BC 	= 1;
			grid.Face_Data[i_f].type 	= 1;
			grid.Face_List_Boundary.push_back(&grid.Face_Data[i_f]);
		}
	}
	grid.NFM = nfm;






	// 3. Create Cell
	ic = grid.Cell_Data[c].index.i;
	jc = grid.Cell_Data[c].index.j;
	kc = grid.Cell_Data[c].index.k;
	int ncm = grid.NCM;

	// Cell1
	ncm++;
	cell_new1->ID = ncm;
	cell_new1->index.i = ic;
	cell_new1->index.j = jc;
	cell_new1->index.k = kc;
	cell_new1->index.location	= 0;
	cell_new1->index.lvl_refine = lvl_refine;
	cell_new1->index.location_history = grid.Cell_Data[c].index.location_history;
	cell_new1->index.location_history.push_back(1);
	cell_new1->N_List.resize(4);
	cell_new1->N_List[0]	= node1;
	cell_new1->N_List[1]	= node_new2;
	cell_new1->N_List[2]	= node_new1;
	cell_new1->N_List[3]	= node_new5;
	cell_new1->F_List.resize(4);
	cell_new1->F_List[0]	= face_new5;
	cell_new1->F_List[1]	= face_new1;
	cell_new1->F_List[2]	= face_new4;
	cell_new1->F_List[3]	= face_new12;
	cell_new1->Parent		= cell;


	// Cell2
	ncm++;
	cell_new2->ID = ncm;
	cell_new2->index.i = ic;
	cell_new2->index.j = jc;
	cell_new2->index.k = kc;
	cell_new2->index.location	= 1;
	cell_new2->index.lvl_refine = lvl_refine;
	cell_new2->index.location_history = grid.Cell_Data[c].index.location_history;
	cell_new2->index.location_history.push_back(1);
	cell_new2->N_List.resize(4);
	cell_new2->N_List[0]	= node_new2;
	cell_new2->N_List[1]	= node2;
	cell_new2->N_List[2]	= node_new3;
	cell_new2->N_List[3]	= node_new1;
	cell_new2->F_List.resize(4);
	cell_new2->F_List[0]	= face_new6;
	cell_new2->F_List[1]	= face_new7;
	cell_new2->F_List[2]	= face_new2;
	cell_new2->F_List[3]	= face_new1;
	cell_new2->Parent		= cell;


	// Cell3
	ncm++;
	cell_new3->ID = ncm;
	cell_new3->index.i = ic;
	cell_new3->index.j = jc;
	cell_new3->index.k = kc;
	cell_new3->index.location	= 2;
	cell_new3->index.lvl_refine = lvl_refine;
	cell_new3->index.location_history = grid.Cell_Data[c].index.location_history;
	cell_new3->index.location_history.push_back(1);
	cell_new3->N_List.resize(4);
	cell_new3->N_List[0]	= node_new1;
	cell_new3->N_List[1]	= node_new3;
	cell_new3->N_List[2]	= node3;
	cell_new3->N_List[3]	= node_new4;
	cell_new3->F_List.resize(4);
	cell_new3->F_List[0]	= face_new2;
	cell_new3->F_List[1]	= face_new8;
	cell_new3->F_List[2]	= face_new9;
	cell_new3->F_List[3]	= face_new3;
	cell_new3->Parent		= cell;


	// Cell4
	ncm++;
	cell_new4->ID = ncm;
	cell_new4->index.i = ic;
	cell_new4->index.j = jc;
	cell_new4->index.k = kc;
	cell_new4->index.location	= 3;
	cell_new4->index.lvl_refine = lvl_refine;
	cell_new4->index.location_history = grid.Cell_Data[c].index.location_history;
	cell_new4->index.location_history.push_back(1);
	cell_new4->N_List.resize(4);
	cell_new4->N_List[0]	= node_new5;
	cell_new4->N_List[1]	= node_new1;
	cell_new4->N_List[2]	= node_new4;
	cell_new4->N_List[3]	= node4;
	cell_new4->F_List.resize(4);
	cell_new4->F_List[0]	= face_new4;
	cell_new4->F_List[1]	= face_new3;
	cell_new4->F_List[2]	= face_new10;
	cell_new4->F_List[3]	= face_new11;
	cell_new4->Parent		= cell;


	grid.whereisCell[cell_new1->ID]	= last_location_cell+1;
	grid.whereisCell[cell_new2->ID]	= last_location_cell+2;
	grid.whereisCell[cell_new3->ID]	= last_location_cell+3;
	grid.whereisCell[cell_new4->ID]	= last_location_cell+4;

	grid.Cell_Index_Map[ic][jc][kc](lvl_refine, 0)	= last_location_cell+1;
	grid.Cell_Index_Map[ic][jc][kc](lvl_refine, 1)	= last_location_cell+2;
	grid.Cell_Index_Map[ic][jc][kc](lvl_refine, 2)	= last_location_cell+3;
	grid.Cell_Index_Map[ic][jc][kc](lvl_refine, 3)	= last_location_cell+4;


	grid.Cell_Data[c].has_Child = true;
	grid.Cell_Data[c].Children.resize(4);
	grid.Cell_Data[c].Children[0]	= cell_new1;
	grid.Cell_Data[c].Children[1]	= cell_new2;
	grid.Cell_Data[c].Children[2]	= cell_new3;
	grid.Cell_Data[c].Children[3]	= cell_new4;




	for (int i_c = grid.NCM-1; i_c <= ncm-1; i_c++)
	{
		if (grid.Cell_Data[i_c].N_List[0]->BC == 1 &&
			grid.Cell_Data[i_c].N_List[1]->BC == 1 &&
			grid.Cell_Data[i_c].N_List[2]->BC == 1 &&
			grid.Cell_Data[i_c].N_List[3]->BC == 1 )
		{
			grid.Cell_Data[i_c].BC	= 0;
			grid.Cell_Data[i_c].type	= 0;

			grid.Cell_List.push_back(&grid.Cell_Data[i_c]);
		}
		else if (grid.Cell_Data[i_c].N_List[0]->BC <= 0 &&
			grid.Cell_Data[i_c].N_List[1]->BC <= 0 &&
			grid.Cell_Data[i_c].N_List[2]->BC <= 0 &&
			grid.Cell_Data[i_c].N_List[3]->BC <= 0 )
		{
			grid.Cell_Data[i_c].BC	= 1;
			grid.Cell_Data[i_c].type	= -1;

			grid.Cell_List_Ghost.push_back(&grid.Cell_Data[i_c]);
			grid.Cell_Data[i_c].remove();
		}
		else
		{
			grid.Cell_Data[i_c].BC	= 0;
			grid.Cell_Data[i_c].type	= 1;

			grid.Cell_List.push_back(&grid.Cell_Data[i_c]);
		}
	}

	GridProcessing_Cell_v2(grid, last_location_cell+1);
	GridProcessing_Cell_v2(grid, last_location_cell+2);
	GridProcessing_Cell_v2(grid, last_location_cell+3);
	GridProcessing_Cell_v2(grid, last_location_cell+4);
	grid.NCM = ncm;
	cell->remove();
}


*/




}
}

