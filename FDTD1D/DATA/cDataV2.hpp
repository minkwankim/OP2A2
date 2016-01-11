/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cDataV2.hpp
 *
 *  Created on: Jan 11, 2016
 *      Author: minkwan
 */

#ifndef CDATAV2_HPP_
#define CDATAV2_HPP_


#include "./COMMON/Map1D.hpp"
#include "./COMMON/ExceptionGeneral.hpp"
#include "./COMMON/ErrorCode.hpp"

using namespace std;

namespace DATA {

class c_Data_v2 {
public:
	c_Data_v2();
	~c_Data_v2();


public:
	string										description;
	vector<double>								data;
	OP2A::Common::Map1D<string, unsigned int>	dataMap;

protected:
	bool m_initialized;



public:
	void add(string variableName);
	void initialize();

	double& operator() (const string varName);

};

} /* namespace DATA */

#endif /* CDATAV2_HPP_ */
