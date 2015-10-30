/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * TecplotZone.hpp
 *
 *  Created on: Oct 30, 2015
 *      Author: minkwan
 */

#ifndef TECPLOTZONE_HPP_
#define TECPLOTZONE_HPP_



#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

#include "./COMMON/Common.hpp"
#include "./COMMON/Array1D.hpp"


namespace OP2A{
namespace IO{


enum IO_Tecplot_ZoneType
{
	ORDERED			=	0,
	FELINESEG		=	1,
	FETRIANGLE		=	2,
	FEQUADRILATERAL	=	3,
	FEPOLYGON		=	4,
	FETETRAHEDRON	=	5,
	FEBRICK			=	6,
	FEPOLYHEDRAL	=	7
};

std::string ZontType_str(IO_Tecplot_ZoneType zonetype);



enum IO_Tecplot_FaceNeighborMode
{
	LOCALONETOONE	= 0,
	LOCALONETOMANY	= 1,
	GLOBALONETOONE	= 2,
	GLOBALONETOMANY = 3
};

std::string FaceNeighborMode_str(IO_Tecplot_FaceNeighborMode facemode);



enum IO_Tecplot_DataType
{
	DOUBLE		= 0,
	SINGLE		= 1,
	LONGINT		= 2,
	SHORTINT	= 3,
	BYTE		= 4,
	BIT			= 5
};

std::string DataType_str(IO_Tecplot_DataType datatype);


enum IO_Tecplot_DataPacking
{
	POINT	= 0,
	BLOCK	= 1
};
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
class TecplotZone
{
	/*
	 * I. Constructor and Destructor
	 */
public:
	TecplotZone()
	//	:I(0), J(0), K(0), NODES(0), ELEMENTS(0), FACES(0), TOTALNUMFACENODES(0), NUMCONNECTEDBOUNDARYFACES(0), TOTALNUMBOUNDARYCONNECTIONS(0)
	{
		title = "";

		zonetype		= ORDERED;
		flag_zonetype	= false;

		I		= 0;
		J 		= 0;
		K		= 0;
		NODES 	= 0;
		ELEMENTS= 0;

		FACES						= 0;
		TOTALNUMFACENODES			= 0;
		NUMCONNECTEDBOUNDARYFACES	= 0;
		TOTALNUMBOUNDARYCONNECTIONS	= 0;

		FACENEIGHBORMODE	= LOCALONETOONE;
		FACENEIGHBORCONNECTIONS = 0;
		flag_faceneighbormode = false;

		flag_dt	= false;

		DATAPACKING	= BLOCK;

		flag_VARSHARELIST = false;
		VARSHAREZONE = 0;

		flag_time = false;
		STRANDID = 0;
		SOLUTIONTIME = 0.0;


		m_filled	= false;
		ND			= 0;
	};
	~TecplotZone()	{	};


	/*
	 * II. Member Variables
	 */
public:
	std::string					title;

	IO_Tecplot_ZoneType			zonetype;
	bool						flag_zonetype;

	unsigned int	I;
	unsigned int	J;
	unsigned int	K;

	unsigned int	NODES;
	unsigned int	ELEMENTS;

	unsigned int	FACES;
	unsigned int	TOTALNUMFACENODES;
	unsigned int	NUMCONNECTEDBOUNDARYFACES;
	unsigned int	TOTALNUMBOUNDARYCONNECTIONS;


	IO_Tecplot_FaceNeighborMode	FACENEIGHBORMODE;
	unsigned int				FACENEIGHBORCONNECTIONS;
	bool						flag_faceneighbormode;

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
	void writeASCII(const std::string& filename);
	void writeBinary(const std::string& filename);

	void settingZoneType (IO_Tecplot_ZoneType zone, int nd);
	void settingZoneType (int nd);
	void settingVarLocation (int numNodal, std::vector<int>& NodalVarList, int numCell, std::vector<int>& CellVarList);

};




}
}


#endif /* TECPLOTZONE_HPP_ */
