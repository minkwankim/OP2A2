/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Area.hpp
 *
 *  Created on: Nov 10, 2015
 *      Author: minkwan
 */

#ifndef AREA_HPP_
#define AREA_HPP_


#include <vector>
#include "./COMMON/Common.hpp"
#include "./COMMON/ExceptionGeneral.hpp"


namespace OP2A{
namespace MATH{


// F-01 - CalLength
// @brief	Calculate the length between two point / Calculate size of vector (n1:start, n2 :end)
// @return double
double CalLength(const std::vector<double>& n1, const std::vector<double>& n2);
double CalLength(const double (&n1)[3], const double (&n2)[3]);
double CalLength(const double (&n1)[3], const double (&n2)[3], const int& nd);
double CalLength(const std::vector<double>& n1);
double CalLength(const double (&n1)[3]);
double CalLength(const double (&n1)[3], const int& nd);


// F-02 - CalAreaTriangle
// @brief	Calculate area of triangle
// @return double
double CalAreaTriangle(const std::vector<double>& n1, const std::vector<double>& n2, const std::vector<double>& n3);
double CalAreaTriangle(const double (&n1)[3], const double (&n2)[3], const double (&n3)[3]);
double CalAreaTriangle(const double (&n1)[3], const double (&n2)[3], const double (&n3)[3], const int& nd);


// F-03 - CalAreaQuadrilateral
// @brief	Calculate area of quadrilateral
// @return double
double CalAreaQuadrilateral(const std::vector<double>& n1, const std::vector<double>& n2,  const std::vector<double>& n3, const std::vector<double>& n4);
double CalAreaQuadrilateral(const double (&n1)[3], const double (&n2)[3], const double (&n3)[3], const double (&n4)[3]);
double CalAreaQuadrilateral(const double (&n1)[3], const double (&n2)[3], const double (&n3)[3], const double (&n4)[3], const int& nd);


// F-04 - CalVolumeTetrahedron
// @brief	Calculate volume of tetrahedron
// @return double
double CalVolumeTetrahedron(const std::vector<double>& n1, const std::vector<double>& n2,  const std::vector<double>& n3, const std::vector<double>& n4);
double CalVolumeTetrahedron(const double (&n1)[3], const double (&n2)[3], const double (&n3)[3], const double (&n4)[3]);


// F-05 - CalVolumePyramid
// @brief	Calculate volume of pyramid
// @return double
double CalVolumePyramid(const std::vector<double>& n1, const std::vector<double>& n2,  const std::vector<double>& n3, const std::vector<double>& n4, const std::vector<double>& n5);
double CalVolumePyramid(const double (&n1)[3], const double (&n2)[3], const double (&n3)[3], const double (&n4)[3], const double (&n5)[3]);


// F-06 - CalVolumeWedge
// @brief	Calculate volume of wedge
// @return double
double CalVolumeWedge(const std::vector<double>& n1, const std::vector<double>& n2, const std::vector<double>& n3, const std::vector<double>& n4, const std::vector<double>& n5, const std::vector<double>& n6);
double CalVolumeWedge(const double (&n1)[3], const double (&n2)[3], const double (&n3)[3], const double (&n4)[3], const double (&n5)[3], const double (&n6)[3]);


// F-07 - CalVolumeHexahedron
// @brief	Calculate volume of Hexahedron
// @return double
double CalVolumeHexahedron(const std::vector<double>& n1, const std::vector<double>& n2, const std::vector<double>& n3, const std::vector<double>& n4, const std::vector<double>& n5, const std::vector<double>& n6, const std::vector<double>& n7, const std::vector<double>& n8);
double CalVolumeHexahedron(const double (&n1)[3], const double (&n2)[3], const double (&n3)[3], const double (&n4)[3], const double (&n5)[3], const double (&n6)[3], const double (&n7)[3], const double (&n8)[3]);



}
}


#endif /* AREA_HPP_ */
