/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Matrix.hpp
 *
 *  Created on: Dec 17, 2015
 *      Author: minkwan
 */

#ifndef MATRIX_HPP_
#define MATRIX_HPP_


namespace OP2A{
namespace MATH{


class MATRIX
{
public:	// Constructor & Destructor
	MATRIX();
	MATRIX(bool matlabType);
	MATRIX(const unsigned int I, const unsigned int J);
	MATRIX(const unsigned int I, const unsigned int J, bool matlabType);
	MATRIX(const std::vector< std::vector< double> >& data_matrix);
	MATRIX(const std::vector< std::vector< double> >& data_matrix, bool matlabType);

	~MATRIX();

public:	// Basic functions
	bool is_allocated() const;
	bool is_MatlabType() const;
	unsigned int sizeI() const;
	unsigned int sizeJ() const;
	void resize(unsigned int I, unsigned int J);
	double val(unsigned int I, unsigned int J) const;

	void ones();
	void ones(unsigned int I, unsigned int J);

	void zeros();
	void zeros(unsigned int I, unsigned int J);

	void diag();
	void diag(unsigned int I);
	void diag(unsigned int I, double value);

	void removeRow(unsigned int I);
	void removeColumn(unsigned int J);

	double sum();


public:	// Operators
	double& operator() (const unsigned int i, const unsigned int j);
	void operator*= (const double s);
	void operator/= (const double s);
	void operator+= (const double s);
	void operator-= (const double s);

	void operator+= (const MATRIX & S);
	void operator-= (const MATRIX & S);

	MATRIX&	operator= (std::vector< std::vector<double> >& A);

public: // Linear Algebra
	MATRIX& MINOR(const int r, const int c);

protected:
	bool m_matlabType;
	bool m_allocated;


	unsigned int m_I;
	unsigned int m_J;

	std::vector < std::vector<double> > m_data;
};


// Operator Functions
MATRIX operator- (MATRIX &A, MATRIX &B);
MATRIX operator+ (MATRIX &A, MATRIX &B);
MATRIX operator* (double a, MATRIX &A);
MATRIX operator* (MATRIX &A, MATRIX &B);
std::vector<double> operator* (MATRIX &A, std::vector<double> &B);



// Linear Algebra
MATRIX MATRIX_Minor(MATRIX &A, const int r, const int c);
double MATRIX_Det(MATRIX &A);
MATRIX MATRIX_Inv(MATRIX &A);


MATRIX MATRIX_Confactor(MATRIX &A);
MATRIX MATRIX_Adjoint(MATRIX &A);
MATRIX MATRIX_Inv2(MATRIX &A);


}
}


#endif /* OP2A_MATRIX_HPP_ */




#endif /* MATRIX_HPP_ */
