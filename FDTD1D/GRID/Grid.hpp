/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Grid.hpp
 *
 *  Created on: Nov 5, 2015
 *      Author: minkwan
 */

#ifndef GRID_HPP_
#define GRID_HPP_

#include <typeinfo>
#include "./GRID/GridTypeDefinitions.hpp"
#include "./DATA/DataSamples.hpp"

#define	OP2A_GRID_AXISSYMMETRIC_ADD	1.0e-9
#define	OP2A_GRID_MATH_ZERO			1.0e-20



namespace OP2A{


template <class NODE, class FACE, class CELL, class GHOST>
class Grid
{
	/*
	 * I. Member Variables
	 */
public:
	OP2A::GRID::Configuration	config;

	std::vector<NODE>		nodes;
	std::vector<FACE>		faces;
	std::vector<CELL>		cells;
	std::vector<GHOST>		ghosts;

	std::vector<int>		whereisNode;
	std::vector<int>		whereisFace;
	std::vector<int>		whereisCell;

private:
	std::vector<int>	m_bc_zone;
	bool				m_isAllocated;
	bool				m_isInit;
	bool				m_isInitNode;
	bool				m_isInitFace;
	bool				m_isInitCell;
	bool				m_isInitGhost;



	/*
	 * II. Constructor and Destructor
	 */
public:
	Grid()
	:m_isAllocated(false),
	 m_isInit(false), m_isInitNode(false), m_isInitFace(false), m_isInitCell(false), m_isInitGhost(false)
	{

	}

	~Grid()
	{
		if (nodes.size() > 0)	nodes.clear();
		if (faces.size() > 0)	faces.clear();
		if (cells.size() > 0)	cells.clear();
		if (ghosts.size() > 0)	ghosts.clear();

		if (m_bc_zone.size() > 0)	m_bc_zone.clear();
	}


	/*
	 * III. Member Functions
	 */
public:
	// MF-PUB-01 - allocateGrid
	// @param newSize new size of vector
	// @return Void
	void allocateGrid()
	{
		mk_assert(config.isConfigured() == true);

		if (m_isAllocated == false)
		{
			nodes.resize(config.NNM+1);
			faces.resize(config.NFM+1);
			cells.resize(config.NCM+1);
			ghosts.resize(config.NGM+1);

			whereisNode.resize(config.NNM+1);
			whereisFace.resize(config.NFM+1);
			whereisCell.resize(config.NCM+1);


			m_isAllocated = true;
		}

		if (m_isAllocated != true)
		{
			OP2A::Common::ExceptionGeneral(FromHere(), "Memory for Grid class is not allocated. Please check the system memory:",  "DataAllocation:");
		}
	}


	// MF-PUB-02 - resizeNode
	// @param newSize new size of vector
	// @return Void
	void resizeNode(const int nnm)
	{
		nodes.resize(nnm+1);
		config.NNM = nnm;
	}


	// MF-PUB-03 - resizeFace
	// @param newSize new size of vector
	// @return Void
	void resizeFace(const int nfm)
	{
		faces.resize(nfm+1);
		config.NFM = nfm;
	}


	// MF-PUB-04 - resizeCell
	// @param newSize new size of vector
	// @return Void
	void resizeCell(const int ncm)
	{
		cells.resize(ncm+1);
		config.NCM = ncm;
	}


	// MF-PUB-05 - resizeGhost
	// @param newSize new size of vector
	// @return Void
	void resizeGhost(const int ngm)
	{
		ghosts.resize(ngm+1);
		config.NGM = ngm;
	}


	// MF-PUB-06 - initialize
	void initializeNode(const NODE& iNode)
	{
		mk_assert(nodes.size() > 0);

		if (m_isInitNode == false)
		{
			for (int n = 0; n <= config.NNM; n++)	nodes[n]	= iNode;
			m_isInitNode = true;
		}
		else
		{
			cout << "Nodes in the grid are already initialized!!" << endl;
		}
	}

	void initializeFace(const FACE& iFace)
	{
		mk_assert(faces.size() > 0);

		if (m_isInitFace == false)
		{
			for (int f = 0; f <= config.NFM; f++)	faces[f]	= iFace;
			m_isInitFace = true;
		}
		else
		{
			cout << "Faces in the grid are already initialized!!" << endl;
		}
	}

	void initializeCell(const CELL& iCell)
	{
		mk_assert(cells.size() > 0);

		if (m_isInitCell == false)
		{
			for (int c = 0; c <= config.NCM; c++)	cells[c]	= iCell;
			m_isInitCell = true;
		}
		else
		{
			cout << "Cells in the grid are already initialized!!" << endl;
		}
	}

