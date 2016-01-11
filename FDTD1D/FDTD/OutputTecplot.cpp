/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * OutputTecplot.cpp
 *
 *  Created on: Nov 11, 2015
 *      Author: minkwan
 */


#include "Output.hpp"

namespace OP2A{
namespace FDTD{


/*
 * III. Member Functions
 */
// MF-PUB-01 - WriteTecplotHeader
// @brief 	Prepare data for Tecplot header
// @param	tec_title		Title of Output
// @param	tec_filefype	File type (0:Full / 1:Grid / 2:Solution)
// @return Void
/*
void OutputTecplot::setVariables()
{
	m_tec_variables.clear();


	switch (m_dim)
	{
	case 1:
		m_tec_variables.push_back("X");

		m_tec_variables.push_back(E);
		m_tec_variables.push_back(H);
		break;

	case 2:
		m_tec_variables.push_back("X");
		m_tec_variables.push_back("Y");

		m_tec_variables.push_back(E + "_x");
		m_tec_variables.push_back(E + "_y");

		m_tec_variables.push_back(H + "_x");
		m_tec_variables.push_back(H + "_y");
		break;

	case 3:
		m_tec_variables.push_back("X");
		m_tec_variables.push_back("Y");
		m_tec_variables.push_back("Z");

		m_tec_variables.push_back(E + "_x");
		m_tec_variables.push_back(E + "_y");
		m_tec_variables.push_back(E + "_z");

		m_tec_variables.push_back(H + "_x");
		m_tec_variables.push_back(H + "_y");
		m_tec_variables.push_back(H + "_z");
		break;
	}
};




// MF-PUB-02 - WriteTecplotHeader
// @brief 	Prepare data for Tecplot header
void OutputTecplot::WriteHeader(const std::string& tec_title, int tec_filetype, int dim)
{
	m_dim = dim;
	setVariables();

	header.title 		= tec_title;
	header.filetype 	= tec_filetype;
	header.variables	= m_tec_variables;

	header.startVar 	= m_dim + 1;
	header.endVar		= m_tec_variables.size();

	m_headerReady = true;
}

// MF-PUB-03 - WriteTecplot
void OutputTecplot::WriteTecplot(const std::string& tec_title, Grid<GRID::Node, GRID::Face, GRID::Cell, GRID::Cell>& grid, int CPUnumber, bool isCellcenter, const std::string& filename)
{
	outputFilename = filename;
	setCpuNumber(CPUnumber);

	m_useCellCenterData =  isCellcenter;

	WriteHeader(tec_title, 0, grid.config.DIM);
	WriteZone(grid.config);
	PrepareFile();

	std::ostringstream tempStr;
	tempStr << outputFilename << "_" << m_cpuNumber << ".plt";

	// OPEN FILE TO APPEND
	ofstream		tecplot_file;
	tecplot_file.open(tempStr.str().c_str(), std::fstream::app);

	if(!tecplot_file)
	{
		throw Common::ExceptionGeneral (FromHere(), "Could not open file: " + filename + "==> Need to run TecplotHeader first", "FileSystem");
	}





	// Data for connectivity
	std::vector< std::vector <int> >	connectivityData(grid.config.NCM+1);

	for (int i = 1; i <= grid.config.NCM; i++)
	{
		int c = grid.cells[i].geo.ID;

		if (c > grid.config.NCM)	Common::ExceptionGeneral(FromHere(), "Problem in the given Cell ID. It exceeds the NCM.", "ExceedRange:");
		connectivityData[c].resize(grid.cells[i].conn.numNodes);

		for (int ii = 0; ii <= grid.cells[i].conn.numNodes-1; ii++)
		{
			int cc = grid.cells[i].conn.listNodes[ii]->geo.ID;

			connectivityData[c][ii] = cc;
		}
	}


	std::vector< std::vector <double> >		nodeData(grid.config.NNM+1, vector<double>(grid.config.DIM));
	for (int i = 1; i <= grid.config.NNM; i++)
	{
		int n = grid.nodes[i].geo.ID;

		if (n > grid.config.NNM)	Common::ExceptionGeneral(FromHere(), "Problem in the given Node ID. It exceeds the NNM.", "ExceedRange:");

		for (int k = 0; k <= grid.config.DIM-1; k++)
		{
			nodeData[n][k]	= grid.nodes[i].geo.x[k];
		}
	}


	if (isCellcenter == true)
	{
		std::vector< std::vector <double> >		resultData(grid.config.NCM+1, vector<double>(header.endVar - grid.config.DIM));


		for (int i = 1; i <= grid.config.NCM; i++)
		{
			int c = grid.cells[i].geo.ID;

			int var = 0;
			int dataIndex;

			// Electric Field
			dataIndex = grid.cells[i].data.dataMapVector.find(E);
			for (int k = 1; k <= grid.config.DIM; k++)
			{
				resultData[c][var] = grid.cells[i].data.dataVector[dataIndex](k);
				var++;
			}

			// Magnetic field
			dataIndex = grid.cells[i].data.dataMapVector.find(H);
			for (int k = 1; k <= grid.config.DIM; k++)
			{
				resultData[c][var] = grid.cells[i].data.dataVector[dataIndex](k);
				var++;
			}
		}

		for (int k = 0; k <= grid.config.DIM-1; k++)
		{
			for (int n = 1; n <= grid.config.NNM; n++)
			{
				tecplot_file << nodeData[n][k] << endl;
			}
		}

		for (int k = 0; k <= resultData[1].size()-1; k++)
		{
			for (int c = 1; c <= grid.config.NCM; c++)
			{
				tecplot_file << resultData[c][k] << endl;
			}
		}
	}
	else
	{
		std::vector< std::vector <double> >		resultData(grid.config.NNM+1, vector<double>(header.endVar - grid.config.DIM));

		for (int i = 1; i <= grid.config.NNM; i++)
		{
			int n = grid.nodes[i].geo.ID;

			int var = 0;
			int dataIndex;

			// Electric Field
			dataIndex = grid.nodes[i].data.dataMapVector.find(E);
			for (int k = 1; k <= grid.config.DIM; k++)
			{
				resultData[n][var] = grid.nodes[i].data.dataVector[dataIndex](k);
				var++;
			}

			// Magnetic field
			dataIndex = grid.nodes[i].data.dataMapVector.find(H);
			for (int k = 1; k <= grid.config.DIM; k++)
			{
				resultData[n][var] = grid.nodes[i].data.dataVector[dataIndex](k);
				var++;
			}
		}

		if (m_useBlockData == true)
		{
			for (int k = 0; k <= grid.config.DIM-1; k++)
			{
				for (int n = 1; n <= grid.config.NNM; n++)
				{
					tecplot_file << nodeData[n][k] << endl;
				}
			}

			for (int k = 0; k <= resultData[1].size()-1; k++)
			{
				for (int n = 1; n <= grid.config.NNM; n++)
				{
					tecplot_file << resultData[n][k] << endl;
				}
			}
		}
		else
		{
			for (int n = 1; n <= grid.config.NNM; n++)
			{
				for (int k = 0; k <= grid.config.DIM-1; k++)
				{
					tecplot_file << nodeData[n][k] << " ";
				}

				for (int k = 0; k <= resultData[1].size()-1; k++)
				{
					tecplot_file << resultData[n][k] << " ";
				}

				tecplot_file << endl;
			}
		}
	}

	if (grid.config.DIM > 1)
	{
		for (int c = 1; c <= grid.config.NCM; c++)
		{
			for (int n = 0; n <= connectivityData[c].size()-1; n++)
			{
				tecplot_file << connectivityData[c][n] << " ";
			}
			tecplot_file << endl;
		}
	}
}

*/

}
}
