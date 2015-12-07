/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Tecplot.cpp
 *
 *  Created on: Nov 12, 2015
 *      Author: minkwan
 */

#include <IO/Tecplot.hpp>

namespace OP2A {
namespace IO {

Tecplot::Tecplot()
:m_includeTimeVariation(false), m_cpuNumber(-1), m_isCPU0(false), m_usingSharedGrid(false),
 m_readyWrite(false), m_headerReady(false), m_zoneReady(false),
 m_dim(0),
 m_useBlockData(false), m_useCellCenterData(true), m_isTimeplot(false),
 m_strandID(0), m_solTime(0.0)
{


}

Tecplot::~Tecplot()
{
	// TODO Auto-generated destructor stub
}




/*
 * III. Member Functions
 */
// MF-PUB-01 - setCpuNumber
// @brief set cpu number. Only cpu number 0 will fill the Tecplot header file.
// @return Void
void Tecplot::setCpuNumber(const unsigned int P)
{
	m_cpuNumber	= P;
	if (P == 0)	m_isCPU0 = true;
	else		m_isCPU0 = false;
}


// MF-PUB-02 - shareGrid
// @brief set flag for grid sharing method.
// @return Void
void Tecplot::shareGrid(bool shareGrid)
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
void Tecplot::setDatatype(unsigned int i)
{
	std::ostringstream tempStr;

	tempStr	<< "([" << header.startVar;
	for (int i = header.startVar+1; i <= header.endVar; i++)
	{
		tempStr	<< "," << i;
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
void Tecplot::WriteHeader(const std::string& tec_title, int tec_filetype, int dim)
{
	m_dim = dim;

	header.title 		= tec_title;
	header.filetype 	= tec_filetype;
	header.variables	= m_tec_variables;

	header.startVar 	= m_dim + 1;
	header.endVar		= m_tec_variables.size();

	m_headerReady = true;
}

void Tecplot::WriteHeader(const std::string& tec_title, int tec_filetype, int dim, const std::vector<string>& variableNames)
{
	m_dim = dim;
	setVariables(variableNames);

	header.title 		= tec_title;
	header.filetype 	= tec_filetype;
	header.variables	= m_tec_variables;

	header.startVar 	= m_dim + 1;
	header.endVar		= m_tec_variables.size();

	m_headerReady = true;
}


void Tecplot::setVariables(const std::vector<string>& variableNames)
{
	m_tec_variables = variableNames;
}


// MF-PUB-05 - WriteTecplotZone
// @brief 	Prepare data for Tecplot Zone
// @param	tec_title		Title of Output
// @param	tec_filefype	File type (0:Full / 1:Grid / 2:Solution)
// @return Void
void Tecplot::WriteZone(const GRID::Configuration &config)
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

	// 3. Set Node/Element information
	if (m_dim == 1)
	{
		zone.I	= config.NNM;
		m_useCellCenterData = false;
	}
	zone.NODES					= config.NNM;
	zone.ELEMENTS				= config.NCM;

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

void Tecplot::setTimeplot(int strandID, double solTime)
{
	m_isTimeplot	= true;
	m_strandID		= strandID;
	m_solTime		= solTime;
}

void Tecplot::setUsingBlockDataPack(bool flag)
{
	m_useBlockData = flag;
}

void Tecplot::setUsingNodalData(bool flag)
{
	if (flag == true)	m_useCellCenterData = false;
	else				m_useCellCenterData = true;
}


// MF-PUB-06 - PrepareFile
// @brief 	Prepare a file
// @return Void
void Tecplot::PrepareFile()
{
	if (m_cpuNumber == -1)
	{
		Common::ExceptionGeneral(FromHere(), "CPU number is not allocated. Need to CPU number using setCpuNumber function.", "NeedPreAction:");
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
		Common::ExceptionGeneral(FromHere(), "Header data is not prepared. Need to prepare it, first.", "NeedPreAction:");
	}

	if (m_zoneReady == true)
	{
		zone.writeASCII(tempStr.str());
	}
	else
	{
		Common::ExceptionGeneral(FromHere(), "Zone data is not prepared. Need to prepare it, first.", "NeedPreAction:");
	}
}

void Tecplot::PrepareFile(const string& filename)
{
	if (m_headerReady == true)
	{
		header.writeASCII(filename.c_str());
	}
	else
	{
		Common::ExceptionGeneral(FromHere(), "Header data is not prepared. Need to prepare it, first.", "NeedPreAction:");
	}

	if (m_zoneReady == true)
	{
		zone.writeASCII(filename.c_str());
	}
	else
	{
		Common::ExceptionGeneral(FromHere(), "Zone data is not prepared. Need to prepare it, first.", "NeedPreAction:");
	}
}



} /* namespace IO */
} /* namespace OP2A */
