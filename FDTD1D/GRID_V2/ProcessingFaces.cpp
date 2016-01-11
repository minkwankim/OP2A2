/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ProcessingFaces.cpp
 *
 *  Created on: Jan 6, 2016
 *      Author: minkwan
 */

#include <omp.h>
#include <limits>

#include "Gridv2.hpp"
#include "GridConfig.hpp"

#include "./COMMON/ExceptionGeneral.hpp"
#include "./COMMON/ErrorCode.hpp"
#include "./MATH/Area.hpp"

namespace GRID
{
	void Processing_Face(c_Grid& grid)
	{
#pragma ivdep
		for (int f = 0; f <= grid.Info.NFM-1; f++)
		{
			// 1. Calculate location of face center
			for (int d = 0; d <= grid.Info.DIM-1; d++)
			{
				grid.Data.faces[f].geometry.x[d]	= 0.0;
				int nn	= grid.Data.faces[f].Specialized.N_List.size();

				for (int n = 0; n <= nn-1; n++)
				{
					grid.Data.faces[f].geometry.x[d] += grid.Data.faces[f].Specialized.N_List[n]->geometry.x[d];
				}
				grid.Data.faces[f].geometry.x[d] /= nn;

				if (grid.Data.faces[f].geometry.x[d] != grid.Data.faces[f].geometry.x[d])
				{
					std::ostringstream error_message;
					error_message << "Face ID:" << grid.Data.faces[f].geometry.id << ", Direction:" << d << "  has problem in calculating postiion: NaN value";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NaNValue());
				}

				if (grid.Data.faces[f].geometry.x[d] == numeric_limits<double>::infinity())
				{
					std::ostringstream error_message;
					error_message << "Face ID:" << grid.Data.faces[f].geometry.id << ", Direction:" << d << "  has problem in calculating postiion: Inf value";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::InfValue());
				}
			}


			// 2. Calculate S (Area/ Volume)
			switch (grid.Data.faces[f].geometry.type)
			{
			case f_line:
				grid.Data.faces[f].geometry.S	= OP2A::MATH::CalLength(grid.Data.faces[f].Specialized.N_List[0]->geometry.x,
																		grid.Data.faces[f].Specialized.N_List[1]->geometry.x);
				break;

			case f_triangle:
				grid.Data.faces[f].geometry.S	= OP2A::MATH::CalAreaTriangle(grid.Data.faces[f].Specialized.N_List[0]->geometry.x,
																			grid.Data.faces[f].Specialized.N_List[1]->geometry.x,
																			grid.Data.faces[f].Specialized.N_List[2]->geometry.x);
				break;

			case f_quadrilateral:
				grid.Data.faces[f].geometry.S	= OP2A::MATH::CalAreaQuadrilateral(grid.Data.faces[f].Specialized.N_List[0]->geometry.x,
																				grid.Data.faces[f].Specialized.N_List[1]->geometry.x,
																				grid.Data.faces[f].Specialized.N_List[2]->geometry.x,
																				grid.Data.faces[f].Specialized.N_List[3]->geometry.x);
				break;
			}

