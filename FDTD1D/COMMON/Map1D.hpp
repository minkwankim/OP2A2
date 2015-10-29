/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Map1D.hpp
 *
 *  Created on: Oct 28, 2015
 *      Author: minkwan
 */

#ifndef MAP1D_HPP_
#define MAP1D_HPP_

#include "Assert.hpp"
#include "StringOps.hpp"
#include "ExceptionGeneral.hpp"


namespace OP2A{
namespace Common{



template <typename KEY, typename VALUE>
class Map1D
{
	/*
	 * I. Constructor and Destructor
	 */
public:
	// Constructor
	Map1D(size_t maxSize) : m_sorted(false)
	{
		if (maxSize > 0) m_vectorMap.reserve(maxSize);
	}

	Map1D() : m_sorted(false)
	{
		m_vectorMap.reserve(1);
	}

	// Destructor
	~Map1D() { }


	/*
	 * II. Member Variables
	 */
private:
	bool m_sorted;
	std::vector<std::pair<KEY, VALUE> >  m_vectorMap;



	/*
	 * III. Member Functions
	 */
public:
	// MF-PUB-01 - reserve
	// @param maxSize size of the map to be set before starting inserting pairs in the  map
	// @post  the memory corresponding to the given size will be reserved for the future insertions.
	// @return Void
	void reserve(size_t maxSize)
	{
		m_vectorMap.reserve(maxSize);
	}


	// MF-PUB-02 - resize
	// @param	newSize	new size of the map
	// @post	The size of pair vector will be adjusted
	// @return	Void
	void resize(size_t	newSize)
	{
		m_vectorMap.resize(newSize);
		m_sorted	= false;
	}


	// MF-PUB-03 - insert
	// @param	key		new key to be inserted
	// @param	value	new value to be inserted, corresponding to the given key
	// @post	a new std::pair<KEY, VALUE> will be created and pushed back in the map
	// @post	the capacity of the map will increase only if the memory hasn't been reserved properly at start up.
	void insert(const KEY& aKey, const VALUE& aValue)
	{
		m_sorted = false;
		m_vectorMap.push_back(std::pair<KEY, VALUE>(aKey, aValue));
	}

	void insert(unsigned int i, const KEY& aKey, const VALUE& aValue)
	{
		m_sorted = false;
		if (m_vectorMap[i].first == "")
		{
			m_vectorMap[i]	= std::pair<KEY, VALUE>(aKey, aValue);
		}
		else
		{
			insert(aKey, aValue);
		}
	}


	// MF-PUB-04 - findBounds
	// @brief	Find the upper and lower pairs of KEY'S and VALUE'S bounding the supplied KEY.
	// @pre		before using findBounds() the Map1D has to be sorted with sortKeys()
	std::pair<typename std::vector<typename std::pair<KEY,VALUE> >::iterator, typename std::vector<typename std::pair<KEY,VALUE> >::iterator> findBounds(const KEY& aKey)
	{
		if(m_vectorMap.empty())	valueNotFound(aKey);
		if(!m_sorted)			sortKeys();

		if(aKey < m_vectorMap.front().first)
		{
			return std::make_pair(m_vectorMap.begin(),m_vectorMap.begin());
		}

		if(aKey > m_vectorMap.back().first)
		{
			return std::make_pair(--m_vectorMap.end(),--m_vectorMap.end());
		}

		typename std::vector<std::pair<KEY,VALUE> >::iterator after = lower_bound(m_vectorMap.begin(),m_vectorMap.end(), aKey,Compare());
		typename std::vector<std::pair<KEY,VALUE> >::iterator before = after;

		--before;

		return std::make_pair(before,after);
	}


	// MF-PUB-05 - find
	// @brief		Find VALUE with the given KEY
	// @param		key  key to be looked-up
	// @pre 		before using find() the Map has to be sorted with sortKeys()
	// @post 		if the key is not in the map, a NoSuchValueException is thrown
	// @return 		copy of found VALUE
	// @exception	NoSuchValueException is thrown if key not in map
	VALUE find(const KEY& aKey)
	{
		if(m_vectorMap.empty())	valueNotFound(aKey);
		if(!m_sorted)			sortKeys();

		typename std::vector<std::pair<KEY,VALUE> >::iterator itr;
		itr = std::lower_bound(m_vectorMap.begin(), m_vectorMap.end(), aKey, Compare());

		if (itr == m_vectorMap.end())	valueNotFound(aKey);
		if (itr->first != aKey)			valueNotFound(aKey);


		mk_assert(itr->first == aKey); // must have one at least
		return itr->second;
	}

