/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * TecplotV2.hpp
 *
 *  Created on: Dec 2, 2015
 *      Author: minkwan
 */

#ifndef TECPLOTV2_HPP_
#define TECPLOTV2_HPP_

#include "TecplotHeader.hpp"
#include "TecplotZone.hpp"
#include "TecplotData.hpp"
#include "Tecplot.hpp"

#include <GRID/GridV2.hpp>
#include <GRID/GridSetupParameter.hpp>


namespace OP2A {
namespace IO {

class TecplotV2 : public Tecplot
{
public:
	TecplotV2();
	~TecplotV2();

	/*
	 * II. Member Variables
	 */
public:
	//TecplotData		data;


private:
	string temp_filename_nodeData;
	string temp_filename_connData;
	string temp_filename_header;


	/*
	 * III. Member Functions
	 */
public:
	// MF-PUB-05 - WriteTecplotZone
	// @brief 	Prepare data for Tecplot Zone
	// @param	tec_title		Title of Output
	// @param	tec_filefype	File type (0:Full / 1:Grid / 2:Solution)
	// @return Void
	void WriteZone(const GRID::c_Grid &grid);
	void WriteNodeData(GRID::c_Grid &grid, const vector<unsigned int>& flagPrintVariable);
	void WriteConnectivity(GRID::c_Grid &grid);
	void WriteFile(const std::string& tec_title, GRID::c_Grid &grid, const vector<unsigned int>& flagPrintVariable);

};

} /* namespace IO */
} /* namespace OP2A */

#endif /* TECPLOTV2_HPP_ */
