/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ReadFace.cpp
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

void ReadGridFaceFluent(const  std::string& mesh_file_name, const OP2A::GRID::Configuration& config,
						vector<GRID::Node>& nodes, const vector<int>& whereisNode,
						vector<GRID::Face>& faces, 	     vector<int>& whereisFace,
						vector<GRID::Cell>& cells, const vector<int>& whereisCell,
						const vector<int>& bc_zone)
{
	int index, index2, zone, first_index, last_index, bc_type, face_type, face_type2;
	int i;
	int type;
	int	cl, cr;
	string line;
	vector<int>	nodes_ID;



	// 1. Open file to read
	std::ifstream mesh_file;
	mesh_file.open(mesh_file_name.c_str());

	int	f;
	faces.resize(config.NFM+1);
	whereisFace.resize(config.NFM+2);
	for (f = 0; f <= config.NFM+1; f++)	whereisFace[f] = -1;

	// Step 2: Read Data
	f = 0;
	if (mesh_file.is_open())
	{
		while (! mesh_file.eof())
		{
		// STEP 2.1: GET INDEX
			index = -1;
			getline(mesh_file, line);
			sscanf(line.c_str(), "(%d ", &index);

			if (index == FLU_INDEX_FACE)
			{
				index2			= -1;
				zone 			= -1;
				first_index 	= -1;
				last_index 		= -1;
				bc_type 		= -1;
				face_type 		= -1;

				sscanf(line.c_str(),"(%d (%x %x %x %d %d)", &index2, &zone, &first_index, &last_index, &bc_type, &face_type); // GETTING INDEX AND ZONE

				if (zone > 0)
				{
					// Assign BC type from data
					bc_type	= bc_zone[zone];

					switch (face_type)
					{
					case GRID::f_mixed:
						for (i = first_index; i <= last_index; i++)
						{
							face_type2 = -1;
							getline(mesh_file, line);
							sscanf(line.c_str(), "%d", &face_type2);

							f++;
							switch (face_type2)
							{
							case GRID::f_line: // LINE
								nodes_ID.resize(2);
								sscanf(line.c_str(), "%d %x %x %x %x", &type, &nodes_ID[0], &nodes_ID[1], &cl, &cr);

								faces[f].geo.ID		= i;
								faces[f].geo.type	= type;

								faces[f].conn.numNodes = 2;
								faces[f].conn.listNodes.resize(2);
								faces[f].conn.listNodes[0]	= &nodes[whereisNode[nodes_ID[0]]];
								faces[f].conn.listNodes[1]	= &nodes[whereisNode[nodes_ID[1]]];

								faces[f].conn.cl[0]	= &cells[whereisCell[cl]];
								faces[f].conn.cr[0]	= &cells[whereisCell[cr]];
								break;

							case GRID::f_triangle:	// TRIANGLE
								nodes_ID.resize(3);

								sscanf(line.c_str(), "%d %x %x %x %x %x", &type, &nodes_ID[0], &nodes_ID[1], &nodes_ID[2], &cl, &cr);

								faces[f].geo.ID		= i;
								faces[f].geo.type	= type;

								faces[f].conn.numNodes = 3;
								faces[f].conn.listNodes.resize(3);
								faces[f].conn.listNodes[0]	= &nodes[whereisNode[nodes_ID[0]]];
								faces[f].conn.listNodes[1]	= &nodes[whereisNode[nodes_ID[1]]];
								faces[f].conn.listNodes[2]	= &nodes[whereisNode[nodes_ID[2]]];

								faces[f].conn.cl[0]	= &cells[whereisCell[cl]];
								faces[f].conn.cr[0]	= &cells[whereisCell[cr]];
								break;

							case GRID::f_quadrilateral: // QUADRILATERAL
								nodes_ID.resize(4);

								sscanf(line.c_str(), "%d %x %x %x %x %x %x", &type, &nodes_ID[0], &nodes_ID[1], &nodes_ID[2], &nodes_ID[3], &cl, &cr);

								faces[f].geo.ID		= i;
								faces[f].geo.type	= type;

								faces[f].conn.numNodes = 4;
								faces[f].conn.listNodes.resize(4);
								faces[f].conn.listNodes[0]	= &nodes[whereisNode[nodes_ID[0]]];
								faces[f].conn.listNodes[1]	= &nodes[whereisNode[nodes_ID[1]]];
								faces[f].conn.listNodes[2]	= &nodes[whereisNode[nodes_ID[2]]];
								faces[f].conn.listNodes[3]	= &nodes[whereisNode[nodes_ID[3]]];


								faces[f].conn.cl[0]	= &cells[whereisCell[cl]];
								faces[f].conn.cr[0]	= &cells[whereisCell[cr]];
								break;

							default:
								Common::ExceptionGeneral(FromHere(), "It is not supported Face-type. PLEASE CHECK THE FACE TYPE IN A MESH FILE!", "NotSupportedOption:");
								break;
							}

							faces[f].geo.BC = bc_type;
							whereisFace[i]	= f;
						}
						break;

					case GRID::f_line: // LINE
						for (i = first_index; i <= last_index; i++)
						{
							f++;
							nodes_ID.resize(2);

							getline(mesh_file, line);
							sscanf(line.c_str(), "%x %x %x %x", &nodes_ID[0], &nodes_ID[1], &cl, &cr);

							faces[f].geo.ID		= i;
							faces[f].geo.type	= face_type;

							faces[f].conn.numNodes = 2;
							faces[f].conn.listNodes.resize(2);
							faces[f].conn.listNodes[0]	= &nodes[whereisNode[nodes_ID[0]]];
							faces[f].conn.listNodes[1]	= &nodes[whereisNode[nodes_ID[1]]];

							faces[f].conn.cl[0]	= &cells[whereisCell[cl]];
							faces[f].conn.cr[0]	= &cells[whereisCell[cr]];


							faces[f].geo.BC = bc_type;
							whereisFace[i]	= f;
						}
						break;

					case GRID::f_triangle:	// TRIANGLE
						for (i = first_index; i <= last_index; i++)
						{
							f++;
							nodes_ID.resize(3);

							getline(mesh_file, line);
							sscanf(line.c_str(), "%x %x %x %x %x", &nodes_ID[0], &nodes_ID[1], &nodes_ID[2], &cl, &cr);

							faces[f].geo.ID		= i;
							faces[f].geo.type	= face_type;

							faces[f].conn.numNodes = 3;
							faces[f].conn.listNodes.resize(3);
							faces[f].conn.listNodes[0]	= &nodes[whereisNode[nodes_ID[0]]];
							faces[f].conn.listNodes[1]	= &nodes[whereisNode[nodes_ID[1]]];
							faces[f].conn.listNodes[2]	= &nodes[whereisNode[nodes_ID[2]]];

							faces[f].conn.cl[0]	= &cells[whereisCell[cl]];
							faces[f].conn.cr[0]	= &cells[whereisCell[cr]];

							faces[f].geo.BC = bc_type;
							whereisFace[i]	= f;
						}
						break;

					case GRID::f_quadrilateral: // QUADRILATERAL
						for (i = first_index; i <= last_index; i++)
						{
							f++;
							nodes_ID.resize(4);

							sscanf(line.c_str(), "%x %x %x %x %x %x", &nodes_ID[0], &nodes_ID[1], &nodes_ID[2], &nodes_ID[2], &cl, &cr);

							faces[f].geo.ID		= i;
							faces[f].geo.type	= type;

							faces[f].conn.numNodes = 4;
							faces[f].conn.listNodes.resize(4);
							faces[f].conn.listNodes[0]	= &nodes[whereisNode[nodes_ID[0]]];
							faces[f].conn.listNodes[1]	= &nodes[whereisNode[nodes_ID[1]]];
							faces[f].conn.listNodes[2]	= &nodes[whereisNode[nodes_ID[2]]];
							faces[f].conn.listNodes[3]	= &nodes[whereisNode[nodes_ID[3]]];

							faces[f].conn.cl[0]	= &cells[whereisCell[cl]];
							faces[f].conn.cr[0]	= &cells[whereisCell[cr]];

							faces[f].geo.BC = bc_type;
							whereisFace[i]	= f;
						}
						break;

					default:
						Common::ExceptionGeneral(FromHere(), "It is not supported Face-type. PLEASE CHECK THE FACE TYPE IN A MESH FILE!", "NotSupportedOption:");
						break;
					}
				}// END READ FACE DATA
			}// END READ MESH FILE
		}

		//Step 2.2 Check Error
		if (f != config.NFM)
		{
			Common::ExceptionGeneral(FromHere(), "PROBLEM IN FACE DATA. TOTAL NUMBER OF FACE DATA DOES NOT MATHCH WITH MESH INFOMATION DATA",  "DataMismatch:");
		}
	}
	else
	{
		Common::ExceptionGeneral(FromHere(), "Cannot find grid file. Please check your grid file!", "CannotOpenFile:");
	}



	for (f = 1; f <= config.NFM; f++)
	{
		i = whereisFace[f];

		int f_pre  = whereisFace[f-1];
		int f_next = whereisFace[f+1];


		if (f_pre != -1)	faces[i].previous = &faces[f_pre];
		else				faces[i].previous = NULL;

		if (f_next != -1)	faces[i].next	= &faces[f_next];
		else				faces[i].next	= NULL;

	}
}

void ReadGridFace(const  std::string& mesh_file_name, const OP2A::GRID::Configuration& config,
				vector<GRID::Node>& nodes, const vector<int>& whereisNode,
				vector<GRID::Face>& faces, 	     vector<int>& whereisFace,
				vector<GRID::Cell>& cells, const vector<int>& whereisCell,
				const vector<int>& bc_zone, int type)
{
	switch (type)
	{
	case FLUENT:
		ReadGridFaceFluent(mesh_file_name, config, nodes, whereisNode, faces, whereisFace, cells, whereisCell, bc_zone);
		break;

	default:
		Common::ExceptionGeneral(FromHere(), "IT IS NOT SUPPORTED MESH FILE TYPE. PLEASE CHECK MESH FILE!!!", "NotSupportedOption:");
		break;
	}
}


}
