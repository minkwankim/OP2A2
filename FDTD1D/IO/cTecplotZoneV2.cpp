/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cTecplotZoneV2.cpp
 *
 *  Created on: Jan 8, 2016
 *      Author: minkwan
 */

#include <IO/cTecplotZoneV2.hpp>

using namespace std;

namespace IO {


std::string ZontType_str(IO_Tecplot_ZoneType zonetype)
{
	switch(zonetype)
	{
	case enum_ORDERED:
		return("ORDERED");
		break;
	case enum_FELINESEG:
		return("FELINESEG");
		break;
	case enum_FETRIANGLE:
		return("FETRIANGLE");
		break;
	case enum_FEQUADRILATERAL:
		return("FEQUADRILATERAL");
		break;
	case enum_FEPOLYGON:
		return("FEPOLYGON");
		break;
	case enum_FETETRAHEDRON:
		return("FETETRAHEDRON");
		break;
	case enum_FEBRICK:
		return("FEBRICK");
		break;
	case enum_FEPOLYHEDRAL:
		return("FEPOLYHEDRAL");
		break;
	}

	return("");
}


std::string FaceNeighborMode_str(IO_Tecplot_FaceNeighborMode facemode)
{
	switch (facemode)
	{
	case enum_LOCALONETOONE:
		return("LOCALONETOONE");
		break;

	case enum_LOCALONETOMANY:
		return("LOCALONETOMANY");
		break;

	case enum_GLOBALONETOONE:
		return("GLOBALONETOONE");
		break;

	case enum_GLOBALONETOMANY:
		return("GLOBALONETOMANY");
		break;
	}

	return("");
}


std::string DataType_str(IO_Tecplot_DataType datatype)
{
	switch (datatype)
	{
	case enum_DOUBLE:
		return ("DOUBLE");
		break;
	case enum_SINGLE:
		return ("SINGLE");
		break;
	case enum_LONGINT:
		return ("LONGINT");
		break;
	case enum_SHORTINT:
		return ("SHORTINT");
		break;
	case enum_BYTE:
		return ("BYTE");
		break;
	case enum_BIT:
		return ("BIT");
		break;
	}

	return ("");
}


std::string DataPacking_str(IO_Tecplot_DataPacking datapack)
{
	switch (datapack)
	{
	case enum_POINT:
		return ("POINT");
		break;
	case enum_BLOCK:
		return ("BLOCK");
		break;
	}

	return ("");
}









c_TecplotZone_v2::c_TecplotZone_v2()
{
	m_filled	= false;

	title	= "";

	zonetype		= enum_ORDERED;
	flag_zonetype	= false;
	ND				= 1;

	I		= 0;
	J 		= 0;
	K		= 0;
	NODES 	= 0;
	ELEMENTS= 0;

	flag_faceneighbormode 	= false;
	FACENEIGHBORMODE		= enum_LOCALONETOONE;
	FACENEIGHBORCONNECTIONS = 0;

	FACES						= 0;
	TOTALNUMFACENODES			= 0;
	NUMCONNECTEDBOUNDARYFACES	= 0;
	TOTALNUMBOUNDARYCONNECTIONS	= 0;

	flag_dt	= false;

	DATAPACKING	= enum_BLOCK;

	flag_VARSHARELIST = false;
	VARSHAREZONE = 0;

	flag_time = false;
	STRANDID = 0;
	SOLUTIONTIME = 0.0;
}

c_TecplotZone_v2::~c_TecplotZone_v2()
{
}



/*
 * III. Member Functions
 */
// MF-PUB-01 - writeASCII
// @brief	Write Tecplot file in ASCII format
void c_TecplotZone_v2::writeASCII(const std::string& filename)
{
	ofstream		tecplot_file;

	// OPEN FILE TO APPEND
	tecplot_file.open(filename.c_str(), std::fstream::app);
	if(!tecplot_file)
	{
		OP2A::Common::ExceptionGeneral (FromHere(), "Could not open file: " + filename + "==> Need to run TecplotHeader first", "FileSystem");
	}


	// STart to write Zone Info
	tecplot_file << "ZONE" << endl;

	//1. Title
	if (title != "")	tecplot_file << "T = \"" << title << "\"" << endl;
	else				tecplot_file << "T = \"OP2A_Result_default \"" << endl;

	//2. Zone type
	if (flag_zonetype == true)	tecplot_file << "ZONETYPE = " << ZontType_str(zonetype) << endl;



	// 3. Element / node information
	if (zonetype == enum_ORDERED)
	{
		switch (ND)
		{
		case 1:
			tecplot_file << "I = " << I;
			break;
		case 2:
			tecplot_file << "I = " << I << ", J = " << J;
			break;
		case 3:
			tecplot_file << "I = " << I << ", J = " << J << ", K = " << K;;
			break;
		}
		tecplot_file << endl;


		if (flag_faceneighbormode == true)
		{
			tecplot_file << "FACENEIGHBORMODE = [" << FaceNeighborMode_str(FACENEIGHBORMODE) << "]" << endl;
			tecplot_file << "FACENEIGHBORCONNECTIONS = " << FACENEIGHBORCONNECTIONS << endl;
		}
	}
	else
	{
		tecplot_file << "NODES = "	<< NODES << endl;
		tecplot_file << "ELEMENTS = " << ELEMENTS << endl;

		if (zonetype == enum_FEPOLYGON || zonetype == enum_FEPOLYHEDRAL)
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
		for (int i = 1; i <= var-1; i++)	tecplot_file << ", " << DataType_str(DT[i]);
		tecplot_file <<")" << endl;
	}


	// 5. Data packing method
	tecplot_file << "DATAPACKING = " << DataPacking_str(DATAPACKING) << endl;


	// 6. Variable Location
	if (ND > 1)	tecplot_file << "VARLOCATION = " << VARLOCATION << endl;


	// 6. Variable shared list
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
void c_TecplotZone_v2::settingZoneType (IO_Tecplot_ZoneType zone, int nd)
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

void c_TecplotZone_v2::settingZoneType (int nd)
{
	ND	= nd;

	switch (nd)
	{
	case 1:
		zonetype		= IO::enum_ORDERED;
		flag_zonetype	= false;
		break;

	case 2:
		zonetype		= IO::enum_FEQUADRILATERAL;
		flag_zonetype	= true;
		break;

	case 3:
		zonetype		= IO::enum_FEBRICK;
		flag_zonetype	= true;
		break;
	}
}




// MF-PUB-03 - settingVarLocation
// @brief	Setting zonetype and dimension
void c_TecplotZone_v2::settingVarLocation (int numNodal, std::vector<int>& NodalVarList, int numCell, std::vector<int>& CellVarList)
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






} /* namespace IO */