	/// @param		key      key to be looked-up
	/// @param 		isFound  flag telling if the value has been found
	/// @pre 		before using find() the CFMultiMap has to be sorted with sortKeys()
	/// @return 	copy of found VALUE
	VALUE find(const KEY& aKey, bool& isFound)
	{
		isFound = false;

		if(m_vectorMap.empty())
		{
			return (-1);
		}

		if(!m_sorted)			sortKeys();
		//mk_assert(!m_vectorMap.empty());
		//mk_assert(m_sorted);

		// this can fail if only one key is inserted !!!
		//mk_assert(m_vectorMap.size() > 1);

		typename std::vector<std::pair<KEY,VALUE> >::iterator itr;
		itr = std::lower_bound(m_vectorMap.begin(), m_vectorMap.end(), aKey, Compare());

		if (itr != m_vectorMap.end())
		{
			if (itr->first == aKey)
			{
				isFound = true;
				return itr->second;
			}
		}

		return itr->second;
	}


	// MF-PUB-06 - exits
	// @brief 		Check if the given KEY is associated to a VALUE
	// @param		key  key to be looked-up
	// @pre 		before using exists() the CFMap has to be sorted with sortKeys()
	// @return		flag to know if key exists
	bool exists(const KEY& aKey)
	{
		if(m_vectorMap.empty())
		{
			return false;
		}

		if(!m_sorted)
		{
			sortKeys();
		}

		typename std::vector<std::pair<KEY,VALUE> >::iterator itr;
		itr = std::lower_bound(m_vectorMap.begin(), m_vectorMap.end(), aKey, Compare());

		if (itr == m_vectorMap.end())
		{
			return false;
		}

		if (itr->first != aKey)
		{
			return false;
		}

		mk_assert(itr->first == aKey); // must have one at least

		return true;
	}


	// MF-PUB-07 - print
	// @brief	Print the content of the map
	// @result	Void
	void print()
	{
		const unsigned int sizeM = m_vectorMap.size();

		for (unsigned int i = 0; i < sizeM; ++i)
		{
			std::cout << m_vectorMap[i].first << " => " << m_vectorMap[i].second << "\n";
		}
	}


	// MF-PUB-08 - clear
	// @brief	Clear the content of the map
	void clear()
	{
		std::vector<std::pair<KEY,VALUE> >().swap(m_vectorMap);
	}


	// MF-PUB-09 - clearContent
	// @brief	Clear the content of the map while keeping its size
	void clearContent()
	{
		if (size() > 0 )
		{
			m_vectorMap.clear();
		}

		mk_assert(size() == 0);
	}


	// MF-PUB-10 - size
	// @brief	Get the number of pairs already inserted
	size_t size() const
	{
		return m_vectorMap.size();
	}


	// MF-PUB-11 - [] (operator)
	// @brief	Overloading of the operator"[]" for assignment
	// @return	m_vectorMap[i].second
	VALUE& operator[] (const unsigned int i)
	{
		mk_assert(i < size());
		return m_vectorMap[i].second;
	}


	// MF-PUB-12 - sortKeys
	// @brief	Sort all the pairs in the map by key
	// @pre		before using find() the Map1D has to be sorted
	void sortKeys()
	{
		std::sort(m_vectorMap.begin(), m_vectorMap.end(), LessThan());
		m_sorted = true;
	}


	// MF-PUB-13 - begin
	// @return	the iterator pointing at the first element
	typename std::vector<std::pair<KEY, VALUE> >::iterator begin()
	{
		return m_vectorMap.begin();
	}


	// MF-PUB-14 - end
	// @return	the iterator pointing at the last element
	typename std::vector<std::pair<KEY, VALUE> >::iterator end()
	{
		return m_vectorMap.end();
	}


