/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cTecplotV3.hpp
 *
 *  Created on: Jan 8, 2016
 *      Author: minkwan
 */

#ifndef CTECPLOTV3_HPP_
#define CTECPLOTV3_HPP_


#include "cTecplotHeaderV2.hpp"
#include "cTecplotZoneV2.hpp"
#include "./GRID_V2/Gridv2.hpp"




namespace IO {

class c_Tecplot_v3 {
public:
	c_Tecplot_v3();
	~c_Tecplot_v3();

	/*
		 * II. Member Variables
	 */
public:
	std::string				outputFilename;
	c_TecplotHeader_v2		header;
	c_TecplotZone_v2		zone;

protected:
	bool	m_headerReady;
	bool	m_zoneReady;
	bool	m_readyWrite;
	bool	m_isCPU0;
	bool	m_usingSharedGrid;
	bool	m_useBlockData;
	bool	m_useCellCenterData;
	bool	m_isTimeplot;

	int	m_dim;
	int	m_cpuNumber;
	int	m_strandID;

	double	m_solTime;

	std::vector<std::string> 	m_tec_variables;


private:
	string temp_filename_nodeData;
	string temp_filename_connData;
	string temp_filename_header;



	/*
	 * III. Member Functions
	 */
public:
	// MF-PUB-01 - setCpuNumber
	// @brief set cpu number. Only cpu number 0 will fill the Tecplot header file.
	// @return Void
	void setCpuNumber(const unsigned int P);
	void setCpuNumber();

	// MF-PUB-02 - shareGrid
	// @brief set flag for grid sharing method.
	// @return Void
	void shareGrid(bool shareGrid);

	// MF-PUB-03 - cellCenteredData
	// @brief set data Type (nodal:0 or cell centered:1) .
	// @return Void
	void setDatatype(unsigned int i);

	// MF-PUB-04 - WriteTecplotHeader
	// @brief 	Prepare data for Tecplot header
	// @param	tec_title		Title of Output
	// @param	tec_filefype	File type (0:Full / 1:Grid / 2:Solution)
	// @return Void
	void WriteHeader(const std::string& tec_title, int tec_filetype, int dim);
	void WriteHeader(const std::string& tec_title, int tec_filetype, int dim, const std::vector<string>& variableNames);
	void setVariables(const std::vector<string>& variableNames);



	// MF-PUB-05 - WriteTecplotZone
	// @brief 	Prepare data for Tecplot Zone
	// @param	tec_title		Title of Output
	// @param	tec_filefype	File type (0:Full / 1:Grid / 2:Solution)
	// @return Void
	void WriteZone(const GRID::c_Grid &grid);
	void setTimeplot(int strandID, double solTime);
	void setUsingBlockDataPack(bool flag);
	void setUsingNodalData(bool flag);

	// MF-PUB-06 - WriteNodeData
	// @brief 	Write node data
	void WriteNodeData(GRID::c_Grid &grid, const vector<unsigned int>& flagPrintVariable);

	// MF-PUB-07 - WriteConnectivity
	// @brief 	Write connectivity of cells
	void WriteConnectivity(GRID::c_Grid &grid);

	// MF-PUB-08 - WriteFile
	void WriteFile(const std::string& tec_title, GRID::c_Grid &grid, const vector<unsigned int>& flagPrintVariable);

	// MF-PUB-09 - PrepareFile
	// @brief 	Prepare a file
	// @return Void
	void PrepareFile();
	void PrepareFile(const string& filename);
};

} /* namespace IO */

#endif /* CTECPLOTV3_HPP_ */
