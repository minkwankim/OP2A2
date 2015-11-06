/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Grid.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: minkwan
 */

#include "Grid.hpp"

namespace OP2A{




Grid::Grid():m_isAllocated(false)
{

};


Grid::~Grid()
{

};

// MF-PUB-01 - allocateGrid
// @param newSize new size of vector
// @return Void
void Grid::allocateGrid()
{
	mk_assert(config.isConfigured() == true);

	if (m_isAllocated == false)
	{
		nodes.resize(config.NNM+1);
		faces.resize(config.NFM+1);
		cells.resize(config.NCM+1);
		ghosts.resize(config.NGM+1);

		m_isAllocated = true;
	}
}


// MF-PUB-02 - resizeNode
// @param newSize new size of vector
// @return Void
void Grid::resizeNode(const int nnm)
{
	nodes.resize(nnm+1);
	config.NNM = nnm;
}


// MF-PUB-03 - resizeFace
// @param newSize new size of vector
// @return Void
void Grid::resizeFace(const int nfm)
{
	faces.resize(nfm+1);
	config.NFM = nfm;
}


// MF-PUB-04 - resizeCell
// @param newSize new size of vector
// @return Void
void Grid::resizeCell(const int ncm)
{
	cells.resize(ncm+1);
	config.NCM = ncm;
}


// MF-PUB-05 - resizeGhost
// @param newSize new size of vector
// @return Void
void Grid::resizeGhost(const int ngm)
{
	ghosts.resize(ngm+1);
	config.NGM = ngm;
}


}


