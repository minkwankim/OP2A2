/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * TecplotZone.cpp
 *
 *  Created on: Oct 30, 2015
 *      Author: minkwan
 */

#include "./COMMON/CodeLocation.hpp"
#include "./COMMON/ExceptionGeneral.hpp"
#include "TecplotZone.hpp"
#include "TECIO.h"

namespace OP2A{
namespace IO{


using namespace std;


std::string ZontType_str(IO_Tecplot_ZoneType zonetype)
{
	switch(zonetype)
	{
	case ORDERED:
		return("ORDERED");
		break;
	case FELINESEG:
		return("FELINESEG");
		break;
	case FETRIANGLE:
		return("FETRIANGLE");
		break;
	case FEQUADRILATERAL:
		return("FEQUADRILATERAL");
		break;
	case FEPOLYGON:
		return("FEPOLYGON");
		break;
	case FETETRAHEDRON:
		return("FETETRAHEDRON");
		break;
	case FEBRICK:
		return("FEBRICK");
		break;
	case FEPOLYHEDRAL:
		return("FEPOLYHEDRAL");
		break;
	}

	return("");
}


std::string FaceNeighborMode_str(IO_Tecplot_FaceNeighborMode facemode)
{
	switch (facemode)
	{
	case LOCALONETOONE:
		return("LOCALONETOONE");
		break;

	case LOCALONETOMANY:
		return("LOCALONETOMANY");
		break;

	case GLOBALONETOONE:
		return("GLOBALONETOONE");
		break;

	case GLOBALONETOMANY:
		return("GLOBALONETOMANY");
		break;
	}

	return("");
}


std::string DataType_str(IO_Tecplot_DataType datatype)
{
	switch (datatype)
	{
	case DOUBLE:
		return ("DOUBLE");
		break;
	case SINGLE:
		return ("SINGLE");
		break;
	case LONGINT:
		return ("LONGINT");
		break;
	case SHORTINT:
		return ("SHORTINT");
		break;
	case BYTE:
		return ("BYTE");
		break;
	case BIT:
		return ("BIT");
		break;
	}

	return ("");
}


std::string DataPacking_str(IO_Tecplot_DataPacking datapack)
{
	switch (datapack)
	{
	case POINT:
		return ("POINT");
		break;
	case BLOCK:
		return ("BLOCK");
		break;
	}

	return ("");
}

/*
 * III. Member Functions
 */
// MF-PUB-01 - writeASCII
// @brief	Write Tecplot file in ASCII format
void TecplotZone::writeASCII(const std::string& filename)
{
	ofstream		tecplot_file;

	// OPEN FILE TO APPEND
	tecplot_file.open(filename.c_str(), std::fstream::app);

	if(!tecplot_file)
	{
		throw Common::ExceptionGeneral (FromHere(), "Could not open file: " + filename + "==> Need to run TecplotHeader first", "FileSystem");
	}

	tecplot_file << "ZONE" << endl;

	//1. Title
	if (title != "")
	{
		tecplot_file << "T = \"" << title << "\"" << endl;
	}

	//2. Zone type
	if (flag_zonetype == true)
	{
		tecplot_file << "ZONETYPE = " << ZontType_str(zonetype) << endl;
	}


	// 3. Element / node information
	if (zonetype == ORDERED)
	{
		tecplot_file << "I = " << I;
		if (ND == 2) tecplot_file << ", J = " << J;
		if (ND == 3) tecplot_file << ", J = " << J << ", K = " << K;
		tecplot_file << endl;

		if (flag_faceneighbormode == true)
		{
			tecplot_file << "FACENEIGHBORMODE = [" << FaceNeighborMode_str(FACENEIGHBORMODE) << "]" << endl;
			tecplot_file << "FACENEIGHBORCONNECTIONS = " << FACENEIGHBORCONNECTIONS << endl;
		}
	}
	else
	{
		tecplot_file << "NODES = " << NODES << endl;
		tecplot_file << "ELEMENTS = " << ELEMENTS << endl;

		if (zonetype == FEPOLYGON || zonetype == FEPOLYHEDRAL)
		{
			tecplot_file << "FACES = " << FACES << endl;
			tecplot_file << "TOTALNUMFACENODES = " << TOTALNUMFACENODES << endl;
			tecplot_file << "NUMCONNECTEDBOUNDARYFACES = " << NUMCONNECTEDBOUNDARYFACES << endl;
			tecplot_file << "TOTALNUMBOUNDARYCONNECTIONS = " << TOTALNUMBOUNDARYCONNECTIONS << endl;
		}
		else
		{
			if (flag_faceneighbormode == true)
			{
				tecplot_file << "FACENEIGHBORMODE = [" << FaceNeighborMode_str(FACENEIGHBORMODE) << "]" << endl;
				tecplot_file << "FACENEIGHBORCONNECTIONS = " << FACENEIGHBORCONNECTIONS << endl;

			}
		}
	}


	// 4. Variable data type
	if (flag_dt == true)
	{
		int var = DT.size();

		tecplot_file << "DT = (" << DataType_str(DT[0]);
		for (int i = 1; i <= var-1; i++)
		{
			tecplot_file << ", " << DataType_str(DT[i]);
		}
		tecplot_file <<")" << endl;
	}


	// 5. Data packing method
	tecplot_file << "DATAPACKING = " << DataPacking_str(DATAPACKING) << endl;


	// 6. Variable Location
	if (ND > 1)	tecplot_file << "VARLOCATION = " << VARLOCATION << endl;



	if (flag_VARSHARELIST == true)
	{
		tecplot_file << "VARSHARELIST = ([1";
		if (ND == 2)	tecplot_file << ", 2";
		if (ND == 3)	tecplot_file << ", 2, 3";
		tecplot_file << "] = " << VARSHAREZONE << ")" << endl;

		if (ND > 1)	tecplot_file << "CONNECTIVITYSHAREZONE = " << VARSHAREZONE << endl;
	}


	if (flag_time == true)
	{
		tecplot_file << "STRANDID = " << STRANDID << endl;
		tecplot_file << "SOLUTIONTIME = " << SOLUTIONTIME << endl;
	}
}



// MF-PUB-02 - settingZoneType
// @brief	Setting zonetype and dimension
void TecplotZone::settingZoneType (IO_Tecplot_ZoneType zone, int nd)
{
	if (nd > 1)
	{
		zonetype		= zone;
		ND				= nd;
		flag_zonetype	= true;
	}
	else
	{
		ND				= nd;
		flag_zonetype	= false;
	}
}

void TecplotZone::settingZoneType (int nd)
{
	ND	= nd;

	switch (nd)
	{
	case 1:
		zonetype		= IO::ORDERED;
		flag_zonetype	= false;
		break;

	case 2:
		zonetype		= IO::FEQUADRILATERAL;
		flag_zonetype	= true;
		break;

	case 3:
		zonetype		= IO::FEBRICK;
		flag_zonetype	= true;
		break;
	}
}


// MF-PUB-03 - settingVarLocation
// @brief	Setting zonetype and dimension
void TecplotZone::settingVarLocation (int numNodal, std::vector<int>& NodalVarList, int numCell, std::vector<int>& CellVarList)
{
	std::ostringstream varLocation;

	varLocation << "(";
	if (numNodal > 0)
	{
		varLocation << "[" << NodalVarList[0];
		for (int i = 1; i <= numNodal-1; i++)	varLocation << ", " << NodalVarList[i];
		varLocation << "]=NODAL ";
	}

	if (numCell > 0)
	{
		if (numNodal > 0)	varLocation <<", [" << CellVarList[0];
		else				varLocation <<"[" << CellVarList[0];

		for (int i = 1; i <= numCell-1; i++)	varLocation << ", " << CellVarList[i];
		varLocation << "]=CELLCENTERED";
	}

	varLocation << ")" << endl;

	VARLOCATION = varLocation.str();
}




}
}


