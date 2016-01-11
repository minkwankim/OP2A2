/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cDataV2.cpp
 *
 *  Created on: Jan 11, 2016
 *      Author: minkwan
 */

#include <DATA/cDataV2.hpp>

namespace DATA {

c_Data_v2::c_Data_v2():
		m_initialized(false)
{
	// TODO Auto-generated constructor stub

}

c_Data_v2::~c_Data_v2() {
	// TODO Auto-generated destructor stub
}


void c_Data_v2::add(string variableName)
{
	bool doesExist;
	unsigned int pos = dataMap.find(variableName, doesExist);

	if (doesExist != true)
	{
		unsigned int n = data.size();

		data.resize(n+1, 0.0);
		dataMap.insert(variableName, n);
	}
}


void c_Data_v2::initialize()
{
	data.clear();
	dataMap.clear();
}


double& c_Data_v2::operator() (const string varName)
{
	int index	= dataMap.find(varName);
	return (data[index]);
}


} /* namespace DATA */


