/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Node_IJK_Info.hpp
 *
 *  Created on: Dec 1, 2015
 *      Author: minkwan
 */

#ifndef NODE_IJK_INFO_HPP_
#define NODE_IJK_INFO_HPP_

namespace OP2A {
namespace GRID {

class Node_IJK_Info {
public:
	Node_IJK_Info();
	~Node_IJK_Info();

public:
	double i;
	double j;
	double k;
};

} /* namespace GRID */
} /* namespace OP2A */

#endif /* NODE_IJK_INFO_HPP_ */
