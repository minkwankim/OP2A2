/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Grid1D.cpp
 *
 *  Created on: Nov 24, 2015
 *      Author: minkwan
 */


#include "Grid.hpp"


namespace OP2A{

/*
 * I. Constructor and Destructor
 */
Grid1D::Grid1D()
:m_isAllocated(false), m_isInit(false), m_isInitNode(false), m_isInitFace(false)
{

}

Grid1D::Grid1D(const unsigned int nfm)
:nodes(nfm+2), faces(nfm+1), m_isInit(false), m_isInitNode(false), m_isInitFace(false), m_isAllocated(true),
whereisNode(nfm+2), whereisFace(nfm+1)
{
	config.Configure(1, nfm+1, nfm, 0, 0, 1.0, false);
}


Grid1D::~Grid1D()
{

}




/*
 * III. Member Functions
 */

// MF-PUB-01 - allocateGrid
// @param newSize new size of vector
// @return Void
void Grid1D::allocateGrid()
{
	mk_assert(config.isConfigured() == true);

	if (m_isAllocated == false)
	{
		nodes.resize(config.NNM+1);
		faces.resize(config.NFM+1);

		whereisNode.resize(config.NNM+1);
		whereisFace.resize(config.NFM+1);


		m_isAllocated = true;
	}

	if (m_isAllocated != true)
	{
		OP2A::Common::ExceptionGeneral(FromHere(), "Memory for Grid class is not allocated. Please check the system memory:",  "DataAllocation:");
	}
}

void Grid1D::allocateGrid(const unsigned int nfm)
{
	config.Configure(1, nfm+1, nfm, 0, 0, 1.0, false);
	allocateGrid();
}

// MF-PUB-02 - resizeNode
// @param newSize new size of vector
// @return Void
void Grid1D::resizeNode(const unsigned int nnm)
{
	nodes.resize(nnm+1);
	whereisNode.resize(nnm+1);
	config.NNM = nnm;
}

// MF-PUB-03 - resizeFace
// @param newSize new size of vector
// @return Void
void Grid1D::resizeFace(const unsigned int nfm)
{
	faces.resize(nfm+1);
	whereisFace.resize(nfm+1);
	config.NFM = nfm;
}


// MF-PUB-04 - initialize
void Grid1D::initializeNode(const GRID::Node& i_node)
{
	mk_assert(nodes.size() > 0);

	if (m_isInitNode == false)
	{
		for (int n = 0; n <= config.NNM; n++)	nodes[n]	= i_node;
		m_isInitNode = true;
	}
	else
	{
		cout << "Nodes in the grid are already initialized!!" << endl;
	}
}

void Grid1D::initializeFace(const GRID::Face& i_face)
{
	mk_assert(faces.size() > 0);

	if (m_isInitFace == false)
	{
		for (int f = 0; f <= config.NFM; f++)	faces[f]	= i_face;
		m_isInitFace = true;
	}
	else
	{
		cout << "Faces in the grid are already initialized!!" << endl;
	}
}





}
