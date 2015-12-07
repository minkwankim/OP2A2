/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * TecplotV2.cpp
 *
 *  Created on: Dec 2, 2015
 *      Author: minkwan
 */


#include <COMMON/FileHandle.hpp>
#include <IO/TecplotV2.hpp>

namespace OP2A {
namespace IO {

TecplotV2::TecplotV2()
{
	// TODO Auto-generated constructor stub
}

TecplotV2::~TecplotV2()
{
	// TODO Auto-generated destructor stub
}




void TecplotV2::WriteZone(const GRID::c_Grid &grid)
{
	IO::IO_Tecplot_ZoneType zonetype;

	switch (m_dim)
	{
	case 2:
		zonetype	= IO::FEQUADRILATERAL;
		break;

	case 3:
		zonetype	= IO::FEBRICK;
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
		zone.DATAPACKING 		= IO::BLOCK;
		setDatatype(1);
	}
	else
	{
		setDatatype(0);
		if (m_useBlockData)		zone.DATAPACKING 		= IO::BLOCK;
		else					zone.DATAPACKING 		= IO::POINT;
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



void TecplotV2::WriteNodeData(GRID::c_Grid &grid, const vector<unsigned int>& flagPrintVariable)
{
	ofstream		tecplot_file;
	tecplot_file.open(temp_filename_nodeData.c_str());

	int num_n = 0;
	for (int i_n = 1; i_n <= grid.NNM; i_n++)
	{
		//unsigned int i = grid.whereisNode[i_n];

		for (int i_k = 0; i_k <= grid.DIM-1; i_k++)
		{
			//tecplot_file << grid.Node_Data[i].x[i_k] << " ";
		}

		for (int i_v = 0; i_v <= flagPrintVariable.size()-1; i_v++)
		{
			//tecplot_file << grid.Node_Data[i].data[flagPrintVariable[i_v]] << "  ";
		}
		tecplot_file << endl;

		num_n++;
	}

	zone.NODES = num_n;
	tecplot_file.close();
}

void TecplotV2::WriteConnectivity(GRID::c_Grid &grid)
{
	ofstream		tecplot_file;
	tecplot_file.open(temp_filename_connData.c_str());


	int num_c = 0;
	for (int i_c = 0; i_c <= grid.NCM-1; i_c++)
	{
		/*
		if (grid.Cell_Data[i_c].isInclude() == true)
		{
			for (int i_n = 0; i_n <= grid.Cell_Data[i_c].N_List.size()-1; i_n++)
			{
				tecplot_file << grid.Cell_Data[i_c].N_List[i_n]->ID <<" ";
			}
			tecplot_file << endl;

			num_c++;
		}
		*/
	}

	zone.ELEMENTS = num_c;
	tecplot_file.close();
}



void TecplotV2::WriteFile(const std::string& tec_title, GRID::c_Grid &grid, const vector<unsigned int>& flagPrintVariable)
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


	setDatatype(0);
	setUsingNodalData(true);
	setUsingBlockDataPack(false);

	m_tec_variables.resize(grid.DIM + flagPrintVariable.size());
	m_tec_variables[0] = "X";
	m_tec_variables[1] = "Y";
	if (grid.DIM == 3) m_tec_variables[2] = "Z";

	for (int i_v = 0; i_v <= flagPrintVariable.size()-1; i_v++)
	{
		m_tec_variables[grid.DIM + i_v] = grid.Node_Data_Map.findKey(flagPrintVariable[i_v]);
	}


	WriteNodeData(grid, flagPrintVariable);
	WriteConnectivity(grid);

	WriteHeader(tec_title, 0, grid.DIM);
	WriteZone(grid);
	PrepareFile(temp_filename_header);


	// 1. Set filename
	//		- name + cup number
	std::ostringstream tempStr;
	tempStr << outputFilename << "_" << m_cpuNumber << ".plt";
	Common::FileHandle::Xmerge(temp_filename_header, temp_filename_nodeData, temp_filename_connData, tempStr.str());
	//std::remove(temp_filename_header.c_str());
	//std::remove(temp_filename_nodeData.c_str());
	//std::remove(temp_filename_connData.c_str());
}



} /* namespace IO */
} /* namespace OP2A */
