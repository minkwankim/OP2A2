/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Vector.hpp
 *
 *  Created on: Nov 10, 2015
 *      Author: minkwan
 */

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <vector>
#include "./COMMON/Common.hpp"
#include "./COMMON/Array1D.hpp"
#include "./COMMON/ExceptionGeneral.hpp"


namespace OP2A{
namespace MATH{

enum VectorDirection
{
	VectorDirection_X	= 0,
	VectorDirection_Y	= 1,
	VectorDirection_Z	= 2
};


class VECTOR: public Common::Array1D<double>
{
	/*
	 * I. Constructor and Destructor
	 */
public:
	//Constructor
	VECTOR();
	VECTOR(const unsigned int dim);
	VECTOR(const double& x, const double& y);
	VECTOR(const double& x, const double& y, const double& z);
	VECTOR(const std::vector<double>& x);
	VECTOR(const std::vector<double>& s, const std::vector<double>& e);
	VECTOR(const double (&x)[3]);
	VECTOR(const double (&s)[3], const double (&e)[3]);
	VECTOR(Common::Array1D<double> x);
	VECTOR(Common::Array1D<double> s, Common::Array1D<double> e);

	// Destructor
	~VECTOR();


	/*
	 * II. Member Variables
	 */
protected:
	bool m_isNormalized;


	/*
	 * III. Member Functions
	 */
public:
	// MF-PUB-01 - length
	// @brief Calculate the length of a vector
	// @return double
	double length();

	// MF-PUB-02 - normalize
	// @brief normalize vector
	// @return void
	void normalize();

	// MF-PUB-03 - rotate
	// @brief vector rotation
	// @return VECTOR
	VECTOR rotate(const double angle, VectorDirection direction);
	VECTOR rotate(const double angle, const int direction);


public:	// Operators
//	void operator *= (double const & s);
//	void operator /= (double const & s);
//	void operator -= (double const & s);
//	void operator += (double const & s);

//	void operator -= (const VECTOR & S);
//	void operator += (const VECTOR & S);

};


// Operators Functions
VECTOR operator- (VECTOR A, VECTOR B);
VECTOR operator+ (VECTOR A, VECTOR B);
VECTOR operator* (const double a, VECTOR B);



// Function for linear algebra
double VectorDotProduct(VECTOR A, VECTOR B);
VECTOR VectorCrossProduct(VECTOR A, VECTOR B);
VECTOR NormalFromThreePoint(VECTOR A, VECTOR B, VECTOR C);

}
}



#endif /* VECTOR_HPP_ */