	//MF-PUB-15 - replaceValue
	// @brief	replace the value of the key: Key, with the value: newValue
	// @param	Key  old key
	// @param	Key  new key
	void replaceValue(KEY Key, VALUE newValue)
	{
		if(!m_sorted)	sortKeys();

		VALUE oldValue = find(Key);
		std::pair<KEY, VALUE > oldPair(Key, oldValue);
		std::pair<KEY, VALUE > newPair(Key, newValue);

		replace(m_vectorMap.begin(), m_vectorMap.end(), oldPair, newPair);
	}


	// MF-PUB-16 - getKey
	// @brief	get the key corresponding to position i
	KEY getKey(const unsigned int i)
	{
		mk_assert(i < size());

		if(!m_sorted)	sortKeys();
		return m_vectorMap[i].first;
	}


	// MF-PUB-17 - findKey
	// @brief	get Key corresponding value
	KEY findKey(VALUE value)
	{
		KEY	key;

		if(m_vectorMap.empty())	keyNotFound(value);


		for (int i = 0; i <= m_vectorMap.size(); i++)
		{
			if (m_vectorMap[i].second == value)
			{
				key = m_vectorMap[i].first;
				return(key);
			}
		}

		if(m_vectorMap.empty())	keyNotFound(value);
		return(key);
	}


private:
	// MF-PRI-01 - valueNotFound
	void valueNotFound(const KEY& aKey)
	{
		std::string msg = "Map1D: VALUE it not found: [for KEY: ";
		msg += Common::StringOps::to_str(aKey);
		msg += "]";

		throw Common::ExceptionGeneral (FromHere(), msg, "NoSuchValue");
	}

	// MF-PRI-02 - keyNotFound
	void keyNotFound(const VALUE& aValue)
	{
		std::string msg = "Map1D: KEY not found: [for VALUE: ";
		msg += Common::StringOps::to_str(aValue);
		msg += "]";

		throw Common::ExceptionGeneral (FromHere(), msg, "NoSuchValue");
	}



/* ============================================
 * Nested Classes
 * ============================================
 */
private:
	/*
	 * This class represents a functor object that is passed as an argument in the std::sort to compare two given pairs.
	 */
	class LessThan
	{
	public:
		/// Overloading of the operator() that makes this class acting as a functor
		/// @param p1  pair to be used as first term of comparison
		/// @param p2  pair to be used as second term of comparison
		/// @return true  if(p1.first < p2.first)
		/// @return false if(p1.first >= p2.first)
		/// @post the pairs will be ordered according to the increasing order of
		///       their keys
		/// @post sortKeys() uses these function to order the inserted pairs
		bool operator() (const std::pair<KEY,VALUE>& p1,	const std::pair<KEY,VALUE>& p2) const
		{
			return (p1.first < p2.first) ? true : false;
		}
	}; // end class LessThan


	/*
	 * This class represents a functor object that is passed as an argument in the std::pair to compare two given pairs.
	 * This functor is passed as an argument in the std::equal_range function in order to find all the pairs containing the specified key
	 */
	class Compare
	{
	public:

		/// Overloading of the operator() that makes this class acting as a functor
		/// @param p1   pair whose key is used as first term of comparison
		/// @param key  given key used as second term of comparison
		/// @return true  if(p1.first < key)
		/// @return false if(p1.first >= key)
		/// @post this is the first test to see if p1.first is == key during the
		///       search with find()
		bool operator() (const std::pair<KEY,VALUE>& p1, const KEY& key) const
		{
			return (p1.first < key) ? true : false;
		}

		/// Overloading of the operator() that makes this class acting as a functor
		/// @param key  given key used as first term of comparison
		/// @param p1   pair whose key is used as second term of comparison
		/// @return true  if(p1.first > key)
		/// @return false if(p1.first <= key)
		/// @post this is the second test to see if p1.first is == key during the
		///       search with find()
		bool operator() (const KEY& key, const std::pair<KEY,VALUE>& p1) const
		{
			return (p1.first > key) ? true : false;
		}
	};


};


}
}


#endif /* MAP1D_HPP_ */
