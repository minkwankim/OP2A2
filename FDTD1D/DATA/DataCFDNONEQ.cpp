/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * DataCFDNONEQ.cpp
 *
 *  Created on: Jan 11, 2016
 *      Author: minkwan
 */

#include "Data.hpp"
#include "./COMMON/TypeConversion.hpp"


namespace DATA
{

namespace NONEQ_CFD
{
	c_Data	dataSampleCell(unsigned int NS, unsigned int DIM, unsigned NE)
	{
		unsigned int n = 0;
		c_Data data_cell;

		// Species Densities
		for(int s = 1; s <= NS; s++)
		{
			if (data_cell.data.size() < n+1)	data_cell.data.resize(n+1, 0.0);
			else								data_cell.data[n] = 0.0;

			data_cell.dataMap.insert("Q" + OP2A::Common::intToString(s), n);	// Conservative variables
			data_cell.dataMap.insert("U" + OP2A::Common::intToString(s), n);	// Primitive variables
			data_cell.dataMap.insert("W" + OP2A::Common::intToString(s), n);	// Primitive variables
			data_cell.dataMap.insert("rho_" + OP2A::Common::intToString(s), n);	// variable name
			n++;
		}

		// Velocities
		for(int k = 1; k <= DIM; k++)
		{
			if (data_cell.data.size() < n+1)	data_cell.data.resize(n+1, 0.0);
			else								data_cell.data[n] = 0.0;

			data_cell.dataMap.insert("U" + OP2A::Common::intToString(NS+k), n);	// Primitive variables
			data_cell.dataMap.insert("W" + OP2A::Common::intToString(NS+k), n);	// Primitive variables
			data_cell.dataMap.insert("u_" + OP2A::Common::intToString(k), n);	// variable name
			n++;
		}

		// Momentums
		for(int k = 1; k <= DIM; k++)
		{
			if (data_cell.data.size() < n+1)	data_cell.data.resize(n+1, 0.0);
			else								data_cell.data[n] = 0.0;

			data_cell.dataMap.insert("Q" + OP2A::Common::intToString(NS+k), n);	// Conservative variables
			n++;
		}


		// Temperature
		if (data_cell.data.size() < n+1)	data_cell.data.resize(n+1, 0.0);
		else								data_cell.data[n] = 0.0;
		data_cell.dataMap.insert("U" + OP2A::Common::intToString(NS+DIM+1), n);	// Primitive variables (Total Temperature)
		data_cell.dataMap.insert("T", n);	// Variable name
		n++;

		// Pressure
		if (data_cell.data.size() < n+1)	data_cell.data.resize(n+1, 0.0);
		else								data_cell.data[n] = 0.0;
		data_cell.dataMap.insert("W" + OP2A::Common::intToString(NS+DIM+1), n);	// Primitive variables (Total Temperature)
		data_cell.dataMap.insert("p", n);	// Variable name
		n++;

		// Other temperature modes
		for(int m = 2; m <= NE; m++)
		{
			if (data_cell.data.size() < n+1)	data_cell.data.resize(n+1, 0.0);
			else								data_cell.data[n] = 0.0;

			data_cell.dataMap.insert("U" + OP2A::Common::intToString(NS+DIM+1+m), n);	// Primitive variables
			data_cell.dataMap.insert("W" + OP2A::Common::intToString(NS+DIM+1+m), n);	// Primitive variables
			data_cell.dataMap.insert("T_" + OP2A::Common::intToString(m), n);	// Primitive variables
			n++;
		}

		// Energy modes
		for(int m = 1; m <= NE; m++)
		{
			if (data_cell.data.size() < n+1)	data_cell.data.resize(n+1, 0.0);
			else								data_cell.data[n] = 0.0;

			data_cell.dataMap.insert("Q" + OP2A::Common::intToString(NS+DIM+m), n);	// Conservative variables
			n++;
		}

		// Mixture density
		if (data_cell.data.size() < n+1)	data_cell.data.resize(n+1, 0.0);
		else								data_cell.data[n] = 0.0;
		data_cell.dataMap.insert("rho", n);
		n++;

		// Mole Fraction
		for(int s = 1; s <= NS; s++)
		{
			if (data_cell.data.size() < n+1)	data_cell.data.resize(n+1, 0.0);
			else								data_cell.data[n] = 0.0;

			data_cell.dataMap.insert("X_" + OP2A::Common::intToString(s), n);
			n++;
		}

		// Mass Fraction
		for(int s = 1; s <= NS; s++)
		{
			if (data_cell.data.size() < n+1)	data_cell.data.resize(n+1, 0.0);
			else								data_cell.data[n] = 0.0;

			data_cell.dataMap.insert("Y_" + OP2A::Common::intToString(s), n);
			n++;
		}



		return(data_cell);
	}






}
}
