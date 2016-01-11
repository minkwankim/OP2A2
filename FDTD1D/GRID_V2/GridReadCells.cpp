/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GridReadCells.cpp
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

unsigned int fluenCellTypeConverter(int flu_celltype)
{
	switch (flu_celltype)
	{
	case FLU_C_TRIANGLE:
		return (c_triangle);
		break;
	case FLU_C_TETRAHEDRON:
		return (c_tetrahedron);
		break;
	case FLU_C_QUADRILATERAL:
		return (c_quadrilateral);
		break;

	case FLU_C_HEXAHEDRON:
		return (c_hexahedron);
		break;

	case FLU_C_PYRAMID:
		return (c_pyramid);
		break;

	case FLU_C_PRISM:
		return (c_prism);
		break;
	}

	return (0);
}



void GridReadCells_Fluent(const string& mesh_file_name, c_Grid& grid)
{
	// Step 1: Open file to read
	ifstream mesh_file(mesh_file_name.c_str());
	if(!mesh_file) throw OP2A::Common::ExceptionGeneral (FromHere(), "Could not open file: " + mesh_file_name, OP2A::Common::ErrorCode::FileSystem());
	grid.Data.cells.resize(grid.Info.NCM);


	// Step 2: Read mesh file
	int index, index2, zone, first_index, last_index, type, element_type;
	int c = 0;
	string line;

	if (mesh_file.is_open())
	{
		while (! mesh_file.eof())
		{
			// STEP 2.1: GET INDEX
			index = -1;
			getline(mesh_file, line);
			sscanf(line.c_str(), "(%d ", &index);

			if (index == FLU_INDEX_CELL)
			{
				index2			= -1;
				zone 			= -1;
				first_index		= -1;
				last_index		= -1;
				type 			= -1;
				element_type	= -1;

				sscanf(line.c_str(),"(%d (%x %x %x %d", &index2, &zone, &first_index, &last_index, &type); // GETTING INDEX AND ZONE
				if (zone > 0)
				{
					sscanf(line.c_str(),"(%d (%x %x %x %d %d)", &index2, &zone, &first_index, &last_index, &type, &element_type); // GETTING INDEX AND ZONE

					if (type == 1)
					{
						if (element_type != FLU_C_MIXED)
						{
							for (int i = first_index; i <= last_index; i++)
							{
								grid.Data.cells[c].geometry.id 		= i;
								grid.Data.cells[c].geometry.type	= fluenCellTypeConverter(element_type);
								grid.Data.cells[c].bc_type.bc 		= interior;
								grid.Map.c_assign_ID_to_pos(grid.Data.cells[c].geometry.id, c);
								c++;
							}
						}
						else
						{
							for (int i = first_index; i <= last_index; i++)
							{
								mesh_file >> element_type;

								grid.Data.cells[c].geometry.id 		= i;
								grid.Data.cells[c].geometry.type	= fluenCellTypeConverter(element_type);
								grid.Data.cells[c].bc_type.bc 		= interior;
								grid.Map.c_assign_ID_to_pos(grid.Data.cells[c].geometry.id, c);
								c++;
							}
						}
					}
				}
			} // END READ CELL DATA
		} // END READ MESH FILE

		if (c != grid.Info.NCM)
		{
			OP2A::Common::ExceptionGeneral(FromHere(), "PROBLEM IN CELL DATA. TOTAL NUMBER OF CELL DATA DOES NOT MATHCH WITH MESH INFOMATION DATA",  OP2A::Common::ErrorCode::DataMismatch());
		}
	}
}



}


