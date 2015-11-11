/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Configuration.hpp
 *
 *  Created on: Nov 3, 2015
 *      Author: minkwan
 */

#ifndef CONFIGURATION_HPP_
#define CONFIGURATION_HPP_

#include "COMMON/Array1D.hpp"
#include "COMMON/Common.hpp"

namespace OP2A{
namespace GRID{

/*
 * Class for Configuration of grid
 *
 * 	Initially written by:	Minkwan Kim
 * 	Last modified on	:	May/14/2015
 *
 */

class Configuration
{
	/*
	 * I. Member Variables
	 */
public:
	int DIM;	// Dimension of grid (default: 1)
	int NNM;	// Number of nodes in a grid
	int NFM;	// Number of faces in a grid
	int NCM;	// Number of cells in a grid
	int NGM;	// Number of ghost in a grid

	double gridFactor;
	bool  isAxisymmetric;
private:
	bool	m_isConfigured;

	/*
	 * II. Constructor and Destructor
	 */
public:
	Configuration(): DIM(1), NNM(0), NFM(0), NCM(0), NGM(0), m_isConfigured(false), gridFactor(1.0), isAxisymmetric(false)	{	};
	Configuration(const int dim, const int nnm, const int nfm, const int ncm, const int ngm)
	:DIM(dim), NNM(nnm), NFM(nfm), NCM(ncm), NGM(ngm), m_isConfigured(true), gridFactor(1.0), isAxisymmetric(false)	{	};

	~Configuration() {	};


	/*
	 * III. Member Functions
	 */
public:
	bool isConfigured();
	void Configure(const int dim, const int nnm, const int nfm, const int ncm, const int ngm, const double mesh_factor, bool is_axisymmetric);

};


}
}



#endif /* CONFIGURATION_HPP_ */
