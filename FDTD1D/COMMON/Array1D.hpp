/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Array1D.hpp
 *
 *  Created on: Oct 27, 2015
 *      Author: minkwan
 */

#ifndef ARRAY1D_HPP_
#define ARRAY1D_HPP_

#include <vector>
#include <iostream>

#include "Common.hpp"
#include "Assert.hpp"


namespace OP2A{
namespace Common{


/*
 * Class for 1D array (Matrix, I)
 * 	- [m_size_I]: size of Coloumn (I)
 * 	- [Data_]: Data of matrix
 *
 * 	Initially written by:	Minkwan Kim
 * 	Last modified on	:	May/14/2015
 * 	Last modified by	:	Minkwan Kim
 */
template <typename T>
class Array1D
{
protected:
	unsigned int m_size_I;
	std::vector<T>	m_data;
	std::string	m_description;

public:
	Array1D():m_size_I(0)
	{

	}

	explicit Array1D(unsigned int i): m_size_I(i), m_data(i)
	{

	}

	explicit Array1D(unsigned int i, const std::string& i_description): m_size_I(i), m_data(i), m_description(i_description)
	{

	}

	explicit Array1D(const std::string& i_description): m_size_I(0), m_description(i_description)
	{

	}

	explicit Array1D(const std::vector<T>& i_data)
	{
		m_size_I = i_data.size();
		m_data.resize(m_size_I);
		m_data	= i_data;
	}

	~Array1D()
	{
		m_data.clear();
	}



	/*
	 * Class Functions
	 */
	// CF-01: Assign elements
	template<class InputIterator>
	void assign (InputIterator first, InputIterator last)
	{
		m_data.assign(first, last);
		m_size_I = m_data.size();
	}

	void assign (unsigned int n, const T& val)
	{
		m_data.assign(n, val);
		m_size_I = m_data.size();
	}


	// CF-02: Return the last element
	const T & back () const
	{
		return m_data.back();
	}


	// CF-03: Return the first element
	const T & front () const
	{
		return m_data.front();
	}


	// CF-04: Getting information about the size
    unsigned int size () const
    {
    	return m_size_I;
    }


	// CF-05: Resize data (I)
	void resize(unsigned int i)
	{
		mk_assert(i > 0);
		m_data.resize(i);
		m_size_I = i;
	}


	// CF-06: Reserve data size
	void reserve (unsigned int i)
	{
		mk_assert(i > 0);
		m_data.reserve (i);
	}


	 // CF-07: Get data
	T & get (unsigned int i)
	{
		mk_assert (i <= m_size_I);
		return m_data[i-1];
	 }

	const T & get (unsigned int i) const
	{
		mk_assert (i <= m_size_I);
		return m_data[i-1];
	}

	T& operator() (const unsigned int i)
	{
		mk_assert (i <= m_size_I);
		return m_data[i-1];
	}


	// CF-08: Push back data
    void push_back (T i_value)
    {
    	m_data.push_back(i_value);
    	m_size_I = m_data.size();
    }


    // CF-09: Delete data
    void erase(unsigned int i)
	{
		mk_assert (i <= m_size_I);
		m_data.erase(m_data.begin()+ (i-1));
		m_size_I	= m_data.size();
	}

    void erase(unsigned int i, unsigned int j)
   	{
   		mk_assert (i <= m_size_I);
   		m_data.erase(m_data.begin() + i-1, m_data.begin() + j);
		m_size_I	= m_data.size();
   	}


    // CF-10: Insert data
    void insert(unsigned int i, const T& i_value)
	{
		mk_assert (i <= m_size_I);
		m_data.insert(m_data.begin() + i-1, i_value);
		m_size_I	= m_data.size();
	}


    // CF-11: Clear data
    void clear ()
    {
    	resize (0);
    	m_size_I = 0;
    }

    // CF-12: give data
    std::vector<T> giveData()
    {
    	return (m_data);
    }


    // CF-13: Show description
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



#endif /* ARRAY1D_HPP_ */
