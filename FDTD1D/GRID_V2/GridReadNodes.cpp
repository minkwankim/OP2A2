/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GridReadNode.cpp
 *
 *  Created on: Jan 11, 2016
 *      Author: minkwan
 */


#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string.h>

#include "Gridv2.hpp"
#include "GridReadConfig.hpp"

#include "./COMMON/ExceptionGeneral.hpp"
#include "./COMMON/ErrorCode.hpp"

using namespace std;

namespace GRID {


void GridReadNodes_Fluent(const string& mesh_file_name, c_Grid& grid)
{
	// Step 1: Open file to read
	ifstream mesh_file(mesh_file_name.c_str());
	if(!mesh_file) throw OP2A::Common::ExceptionGeneral (FromHere(), "Could not open file: " + mesh_file_name, OP2A::Common::ErrorCode::FileSystem());

	grid.Data.nodes.resize(grid.Info.NNM);



	// Step 2: Read Data
	int n = 0;
	int index, index2, zone, first_index, last_index, type, nd;
	double x, y, z;
	string line;


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
					if (nd != grid.Info.DIM)
					{
						OP2A::Common::ExceptionGeneral(FromHere(), "PROBLEM IN DIMENSION OF NODE DATA. Please the dimension of grid file",  "MismatchData:");
					}
					else
					{
						switch (nd)
						{
						case 2:
							for (int i = first_index; i <= last_index; i++)
							{
								x = 0.0;
								y = 0.0;

								getline(mesh_file, line);
								sscanf(line.c_str(), "%lf %lf", &x, &y);

								if (fabs(x) <= CONST_GRID_MATH_ZERO)	x = 0.0;
								if (fabs(y) <= CONST_GRID_MATH_ZERO)	y = 0.0;

								grid.Data.nodes[n].geometry.id	= i;
								grid.Data.nodes[n].geometry.x[0]	= x;
								grid.Data.nodes[n].geometry.x[1]	= y;
								grid.Data.nodes[n].geometry.x[2]	= 0.0;

								grid.Map.n_assign_ID_to_pos(grid.Data.nodes[n].geometry.id, n);
								n++;

							}
							break;
						case 3:
							for (int i = first_index; i <= last_index; i++)
							{
								x = 0.0;
								y = 0.0;
								z = 0.0;

								getline(mesh_file, line);
								sscanf(line.c_str(), "%lf %lf %lf", &x, &y, &z);

								if (fabs(x) <= CONST_GRID_MATH_ZERO)	x = 0.0;
								if (fabs(y) <= CONST_GRID_MATH_ZERO)	y = 0.0;
								if (fabs(z) <= CONST_GRID_MATH_ZERO)	z = 0.0;

								grid.Data.nodes[n].geometry.id		= i;
								grid.Data.nodes[n].geometry.x[0]	= x;
								grid.Data.nodes[n].geometry.x[1]	= y;
								grid.Data.nodes[n].geometry.x[2]	= z;

								grid.Map.n_assign_ID_to_pos(grid.Data.nodes[n].geometry.id, n);
								n++;
							}
							break;
						}
					}
				}// END READ NODE DATA
			}

		}// END READ MESH FILE

		// Step 3: Check error
		if (n != grid.Info.NNM)
		{
			OP2A::Common::ExceptionGeneral(FromHere(), "PROBLEM IN NODE DATA. TOTAL NUMBER OF NODE DATA DOES NOT MATHCH WITH MESH INFOMATION DATA",  OP2A::Common::ErrorCode::DataMismatch());
		}
	}

	mesh_file.close();
}











}