	void initializeGhost(const GHOST& iGhost)
	{
		mk_assert(ghosts.size() > 0);

		if (m_isInitGhost == false)
		{
			for (int g = 0; g <= config.NGM; g++)	ghosts[g]	= iGhost;
			m_isInitGhost = true;
		}
		else
		{
			cout << "Ghosts in the grid are already initialized!!" << endl;
		}
	}

	void initialize(const NODE& iNode, const FACE& iFace, const CELL& iCell, const GHOST& iGhost)
	{
		initializeNode(iNode);
		initializeFace(iFace);
		initializeCell(iCell);
		initializeGhost(iGhost);
	}


	// MF-PUB-07 Access m_bc_zone
	std::vector<int>&	accessBCzone()
	{
		return (m_bc_zone);
	}



};



template <class GRIDTYPE, class DATATYPE>
void GridAllocateData(const int num, std::vector<GRIDTYPE>& elements)
{
	if (typeid(elements[0]) != typeid(GRID::Node) &&
		typeid(elements[0]) != typeid(GRID::Face) &&
		typeid(elements[0]) != typeid(GRID::Cell) &&
		typeid(elements[0]) != typeid(GRID::FaceCart) &&
		typeid(elements[0]) != typeid(GRID::CellCart))
	{
		OP2A::Common::ExceptionGeneral(FromHere(), "The given grid element type is not supported grid element type. Please check the provided grid element type:",  "NotSupportedType:");
	}

	DATATYPE tempData;
	for (int i = 0; i <= num; i++)	elements[i].data = tempData;
}




/*
 * ==========================================
 * Grid1D class
 * 	Initially written by:	Minkwan Kim
 * 	Last modified on	:	May/14/2015
 * 	Last modified by	:	Minkwan Kim
 * =========================================
 */

class Grid1D
{
	/*
	 * I. Constructor and Destructor
	 */
public:
	Grid1D();
	Grid1D(const unsigned int nfm);
	~Grid1D();

	/*
	 * II. Member Variables
	 */
public:
	OP2A::GRID::Configuration	config;
	std::vector<GRID::Node>		nodes;
	std::vector<GRID::Face>		faces;
	std::vector<GRID::Face>		ghosts;

	Common::Map1D<double, int>	mapNode;
	Common::Map1D<double, int>	mapFace;


private:
	bool				m_isAllocated;
	bool				m_isInit;
	bool				m_isInitNode;
	bool				m_isInitFace;


	/*
	 * III. Member Functions
	 */
public:
	// MF-PUB-01 - allocateGrid
	// @param newSize new size of vector
	// @return Void
	void allocateGrid();
	void allocateGrid(const unsigned int nfm);


	// MF-PUB-02 - resizeNode
	// @param newSize new size of vector
	// @return Void
	void resizeNode(const unsigned int nnm);

	// MF-PUB-03 - resizeFace
	// @param newSize new size of vector
	// @return Void
	void resizeFace(const unsigned int nnm);


	// MF-PUB-04 - initialize
	void initializeNode(const GRID::Node& i_node);
	void initializeNode(const GRID::Node& i_node, bool isOnlyData);

	void initializeFace(const GRID::Face& i_face);
	void initializeFace(const GRID::Face& i_face, bool isOnlyData);

	// MF-PUB-05 - Node/Face
	GRID::Node&	NODE(const double i);
	GRID::Face&	FACE(const double i);
};

void GridGen1Dv2(const double x0, const double xL, const int nfm, Grid1D& grid);
Grid<GRID::Node, GRID::Face, GRID::Cell, GRID::Cell> GridGen1D(const double x0, const double xL, const int N, const int gridFlag);











void GridProcessingGeometryNode(OP2A::GRID::Configuration&	config, std::vector<GRID::Node>& nodes);

void GridProcessingGeometryFace(OP2A::GRID::Configuration&	config, std::vector<GRID::Face>& faces);
void GridProcessingGeometryFace(OP2A::GRID::Configuration&	config, std::vector<GRID::FaceCart>& faces);

void GridProcessingGeometryCell(OP2A::GRID::Configuration&	config, std::vector<GRID::Cell>& cells);
void GridProcessingGeometryCellCart(OP2A::GRID::Configuration&	config, std::vector<GRID::CellCart>& cells);

void GridProcessingGeometryGhost(OP2A::GRID::Configuration&	config, 	std::vector<GRID::Face>& faces, 	std::vector<GRID::Cell>& ghosts);
void GridProcessingGeometryGhostCart(OP2A::GRID::Configuration&	config, std::vector<GRID::FaceCart>& faces, std::vector<GRID::CellCart>& ghosts);



void GridProcessing(Grid<GRID::Node, GRID::Face, GRID::Cell, GRID::Cell>& grid);
void GridProcessingCart(Grid<GRID::Node, GRID::FaceCart, GRID::CellCart, GRID::CellCart>& grid);








}


#endif /* GRID_HPP_ */
