/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Area.cpp
 *
 *  Created on: Nov 10, 2015
 *      Author: minkwan
 */

#include <limits>

#include "./MATH/Area.hpp"
#include "./MATH/Vector.hpp"



using namespace std;
namespace OP2A{
namespace MATH{


// F-01 - CalLength
// @brief	Calculate the length between two point / Calculate size of vector (n1:start, n2 :end)
// @return double
double CalLength(const std::vector<double>& n1, const std::vector<double>& n2)
{
	int N = n1.size();

	if (N != n2.size())
	{
		Common::ExceptionGeneral (FromHere(), "Dimension of X and Y values do not match", "DimensionMismatch:");
	}


	double len	= 0.0;
	for (int i = 0; i <= N-1; i++)	len	+= pow(n1[i] - n2[i], 2.0);

	return (sqrt(len));
}


double CalLength(const double (&n1)[3], const double (&n2)[3])
{
	double len	= 0.0;
	for (int i = 0; i <= 2; i++)	len	+= pow(n1[i] - n2[i], 2.0);

	return (sqrt(len));
}


double CalLength(const double (&n1)[3], const double (&n2)[3], const int& nd)
{
	double len	= 0.0;
	for (int i = 0; i <= nd-1; i++)	len	+= pow(n1[i] - n2[i], 2.0);

	return (sqrt(len));
}

double CalLength(const std::vector<double>& n1)
{
	double len	= 0.0;
	for (int i = 0; i <= n1.size()-1; i++)	len	+= pow(n1[i], 2.0);

	return (sqrt(len));
}

double CalLength(const double (&n1)[3])
{
	double len	= 0.0;
	for (int i = 0; i <= 2; i++)	len	+= pow(n1[i], 2.0);

	return (sqrt(len));
}

double CalLength(const double (&n1)[3], const int& nd)
{
	double len	= 0.0;
	for (int i = 0; i <= nd-1; i++)	len	+= pow(n1[i], 2.0);

	return (sqrt(len));
}



// F-02 - CalAreaTriangle
// @brief	Calculate area of triangle
// @return double
double CalAreaTriangle(const std::vector<double>& n1, const std::vector<double>& n2, const std::vector<double>& n3)
{
	double a, b, c, s;
	double area;

	a = CalLength(n1, n2);
	b = CalLength(n2, n3);
	c = CalLength(n3, n1);

	s = 0.5 * (a + b + c);

	area	= s * (s-a) * (s-b) * (s-c);
	if (area < 0.0)
	{
		Common::ExceptionGeneral (FromHere(), "Negative value in the calculation of triangle area", "NegativeValue:");
	}

	return (sqrt(area));
}


double CalAreaTriangle(const double (&n1)[3], const double (&n2)[3], const double (&n3)[3])
{
	double a, b, c, s;
	double area;

	a = CalLength(n1, n2);
	b = CalLength(n2, n3);
	c = CalLength(n3, n1);

	s = 0.5 * (a + b + c);

	area	= s * (s-a) * (s-b) * (s-c);
	if (area < 0.0)
	{
		Common::ExceptionGeneral (FromHere(), "Negative value in the calculation of triangle area", "NegativeValue:");
	}

	return (sqrt(area));
}

double CalAreaTriangle(const double (&n1)[3], const double (&n2)[3], const double (&n3)[3], const int& nd)
{
	double a, b, c, s;
	double area;

	a = CalLength(n1, n2, nd);
	b = CalLength(n2, n3, nd);
	c = CalLength(n3, n1, nd);

	s = 0.5 * (a + b + c);

	area	= s * (s-a) * (s-b) * (s-c);
	if (area < 0.0)
	{
		Common::ExceptionGeneral (FromHere(), "Negative value in the calculation of triangle area", "NegativeValue:");
	}

	return (sqrt(area));
}



// F-03 - CalAreaQuadrilateral
// @brief	Calculate area of quadrilateral
// @return double
double CalAreaQuadrilateral(const std::vector<double>& n1, const std::vector<double>& n2,  const std::vector<double>& n3, const std::vector<double>& n4)
{
	double s1, s2;

	s1 = CalAreaTriangle(n1, n2, n3);
	s2 = CalAreaTriangle(n2, n3, n4);

	return (s1 + s2);
}

double CalAreaQuadrilateral(const double (&n1)[3], const double (&n2)[3], const double (&n3)[3], const double (&n4)[3])
{
	double s1, s2;

	s1 = CalAreaTriangle(n1, n2, n3);
	s2 = CalAreaTriangle(n2, n3, n4);

	return (s1 + s2);
}

double CalAreaQuadrilateral(const double (&n1)[3], const double (&n2)[3], const double (&n3)[3], const double (&n4)[3], const int& nd)
{
	double s1, s2;

	s1 = CalAreaTriangle(n1, n2, n3, nd);
	s2 = CalAreaTriangle(n2, n3, n4, nd);

	return (s1 + s2);
}



// F-04 - CalVolumeTetrahedron
// @brief	Calculate volume of tetrahedron
// @return double
double CalVolumeTetrahedron(const std::vector<double>& n1, const std::vector<double>& n2,  const std::vector<double>& n3, const std::vector<double>& n4)
{
	double vol;
	VECTOR A(n4, n1);
	VECTOR B(n4, n2);
	VECTOR C(n4, n3);

	VECTOR TEMP1	= VectorCrossProduct(B, C);
	vol		= VectorDotProduct(A, TEMP1);
	vol		= fabs(vol) / 6.0;

	if (vol	!= vol)
	{
		Common::ExceptionGeneral (FromHere(), "NaN value for Tetrahedron volume",  "NaNValue:");
	}

	if (vol == numeric_limits<double>::infinity())
	{
		Common::ExceptionGeneral (FromHere(), "Inifnite Value for Tetrahedron volume", "InfValue");
	}

	return (vol);
}


double CalVolumeTetrahedron(const double (&n1)[3], const double (&n2)[3], const double (&n3)[3], const double (&n4)[3])
{
	double vol;
	VECTOR A(n4, n1);
	VECTOR B(n4, n2);
	VECTOR C(n4, n3);

	VECTOR TEMP1	= VectorCrossProduct(B, C);
	vol		= VectorDotProduct(A, TEMP1);
	vol		= fabs(vol) / 6.0;

	if (vol	!= vol)
	{
		Common::ExceptionGeneral (FromHere(), "NaN value for Tetrahedron volume",  "NaNValue:");
	}

	if (vol == numeric_limits<double>::infinity())
	{
		Common::ExceptionGeneral (FromHere(), "Inifnite Value for Tetrahedron volume", "InfValue");
	}

	return (vol);
}



// F-05 - CalVolumePyramid
// @brief	Calculate volume of pyramid
// @return double
double CalVolumePyramid(const std::vector<double>& n1, const std::vector<double>& n2,  const std::vector<double>& n3, const std::vector<double>& n4, const std::vector<double>& n5)
{
	int i;
	double volume;
	std::vector<double> n6(3, 0.0);


	for (i = 0; i <= 2; i++)	n6[i] = 0.25 * (n1[i] + n2[i] + n3[i] + n4[i]);


	volume = CalVolumeTetrahedron(n1, n2, n6, n5);
	volume += CalVolumeTetrahedron(n2, n3, n6, n5);
	volume += CalVolumeTetrahedron(n3, n4, n6, n5);
	volume += CalVolumeTetrahedron(n4, n1, n6, n5);

	if (volume	!= volume)
	{
		Common::ExceptionGeneral (FromHere(), "NaN value for Pyramid volume",  "NaNValue:");
	}

	if (volume == numeric_limits<double>::infinity())
	{
		Common::ExceptionGeneral (FromHere(), "Inifnite Value for Pyramid volume", "InfValue");
	}

	return (volume);
}

double CalVolumePyramid(const double (&n1)[3], const double (&n2)[3], const double (&n3)[3], const double (&n4)[3], const double (&n5)[3])
{
	int i;
	double volume;
	double n6[3];


	for (i = 0; i <= 2; i++)
	{
		n6[i] = 0.25 * (n1[i] + n2[i] + n3[i] + n4[i]);
	}


	volume = CalVolumeTetrahedron(n1, n2, n6, n5);
	volume += CalVolumeTetrahedron(n2, n3, n6, n5);
	volume += CalVolumeTetrahedron(n3, n4, n6, n5);
	volume += CalVolumeTetrahedron(n4, n1, n6, n5);


	if (volume	!= volume)
	{
		Common::ExceptionGeneral (FromHere(), "NaN value for Pyramid volume",  "NaNValue:");
	}

	if (volume == numeric_limits<double>::infinity())
	{
		Common::ExceptionGeneral (FromHere(), "Inifnite Value for Pyramid volume", "InfValue");
	}

	return (volume);
}


// F-06 - CalVolumeWedge
// @brief	Calculate volume of wedge
// @return double
double CalVolumeWedge(const std::vector<double>& n1, const std::vector<double>& n2, const std::vector<double>& n3, const std::vector<double>& n4, const std::vector<double>& n5, const std::vector<double>& n6)
{
	int i;
	std::vector<double> n7(3, 0.0);

	double volume;

	for (i = 0; i <= 2; i++)	n7[i] = (n1[i] + n2[i] + n3[i] + n4[i] + n5[i] + n6[i]) / 6.0;

	volume = CalVolumePyramid(n1, n4, n5, n2, n7);
	volume += CalVolumePyramid(n2, n3, n6, n3, n7);
	volume += CalVolumePyramid(n1, n3, n6, n4, n7);
	volume += CalVolumeTetrahedron(n1, n2, n3, n7);
	volume += CalVolumeTetrahedron(n4, n6, n5, n7);

	if (volume	!= volume)
	{
		Common::ExceptionGeneral (FromHere(), "NaN value for Wedge volume",  "NaNValue:");
	}

	if (volume == numeric_limits<double>::infinity())
	{
		Common::ExceptionGeneral (FromHere(), "Inifnite Value for Wedge volume", "InfValue");
	}

	return (volume);
}


double CalVolumeWedge(const double (&n1)[3], const double (&n2)[3], const double (&n3)[3], const double (&n4)[3], const double (&n5)[3], const double (&n6)[3])
{
	int i;
	double n7[3];
	double volume;

	for (i = 0; i <= 2; i++)
	{
		n7[i] = (n1[i] + n2[i] + n3[i] + n4[i] + n5[i] + n6[i]) / 6.0;
	}


	volume = CalVolumePyramid(n1, n4, n5, n2, n7);
	volume += CalVolumePyramid(n2, n3, n6, n3, n7);
	volume += CalVolumePyramid(n1, n3, n6, n4, n7);
	volume += CalVolumeTetrahedron(n1, n2, n3, n7);
	volume += CalVolumeTetrahedron(n4, n6, n5, n7);


	if (volume	!= volume)
	{
		Common::ExceptionGeneral (FromHere(), "NaN value for Wedge volume",  "NaNValue:");
	}

	if (volume == numeric_limits<double>::infinity())
	{
		Common::ExceptionGeneral (FromHere(), "Inifnite Value for Wedge volume", "InfValue");
	}

	return (volume);
}


double CalVolumeHexahedron(const std::vector<double>& n1, const std::vector<double>& n2, const std::vector<double>& n3, const std::vector<double>& n4, const std::vector<double>& n5, const std::vector<double>& n6, const std::vector<double>& n7, const std::vector<double>& n8)
{
	int i;
	std::vector<double> n9(3, 0.0);
	double volume;

	for (i = 0; i <= 2; i++)	n9[i] = 0.125 * (n1[i] + n2[i] + n3[i] + n4[i] + n5[i] + n6[i] + n7[i] + n8[i]);


	volume = CalVolumePyramid(n1, n2, n3, n4, n9);
	volume += CalVolumePyramid(n5, n8, n7, n6, n9);
	volume += CalVolumePyramid(n1, n5, n6, n2, n9);
	volume += CalVolumePyramid(n3, n7, n8, n4, n9);
	volume += CalVolumePyramid(n2, n6, n7, n3, n9);
	volume += CalVolumePyramid(n1, n4, n8, n5, n9);

	if (volume	!= volume)
	{
		Common::ExceptionGeneral (FromHere(), "NaN value for Wedge volume",  "NaNValue:");
	}

	if (volume == numeric_limits<double>::infinity())
	{
		Common::ExceptionGeneral (FromHere(), "Inifnite Value for Wedge volume", "InfValue");
	}

	return (volume);
}


double CalVolumeHexahedron(const double (&n1)[3], const double (&n2)[3], const double (&n3)[3], const double (&n4)[3], const double (&n5)[3], const double (&n6)[3], const double (&n7)[3], const double (&n8)[3])
{
	int i;
	double n9[3];
	double volume;

	for (i = 0; i <= 2; i++)	n9[i] = 0.125 * (n1[i] + n2[i] + n3[i] + n4[i] + n5[i] + n6[i] + n7[i] + n8[i]);


	volume = CalVolumePyramid(n1, n2, n3, n4, n9);
	volume += CalVolumePyramid(n5, n8, n7, n6, n9);
	volume += CalVolumePyramid(n1, n5, n6, n2, n9);
	volume += CalVolumePyramid(n3, n7, n8, n4, n9);
	volume += CalVolumePyramid(n2, n6, n7, n3, n9);
	volume += CalVolumePyramid(n1, n4, n8, n5, n9);

	if (volume	!= volume)
	{
		Common::ExceptionGeneral (FromHere(), "NaN value for Wedge volume",  "NaNValue:");
	}

	if (volume == numeric_limits<double>::infinity())
	{
		Common::ExceptionGeneral (FromHere(), "Inifnite Value for Wedge volume", "InfValue");
	}

	return (volume);
}


}
}
