/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cTecplotZoneV2.hpp
 *
 *  Created on: Jan 8, 2016
 *      Author: minkwan
 */

#ifndef CTECPLOTZONEV2_HPP_
#define CTECPLOTZONEV2_HPP_


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

#include "./COMMON/ErrorCode.hpp"
#include "./COMMON/ExceptionGeneral.hpp"

namespace IO {


enum IO_Tecplot_ZoneType
{
	enum_ORDERED		 =	0,
	enum_FELINESEG		 =	1,
	enum_FETRIANGLE		 =	2,
	enum_FEQUADRILATERAL =	3,
	enum_FEPOLYGON		 =	4,
	enum_FETETRAHEDRON	 =	5,
	enum_FEBRICK		 =	6,
	enum_FEPOLYHEDRAL	 =	7
};

enum IO_Tecplot_FaceNeighborMode
{
	enum_LOCALONETOONE	= 0,
	enum_LOCALONETOMANY	= 1,
	enum_GLOBALONETOONE	= 2,
	enum_GLOBALONETOMANY = 3
};


enum IO_Tecplot_DataType
{
	enum_DOUBLE		= 0,
	enum_SINGLE		= 1,
	enum_LONGINT		= 2,
	enum_SHORTINT	= 3,
	enum_BYTE		= 4,
	enum_BIT			= 5
};

enum IO_Tecplot_DataPacking
{
	enum_POINT	= 0,
	enum_BLOCK	= 1
};

std::string ZontType_str(IO_Tecplot_ZoneType zonetype);
std::string FaceNeighborMode_str(IO_Tecplot_FaceNeighborMode facemode);
std::string DataType_str(IO_Tecplot_DataType datatype);
std::string DataPacking_str(IO_Tecplot_DataPacking datapack);


enum IO_Tecplot_VarLocation
{
	NODAL			= 0,
	CELLCENTERED	= 1
};






/*
 * Class for Tecplot ZoneHeader
 *
 * 	Initially written by:	Minkwan Kim
 * 	Last modified on	:	Oct/29/2015
 * 	Last modified by	:	Minkwan Kim
 */
class c_TecplotZone_v2 {
public:
	c_TecplotZone_v2();
	~c_TecplotZone_v2();


public:
	std::string					title;

	IO_Tecplot_ZoneType			zonetype;		// Type of zone
	bool						flag_zonetype;

	// Grin Basic Info
	unsigned int	I;
	unsigned int	J;
	unsigned int	K;
	unsigned int	NODES;
	unsigned int	ELEMENTS;

	IO_Tecplot_FaceNeighborMode	FACENEIGHBORMODE;
	unsigned int				FACENEIGHBORCONNECTIONS;
	bool						flag_faceneighbormode;

	unsigned int	FACES;
	unsigned int	TOTALNUMFACENODES;
	unsigned int	NUMCONNECTEDBOUNDARYFACES;
	unsigned int	TOTALNUMBOUNDARYCONNECTIONS;

	std::vector<IO_Tecplot_DataType>	DT;
	bool								flag_dt;

	IO_Tecplot_DataPacking				DATAPACKING;

	std::string	VARLOCATION;

	int			VARSHAREZONE;
	bool		flag_VARSHARELIST;

	bool		flag_time;
	int			STRANDID;
	double		SOLUTIONTIME;

private:
	bool m_filled;
	int ND;



	/*
	 * III. Member Functions
	 */
public:
	void settingZoneType (IO_Tecplot_ZoneType zone, int nd);
	void settingZoneType (int nd);
	void settingVarLocation (int numNodal, std::vector<int>& NodalVarList, int numCell, std::vector<int>& CellVarList);


	void writeASCII(const std::string& filename);

};

} /* namespace IO */

#endif /* CTECPLOTZONEV2_HPP_ */
