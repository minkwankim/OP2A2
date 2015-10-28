/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Array2D.hpp
 *
 *  Created on: Oct 28, 2015
 *      Author: minkwan
 */

#ifndef ARRAY2D_HPP_
#define ARRAY2D_HPP_

#include "Common.hpp"
#include "Assert.hpp"
#include "VectorMultiDimension.hpp"
#include <math.h>


namespace OP2A{
namespace Common{

/*
 * Class for 2D array (Matrix, I x J)
 * 	- [Size_]: size of Coloumn (I)
 * 	- [ElementSize_]: Size of row (J)
 * 	- [Data_]: Data of matrix
 *
 * 	Initially written by:	Minkwan Kim
 * 	Last modified on	:	May/14/2015
 * 	Last modified by	:	Minkwan Kim
 */

template <typename T>
class Array2D
{
protected:
	unsigned int m_size_I;
	unsigned int m_size_J;
	std::vector< std::vector<T>	> m_data;
	std::string	m_description;

public:
	// Constructors
	Array2D():m_size_I(0), m_size_J(0)
	{

	}

	explicit Array2D(unsigned int i, unsigned int j):m_size_I(i), m_size_J(j), m_data(i, std::vector<T>(j))
	{

	}

	explicit Array2D(const std::vector< std::vector< double> >& data_matrix)
	{
		m_size_I	= data_matrix.size();
		m_size_J	= data_matrix[0].size();
		m_data = data_matrix;
	}

	explicit Array2D(unsigned int i, unsigned int j, const std::string& i_description):m_size_I(i), m_size_J(j), m_data(i, std::vector<T>(j)), m_description(i_description)
	{

	}

	explicit Array2D(const std::string& i_description):m_size_I(0), m_size_J(0), m_description(i_description)
	{

	}

	~Array2D()
	{
		for (int i = 0; i <= m_size_I-1; i++)	m_data[i].clear();
		m_data.clear();

	}



	/*
	 * Overloading parameters
	 */
	T& operator()(const unsigned i, const unsigned j)
	{
		mk_assert(i > 0);	mk_assert(i <= m_size_I);
		mk_assert(j > 0);	mk_assert(j <= m_size_J);

		return m_data[i-1][j-1];
	}



	/*
	 * Class functions
	 */
	// CF-01: assign
	//			- Assign element
	void assign(unsigned int i, unsigned int j, const T& val)
	{
		m_data.assign(i, std::vector<T>(j, val));
		m_size_I	= m_data.size();
		m_size_J	= m_data[0].size();
	}

	// CF-02: size
	//			- get the information of the size
	unsigned int size(unsigned int i) const
	{
		mk_assert(i > 0);
		mk_assert(i <= 2);

		if (i == 1)		return m_size_I;
		else			return m_size_J;
	}


	// CF-03 resize
	//			- resize
	void resize(unsigned int i, unsigned int j)
	{
		mk_assert(i > 0);
		mk_assert(j > 0);

		unsigned int i_max = fmax(i, m_size_I);

		for (int itr = 0; itr <= i_max-1; itr++)	m_data[itr].resize(j);
		m_data.resize(i);

		m_size_I	= m_data.size();
		m_size_J	= m_data[0].size();
	}

	void resize_Row(unsigned int i)
	{
		m_data.resize(i);
		for (int itr = m_size_I; itr <= i-1; itr++)	m_data[itr].resize(m_size_J);

		m_size_I	= m_data.size();
	}

	void resize_Col(unsigned int j)
	{
		for (int itr = 0; itr <= m_size_I-1; itr++)	m_data[itr].resize(j);
		m_size_J	= m_data[0].size();
	}


	// CF-04 reserve
	//			- Reserve memory space
	void reserve (unsigned int i, unsigned int j)
	{
		mk_assert(i > 0);
		mk_assert(j > 0);

		m_data.reserve(i);
		for (int itr = 0; itr <= i-1; itr++)	m_data[itr].reserve(j);
	}


	// CF-05 erase
	void erase_Row(unsigned int i)
	{
		mk_assert (i <= m_size_I);
		mk_assert (i > 0);

		m_data.erase(m_data.begin() + i-1);
		m_size_I	= m_data.size();
	}

	void erase_Col(unsigned int j)
	{
		mk_assert (j <= m_size_J);
		mk_assert (j > 0);

		for (int itr = 0; itr <= m_size_I-1; itr++)	m_data[itr].erase(m_data[itr].begin() + j-1);
		m_size_J	= m_data[0].size();
	}

	void erase(unsigned int i, unsigned int j)
	{
		erase_Row(i);
		erase_Col(j);
	}

	// CF-06 insert
	//		- Insert elements
	void insert_Row(unsigned int i)
	{
		mk_assert(i > 0);
		mk_assert(i <= m_size_I+1);

		std::vector<T>	val(m_size_J, 0.0);
		m_data.insert(m_data.begin() + i-1, val);
		m_size_I	= m_data.size();
	}

	void insert_Row(unsigned int i, const T& value)
	{
		mk_assert(i > 0);
		mk_assert(i <= m_size_I+1);

		std::vector<T>	val(m_size_J, value);
		m_data.insert(m_data.begin() + i-1, val);
		m_size_I	= m_data.size();
	}

	void insert_Row(unsigned int i, const std::vector<T>& value)
	{
		mk_assert(i > 0);
		mk_assert(i <= m_size_I+1);

		std::vector<T>	val = value;	val.resize(m_size_J);
		m_data.insert(m_data.begin() + i-1, val);
		m_size_I	= m_data.size();
	}

	void insert_Row()
	{
		insert_Row(m_size_I+1, 0.0);
	}

	void insert_Col(unsigned int j)
	{
		mk_assert(j > 0);
		mk_assert(j <= m_size_J+1);

		for (int itr = 0; itr <= m_size_I-1; itr++)	m_data[itr].insert(m_data[itr].begin() + j-1, 0.0);
		m_size_J	= m_data[0].size();
	}

	void insert_Col(unsigned int j, const T& value)
	{
		mk_assert(j > 0);
		mk_assert(j <= m_size_J+1);

		for (int itr = 0; itr <= m_size_I-1; itr++)	m_data[itr].insert(m_data[itr].begin() + j-1, value);
		m_size_J	= m_data[0].size();
	}


	void insert_Col(unsigned int j, const std::vector<T>& value)
	{
		mk_assert(j > 0);
		mk_assert(j <= m_size_J+1);
		value.resize(m_size_I);

		for (int itr = 0; itr <= m_size_I-1; itr++)	m_data[itr].insert(m_data[itr].begin() + j-1, value[itr]);
		m_size_J	= m_data[0].size();
	}

	void insert_Col()
	{
		insert_Col(m_size_J+1, 0.0);
	}

	void insert(unsigned int i, unsigned int j)
	{
		insert_Row(i);
		insert_Col(j);
	}

	void insert(unsigned int i, unsigned int j, const T& value)
	{
		insert_Row(i, value);
		insert_Col(j, value);
	}


	// CF-07 clear
	void clear()
	{
		resize(0, 0);
		m_size_I = 0;
		m_size_J = 0;
	}


	// CF-08: Show description
	std::string	description()
	{
		return (m_description);
	}

	void set_description(const std::string& i_description)
	{
		m_description = i_description;
	}

};


}
}

#endif /* ARRAY2D_HPP_ */
