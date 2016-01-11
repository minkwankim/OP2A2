/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * VectorPointer.hpp
 *
 *  Created on: Dec 2, 2015
 *      Author: minkwan
 */

#ifndef VECTORPOINTER_HPP_
#define VECTORPOINTER_HPP_

#include <vector>
#include <algorithm>
#include <iterator>

#include "NonInstantiable.hpp"
#include "Common.hpp"

using namespace std;

namespace OP2A {
namespace Common {

template <class type>
void addPointerInVector(std::vector<type*>& vectorPointerList, type* cand_Pointer)
{
	int num	= vectorPointerList.size();
	bool flag = true;

	if (num > 0)
	{
		for (int n = 0; n <= num-1; n++)
		{
			if (cand_Pointer == vectorPointerList[n])
			{
				flag = false;
				break;
			}
		}

		if (flag == true)
		{
			vectorPointerList.push_back(cand_Pointer);
		}
	}
	else
	{
		vectorPointerList.push_back(cand_Pointer);
	}
}

template <class type>
void removePointerInVector(std::vector<type*>& vectorPointerList, type* cand_Pointer)
{
	vectorPointerList.erase(std::remove(vectorPointerList.begin(), vectorPointerList.end(), cand_Pointer), vectorPointerList.end());
}


template <class type>
void removeNULLInVector(std::vector<type*>& vectorPointerList)
{
    std::vector<double*>::iterator iter = vectorPointerList.begin();
	while (iter != vectorPointerList.end())
	{
		if (*iter == NULL)
		{
			iter = vectorPointerList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}













class COMMON_API VectorPointer :public Common::NonInstantiable<VectorPointer>
{
public:

	template <class data>
	static void removeNULL(vector<data*>& data_vector)
	{
		bool flaghasNull = true;
		while (flaghasNull == true)
		{
			flaghasNull = false;
			for (int i = 0; i <= data_vector.size()-1; i++)
			{
				if (data_vector[i] == NULL)
				{
					flaghasNull = true;
					data_vector.erase(data_vector.begin()+i);
					break;
				}
			}
		}
	}


};

} /* namespace Common */
} /* namespace OP2A */

#endif /* VECTORPOINTER_HPP_ */
