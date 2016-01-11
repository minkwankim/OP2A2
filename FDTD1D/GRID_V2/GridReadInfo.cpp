/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GridReadInfo.cpp
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


void GridReadInfo_Fluent(const string& mesh_file_name, c_Grid& grid, vector<int>& bc_zone)
{
	vector<int>	num_mesh_zone(CONST_MAX_ZONE_READ_MESH, 0);
	bc_zone.resize(CONST_MAX_ZONE_READ_MESH, 0);


	// Step 1: Open file to read
	ifstream mesh_file(mesh_file_name.c_str());
	if(!mesh_file) throw OP2A::Common::ExceptionGeneral (FromHere(), "Could not open file: " + mesh_file_name, OP2A::Common::ErrorCode::FileSystem());



	//////////////////
	// Read file	//
	//////////////////
	int index, temp, zone, bc_type;
	int zone_temp;
	int index_s, index_e;
	int nd, nfm, ncm, nnm, ngm;
	int nfm_zone, num_zone;

	char zone_type[20];
	string line;

	num_zone = 0;
	ngm = 0;

	// Step 2: FIRST READ
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
			grid.Info.DIM = nd;
			break;

		case FLU_INDEX_NODE:
			nnm = 0;
			index_s = 0;
			index_e = 0;
			sscanf(line.c_str(),"(%d (%x %x %x", &temp, &zone, &index_s, &index_e); // GETTING INDEX AND ZONE
			if (zone == 0) // READ GENERAL INFORMATION OF NODES
			{
				grid.Info.NNM = index_e - index_s + 1;
			}
			break;

		case FLU_INDEX_CELL:
			ncm = 0;
			index_s = 0;
			index_e = 0;
			sscanf(line.c_str(),"(%d (%x %x %x", &temp, &zone, &index_s, &index_e); // GETTING INDEX AND ZONE
			if (zone == 0) // READ GENERAL INFORMATION OF NODES
			{
				grid.Info.NCM = index_e - index_s + 1;
			}
			break;

		case FLU_INDEX_FACE:
			nfm = 0;
			index_s = 0;
			index_e = 0;
			sscanf(line.c_str(),"(%d (%x %x %x", &temp, &zone, &index_s, &index_e); // GETTING INDEX AND ZONE

			if (zone == 0) // READ GENERAL INFORMATION OF NODES
			{
				grid.Info.NFM = index_e - index_s + 1;
			}
			else
			{
				sscanf(line.c_str(),"(%d (%x %x %x %d", &temp, &zone_temp, &index_s, &index_e, &bc_type); // GETTING INDEX AND ZONE
				nfm_zone 			= index_e - index_s + 1;
				num_mesh_zone[zone] = nfm_zone;
				num_zone++;
			}
			break;

		case FLU_INDEX_BC:
			sscanf(line.c_str(),"(%d (%d %s", &index, &zone, zone_type); // GETTING INDEX AND ZONE

			if (zone > CONST_MAX_ZONE_READ_MESH)
			{
				OP2A::Common::ExceptionGeneral (FromHere(), "PROBLEM READING MESH FILE - TOO MANY ZONES!! PLEASE ADJUST MAXIMUM LIMIT OF ZONES", OP2A::Common::ErrorCode::ExceedLimit());
			}

			// GENERAL TYPE OF BOUNDARY CONDITIONS
			if (strcmp(zone_type,"interior") == 0) 				bc_zone[zone] = interior;
			if (strcmp(zone_type,"wall") == 0) 					bc_zone[zone] = wall;
			if (strcmp(zone_type,"pressure-inlet") == 0)		bc_zone[zone] = inlet;
			if (strcmp(zone_type,"pressure-outlet") == 0)		bc_zone[zone] = outlet;
			if (strcmp(zone_type,"pressure-far-field") == 0)	bc_zone[zone] = freestream;
			if (strcmp(zone_type,"symmetry") == 0)				bc_zone[zone] = symmetric;
			if (strcmp(zone_type,"axis") == 0)					bc_zone[zone] = axis;
			if (strcmp(zone_type,"anode") == 0) 				bc_zone[zone] = anode;
			if (strcmp(zone_type,"cathode") == 0) 				bc_zone[zone] = cathode;
			if (strcmp(zone_type,"dielectric-wall") == 0) 		bc_zone[zone] = dielectricwall;
			break;
		}
	}


	// Step 3. CHECK BOUNDARY CONDITION
	for (int i = 0; i <= CONST_MAX_ZONE_READ_MESH-1; i++)
	{
		nfm_zone		= num_mesh_zone[i];
		if (bc_zone[i] != interior)
		{
			ngm += nfm_zone;
		}
	}
	grid.Info.NGM = ngm;

	mesh_file.close();
}



}
