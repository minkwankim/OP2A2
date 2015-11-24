/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ReadGridCell.cpp
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



void ReadGridCellFluent(const  std::string& mesh_file_name, const OP2A::GRID::Configuration& config,
						vector<GRID::Cell>& cells, vector<int>& whereisCell)
{
	int i;
	int index, index2, zone, first_index, last_index, type, element_type;

	string line;

	// 1. Open file to read
	std::ifstream mesh_file;
	mesh_file.open(mesh_file_name.c_str());

	int	c;
	cells.resize(config.NCM+1);
	whereisCell.resize(config.NCM+2);
	for (c = 0; c <= config.NCM+1; c++)	whereisCell[c] = -1;

	// Step 2: Read mesh file
	c = 0;
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
						if (element_type != GRID::c_mixed)
						{
							for (i = first_index; i <= last_index; i++)
							{
								c++;

								cells[c].geo.ID		= i;
								cells[c].geo.BC		= type;
								cells[c].geo.type	= element_type;

								whereisCell[i]	= c;
							}
						}
						else
						{
							for (i = first_index; i <= last_index; i++)
							{
								mesh_file >> element_type;

								c++;
								cells[c].geo.ID	= i;
								cells[c].geo.BC	= type;
								cells[c].geo.type	= element_type;

								whereisCell[i]	= c;
							}
						}
					}
				}
			} // END READ CELL DATA
		} // END READ MESH FILE

		if (c != config.NCM)
		{
			Common::ExceptionGeneral(FromHere(), "PROBLEM IN CELL DATA. TOTAL NUMBER OF CELL DATA DOES NOT MATHCH WITH MESH INFOMATION DATA",  "DataMismatch:");
		}
	}
	else
	{
		Common::ExceptionGeneral(FromHere(), "Cannot find grid file. Please check your grid file!", "CannotOpenFile:");
	}


	for (c = 1; c <= config.NCM; c++)
	{
		i = whereisCell[c];

		int c_pre  = whereisCell[c-1];
		int c_next = whereisCell[c+1];

		/*
		if (c_pre != -1)	cells[i].previous = &cells[c_pre];
		else				cells[i].previous = NULL;

		if (c_next != -1)	cells[i].next	= &cells[c_next];
		else				cells[i].next	= NULL;
		*/
	}
}



void ReadGridCell(const  std::string& mesh_file_name, const OP2A::GRID::Configuration& config,
				vector<GRID::Cell>& cells, vector<int>& whereisCell, int type)
{
	switch (type)
	{
	case FLUENT:
		ReadGridCellFluent(mesh_file_name, config, cells, whereisCell);
		break;

	default:
		Common::ExceptionGeneral(FromHere(), "IT IS NOT SUPPORTED MESH FILE TYPE. PLEASE CHECK MESH FILE!!!", "NotSupportedOption:");
		break;
	}
}


}