			if (grid.Data.faces[f].geometry.S != grid.Data.faces[f].geometry.S)
			{
				std::ostringstream error_message;
				error_message << "Face ID:" << grid.Data.faces[f].geometry.id << " has problem in calculating area: NaN value";
				OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NaNValue());
			}

			if (grid.Data.faces[f].geometry.S == numeric_limits<double>::infinity())
			{
				std::ostringstream error_message;
				error_message << "Face ID:" << grid.Data.faces[f].geometry.id << " has problem in calculating area: Inf value";
				OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::InfValue());
			}

			if (grid.Data.faces[f].geometry.S < 0.0)
			{
				std::ostringstream error_message;
				error_message << "Face ID:" << grid.Data.faces[f].geometry.id << " has problem in calculating area: Negative value";
				OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NegativeValue());
			}


			// 3. Find directional vectors
			int n1, n2, n3, n4;
			double x1, y1, z1;
			double x2, y2, z2;
			double x3, y3, z3;
			double S, length_x1, length_x2;
			double error_ck;

			switch (grid.Data.faces[f].geometry.type)
			{
			case f_line:
				x1	= grid.Data.faces[f].Specialized.N_List[1]->geometry.x[0] - grid.Data.faces[f].Specialized.N_List[0]->geometry.x[0];
				y1	= grid.Data.faces[f].Specialized.N_List[1]->geometry.x[1] - grid.Data.faces[f].Specialized.N_List[0]->geometry.x[1];
				S	= sqrt(x1*x1 + y1*y1);

				grid.Data.faces[f].Specialized.n[0][0]	= y1/S;
				grid.Data.faces[f].Specialized.n[0][1]	= -x1/S;

				grid.Data.faces[f].Specialized.n[1][0]	= -grid.Data.faces[f].Specialized.n[0][1];
				grid.Data.faces[f].Specialized.n[1][1]	=  grid.Data.faces[f].Specialized.n[0][0];

				// ERROR CHECK
				error_ck =  pow(grid.Data.faces[f].Specialized.n[0][0], 2.0);
				error_ck += pow(grid.Data.faces[f].Specialized.n[0][1], 2.0);
				error_ck = sqrt(error_ck);

				if (error_ck != error_ck)
				{
					std::ostringstream error_message;
					error_message << "Face ID:" << grid.Data.faces[f].geometry.id << " has problem in calculating direction vectors: NaN value";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NaNValue());
				}

				if (error_ck == numeric_limits<double>::infinity())
				{
					std::ostringstream error_message;
					error_message << "Face ID:" << grid.Data.faces[f].geometry.id << " has problem in calculating direction vectors: Inf value";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::InfValue());
				}


				if (fabs(error_ck - 1.0) > 1.0e-10)
				{
					std::ostringstream error_message;
					error_message << "Face ID:" << grid.Data.faces[f].geometry.id << " has problem in calculating direction vectors: Non-unit value";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::ExceedLimit());
				}

				break;


			case f_triangle:
				x1	= grid.Data.faces[f].Specialized.N_List[1]->geometry.x[0] - grid.Data.faces[f].Specialized.N_List[0]->geometry.x[0];
				y1	= grid.Data.faces[f].Specialized.N_List[1]->geometry.x[1] - grid.Data.faces[f].Specialized.N_List[0]->geometry.x[1];
				z1	= grid.Data.faces[f].Specialized.N_List[1]->geometry.x[2] - grid.Data.faces[f].Specialized.N_List[0]->geometry.x[2];
				length_x1	= sqrt(x1*x1 + y1*y1 + z1*z1);

				x2	= grid.Data.faces[f].Specialized.N_List[2]->geometry.x[0] - grid.Data.faces[f].Specialized.N_List[0]->geometry.x[0];
				y2	= grid.Data.faces[f].Specialized.N_List[2]->geometry.x[1] - grid.Data.faces[f].Specialized.N_List[0]->geometry.x[1];
				z2	= grid.Data.faces[f].Specialized.N_List[2]->geometry.x[2] - grid.Data.faces[f].Specialized.N_List[0]->geometry.x[2];

				grid.Data.faces[f].Specialized.n[0][0]	=   0.5*(y1*z2 - z1*y2) / grid.Data.faces[f].geometry.S;
				grid.Data.faces[f].Specialized.n[0][1]	=  -0.5*(x1*z2 - z1*x2) / grid.Data.faces[f].geometry.S;
				grid.Data.faces[f].Specialized.n[0][2]	=   0.5*(x1*y2 - y1*x2) / grid.Data.faces[f].geometry.S;

				grid.Data.faces[f].Specialized.n[1][0]	= x1 / length_x1;
				grid.Data.faces[f].Specialized.n[1][1]	= y1 / length_x1;
				grid.Data.faces[f].Specialized.n[1][2]	= z1 / length_x1;

				grid.Data.faces[f].Specialized.n[2][0]	=  grid.Data.faces[f].Specialized.n[0][1]*grid.Data.faces[f].Specialized.n[1][2] - grid.Data.faces[f].Specialized.n[0][2]*grid.Data.faces[f].Specialized.n[1][1];
				grid.Data.faces[f].Specialized.n[2][1]	= -grid.Data.faces[f].Specialized.n[0][0]*grid.Data.faces[f].Specialized.n[1][2] + grid.Data.faces[f].Specialized.n[0][2]*grid.Data.faces[f].Specialized.n[1][0];
				grid.Data.faces[f].Specialized.n[2][2]	=  grid.Data.faces[f].Specialized.n[0][0]*grid.Data.faces[f].Specialized.n[1][1] - grid.Data.faces[f].Specialized.n[0][1]*grid.Data.faces[f].Specialized.n[1][0];


				error_ck =  pow(grid.Data.faces[f].Specialized.n[0][0], 2.0);
				error_ck += pow(grid.Data.faces[f].Specialized.n[0][1], 2.0);
				error_ck += pow(grid.Data.faces[f].Specialized.n[0][2], 2.0);
				error_ck = sqrt(error_ck);

				if (error_ck != error_ck)
				{
					std::ostringstream error_message;
					error_message << "Face ID:" << grid.Data.faces[f].geometry.id << " has problem in calculating normal-direction vectors: NaN value";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NaNValue());
				}

				if (error_ck == numeric_limits<double>::infinity())
				{
					std::ostringstream error_message;
					error_message << "Face ID:" << grid.Data.faces[f].geometry.id << " has problem in calculating normal-direction vectors: Inf value";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::InfValue());
				}

				if (fabs(error_ck - 1.0) > 1.0e-10)
				{
					std::ostringstream error_message;
					error_message << "Face ID:" << grid.Data.faces[f].geometry.id << " has problem in calculating normal-direction vectors: Non-unit value";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::ExceedLimit());
				}

				error_ck =  pow(grid.Data.faces[f].Specialized.n[1][0], 2.0);
				error_ck += pow(grid.Data.faces[f].Specialized.n[1][1], 2.0);
				error_ck += pow(grid.Data.faces[f].Specialized.n[1][2], 2.0);
				error_ck = sqrt(error_ck);

				if (error_ck != error_ck)
				{
					std::ostringstream error_message;
					error_message << "Face ID:" << grid.Data.faces[f].geometry.id << " has problem in calculating tangential1-direction vectors: NaN value";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NaNValue());
				}

				if (error_ck == numeric_limits<double>::infinity())
				{
					std::ostringstream error_message;
					error_message << "Face ID:" << grid.Data.faces[f].geometry.id << " has problem in calculating tangential1-direction vectors: Inf value";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::InfValue());
				}

				if (fabs(error_ck - 1.0) > 1.0e-10)
				{
					std::ostringstream error_message;
					error_message << "Face ID:" << grid.Data.faces[f].geometry.id << " has problem in calculating tangential1-direction vectors: Non-unit value";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::ExceedLimit());
				}


				error_ck =  pow(grid.Data.faces[f].Specialized.n[2][0], 2.0);
				error_ck += pow(grid.Data.faces[f].Specialized.n[2][1], 2.0);
				error_ck += pow(grid.Data.faces[f].Specialized.n[2][2], 2.0);
				error_ck = sqrt(error_ck);

				if (error_ck != error_ck)
				{
					std::ostringstream error_message;
					error_message << "Face ID:" << grid.Data.faces[f].geometry.id << " has problem in calculating tangential2-direction vectors: NaN value";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NaNValue());
				}

				if (error_ck == numeric_limits<double>::infinity())
				{
					std::ostringstream error_message;
					error_message << "Face ID:" << grid.Data.faces[f].geometry.id << " has problem in calculating tangential2-direction vectors: Inf value";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::InfValue());
				}

				if (fabs(error_ck - 1.0) > 1.0e-10)
				{
					std::ostringstream error_message;
					error_message << "Face ID:" << grid.Data.faces[f].geometry.id << " has problem in calculating tangential2-direction vectors: Non-unit value";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::ExceedLimit());
				}

				break;

			case f_quadrilateral:

				x1	= grid.Data.faces[f].Specialized.N_List[1]->geometry.x[0] - grid.Data.faces[f].Specialized.N_List[0]->geometry.x[0];
				y1	= grid.Data.faces[f].Specialized.N_List[1]->geometry.x[1] - grid.Data.faces[f].Specialized.N_List[0]->geometry.x[1];
				z1	= grid.Data.faces[f].Specialized.N_List[1]->geometry.x[2] - grid.Data.faces[f].Specialized.N_List[0]->geometry.x[2];

				x2	= grid.Data.faces[f].Specialized.N_List[2]->geometry.x[0] - grid.Data.faces[f].Specialized.N_List[0]->geometry.x[0];
				y2	= grid.Data.faces[f].Specialized.N_List[2]->geometry.x[1] - grid.Data.faces[f].Specialized.N_List[0]->geometry.x[1];
				z2	= grid.Data.faces[f].Specialized.N_List[2]->geometry.x[2] - grid.Data.faces[f].Specialized.N_List[0]->geometry.x[2];
				length_x2	= sqrt(x2*x2 + y2*y2 + z2*z2);

				x3	= grid.Data.faces[f].Specialized.N_List[3]->geometry.x[0] - grid.Data.faces[f].Specialized.N_List[0]->geometry.x[0];
				y3	= grid.Data.faces[f].Specialized.N_List[3]->geometry.x[1] - grid.Data.faces[f].Specialized.N_List[0]->geometry.x[1];
				z3	= grid.Data.faces[f].Specialized.N_List[3]->geometry.x[2] - grid.Data.faces[f].Specialized.N_List[0]->geometry.x[2];

				grid.Data.faces[f].Specialized.n[0][0]	=   0.5*(y1*z2 - z1*y2 + y2*z3 - z2*y3) / grid.Data.faces[f].geometry.S;
				grid.Data.faces[f].Specialized.n[0][1]	=  -0.5*(x1*z2 - z1*x2 + x2*z3 - z2*x3) / grid.Data.faces[f].geometry.S;
				grid.Data.faces[f].Specialized.n[0][2]	=   0.5*(x1*y2 - y1*x2 + x2*y3 - y2*x3) / grid.Data.faces[f].geometry.S;

				grid.Data.faces[f].Specialized.n[1][0]	= x2 / length_x2;
				grid.Data.faces[f].Specialized.n[1][1]	= y2 / length_x2;
				grid.Data.faces[f].Specialized.n[1][2]	= z2 / length_x2;

				grid.Data.faces[f].Specialized.n[2][0]	=  grid.Data.faces[f].Specialized.n[0][1]*grid.Data.faces[f].Specialized.n[1][2] - grid.Data.faces[f].Specialized.n[0][2]*grid.Data.faces[f].Specialized.n[1][1];
				grid.Data.faces[f].Specialized.n[2][1]	= -grid.Data.faces[f].Specialized.n[0][0]*grid.Data.faces[f].Specialized.n[1][2] + grid.Data.faces[f].Specialized.n[0][2]*grid.Data.faces[f].Specialized.n[1][0];
				grid.Data.faces[f].Specialized.n[2][2]	=  grid.Data.faces[f].Specialized.n[0][0]*grid.Data.faces[f].Specialized.n[1][1] - grid.Data.faces[f].Specialized.n[0][1]*grid.Data.faces[f].Specialized.n[1][0];


				error_ck =  pow(grid.Data.faces[f].Specialized.n[0][0], 2.0);
				error_ck += pow(grid.Data.faces[f].Specialized.n[0][1], 2.0);
				error_ck += pow(grid.Data.faces[f].Specialized.n[0][2], 2.0);
				error_ck = sqrt(error_ck);

				if (error_ck != error_ck)
				{
					std::ostringstream error_message;
					error_message << "Face ID:" << grid.Data.faces[f].geometry.id << " has problem in calculating normal-direction vectors: NaN value";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NaNValue());
				}

				if (error_ck == numeric_limits<double>::infinity())
				{
					std::ostringstream error_message;
					error_message << "Face ID:" << grid.Data.faces[f].geometry.id << " has problem in calculating normal-direction vectors: Inf value";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::InfValue());
				}

				if (fabs(error_ck - 1.0) > 1.0e-10)
				{
					std::ostringstream error_message;
					error_message << "Face ID:" << grid.Data.faces[f].geometry.id << " has problem in calculating normal-direction vectors: Non-unit value";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::ExceedLimit());
				}

				error_ck =  pow(grid.Data.faces[f].Specialized.n[1][0], 2.0);
				error_ck += pow(grid.Data.faces[f].Specialized.n[1][1], 2.0);
				error_ck += pow(grid.Data.faces[f].Specialized.n[1][2], 2.0);
				error_ck = sqrt(error_ck);

				if (error_ck != error_ck)
				{
					std::ostringstream error_message;
					error_message << "Face ID:" << grid.Data.faces[f].geometry.id << " has problem in calculating tangential1-direction vectors: NaN value";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NaNValue());
				}

				if (error_ck == numeric_limits<double>::infinity())
				{
					std::ostringstream error_message;
					error_message << "Face ID:" << grid.Data.faces[f].geometry.id << " has problem in calculating tangential1-direction vectors: Inf value";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::InfValue());
				}

				if (fabs(error_ck - 1.0) > 1.0e-10)
				{
					std::ostringstream error_message;
					error_message << "Face ID:" << grid.Data.faces[f].geometry.id << " has problem in calculating tangential1-direction vectors: Non-unit value";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::ExceedLimit());
				}


				error_ck =  pow(grid.Data.faces[f].Specialized.n[2][0], 2.0);
				error_ck += pow(grid.Data.faces[f].Specialized.n[2][1], 2.0);
				error_ck += pow(grid.Data.faces[f].Specialized.n[2][2], 2.0);
				error_ck = sqrt(error_ck);

				if (error_ck != error_ck)
				{
					std::ostringstream error_message;
					error_message << "Face ID:" << grid.Data.faces[f].geometry.id << " has problem in calculating tangential2-direction vectors: NaN value";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NaNValue());
				}

				if (error_ck == numeric_limits<double>::infinity())
				{
					std::ostringstream error_message;
					error_message << "Face ID:" << grid.Data.faces[f].geometry.id << " has problem in calculating tangential2-direction vectors: Inf value";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::InfValue());
				}

				if (fabs(error_ck - 1.0) > 1.0e-10)
				{
					std::ostringstream error_message;
					error_message << "Face ID:" << grid.Data.faces[f].geometry.id << " has problem in calculating tangential2-direction vectors: Non-unit value";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::ExceedLimit());
				}
				break;
			}
		}

	}



}
