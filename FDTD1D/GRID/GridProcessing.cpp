/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GridProcessing.cpp
 *
 *  Created on: Nov 9, 2015
 *      Author: minkwan
 */

#include <omp.h>
#include <limits>

#include "Grid.hpp"
#include "GeometryCommon.hpp"

#include "./COMMON/TypeConversion.hpp"

#include "./MATH/Area.hpp"
#include "./MATH/Vector.hpp"


namespace OP2A
{

//	1. Node data
void GridProcessingGeometryNode(OP2A::GRID::Configuration&	config, std::vector<GRID::Node>& nodes)
{

	if (config.gridFactor != 1.0)
	{
#pragma ivdep
		for (int n = 1; n <= config.NCM; n++)
		{
			for (int k = 0; k <= config.DIM-1; k++)
			{
				nodes[n].geo.x[k]	/= config.gridFactor;
			}
		}
	}

	if (config.isAxisymmetric == true)
	{
#pragma ivdep
		for (int n = 1; n <= config.NCM; n++)
		{
			nodes[n].geo.x[1]	+= OP2A_GRID_AXISSYMMETRIC_ADD;
		}
	}
}



// 2. Face Data
void GridProcessingGeometryFace(OP2A::GRID::Configuration&	config, std::vector<GRID::Face>& faces)
{
#pragma ivdep
	for (int f = 1; f <= config.NFM; f++)
	{
		// 1. Calculate location of face center
		for (int k = 0; k <= config.DIM-1; k++)
		{
			faces[f].geo.x[k]	= 0.0;	// Initialize value
			for (int n = 0; n <= faces[f].conn.numNodes-1; n++)
			{
				faces[f].geo.x[k]	+= faces[f].conn.listNodes[n]->geo.x[k];
			}

			faces[f].geo.x[k]	/= faces[f].conn.numNodes;

			if (faces[f].geo.x[k] != faces[f].geo.x[k])
			{
				Common::ExceptionGeneral(FromHere(), "NaN value for face center location", "NaNValue:");
			}

			if (fabs(faces[f].geo.x[k]) == numeric_limits<double>::infinity())
			{
				Common::ExceptionGeneral(FromHere(), "Infinite value for face center location", "InfValue:");
			}
		}


		// 2. Calculate Area
		switch (faces[f].geo.type)
		{
		case GRID::f_point:
			faces[f].geo.S	= 0.0;
			break;

		case GRID::f_line:
			faces[f].geo.S 	= MATH::CalLength(faces[f].conn.listNodes[0]->geo.x, faces[f].conn.listNodes[1]->geo.x);
			break;

		case GRID::f_triangle:
			faces[f].geo.S 	= MATH::CalAreaTriangle(faces[f].conn.listNodes[0]->geo.x, faces[f].conn.listNodes[1]->geo.x, faces[f].conn.listNodes[2]->geo.x);
			break;

		case GRID::f_quadrilateral:
			faces[f].geo.S 	= MATH::CalAreaQuadrilateral(faces[f].conn.listNodes[0]->geo.x, faces[f].conn.listNodes[1]->geo.x, faces[f].conn.listNodes[2]->geo.x, faces[f].conn.listNodes[3]->geo.x);
			break;
		}


		// 3. Find directional vectors
		MATH::VECTOR	face_normal;
		MATH::VECTOR 	face_tan;


		if (faces[f].geo.type == GRID::f_point)
		{
			faces[f].geo.n[0][0]	= 0.0;
			faces[f].geo.n[0][1]	= 0.0;

			faces[f].geo.n[1][0]	= 0.0;
			faces[f].geo.n[1][1]	= 0.0;
		}
		else if (faces[f].geo.type == GRID::f_line)
		{
			MATH::VECTOR	n12(faces[f].conn.listNodes[0]->geo.x, faces[f].conn.listNodes[1]->geo.x);
			n12.normalize();

			face_normal(1) = n12(2);
			face_normal(2) = -n12(1);

			faces[f].geo.n[0][0]	= face_normal(1);
			faces[f].geo.n[0][1]	= face_normal(2);

			faces[f].geo.n[1][0]	= n12(1);
			faces[f].geo.n[1][1]	= n12(2);
		}
		else if(faces[f].geo.type == GRID::f_triangle)
		{
			MATH::VECTOR X1(faces[f].conn.listNodes[1]->geo.x, faces[f].conn.listNodes[0]->geo.x);
			MATH::VECTOR X2(faces[f].conn.listNodes[2]->geo.x, faces[f].conn.listNodes[0]->geo.x);

			face_normal	= VectorCrossProduct(X1, X2);

			face_normal.normalize();
			X1.normalize();

			face_tan	= VectorCrossProduct(face_normal, X1);
			face_tan.normalize();

			faces[f].geo.n[0][0]	=  face_normal(1);
			faces[f].geo.n[0][1]	=  face_normal(2);
			faces[f].geo.n[0][2]	=  face_normal(3);

			faces[f].geo.n[1][0]	=  X1(1);
			faces[f].geo.n[1][1]	=  X1(2);
			faces[f].geo.n[1][2]	=  X1(3);

			faces[f].geo.n[2][0]	=  face_tan(1);
			faces[f].geo.n[2][1]	=  face_tan(2);
			faces[f].geo.n[2][2]	=  face_tan(3);
		}
		else if(faces[f].geo.type == GRID::f_quadrilateral)
		{
			MATH::VECTOR V1(faces[f].conn.listNodes[1]->geo.x, faces[f].conn.listNodes[0]->geo.x);
			MATH::VECTOR V2(faces[f].conn.listNodes[2]->geo.x, faces[f].conn.listNodes[0]->geo.x);
			MATH::VECTOR V3(faces[f].conn.listNodes[3]->geo.x, faces[f].conn.listNodes[0]->geo.x);

			face_normal	= NormalFromThreePoint(V1, V2, V3);
			face_normal.normalize();

			V2.normalize();

			face_tan	= VectorCrossProduct(face_normal, V2);
			face_tan.normalize();

			faces[f].geo.n[0][0]	=  face_normal(1);
			faces[f].geo.n[0][1]	=  face_normal(2);
			faces[f].geo.n[0][2]	=  face_normal(3);

			faces[f].geo.n[1][0]	=  V2(1);
			faces[f].geo.n[1][1]	=  V2(2);
			faces[f].geo.n[1][2]	=  V2(3);

			faces[f].geo.n[2][0]	=  face_tan(1);
			faces[f].geo.n[2][1]	=  face_tan(2);
			faces[f].geo.n[2][2]	=  face_tan(3);
		}
		else
		{
			Common::ExceptionGeneral (FromHere(), "Selected Face type is not supported", "NoSuchValue");
		}
	}
}


void GridProcessingGeometryFace(OP2A::GRID::Configuration&	config, std::vector<GRID::FaceCart>& faces)
{
#pragma ivdep
	for (int f = 1; f <= config.NFM; f++)
	{
		// 1. Calculate location of face center
		for (int k = 0; k <= config.DIM-1; k++)
		{
			faces[f].geo.x[k]	= 0.0;	// Initialize value
			for (int n = 0; n <= faces[f].conn.numNodes-1; n++)
			{
				faces[f].geo.x[k]	+= faces[f].conn.listNodes[n]->geo.x[k];
			}

			faces[f].geo.x[k]	/= faces[f].conn.numNodes;

			if (faces[f].geo.x[k] != faces[f].geo.x[k])
			{
				Common::ExceptionGeneral(FromHere(), "NaN value for face center location", "NaNValue:");
			}

			if (fabs(faces[f].geo.x[k]) == numeric_limits<double>::infinity())
			{
				Common::ExceptionGeneral(FromHere(), "Infinite value for face center location", "InfValue:");
			}
		}


		// 2. Calculate Area
		switch (faces[f].geo.type)
		{
		case GRID::f_point:
			faces[f].geo.S	= 0.0;
			break;

		case GRID::f_line:
			faces[f].geo.S 	= MATH::CalLength(faces[f].conn.listNodes[0]->geo.x, faces[f].conn.listNodes[1]->geo.x);
			break;

		case GRID::f_quadrilateral:
			faces[f].geo.S 	= MATH::CalAreaQuadrilateral(faces[f].conn.listNodes[0]->geo.x, faces[f].conn.listNodes[1]->geo.x, faces[f].conn.listNodes[2]->geo.x, faces[f].conn.listNodes[3]->geo.x);
			break;
		}


		// 3. Find directional vectors
		MATH::VECTOR	face_normal;
		MATH::VECTOR 	face_tan;


		if (faces[f].geo.type == GRID::f_point)
		{
			faces[f].geo.n[0][0]	= 0.0;
			faces[f].geo.n[0][1]	= 0.0;

			faces[f].geo.n[1][0]	= 0.0;
			faces[f].geo.n[1][1]	= 0.0;
		}
		else if (faces[f].geo.type == GRID::f_line)
		{
			MATH::VECTOR	n12(faces[f].conn.listNodes[0]->geo.x, faces[f].conn.listNodes[1]->geo.x);
			n12.normalize();

			face_normal(1) = n12(2);
			face_normal(2) = -n12(1);

			faces[f].geo.n[0][0]	= face_normal(1);
			faces[f].geo.n[0][1]	= face_normal(2);

			faces[f].geo.n[1][0]	= n12(1);
			faces[f].geo.n[1][1]	= n12(2);
		}
		else if(faces[f].geo.type == GRID::f_quadrilateral)
		{
			MATH::VECTOR V1(faces[f].conn.listNodes[1]->geo.x, faces[f].conn.listNodes[0]->geo.x);
			MATH::VECTOR V2(faces[f].conn.listNodes[2]->geo.x, faces[f].conn.listNodes[0]->geo.x);
			MATH::VECTOR V3(faces[f].conn.listNodes[3]->geo.x, faces[f].conn.listNodes[0]->geo.x);

			face_normal	= NormalFromThreePoint(V1, V2, V3);
			face_normal.normalize();

			V2.normalize();

			face_tan	= VectorCrossProduct(face_normal, V2);
			face_tan.normalize();

			faces[f].geo.n[0][0]	=  face_normal(1);
			faces[f].geo.n[0][1]	=  face_normal(2);
			faces[f].geo.n[0][2]	=  face_normal(3);

			faces[f].geo.n[1][0]	=  V2(1);
			faces[f].geo.n[1][1]	=  V2(2);
			faces[f].geo.n[1][2]	=  V2(3);

			faces[f].geo.n[2][0]	=  face_tan(1);
			faces[f].geo.n[2][1]	=  face_tan(2);
			faces[f].geo.n[2][2]	=  face_tan(3);
		}
		else
		{
			Common::ExceptionGeneral (FromHere(), "Selected Face type is not supported", "NoSuchValue");
		}
	}
}




// 3. Cell Data
void GridProcessingGeometryCell(OP2A::GRID::Configuration&	config, std::vector<GRID::Cell>& cells)
{
#pragma ivdep
	for (int c = 1; c <= config.NCM; c++)
	{
		// 1. Calculate location of face center
		for (int k = 0; k <= config.DIM-1; k++)
		{
			cells[c].geo.x[k]	= 0.0;	// Initialize value
			for (int n = 0; n <= cells[c].conn.numNodes-1; n++)
			{
				cells[c].geo.x[k]	+= cells[c].conn.listNodes[n]->geo.x[k];
			}

			cells[c].geo.x[k]	/= cells[c].conn.numNodes;

			if (cells[c].geo.x[k] != cells[c].geo.x[k])
			{
				Common::ExceptionGeneral(FromHere(), "NaN value for cell center location", "NaNValue:");
			}

			if (fabs(cells[c].geo.x[k]) == numeric_limits<double>::infinity())
			{
				Common::ExceptionGeneral(FromHere(), "Infinite cell for face center location", "InfValue:");
			}
		}


		// 2. Calculate Area
		switch (cells[c].geo.type)
		{
		case GRID::c_line:
			cells[c].geo.S 	= MATH::CalLength(cells[c].conn.listNodes[0]->geo.x, cells[c].conn.listNodes[1]->geo.x);
			break;

		case GRID::c_triangle:
			cells[c].geo.S	= MATH::CalAreaTriangle(cells[c].conn.listNodes[0]->geo.x, cells[c].conn.listNodes[1]->geo.x, cells[c].conn.listNodes[2]->geo.x);
			break;

		case GRID::c_tetrahedron:
			cells[c].geo.S	= MATH::CalVolumeTetrahedron(cells[c].conn.listNodes[0]->geo.x, cells[c].conn.listNodes[1]->geo.x, cells[c].conn.listNodes[2]->geo.x, cells[c].conn.listNodes[3]->geo.x);
			break;

		case GRID::c_quadrilateral:
			cells[c].geo.S	= MATH::CalAreaQuadrilateral(cells[c].conn.listNodes[0]->geo.x, cells[c].conn.listNodes[1]->geo.x, cells[c].conn.listNodes[2]->geo.x, cells[c].conn.listNodes[3]->geo.x);
			break;

		case GRID::c_hexahedron:
			cells[c].geo.S	= MATH::CalVolumeHexahedron(cells[c].conn.listNodes[0]->geo.x, cells[c].conn.listNodes[1]->geo.x, cells[c].conn.listNodes[2]->geo.x, cells[c].conn.listNodes[3]->geo.x, cells[c].conn.listNodes[4]->geo.x, cells[c].conn.listNodes[5]->geo.x, cells[c].conn.listNodes[6]->geo.x, cells[c].conn.listNodes[7]->geo.x);
			break;

		case GRID::c_pyramid:
			cells[c].geo.S	= MATH::CalVolumePyramid(cells[c].conn.listNodes[0]->geo.x, cells[c].conn.listNodes[1]->geo.x, cells[c].conn.listNodes[2]->geo.x, cells[c].conn.listNodes[3]->geo.x, cells[c].conn.listNodes[4]->geo.x);
			break;

		case GRID::c_wedge:
			cells[c].geo.S	= MATH::CalVolumeWedge(cells[c].conn.listNodes[0]->geo.x, cells[c].conn.listNodes[1]->geo.x, cells[c].conn.listNodes[2]->geo.x, cells[c].conn.listNodes[3]->geo.x, cells[c].conn.listNodes[4]->geo.x, cells[c].conn.listNodes[5]->geo.x);
			break;
		}

		// 3. Characteristic length
		std::vector <double> Xf1(config.DIM, 0.0);
		std::vector <double> Xf2(config.DIM, 0.0);
		std::vector <double> Xf3(config.DIM, 0.0);
		std::vector <double> Xf4(config.DIM, 0.0);

		double aux;
		double length;

		switch (cells[c].geo.type)
		{
		case GRID::c_line:
			cells[c].geo.characteristicLength	= cells[c].geo.S;
			break;

		case GRID::c_triangle:
			cells[c].geo.characteristicLength	= sqrt(cells[c].geo.S);
			break;

		case GRID::c_tetrahedron:
			for (int k = 0; k <= config.DIM-1; k++)
			{
				Xf1[k]	= (cells[c].conn.listNodes[0]->geo.x[k] + cells[c].conn.listNodes[1]->geo.x[k] + cells[c].conn.listNodes[2]->geo.x[k]) / 3.0;
				Xf2[k]	= (cells[c].conn.listNodes[0]->geo.x[k] + cells[c].conn.listNodes[1]->geo.x[k] + cells[c].conn.listNodes[3]->geo.x[k]) / 3.0;
				Xf3[k]	= (cells[c].conn.listNodes[1]->geo.x[k] + cells[c].conn.listNodes[2]->geo.x[k] + cells[c].conn.listNodes[3]->geo.x[k]) / 3.0;
				Xf4[k]	= (cells[c].conn.listNodes[0]->geo.x[k] + cells[c].conn.listNodes[3]->geo.x[k] + cells[c].conn.listNodes[2]->geo.x[k]) / 3.0;
			}

			aux	= 0.0;
			for (int k = 0; k <=config.DIM-1; k++)
			{
				aux += pow(cells[c].geo.x[k] - Xf1[k], 2.0);
			}

			length	= sqrt(aux);

			aux = 0.0;
			for (int k = 0; k <= config.DIM-1; k++)
			{
				aux += pow(cells[c].geo.x[k] - Xf2[k], 2.0);
			}
			aux 	= sqrt(aux);
			length	= fmin(length, aux);

			aux = 0.0;
			for (int k = 0; k <= config.DIM-1; k++)
			{
				aux += pow(cells[c].geo.x[k] - Xf3[k], 2.0);
			}
			aux 	= sqrt(aux);
			length	= fmin(length, aux);


			aux = 0.0;
			for (int k = 0; k <= config.DIM-1; k++)
			{
				aux += pow(cells[c].geo.x[k] - Xf4[k], 2.0);
			}
			aux 	= sqrt(aux);
			length	= fmin(length, aux);

			cells[c].geo.characteristicLength = 2.0* length;
			break;

		case GRID::c_quadrilateral:
			for (int k = 0; k <= config.DIM-1; k++)
			{
				Xf1[k]	= cells[c].conn.listNodes[1]->geo.x[k] - cells[c].conn.listNodes[0]->geo.x[k];
				Xf2[k]	= cells[c].conn.listNodes[3]->geo.x[k] - cells[c].conn.listNodes[0]->geo.x[k];
			}

			length	= 0.0;	aux		= 0.0;
			for (int k = 0; k <= config.DIM-1; k++)
			{
				length	+= pow(Xf1[k], 2.0);
				aux		+= pow(Xf2[k], 2.0);
			}

			length	= fmin(length, aux);
			cells[c].geo.characteristicLength= sqrt(length);
			break;

		case GRID::c_hexahedron:
			for (int k = 0; k <= config.DIM-1; k++)
			{
				Xf1[k]	= cells[c].conn.listNodes[1]->geo.x[k] - cells[c].conn.listNodes[0]->geo.x[k];
				Xf2[k]	= cells[c].conn.listNodes[2]->geo.x[k] - cells[c].conn.listNodes[0]->geo.x[k];
				Xf3[k]	= cells[c].conn.listNodes[3]->geo.x[k] - cells[c].conn.listNodes[0]->geo.x[k];
			}

			length	= 0.0;	aux		= 0.0;
			for (int k = 0; k <= config.DIM-1; k++)
			{
				length	+= pow(Xf1[k], 2.0);
				aux		+= pow(Xf2[k], 2.0);
			}
			length	= fmin(length, aux);

			aux = 0.0;
			for (int k = 0; k <= config.DIM-1; k++)
			{
				aux += pow(Xf3[k], 2.0);
			}
			length	= fmin(length, aux);

			cells[c].geo.characteristicLength = sqrt(length);
			break;

		case GRID::c_pyramid:
			length = pow(cells[c].geo.S, 1.0/3.0);
			cells[c].geo.characteristicLength = sqrt(length);
			break;

		case GRID::c_wedge:
			for (int k = 0; k <= config.DIM-1; k++)
			{
				Xf1[k]	= cells[c].conn.listNodes[1]->geo.x[k] - cells[c].conn.listNodes[0]->geo.x[k];
				Xf2[k]	= cells[c].conn.listNodes[2]->geo.x[k] - cells[c].conn.listNodes[0]->geo.x[k];
				Xf3[k]	= cells[c].conn.listNodes[3]->geo.x[k] - cells[c].conn.listNodes[0]->geo.x[k];
			}

			aux = 	pow(0.5*(Xf1[1]*Xf2[2] - Xf1[2]*Xf2[1]), 2.0);
			aux	+= 	pow(-0.5*(Xf1[0]*Xf2[2] - Xf1[2]*Xf2[0]), 2.0);
			aux	+=	pow(0.5*(Xf1[0]*Xf2[1] - Xf1[1]*Xf2[0]), 2.0);
			length	= pow(aux, 0.25);

			aux = 0.0;
			for (int k = 0; k <= config.DIM-1; k++)
			{
				aux += pow(Xf3[k], 2.0);
			}
			aux = sqrt(aux);

			length	= fmin(length, aux);
			cells[c].geo.characteristicLength = length;
			break;
		}
	}
}


// 4. Cell Data
void GridProcessingGeometryCellCart(OP2A::GRID::Configuration&	config, std::vector<GRID::CellCart>& cells)
{
	if (config.DIM == 2)
	{
#pragma ivdep
		for (int c = 1; c <= config.NCM; c++)
		{
			cells[c].geo.type = GRID::c_quadrilateral;
		}
	}
	else if (config.DIM == 3)
	{
#pragma ivdep
		for (int c = 1; c <= config.NCM; c++)
		{
			cells[c].geo.type = GRID::c_hexahedron;
		}
	}


#pragma ivdep
	for (int c = 1; c <= config.NCM; c++)
	{
		// 1. Calculate location of face center
		for (int k = 0; k <= config.DIM-1; k++)
		{
			cells[c].geo.x[k]	= 0.0;	// Initialize value
			for (int n = 0; n <= cells[c].conn.numNeighborCells-1; n++)
			{
				cells[c].geo.x[k]	+= cells[c].conn.listNodes[n]->geo.x[k];
			}

			cells[c].geo.x[k]	/= cells[c].conn.numNodes;

			if (cells[c].geo.x[k] != cells[c].geo.x[k])
			{
				Common::ExceptionGeneral(FromHere(), "NaN value for cell center location", "NaNValue:");
			}

			if (fabs(cells[c].geo.x[k]) == numeric_limits<double>::infinity())
			{
				Common::ExceptionGeneral(FromHere(), "Infinite cell for face center location", "InfValue:");
			}
		}


		// 2. Calculate Area
		switch (cells[c].geo.type)
		{
		case GRID::c_line:
			cells[c].geo.S 	= MATH::CalLength(cells[c].conn.listNodes[0]->geo.x, cells[c].conn.listNodes[1]->geo.x);
			break;

		case GRID::c_quadrilateral:
			cells[c].geo.S	= MATH::CalAreaQuadrilateral(cells[c].conn.listNodes[0]->geo.x, cells[c].conn.listNodes[1]->geo.x, cells[c].conn.listNodes[2]->geo.x, cells[c].conn.listNodes[3]->geo.x);
			break;

		case GRID::c_hexahedron:
			cells[c].geo.S	= MATH::CalVolumeHexahedron(cells[c].conn.listNodes[0]->geo.x, cells[c].conn.listNodes[1]->geo.x, cells[c].conn.listNodes[2]->geo.x, cells[c].conn.listNodes[3]->geo.x, cells[c].conn.listNodes[4]->geo.x, cells[c].conn.listNodes[5]->geo.x, cells[c].conn.listNodes[6]->geo.x, cells[c].conn.listNodes[7]->geo.x);
			break;
		}
	}
}


// 5. Ghost Data
void GridProcessingGeometryGhost(OP2A::GRID::Configuration&	config, std::vector<GRID::Face>& faces, std::vector<GRID::Cell>& ghosts)
{
	int counter = 0;

	for (int f = 1; f <= config.NFM; f++)
	{
		if (faces[f].conn.cr[0]	== NULL)
		{
			counter++;
			faces[f].conn.cr[0]	= &ghosts[counter];

			ghosts[counter].geo.ID	 = -counter;
			ghosts[counter].geo.type = GRID::c_ghost;

			for (int k = 0; k <= config.DIM-1; k++)
			{
				ghosts[counter].geo.x[k] = 2.0*faces[f].geo.x[k] - faces[f].conn.cl[0]->geo.x[k];
			}

			ghosts[counter].geo.S 						= faces[f].geo.S;
			ghosts[counter].geo.characteristicLength	= faces[f].geo.S;
			ghosts[counter].geo.BC 						= faces[f].geo.BC;


			ghosts[counter].conn.numFaces	= 1;
			ghosts[counter].conn.listFaces.resize(ghosts[counter].conn.numFaces);
			ghosts[counter].conn.listFaces[0] = &faces[f];

			ghosts[counter].conn.numNodes	= faces[f].conn.numNodes;
			ghosts[counter].conn.listNodes	= faces[f].conn.listNodes;
		}
		else if (faces[f].conn.cl[0]	== NULL)
		{
			counter++;
			faces[f].conn.cl[0]	= faces[f].conn.cr[0];
			faces[f].conn.cr[0]	= &ghosts[counter];

			for (int k1 = 0; k1 <= config.DIM-1; k1++)
			{
				for (int k2 = 0; k2 <= config.DIM-1; k2++)
				{
					faces[f].geo.n[k1][k2]	= -faces[f].geo.n[k1][k2];
				}
			}

			ghosts[counter].geo.ID	= -counter;
			ghosts[counter].geo.type = GRID::c_ghost;



			for (int k = 0; k <= config.DIM-1; k++)
			{
				ghosts[counter].geo.x[k] = 2.0*faces[f].geo.x[k] - faces[f].conn.cl[0]->geo.x[k];
			}

			ghosts[counter].geo.S 						= faces[f].geo.S;
			ghosts[counter].geo.characteristicLength	= faces[f].geo.S;
			ghosts[counter].geo.BC 						= faces[f].geo.BC;


			ghosts[counter].conn.numFaces	= 1;
			ghosts[counter].conn.listFaces.resize(ghosts[counter].conn.numFaces);
			ghosts[counter].conn.listFaces[0] = &faces[f];

			ghosts[counter].conn.numNodes	= faces[f].conn.numNodes;
			ghosts[counter].conn.listNodes	= faces[f].conn.listNodes;
		}
	}


	if (counter != config.NGM)
	{
		Common::ExceptionGeneral (FromHere(), "PROBLEM IN the creation of ghost-Cell DATA. TOTAL NUMBER OF created ghost-Cell DATA DOES NOT MATHCH WITH MESH INFOMATION DATA", "GridDataMismatch:");
	}
}


void GridProcessingGeometryGhostCart(OP2A::GRID::Configuration&	config, std::vector<GRID::FaceCart>& faces, std::vector<GRID::CellCart>& ghosts)
{
	int counter = 0;

	for (int f = 1; f <= config.NFM; f++)
	{
		if (faces[f].conn.cr[0]	== NULL)
		{
			counter++;
			faces[f].conn.cr[0]	= &ghosts[counter];

			ghosts[counter].geo.ID	 = -counter;
			ghosts[counter].geo.type = GRID::c_ghost;

			for (int k = 0; k <= config.DIM-1; k++)
			{
				ghosts[counter].geo.x[k] = 2.0*faces[f].geo.x[k] - faces[f].conn.cl[0]->geo.x[k];
			}

			ghosts[counter].geo.S 						= faces[f].geo.S;
			ghosts[counter].geo.characteristicLength	= faces[f].geo.S;
			ghosts[counter].geo.BC 						= faces[f].geo.BC;


			ghosts[counter].conn.numFaces	= 1;
			ghosts[counter].conn.listFaces.resize(ghosts[counter].conn.numFaces);
			ghosts[counter].conn.listFaces[0] = &faces[f];

			ghosts[counter].conn.numNodes	= faces[f].conn.numNodes;
			ghosts[counter].conn.listNodes	= faces[f].conn.listNodes;
		}
		else if (faces[f].conn.cl[0]	== NULL)
		{
			counter++;
			faces[f].conn.cl[0]	= faces[f].conn.cr[0];
			faces[f].conn.cr[0]	= &ghosts[counter];

			for (int k1 = 0; k1 <= config.DIM-1; k1++)
			{
				for (int k2 = 0; k2 <= config.DIM-1; k2++)
				{
					faces[f].geo.n[k1][k2]	= -faces[f].geo.n[k1][k2];
				}
			}

			ghosts[counter].geo.ID	= -counter;
			ghosts[counter].geo.type = GRID::c_ghost;



			for (int k = 0; k <= config.DIM-1; k++)
			{
				ghosts[counter].geo.x[k] = 2.0*faces[f].geo.x[k] - faces[f].conn.cl[0]->geo.x[k];
			}

			ghosts[counter].geo.S 						= faces[f].geo.S;
			ghosts[counter].geo.characteristicLength	= faces[f].geo.S;
			ghosts[counter].geo.BC 						= faces[f].geo.BC;


			ghosts[counter].conn.numFaces	= 1;
			ghosts[counter].conn.listFaces.resize(ghosts[counter].conn.numFaces);
			ghosts[counter].conn.listFaces[0] = &faces[f];

			ghosts[counter].conn.numNodes	= faces[f].conn.numNodes;
			ghosts[counter].conn.listNodes	= faces[f].conn.listNodes;
		}
	}


	if (counter != config.NGM)
	{
		Common::ExceptionGeneral (FromHere(), "PROBLEM IN the creation of ghost-Cell DATA. TOTAL NUMBER OF created ghost-Cell DATA DOES NOT MATHCH WITH MESH INFOMATION DATA", "GridDataMismatch:");
	}
}






void GridProcessing(Grid<GRID::Node, GRID::Face, GRID::Cell, GRID::Cell>& grid)
{
	GridProcessingGeometryNode(grid.config, grid.nodes);


}





}

