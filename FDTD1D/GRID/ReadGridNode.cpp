/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ReadGridNode.cpp
 *
 *  Created on: Nov 16, 2015
 *      Author: minkwan
 */


#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>



#include "./GRID/ReadGrid.hpp"
#include "./GRID/GridReadIndex.hpp"


using namespace std;
namespace OP2A{


void ReadGridNodeFluent(const  std::string& mesh_file_name, const OP2A::GRID::Configuration&	config, vector<GRID::Node>& nodes,  vector<int>& whereis)
{
	int i, n;
	int index, index2, zone, first_index, last_index, type, nd;
	double x, y, z;
	string line;


	// 1. Open file to read
	std::ifstream mesh_file;
	mesh_file.open(mesh_file_name.c_str());
	nodes.resize(config.NNM+1);
	whereis.resize(config.NNM+2);
	for (n = 0; n <= config.NNM+1; n++)	whereis[n] = -1;


	// Step 2: Read Data
	n = 0;
	if (mesh_file.is_open())
	{
		while (! mesh_file.eof())
		{
			// STEP 1: GET INDEX
			index = -1;
			getline(mesh_file, line);
			sscanf(line.c_str(), "(%d ", &index);

			if (index == FLU_INDEX_NODE)
			{
				index2		= -1;
				zone 		= -1;
				first_index	= -1;
				last_index	= -1;
				type		= -1;
				nd			= -1;

				sscanf(line.c_str(),"(%d (%x %x %x %d %d)", &index2, &zone, &first_index, &last_index, &type, &nd); // GETTING INDEX AND ZONE
				if (zone > 0)
				{
					if (nd != config.DIM)
					{
						Common::ExceptionGeneral(FromHere(), "PROBLEM IN DIMENSION OF NODE DATA. Please the dimension of grid file",  "MismatchData:");
					}
					else
					{
						switch (nd)
						{
						case 2:
							for (i = first_index; i <= last_index; i++)
							{
								x = 0.0;
								y = 0.0;

								getline(mesh_file, line);
								sscanf(line.c_str(), "%lf %lf", &x, &y);

								if (fabs(x) <= OP2A_GRID_MATH_ZERO)	x = 0.0;
								if (fabs(y) <= OP2A_GRID_MATH_ZERO)	y = 0.0;

								n++;
								nodes[n].geo.ID	= i;
								nodes[n].geo.x[0]	= x;
								nodes[n].geo.x[1]	= y;
								nodes[n].geo.x[2]	= 0.0;

								whereis[i] = n;
							}
							break;
						case 3:
							for (i = first_index; i <= last_index; i++)
							{
								x = 0.0;
								y = 0.0;
								z = 0.0;

								getline(mesh_file, line);
								sscanf(line.c_str(), "%lf %lf %lf", &x, &y, &z);

								if (fabs(x) <= OP2A_GRID_MATH_ZERO)	x = 0.0;
								if (fabs(y) <= OP2A_GRID_MATH_ZERO)	y = 0.0;
								if (fabs(z) <= OP2A_GRID_MATH_ZERO)	z = 0.0;

								n++;
								nodes[n].geo.ID	= i;
								nodes[n].geo.x[0]	= x;
								nodes[n].geo.x[1]	= y;
								nodes[n].geo.x[2]	= z;

								whereis[i] = n;
							}
							break;
						}
					}
				}// END READ NODE DATA
			}

		}// END READ MESH FILE

		// Step 3: Check error
		if (n != config.NNM)
		{
			Common::ExceptionGeneral(FromHere(), "PROBLEM IN NODE DATA. TOTAL NUMBER OF NODE DATA DOES NOT MATHCH WITH MESH INFOMATION DATA",  "DataMismatch:");
		}
	}
	else
	{
		Common::ExceptionGeneral(FromHere(), "Cannot find grid file. Please check your grid file!", "CannotOpenFile:");
	}


	for (n = 1; n <= config.NNM; n++)
	{
		i = whereis[n];

		int n_pre  = whereis[n-1];
		int n_next = whereis[n+1];


		if (n_pre != -1)	nodes[i].previous = &nodes[n_pre];
		else				nodes[i].previous = NULL;

		if (n_next != -1)	nodes[i].next	= &nodes[n_next];
		else				nodes[i].next	= NULL;

	}

	mesh_file.close();
}




void ReadGridNode(const  std::string& mesh_file_name, const OP2A::GRID::Configuration&	config, vector<GRID::Node>& nodes,  vector<int>& whereis, int type)
{
	switch (type)
	{
	case FLUENT:
		ReadGridNodeFluent(mesh_file_name, config, nodes, whereis);
		break;

	default:
		Common::ExceptionGeneral(FromHere(), "IT IS NOT SUPPORTED MESH FILE TYPE. PLEASE CHECK MESH FILE!!!", "NotSupportedOption:");
		break;
	}
}



}
