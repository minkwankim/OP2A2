/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Vector.cpp
 *
 *  Created on: Nov 10, 2015
 *      Author: minkwan
 */


#include "./MATH/Vector.hpp"
#include "./MATH/Area.hpp"



namespace OP2A{
namespace MATH{

/*
 * I. Constructor and Destructor
 */
VECTOR::VECTOR():m_isNormalized(false)
{
	m_size_I	= 2;
	m_data.resize(2);
}


VECTOR::VECTOR(const unsigned int dim):m_isNormalized(false)
{
	m_size_I	= dim;
	m_data.resize(dim);
}


VECTOR::VECTOR(const double& x, const double& y):m_isNormalized(false)
{
	m_size_I	= 2;
	m_data.resize(2);

	m_data[0] = x;
	m_data[1] = y;
}


VECTOR::VECTOR(const double& x, const double& y, const double& z):m_isNormalized(false)
{
	m_size_I	= 3;
	m_data.resize(3);

	m_data[0] = x;
	m_data[1] = y;
	m_data[2] = z;
}


VECTOR::VECTOR(const std::vector<double>& x):m_isNormalized(false)
{
	m_size_I	= x.size();
	m_data		= x;
}


VECTOR::VECTOR(const std::vector<double>& s, const std::vector<double>& e):m_isNormalized(false)
{
	m_size_I	= s.size();
	m_data		= s;

	if (s.size() != e.size())
	{
		Common::ExceptionGeneral (FromHere(), "Dimension of X and Y values do not match", "DimensionMismatch:");
	}


	for (int i = 0; i <= m_size_I-1; i++)
	{
		m_data[i]	= e[i] - s[i];
	}
}


VECTOR::VECTOR(const double (&x)[3]):m_isNormalized(false)
{
	m_size_I	= 3;
	m_data.resize(3);

	m_data[0] = x[0];
	m_data[1] = x[1];
	m_data[2] = x[2];
}


VECTOR::VECTOR(const double (&s)[3], const double (&e)[3]):m_isNormalized(false)
{
	m_size_I	= 3;
	m_data.resize(3);

	m_data[0] = e[0] - s[0];
	m_data[1] = e[1] - s[1];
	m_data[2] = e[2] - s[2];
}


VECTOR::VECTOR(Common::Array1D<double> x):m_isNormalized(false)
{
	m_size_I	= x.size();
	m_data 		= x.giveData();
}


VECTOR::VECTOR(Common::Array1D<double> s, Common::Array1D<double> e):m_isNormalized(false)
{
	m_size_I	= s.size();
	m_data.resize(m_size_I);

	if (s.size() != e.size())
	{
		Common::ExceptionGeneral (FromHere(), "Dimension of X and Y values do not match", "DimensionMismatch:");
	}


	for (int i = 0; i <= m_size_I-1; i++)
	{
		m_data[i]	= e(i+1) - s(i+1);
	}
}



VECTOR::~VECTOR()
{

}


// MF-PUB-01 - length
// @brief Calculate the length of a vector
// @return double
double VECTOR::length()
{
	return (MATH::CalLength(m_data));
}


// MF-PUB-02 - normalize
// @brief normalize vector
// @return void
void VECTOR::normalize()
{
	if(m_isNormalized == false)
	{
		double len = length();
		for (int i = 0; i <= m_size_I-1; i++)
		{
			m_data[i] /= len;
		}

		m_isNormalized = true;
	}
}


// MF-PUB-03 - rotate
// @brief vector rotation
// @return VECTOR
VECTOR VECTOR::rotate(const double angle, VectorDirection direction)
{
	VECTOR ans(m_size_I);

	double cos_theta = cos(angle);
	double sin_theta = sin(angle);

	if (m_size_I == 2)
	{
		ans(1)	= cos_theta*m_data[0] - sin_theta*m_data[1];
		ans(2)	= sin_theta*m_data[0] + cos_theta*m_data[1];
	}
	else
	{
		switch(direction)
		{
		case VectorDirection_X:
			ans(1)	= m_data[0];
			ans(2)	= cos_theta*m_data[1] - sin_theta*m_data[2];
			ans(3)	= sin_theta*m_data[1] + cos_theta*m_data[2];
			break;

		case VectorDirection_Y:
			ans(1)	= cos_theta*m_data[0] + sin_theta*m_data[2];
			ans(2)	= m_data[1];
			ans(3)	= -sin_theta*m_data[0] + cos_theta*m_data[2];
			break;

		case VectorDirection_Z:
			ans(1)	= cos_theta*m_data[0] - sin_theta*m_data[1];
			ans(2)	= sin_theta*m_data[0] + cos_theta*m_data[1];
			ans(3)	= m_data[2];
			break;
		}
	}

	return (ans);
}

VECTOR VECTOR::rotate(const double angle, const int direction)
{
	return (rotate(angle, static_cast<VectorDirection>(direction)));
}




}
}


