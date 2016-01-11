/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * cGridInfo.hpp
 *
 *  Created on: Jan 6, 2016
 *      Author: minkwan
 */

#ifndef CGRIDINFO_HPP_
#define CGRIDINFO_HPP_

namespace GRID {

class c_GridInfo {
public:
	c_GridInfo();
	~c_GridInfo();

public:
	unsigned int DIM;
	unsigned int NNM;
	unsigned int NFM;
	unsigned int NCM;
	unsigned int NGM;
};

} /* namespace GRID */

#endif /* CGRIDINFO_HPP_ */
