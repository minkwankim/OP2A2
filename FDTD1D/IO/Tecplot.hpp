/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Tecplot.hpp
 *
 *  Created on: Nov 12, 2015
 *      Author: minkwan
 */

#ifndef TECPLOT_HPP_
#define TECPLOT_HPP_

#include "TecplotHeader.hpp"
#include "TecplotZone.hpp"
#include "TecplotData.hpp"
#include "./GRID/Grid.hpp"

namespace OP2A {
namespace IO {





class Tecplot
{

	/*
	 * I. Constructor and Destructor
	 */
public:
	Tecplot();
	~Tecplot();


	/*
	 * II. Member Variables
	 */
public:
	std::string		outputFilename;
	TecplotHeader	header;
	TecplotZone		zone;

protected:
	bool			m_includeTimeVariation;

	int				m_cpuNumber;
	bool			m_isCPU0;

	bool			m_usingSharedGrid;
	std::string		m_varShareList;

	bool			m_readyWrite;
	bool			m_headerReady;
	bool			m_zoneReady;

	int							m_dim;
	std::vector<std::string> 	m_tec_variables;

	bool			m_useBlockData;
	bool			m_useCellCenterData;

	bool			m_isTimeplot;
	int				m_strandID;
	double			m_solTime;

	//TecplotData		data;

	/*
	 * III. Member Functions
	 */
public:
	// MF-PUB-01 - setCpuNumber
	// @brief set cpu number. Only cpu number 0 will fill the Tecplot header file.
	// @return Void
	void setCpuNumber(const unsigned int P);

	// MF-PUB-02 - shareGrid
	// @brief set flag for grid sharing method.
	// @return Void
	void shareGrid(bool shareGrid);

	// MF-PUB-03 - cellCenteredData
	// @brief set data Type (nodal[0] or cell centered[1]) .
	// @return Void
	void setDatatype(unsigned int i);

	// MF-PUB-04 - WriteTecplotHeader
	// @brief 	Prepare data for Tecplot header
	// @param	tec_title		Title of Output
	// @param	tec_filefype	File type (0:Full / 1:Grid / 2:Solution)
	// @return Void
	void WriteHeader(const std::string& tec_title, int tec_filetype, int dim);
	void setVariables();

	// MF-PUB-05 - WriteTecplotZone
	// @brief 	Prepare data for Tecplot Zone
	// @param	tec_title		Title of Output
	// @param	tec_filefype	File type (0:Full / 1:Grid / 2:Solution)
	// @return Void
	void WriteZone(const GRID::Configuration &config);
	void setTimeplot(int strandID, double solTime);
	void setUsingBlockDataPack();
	void setUsingNodalData();

	// MF-PUB-06 - PrepareFile
	// @brief 	Prepare a file
	// @return Void
	void PrepareFile();
};

} /* namespace IO */
} /* namespace OP2A */

#endif /* TECPLOT_HPP_ */
