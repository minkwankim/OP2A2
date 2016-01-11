/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GridReadFaces.cpp
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

unsigned int fluentFaceTypeConverter(int flu_facetype)
{
	switch (flu_facetype)
	{
	case FLU_F_LINE:
		return (f_line);
		break;
	case FLU_F_TRIANGLE:
		return (f_triangle);
		break;
	case FLU_F_QUADRILATERAL:
		return (f_quadrilateral);
		break;
	}

	return (0);
}


void GridReadFaces_Fluent(const string& mesh_file_name, c_Grid& grid, vector<int>& bc_zone)
{
	// Step 1: Open file to read
	ifstream mesh_file(mesh_file_name.c_str());
	if(!mesh_file) throw OP2A::Common::ExceptionGeneral (FromHere(), "Could not open file: " + mesh_file_name, OP2A::Common::ErrorCode::FileSystem());

	grid.Data.faces.resize(grid.Info.NFM);


	// Step 2: Read Data
	int index, index2, zone, first_index, last_index, bc_type, face_type, face_type2;
	int f = 0;
	int type;
	int	nodes[4];
	int	cl, cr;
	string line;

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
					case FLU_F_MIXED:
						for (int i = first_index; i <= last_index; i++)
						{
							face_type2 = -1;
							getline(mesh_file, line);
							sscanf(line.c_str(), "%d", &face_type2);

							switch (face_type2)
							{
							case FLU_F_LINE: // LINE
								sscanf(line.c_str(), "%d %x %x %x %x", &type, &nodes[0], &nodes[1], &cl, &cr);

								grid.Data.faces[f].geometry.id	= i;
								grid.Data.faces[f].geometry.type = fluentFaceTypeConverter(type);

								grid.Data.faces[f].Specialized.N_List.resize(2);
								grid.Data.faces[f].Specialized.N_List[0]	= &grid.NODE_id(nodes[0]);
								grid.Data.faces[f].Specialized.N_List[1]	= &grid.NODE_id(nodes[1]);

								if (cl > 0) grid.Data.faces[f].Specialized.cl	= &grid.CELL_id(cl);
								else		grid.Data.faces[f].Specialized.cl	= NULL;

								if (cr > 0) grid.Data.faces[f].Specialized.cr	= &grid.CELL_id(cr);
								else 		grid.Data.faces[f].Specialized.cr = NULL;

								break;

							case FLU_F_TRIANGLE:	// TRIANGLE
								sscanf(line.c_str(), "%d %x %x %x %x %x", &type, &nodes[0], &nodes[1], &nodes[2], &cl, &cr);

								grid.Data.faces[f].geometry.id	= i;
								grid.Data.faces[f].geometry.type = fluentFaceTypeConverter(type);

								grid.Data.faces[f].Specialized.N_List.resize(3);
								grid.Data.faces[f].Specialized.N_List[0]	= &grid.NODE_id(nodes[0]);
								grid.Data.faces[f].Specialized.N_List[1]	= &grid.NODE_id(nodes[1]);
								grid.Data.faces[f].Specialized.N_List[2]	= &grid.NODE_id(nodes[2]);

								if (cl > 0) grid.Data.faces[f].Specialized.cl	= &grid.CELL_id(cl);
								else		grid.Data.faces[f].Specialized.cl	= NULL;

								if (cr > 0) grid.Data.faces[f].Specialized.cr	= &grid.CELL_id(cr);
								else 		grid.Data.faces[f].Specialized.cr = NULL;

								break;

							case FLU_F_QUADRILATERAL: // QUADRILATERAL
								sscanf(line.c_str(), "%d %x %x %x %x %x %x", &type, &nodes[0], &nodes[1], &nodes[2], &nodes[3], &cl, &cr);

								grid.Data.faces[f].geometry.id	= i;
								grid.Data.faces[f].geometry.type = fluentFaceTypeConverter(type);

								grid.Data.faces[f].Specialized.N_List.resize(4);
								grid.Data.faces[f].Specialized.N_List[0]	= &grid.NODE_id(nodes[0]);
								grid.Data.faces[f].Specialized.N_List[1]	= &grid.NODE_id(nodes[1]);
								grid.Data.faces[f].Specialized.N_List[2]	= &grid.NODE_id(nodes[2]);
								grid.Data.faces[f].Specialized.N_List[3]	= &grid.NODE_id(nodes[3]);

								if (cl > 0) grid.Data.faces[f].Specialized.cl	= &grid.CELL_id(cl);
								else		grid.Data.faces[f].Specialized.cl	= NULL;

								if (cr > 0) grid.Data.faces[f].Specialized.cr	= &grid.CELL_id(cr);
								else 		grid.Data.faces[f].Specialized.cr = NULL;

								break;

							default:
								OP2A::Common::ExceptionGeneral(FromHere(), "Given Face-type number IS NOT SUPPORTED FACE TYPE", OP2A::Common::ErrorCode::NotSupportedType());
								break;
							}

							grid.Data.faces[f].bc_type.bc 	= bc_type;

							if (bc_type == interior)	grid.Data.faces[f].bc_type.type = inside_domain;
							else						grid.Data.faces[f].bc_type.type = edge_domain;

							grid.Map.f_assign_ID_to_pos(grid.Data.faces[f].geometry.id, f);
							f++;;
						}
						break;

					case FLU_F_LINE: // LINE
						for (int i = first_index; i <= last_index; i++)
						{
							getline(mesh_file, line);
							sscanf(line.c_str(), "%x %x %x %x", &nodes[0], &nodes[1], &cl, &cr);

							grid.Data.faces[f].geometry.id	= i;
							grid.Data.faces[f].geometry.type = fluentFaceTypeConverter(face_type);

							grid.Data.faces[f].Specialized.N_List.resize(2);
							grid.Data.faces[f].Specialized.N_List[0]	= &grid.NODE_id(nodes[0]);
							grid.Data.faces[f].Specialized.N_List[1]	= &grid.NODE_id(nodes[1]);

							if (cl > 0) grid.Data.faces[f].Specialized.cl	= &grid.CELL_id(cl);
							else		grid.Data.faces[f].Specialized.cl	= NULL;

							if (cr > 0) grid.Data.faces[f].Specialized.cr	= &grid.CELL_id(cr);
							else 		grid.Data.faces[f].Specialized.cr = NULL;


							grid.Data.faces[f].bc_type.bc 	= bc_type;

							if (bc_type == interior)	grid.Data.faces[f].bc_type.type = inside_domain;
							else						grid.Data.faces[f].bc_type.type = edge_domain;

							grid.Map.f_assign_ID_to_pos(grid.Data.faces[f].geometry.id, f);
							f++;
						}
						break;

					case FLU_F_TRIANGLE:	// TRIANGLE
						for (int i = first_index; i <= last_index; i++)
						{
							getline(mesh_file, line);
							sscanf(line.c_str(), "%x %x %x %x %x", &nodes[0], &nodes[1], &nodes[2], &cl, &cr);

							grid.Data.faces[f].geometry.id	= i;
							grid.Data.faces[f].geometry.type = fluentFaceTypeConverter(face_type);

							grid.Data.faces[f].Specialized.N_List.resize(3);
							grid.Data.faces[f].Specialized.N_List[0]	= &grid.NODE_id(nodes[0]);
							grid.Data.faces[f].Specialized.N_List[1]	= &grid.NODE_id(nodes[1]);
							grid.Data.faces[f].Specialized.N_List[2]	= &grid.NODE_id(nodes[2]);

							if (cl > 0) grid.Data.faces[f].Specialized.cl	= &grid.CELL_id(cl);
							else		grid.Data.faces[f].Specialized.cl	= NULL;

							if (cr > 0) grid.Data.faces[f].Specialized.cr	= &grid.CELL_id(cr);
							else 		grid.Data.faces[f].Specialized.cr = NULL;

							grid.Data.faces[f].bc_type.bc 	= bc_type;

							if (bc_type == interior)	grid.Data.faces[f].bc_type.type = inside_domain;
							else						grid.Data.faces[f].bc_type.type = edge_domain;

							grid.Map.f_assign_ID_to_pos(grid.Data.faces[f].geometry.id, f);
							f++;
						}
						break;

					case FLU_F_QUADRILATERAL: // QUADRILATERAL
						for (int i = first_index; i <= last_index; i++)
						{
							getline(mesh_file, line);
							sscanf(line.c_str(), "%x %x %x %x %x %x", &nodes[0], &nodes[1], &nodes[2], &nodes[2], &cl, &cr);

							grid.Data.faces[f].geometry.id	= i;
							grid.Data.faces[f].geometry.type = fluentFaceTypeConverter(face_type);

							grid.Data.faces[f].Specialized.N_List.resize(4);
							grid.Data.faces[f].Specialized.N_List[0]	= &grid.NODE_id(nodes[0]);
							grid.Data.faces[f].Specialized.N_List[1]	= &grid.NODE_id(nodes[1]);
							grid.Data.faces[f].Specialized.N_List[2]	= &grid.NODE_id(nodes[2]);
							grid.Data.faces[f].Specialized.N_List[3]	= &grid.NODE_id(nodes[3]);

							if (cl > 0) grid.Data.faces[f].Specialized.cl	= &grid.CELL_id(cl);
							else		grid.Data.faces[f].Specialized.cl	= NULL;

							if (cr > 0) grid.Data.faces[f].Specialized.cr	= &grid.CELL_id(cr);
							else 		grid.Data.faces[f].Specialized.cr = NULL;

							grid.Data.faces[f].bc_type.bc 	= bc_type;

							if (bc_type == interior)	grid.Data.faces[f].bc_type.type = inside_domain;
							else						grid.Data.faces[f].bc_type.type = edge_domain;

							grid.Map.f_assign_ID_to_pos(grid.Data.faces[f].geometry.id, f);
							f++;
						}
						break;

					default:
						OP2A::Common::ExceptionGeneral (FromHere(), "Given Face-type number IS NOT SUPPORTED FACE TYPE", OP2A::Common::ErrorCode::NotSupportedType());
						break;
					}
				}// END READ FACE DATA
			}// END READ MESH FILE
		}

		//Step 2.2 Check Error
		if (f != grid.Info.NFM)
		{
			OP2A::Common::ExceptionGeneral(FromHere(), "PROBLEM IN FACE DATA. TOTAL NUMBER OF FACE DATA DOES NOT MATHCH WITH MESH INFOMATION DATA",  OP2A::Common::ErrorCode::DataMismatch());
		}
	}
}





}
