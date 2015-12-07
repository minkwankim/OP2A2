/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Face_IJK_info.h
 *
 *  Created on: Dec 1, 2015
 *      Author: minkwan
 */

#ifndef FACE_IJK_INFO_H_
#define FACE_IJK_INFO_H_

namespace OP2A {
namespace GRID {

class Face_IJK_Info {
public:
	Face_IJK_Info();
	~Face_IJK_Info();

public:
	double i;
	double j;
	double k;
	unsigned int lvl_refine;
	unsigned int direction;

};

} /* namespace GRID */
} /* namespace OP2A */

#endif /* FACE_IJK_INFO_H_ */
