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
#include "NonInstantiable.hpp"
#include "Common.hpp"

using namespace std;

namespace OP2A {
namespace Common {

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
