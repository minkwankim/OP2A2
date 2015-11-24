/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ReadGridBasicInfo.cpp
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

void ReadGridInfoFluent(const  std::string& mesh_file_name,		// Mesh file name
						OP2A::GRID::Configuration&	config,		// Grid Configuration
						std::vector<int>& bcZone)				// BC Information
{
	int i;
	int index, temp, zone, bc_type;
	int zone_temp;
	int index_s, index_e;
	int nd, nfm, ncm, nnm;
	int nfm_zone;

	char zone_type[20];
	string line;



	// 1. Open file to read
	std::ifstream mesh_file;
	mesh_file.open(mesh_file_name.c_str());


	// 2. Initialize counter
	int ngm = 0;
	int maxZone = 0;


	if (mesh_file.is_open())
	{
		// 3. FIRST READ
		while (! mesh_file.eof())
		{
			index = -1;

			getline(mesh_file, line);
			sscanf(line.c_str(), "(%d ", &index);

			switch(index)
			{
			case FLU_INDEX_DIMENSIONS:
				nd = 0;
				sscanf(line.c_str(), "(%d %d)", &temp, &nd);
				config.DIM = nd;
				break;

			case FLU_INDEX_NODE:
				nnm = 0;
				index_s = 0;
				index_e = 0;
				sscanf(line.c_str(),"(%d (%x %x %x", &temp, &zone, &index_s, &index_e); // GETTING INDEX AND ZONE
				if (zone == 0) // READ GENERAL INFORMATION OF NODES
				{
					config.NNM = index_e - index_s + 1;
				}
				break;

			case FLU_INDEX_CELL:
				ncm = 0;
				index_s = 0;
				index_e = 0;
				sscanf(line.c_str(),"(%d (%x %x %x", &temp, &zone, &index_s, &index_e); // GETTING INDEX AND ZONE
				if (zone == 0) // READ GENERAL INFORMATION OF NODES
				{
					config.NCM = index_e - index_s + 1;
				}
				break;

			case FLU_INDEX_FACE:
				nfm = 0;
				index_s = 0;
				index_e = 0;
				sscanf(line.c_str(),"(%d (%x %x %x", &temp, &zone, &index_s, &index_e); // GETTING INDEX AND ZONE

				if (zone == 0) // READ GENERAL INFORMATION OF NODES
				{
					config.NFM = index_e - index_s + 1;
				}
				else
				{
					maxZone = fmax(maxZone, zone);
				}
				break;
			}
		}

		std::vector<int>	nfmZone(maxZone+1, 0);
		bcZone.resize(maxZone+1);
		for (int i = 0; i <= maxZone; i++)	bcZone[i]	= -1;


		// 5. Second Read
		mesh_file.clear();
		mesh_file.seekg(0, ios::beg);
		int num_zone = 0;

		while (! mesh_file.eof())
		{
			index = -1;

			getline(mesh_file, line);
			sscanf(line.c_str(), "(%d ", &index);

			switch(index)
			{
			case FLU_INDEX_FACE:
				nfm 	= 0;
				index_s = 0;
				index_e = 0;
				sscanf(line.c_str(),"(%d (%x %x %x", &temp, &zone, &index_s, &index_e); // GETTING INDEX AND ZONE

				if (zone != 0)
				{
					sscanf(line.c_str(),"(%d (%x %x %x %d", &temp, &zone_temp, &index_s, &index_e, &bc_type); // GETTING INDEX AND ZONE
					nfm_zone 		= index_e - index_s + 1;
					nfmZone[zone]	= nfm_zone;
					num_zone++;
				}
				break;


			case FLU_INDEX_BC:
				sscanf(line.c_str(),"(%d (%d %s", &index, &zone, zone_type); // GETTING INDEX AND ZONE

				// GENERAL TYPE OF BOUNDARY CONDITIONS
				bool flagFindBCtype = false;

				if (strcmp(zone_type,"interior") == 0)
				{
					bcZone[zone] = GRID::bc_interior;
					flagFindBCtype = true;
				}

				if (strcmp(zone_type,"wall") == 0)
				{
					bcZone[zone] = GRID::bc_wall;
					flagFindBCtype = true;
				}

				if (strcmp(zone_type,"pressure-inlet") == 0)
				{
					bcZone[zone] = GRID::bc_inlet;
					flagFindBCtype = true;
				}

				if (strcmp(zone_type,"pressure-outlet") == 0)
				{
					bcZone[zone] = GRID::bc_outlet;
					flagFindBCtype = true;
				}

				if (strcmp(zone_type,"pressure-far-field") == 0)
				{
					bcZone[zone] = GRID::bc_freestream;
					flagFindBCtype = true;
				}

				if (strcmp(zone_type,"symmetry") == 0)
				{
					bcZone[zone] = GRID::bc_symmetric;
					flagFindBCtype = true;
				}

				if (strcmp(zone_type,"axis") == 0)
				{
					bcZone[zone] = GRID::bc_axis;
					flagFindBCtype = true;
				}

				if (strcmp(zone_type,"anode") == 0)
				{
					bcZone[zone] = GRID::bc_anode;
					flagFindBCtype = true;
				}

				if (strcmp(zone_type,"cathode") == 0)
				{
					bcZone[zone] = GRID::bc_cathode;
					flagFindBCtype = true;
				}

				if (strcmp(zone_type,"dielectric-wall") == 0)
				{
					bcZone[zone] = GRID::bc_dielectricwall;
					flagFindBCtype = true;
				}

				if (flagFindBCtype == false)
				{
					Common::ExceptionGeneral(FromHere(), "Given BC type in the grid is not supported BC type. Please check BC type in the grid girl", "NotSupportedValue:");
				}
				break;
			}
		}


		// Step 3. CHECK BOUNDARY CONDITION
		for (int i = 1; i <= maxZone-1; i++)
		{
			nfm_zone	= nfmZone[i];
			if (bcZone[i] != -1 && bcZone[i] != GRID::bc_interior)
			{
				ngm += nfmZone[i];
			}
		}

		config.NGM = ngm;
	}
	else
	{
		Common::ExceptionGeneral(FromHere(), "Cannot find grid file. Please check your grid file!", "CannotOpenFile:");
	}

	mesh_file.close();
}


void ReadGridInfo(const  std::string& mesh_file_name, OP2A::GRID::Configuration& config, std::vector<int>& bc_zone, int type)
{
	switch (type)
	{
	case FLUENT:
		ReadGridInfoFluent(mesh_file_name, config, bc_zone);
		break;

	default:
		Common::ExceptionGeneral(FromHere(), "IT IS NOT SUPPORTED MESH FILE TYPE. PLEASE CHECK MESH FILE!!!", "NotSupportedOption:");
		break;
	}
}






}
