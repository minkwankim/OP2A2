/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cTecplotV3.cpp
 *
 *  Created on: Jan 8, 2016
 *      Author: minkwan
 */
#include <mpi.h>

#include <IO/cTecplotV3.hpp>
#include "./COMMON/FileHandle.hpp"

namespace IO {

c_Tecplot_v3::c_Tecplot_v3()
{
	m_headerReady	= false;
	m_zoneReady		= false;
	m_readyWrite	= false;
	m_isCPU0		= false;
	m_usingSharedGrid	= false;
	m_useBlockData	= false;
	m_useCellCenterData	= false;
	m_isTimeplot	= false;


	m_cpuNumber	= -1;
	m_dim		= 2;
	m_strandID	= 0;

	m_solTime	= 0.0;
}

c_Tecplot_v3::~c_Tecplot_v3() {
	// TODO Auto-generated destructor stub
}




/*
 * III. Member Functions
 */
// MF-PUB-01 - setCpuNumber
// @brief set cpu number. Only cpu number 0 will fill the Tecplot header file.
// @return Void
void c_Tecplot_v3::setCpuNumber(const unsigned int P)
{
	m_cpuNumber	= P;
	if (P == 0)	m_isCPU0 = true;
	else		m_isCPU0 = false;
}

void c_Tecplot_v3::setCpuNumber()
{
	int size, rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	setCpuNumber(rank);
}


// MF-PUB-02 - shareGrid
// @brief set flag for grid sharing method.
// @return Void
void c_Tecplot_v3::shareGrid(bool shareGrid)
{
	m_usingSharedGrid = shareGrid;

	if (shareGrid == true)
	{
		zone.flag_VARSHARELIST = true;
		zone.VARSHAREZONE = 1;
	}
}


// MF-PUB-03 - cellCenteredData
// @brief set data Type (nodal[0] or cell centered[1]) .
// @return Void
void c_Tecplot_v3::setDatatype(unsigned int i)
{
	ostringstream tempStr;

	tempStr	<< "([" << m_dim+1;
	for (int ii = m_dim; ii <= m_tec_variables.size()-1; ii++)
	{
		tempStr	<< "," << ii+1;
	}
	tempStr << "]";


	switch (i)
	{
	case 0:
		tempStr << " = NODAL";
		break;
	case 1:
		tempStr << "= CELLCENTERED";
		break;
	}

	tempStr << ")";
	zone.VARLOCATION = tempStr.str();
}


// MF-PUB-04 - WriteTecplotHeader
// @brief 	Prepare data for Tecplot header
// @param	tec_title		Title of Output
// @param	tec_filefype	File type (0:Full / 1:Grid / 2:Solution)
// @return Void
void c_Tecplot_v3::WriteHeader(const std::string& tec_title, int tec_filetype, int dim)
{
	m_dim = dim;

	header.title 		= tec_title;
	header.setFileType(tec_filetype);
	header.variables	= m_tec_variables;
	m_headerReady = true;
}

void c_Tecplot_v3::WriteHeader(const std::string& tec_title, int tec_filetype, int dim, const std::vector<string>& variableNames)
{
	m_dim = dim;
	setVariables(variableNames);

	WriteHeader(tec_title, tec_filetype, dim);
}

void c_Tecplot_v3::setVariables(const std::vector<string>& variableNames)
{
	m_tec_variables = variableNames;
}



// MF-PUB-05 - WriteTecplotZone
// @brief 	Prepare data for Tecplot Zone
// @param	tec_title		Title of Output
// @param	tec_filefype	File type (0:Full / 1:Grid / 2:Solution)
// @return Void
void c_Tecplot_v3::WriteZone(const GRID::c_Grid &grid)
{
	m_dim	= grid.Info.DIM;

	IO::IO_Tecplot_ZoneType zonetype;
	switch (m_dim)
	{
	case 2:
		zonetype	= IO::enum_FEQUADRILATERAL;
		break;

	case 3:
		zonetype	= IO::enum_FEBRICK;
		break;
	}



	// 1. Set title name of zone
	//		- cup number
	std::ostringstream tempStr;
	tempStr << "CPU number:" << m_cpuNumber;
	zone.title	= tempStr.str();

	// 2. Set Zonetype
	zone.settingZoneType(zonetype, m_dim);


	// 4. Data type (Not activated)
	zone.flag_dt			= false;

	// 5. Data packing method


	// 6. Set Variable location
	if (m_useCellCenterData == true)
	{
		zone.DATAPACKING 		= IO::enum_BLOCK;
		setDatatype(1);
	}
	else
	{
		setDatatype(0);
		if (m_useBlockData)		zone.DATAPACKING 		= IO::enum_BLOCK;
		else					zone.DATAPACKING 		= IO::enum_POINT;
	}


	// 7. Shared variable and connectivity
	if (m_isCPU0 == true)	zone.flag_VARSHARELIST	= false;
	else					zone.flag_VARSHARELIST	= true;

	// 8. Time information
	zone.flag_time			= m_isTimeplot;
	if (m_isTimeplot == true)
	{
		zone.STRANDID 		= m_strandID;
		zone.SOLUTIONTIME	= m_solTime;
	}

	m_zoneReady = true;
}

void c_Tecplot_v3::setTimeplot(int strandID, double solTime)
{
	m_isTimeplot	= true;
	m_strandID		= strandID;
	m_solTime		= solTime;
}

void c_Tecplot_v3::setUsingBlockDataPack(bool flag)
{
	m_useBlockData = flag;
}

void c_Tecplot_v3::setUsingNodalData(bool flag)
{
	if (flag == true)	m_useCellCenterData = false;
	else				m_useCellCenterData = true;
}


// MF-PUB-06 - WriteNodeData
// @brief 	Write node data
void c_Tecplot_v3::WriteNodeData(GRID::c_Grid &grid, const vector<unsigned int>& flagPrintVariable)
{
	ofstream		tecplot_file;
	tecplot_file.open(temp_filename_nodeData.c_str());

	int num_n = 0;
	for (int i_n = 0; i_n <= grid.Info.NNM-1; i_n++)
	{
		for (int i_k = 0; i_k <= grid.Info.DIM-1; i_k++)
		{
			tecplot_file << grid.Data.nodes[i_n].geometry.x[i_k] << " ";
		}

		for (int i_v = 0; i_v <= flagPrintVariable.size()-1; i_v++)
		{
			tecplot_file << grid.Data.nodes[i_n].data[flagPrintVariable[i_v]] << "  ";
		}
		tecplot_file << endl;

		num_n++;
	}

	zone.NODES = num_n;
	tecplot_file.close();
}


// MF-PUB-07 - WriteConnectivity
// @brief 	Write connectivity of cells
void c_Tecplot_v3::WriteConnectivity(GRID::c_Grid &grid)
{
	ofstream		tecplot_file;
	tecplot_file.open(temp_filename_connData.c_str());


	int num_c = 0;
	for (int c = 0; c <= grid.Info.NCM-1; c++)
	{
		for (int n = 0; n <= grid.Data.cells[c].Specialized.N_List.size()-1; n++)
		{
			int pos = grid.Map.n_ID_to_pos[grid.Data.cells[c].Specialized.N_List[n]->geometry.id];
			if (pos >= 0)	tecplot_file << pos+1 <<" ";
			else			OP2A::Common::ExceptionGeneral(FromHere(), "[Tecplot]: Problem in Node List", OP2A::Common::ErrorCode::NotAllocated());
		}

		tecplot_file << endl;
		num_c++;
	}


	zone.ELEMENTS = num_c;
	tecplot_file.close();
}



// MF-PUB-08 - WriteFile
void c_Tecplot_v3::WriteFile(const std::string& tec_title, GRID::c_Grid &grid, const vector<unsigned int>& flagPrintVariable)
{
	std::ostringstream tempStr1;
	tempStr1 << outputFilename << "_nodeData.tmp";
	temp_filename_nodeData = tempStr1.str();

	std::ostringstream tempStr2;
	tempStr2 << outputFilename << "_connData.tmp";
	temp_filename_connData = tempStr2.str();

	std::ostringstream tempStr3;
	tempStr3 << outputFilename << "_header_" << m_cpuNumber << ".tmp";
	temp_filename_header = tempStr3.str();


	m_tec_variables.resize(grid.Info.DIM + flagPrintVariable.size());
	m_tec_variables[0] = "X";
	m_tec_variables[1] = "Y";
	if (grid.Info.DIM == 3) m_tec_variables[2] = "Z";

	for (int i_v = 0; i_v <= flagPrintVariable.size()-1; i_v++)
	{
		m_tec_variables[grid.Info.DIM + i_v] = grid.Map.n_Data_Map.findKey(flagPrintVariable[i_v]);
	}
	setDatatype(0);
	setUsingNodalData(true);
	setUsingBlockDataPack(false);



	WriteNodeData(grid, flagPrintVariable);
	WriteConnectivity(grid);

	WriteHeader(tec_title, 0, grid.Info.DIM);
	WriteZone(grid);
	PrepareFile(temp_filename_header);


	// 1. Set filename
	//		- name + cup number
	std::ostringstream tempStr;
	tempStr << outputFilename << "_" << m_cpuNumber << ".plt";
	OP2A::Common::FileHandle::Xmerge(temp_filename_header, temp_filename_nodeData, temp_filename_connData, tempStr.str());
	//std::remove(temp_filename_header.c_str());
	//std::remove(temp_filename_nodeData.c_str());
	//std::remove(temp_filename_connData.c_str());
}


// MF-PUB-09 - PrepareFile
// @brief 	Prepare a file
// @return Void
void c_Tecplot_v3::PrepareFile()
{
	if (m_cpuNumber == -1)
	{
		OP2A::Common::ExceptionGeneral(FromHere(), "CPU number is not allocated. Need to CPU number using setCpuNumber function.", "NeedPreAction:");
	}

	// 1. Set filename
	//		- name + cup number
	std::ostringstream tempStr;
	tempStr << outputFilename << "_" << m_cpuNumber << ".plt";

	if (m_headerReady == true)
	{
		header.writeASCII(tempStr.str());
	}
	else
	{
		OP2A::Common::ExceptionGeneral(FromHere(), "Header data is not prepared. Need to prepare it, first.", "NeedPreAction:");
	}

	if (m_zoneReady == true)
	{
		zone.writeASCII(tempStr.str());
	}
	else
	{
		OP2A::Common::ExceptionGeneral(FromHere(), "Zone data is not prepared. Need to prepare it, first.", "NeedPreAction:");
	}
}

void c_Tecplot_v3::PrepareFile(const string& filename)
{
	if (m_headerReady == true)
	{
		header.writeASCII(filename.c_str());
	}
	else
	{
		OP2A::Common::ExceptionGeneral(FromHere(), "Header data is not prepared. Need to prepare it, first.", "NeedPreAction:");
	}

	if (m_zoneReady == true)
	{
		zone.writeASCII(filename.c_str());
	}
	else
	{
		OP2A::Common::ExceptionGeneral(FromHere(), "Zone data is not prepared. Need to prepare it, first.", "NeedPreAction:");
	}
}



} /* namespace IO */
