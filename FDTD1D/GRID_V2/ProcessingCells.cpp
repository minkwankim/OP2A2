/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * ProcessingCells.cpp
 *
 *  Created on: Jan 6, 2016
 *      Author: minkwan
 */


#include <omp.h>
#include <limits>

#include "Gridv2.hpp"
#include "GridConfig.hpp"

#include "./COMMON/VectorPointer.hpp"
#include "./COMMON/ExceptionGeneral.hpp"
#include "./COMMON/ErrorCode.hpp"
#include "./MATH/Area.hpp"

namespace GRID
{

void Processing_Cell(c_Grid& grid)
{
	for (int c	= 0; c <= grid.Info.NCM-1; c++)
	{
		switch (grid.Data.cells[c].geometry.type)
		{
		case c_triangle:
			grid.Data.cells[c].Specialized.N_List.resize(3, NULL);
			grid.Data.cells[c].Specialized.F_List.resize(3, NULL);
			break;

		case c_tetrahedron:
			grid.Data.cells[c].Specialized.N_List.resize(4, NULL);
			grid.Data.cells[c].Specialized.F_List.resize(4, NULL);
			break;

		case c_quadrilateral:
			grid.Data.cells[c].Specialized.N_List.resize(4, NULL);
			grid.Data.cells[c].Specialized.F_List.resize(4, NULL);
			break;

		case c_hexahedron:
			grid.Data.cells[c].Specialized.N_List.resize(8, NULL);
			grid.Data.cells[c].Specialized.F_List.resize(6, NULL);
			break;

		case c_pyramid:
			grid.Data.cells[c].Specialized.N_List.resize(5, NULL);
			grid.Data.cells[c].Specialized.F_List.resize(5, NULL);
			break;

		case c_prism:
			grid.Data.cells[c].Specialized.N_List.resize(6, NULL);
			grid.Data.cells[c].Specialized.F_List.resize(5, NULL);
			break;
		}
	}


	// 2. Find face and node information of a cell
	int	flag;
	int cl, cr;
	c_Cell* CL;
	c_Cell* CR;

	vector<int> filled_nodes(grid.Info.NCM, 0);

	for (int f = 0; f <= grid.Info.NFM-1; f++)
	{
		CR	= grid.Data.faces[f].Specialized.cr;
		CL	= grid.Data.faces[f].Specialized.cl;

		// FOR RIGHT-CELL //
		cr = -1;
		if (CR != NULL)
		{
			cr	= grid.Map.c_ID_to_pos[grid.Data.faces[f].Specialized.cr->geometry.id];
			switch (CR->geometry.type)
			{
			case c_triangle:
				// Numbering: CCW
				if (grid.Data.faces[f].geometry.type == f_line)
				{
					if (filled_nodes[cr] == 0) // FIRST FILLING
					{
						CR->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[1];
						CR->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[0];
						filled_nodes[cr] = 2;
					}
					else if (filled_nodes[cr] == 2) // Second filling
					{
						if (grid.Data.faces[f].Specialized.N_List[0] == CR->Specialized.N_List[0])
						{
							CR->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cr]	= 3;
						}
						else if (grid.Data.faces[f].Specialized.N_List[1] == CR->Specialized.N_List[1])
						{
							CR->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[0];
							filled_nodes[cr]	= 3;
						}
						else
						{
							std::ostringstream error_message;
							error_message << "Cell ID:" << CR->geometry.id << " has problem during cell mesh construction";
							OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NotSupportedType());
						}
					}
				}
				else
				{
					std::ostringstream error_message;
					error_message << "Cell ID:" << CR->geometry.id << " has problem during cell mesh construction. For triangle cell, only line-type face is allowed";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NotSupportedType());
				}
				break;

			case c_quadrilateral:
				// Numbering: CCW
				if (grid.Data.faces[f].geometry.type == f_line)
				{
					if (filled_nodes[cr] == 0)		// FIRST FILLING
					{
						CR->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[1];
						CR->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[0];
						filled_nodes[cr] = 2;
					}
					else if (filled_nodes[cr] == 2)
					{
						if (grid.Data.faces[f].Specialized.N_List[0] != CR->Specialized.N_List[0] && grid.Data.faces[f].Specialized.N_List[0] != CR->Specialized.N_List[1] &&
							grid.Data.faces[f].Specialized.N_List[1] != CR->Specialized.N_List[0] && grid.Data.faces[f].Specialized.N_List[1] != CR->Specialized.N_List[1])
						{
							CR->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[1];
							CR->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[0];
							filled_nodes[cr] = 4;
						}

					}
				}
				else
				{
					std::ostringstream error_message;
					error_message << "Cell ID:" << CR->geometry.id << " has problem during cell mesh construction. For quadrilateral cell, only line-type face is allowed";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NotSupportedType());
				}
				break;

			case c_tetrahedron:
				if (grid.Data.faces[f].geometry.type == f_triangle)
				{
					if (filled_nodes[cr] == 0) // FIRST FILLING
					{
						CR->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
						CR->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[1];
						CR->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
						filled_nodes[cr] = 3;
					}
					else if (filled_nodes[cr] == 3) // Second filling
					{
						if (grid.Data.faces[f].Specialized.N_List[0] != CR->Specialized.N_List[0] &&
							grid.Data.faces[f].Specialized.N_List[0] != CR->Specialized.N_List[1] &&
							grid.Data.faces[f].Specialized.N_List[0] != CR->Specialized.N_List[2])
						{
							CR->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[0];
							filled_nodes[cr]++;
						}
						else if(grid.Data.faces[f].Specialized.N_List[1] != CR->Specialized.N_List[0] &&
								grid.Data.faces[f].Specialized.N_List[1] != CR->Specialized.N_List[1] &&
								grid.Data.faces[f].Specialized.N_List[1] != CR->Specialized.N_List[2])
						{
							CR->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cr]++;
						}
						else if(grid.Data.faces[f].Specialized.N_List[2] != CR->Specialized.N_List[0] &&
								grid.Data.faces[f].Specialized.N_List[2] != CR->Specialized.N_List[1] &&
								grid.Data.faces[f].Specialized.N_List[2] != CR->Specialized.N_List[2])
						{
							CR->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[0];
							filled_nodes[cr]++;
						}
						else
						{
							std::ostringstream error_message;
							error_message << "Cell ID:" << CR->geometry.id << " has problem during cell mesh construction. It is impossible configuration for tetrahedron cell.";
							OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NotSupportedType());
						}
					}
				}
				else
				{
					std::ostringstream error_message;
					error_message << "Cell ID:" << CR->geometry.id << " has problem during cell mesh construction. For tetrahedron cell, only triangle-type face is allowed";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NotSupportedType());
				}
				break;

			case c_hexahedron:
				if (grid.Data.faces[f].geometry.type == f_quadrilateral)
				{
					if (filled_nodes[cr] == 0) // FIRST FILLING
					{
						CR->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
						CR->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[1];
						CR->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
						CR->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[3];
						filled_nodes[cr] = 4;
					}
					else if (filled_nodes[cr] == 4 || filled_nodes[cr] == 6)
					{
						if (CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[0] &&
							CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[3])
						{
							CR->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[1];
							CR->Specialized.N_List[5] = grid.Data.faces[f].Specialized.N_List[2];
							filled_nodes[cr] += 2;
						}
						else if(CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[1] &&
								CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[0])
						{
							CR->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[2];
							CR->Specialized.N_List[5] = grid.Data.faces[f].Specialized.N_List[3];
							filled_nodes[cr] += 2;
						}
						else if(CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[2] &&
								CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[1])
						{
							CR->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[3];
							CR->Specialized.N_List[5] = grid.Data.faces[f].Specialized.N_List[0];
							filled_nodes[cr] += 2;
						}
						else if(CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[3] &&
								CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[2])
						{
							CR->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[0];
							CR->Specialized.N_List[5] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cr] += 2;
						}
						else if(CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[0] &&
								CR->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[3])
						{
							CR->Specialized.N_List[6] = grid.Data.faces[f].Specialized.N_List[1];
							CR->Specialized.N_List[7] = grid.Data.faces[f].Specialized.N_List[2];
							filled_nodes[cr] += 2;
						}
						else if(CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[1] &&
								CR->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[0])
						{
							CR->Specialized.N_List[6] = grid.Data.faces[f].Specialized.N_List[2];
							CR->Specialized.N_List[7] = grid.Data.faces[f].Specialized.N_List[3];
							filled_nodes[cr] += 2;
						}
						else if(CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[2] &&
								CR->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[1])
						{
							CR->Specialized.N_List[6] = grid.Data.faces[f].Specialized.N_List[3];
							CR->Specialized.N_List[7] = grid.Data.faces[f].Specialized.N_List[0];
							filled_nodes[cr] += 2;
						}
						else if(CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[3] &&
								CR->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[2])
						{
							CR->Specialized.N_List[6] = grid.Data.faces[f].Specialized.N_List[0];
							CR->Specialized.N_List[7] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cr] += 2;
						}
					}
				}
				else
				{
					std::ostringstream error_message;
					error_message << "Cell ID:" << CR->geometry.id << " has problem during cell mesh construction. For hexahedron cell, only quadrilateral-type face is allowed";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NotSupportedType());
				}
				break;

			case c_pyramid:
				if (grid.Data.faces[f].geometry.type == f_quadrilateral)
				{
					if (filled_nodes[cr] == 0) // FIRST FILLING
					{
						CR->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
						CR->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[1];
						CR->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
						CR->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[3];
						filled_nodes[cr] = 4;
					}
					else if (filled_nodes[cr] == 3)
					{
						if (CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[0] &&
							CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[3])
						{
							CR->Specialized.N_List[4] = CR->Specialized.N_List[2];

							CR->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
							CR->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[1];
							CR->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
							CR->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[3];
							filled_nodes[cr] = 5;
						}
						else if(CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[1] &&
								CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[0])
						{
							CR->Specialized.N_List[4] = CR->Specialized.N_List[2];

							CR->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
							CR->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[1];
							CR->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
							CR->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[3];
							filled_nodes[cr] = 5;
						}
						else if(CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[2] &&
								CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[1])
						{
							CR->Specialized.N_List[4] = CR->Specialized.N_List[2];

							CR->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
							CR->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[1];
							CR->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
							CR->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[3];
							filled_nodes[cr] = 5;
						}
						else if(CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[3] &&
								CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[2])
						{
							CR->Specialized.N_List[4] = CR->Specialized.N_List[2];

							CR->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
							CR->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[1];
							CR->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
							CR->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[3];
							filled_nodes[cr] = 5;
						}
						else if(CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[0] &&
								CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[3])
						{
							CR->Specialized.N_List[4] = CR->Specialized.N_List[0];

							CR->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
							CR->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[1];
							CR->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
							CR->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[3];
							filled_nodes[cr] = 5;
						}
						else if(CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[1] &&
								CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[0])
						{
							CR->Specialized.N_List[4] = CR->Specialized.N_List[0];

							CR->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
							CR->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[1];
							CR->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
							CR->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[3];
							filled_nodes[cr] = 5;
						}
						else if(CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[2] &&
								CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[1])
						{
							CR->Specialized.N_List[4] = CR->Specialized.N_List[0];

							CR->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
							CR->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[1];
							CR->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
							CR->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[3];
							filled_nodes[cr] = 5;
						}
						else if(CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[3] &&
								CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[2])
						{
							CR->Specialized.N_List[4] = CR->Specialized.N_List[0];

							CR->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
							CR->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[1];
							CR->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
							CR->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[3];
							filled_nodes[cr] = 5;
						}
						else if(CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[0] &&
								CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[3])
						{
							CR->Specialized.N_List[4] = CR->Specialized.N_List[1];

							CR->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
							CR->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[1];
							CR->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
							CR->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[3];
							filled_nodes[cr] = 5;
						}
						else if(CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[1] &&
								CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[0])
						{
							CR->Specialized.N_List[4] = CR->Specialized.N_List[1];

							CR->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
							CR->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[1];
							CR->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
							CR->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[3];
							filled_nodes[cr] = 5;
						}
						else if(CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[2] &&
								CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[1])
						{
							CR->Specialized.N_List[4] = CR->Specialized.N_List[1];

							CR->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
							CR->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[1];
							CR->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
							CR->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[3];
							filled_nodes[cr] = 5;
						}
						else if(CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[3] &&
								CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[2])
						{
							CR->Specialized.N_List[4] = CR->Specialized.N_List[1];

							CR->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
							CR->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[1];
							CR->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
							CR->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[3];
							filled_nodes[cr] = 5;
						}
					}
				}
				else if (grid.Data.faces[f].geometry.type == f_triangle)
				{
					if (filled_nodes[cr] == 0) // FIRST FILLING
					{
						CR->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
						CR->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[1];
						CR->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
						filled_nodes[cr] = 3;
					}
					else if (filled_nodes[cr] == 4)
					{
						if (CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[0] &&
							CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[2])
						{
							CR->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cr] += 1;
						}
						else if(CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[1] &&
								CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[0])
						{
							CR->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[2];
							filled_nodes[cr] += 1;
						}
						else if(CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[2] &&
								CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[1])
						{
							CR->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[0];
							filled_nodes[cr] += 1;
						}
						else if(CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[0] &&
								CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[1])
						{
							CR->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cr] += 1;
						}
						else if(CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[1] &&
								CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[0])
						{
							CR->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[2];
							filled_nodes[cr] += 1;
						}
						else if(CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[2] &&
								CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[1])
						{
							CR->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[0];
							filled_nodes[cr] += 1;
						}
						else if(CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[0] &&
								CR->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[2])
						{
							CR->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cr] += 1;
						}
						else if(CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[1] &&
								CR->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[0])
						{
							CR->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[2];
							filled_nodes[cr] += 1;
						}
						else if(CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[2] &&
								CR->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[1])
						{
							CR->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[0];
							filled_nodes[cr] += 1;
						}
						else if(CR->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[0] &&
								CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[2])
						{
							CR->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cr] += 1;
						}
						else if(CR->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[1] &&
								CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[0])
						{
							CR->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[2];
							filled_nodes[cr] += 1;
						}
						else if(CR->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[2] &&
								CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[1])
						{
							CR->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[0];
							filled_nodes[cr] += 1;
						}
					}
				}
				break;

			case c_prism:
				if (grid.Data.faces[f].geometry.type == f_quadrilateral)
				{
					if (filled_nodes[cr] == 0) // FIRST FILLING
					{
						CR->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
						CR->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[1];
						CR->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
						CR->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[3];
						filled_nodes[cr] = 4;
					}
					else if(filled_nodes[cr] == 4)
					{
						vector<c_Node*> swap(6, NULL);

						if (CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[0] &&
							CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[3])
						{
							swap[0]	= CR->Specialized.N_List[0];
							swap[1]	= CR->Specialized.N_List[3];
							swap[2]	= grid.Data.faces[f].Specialized.N_List[1];
							swap[3]	= CR->Specialized.N_List[1];
							swap[4]	= CR->Specialized.N_List[2];
							swap[5]	= grid.Data.faces[f].Specialized.N_List[2];
						}
						else if(CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[1] &&
								CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[0])
						{
							swap[0]	= CR->Specialized.N_List[0];
							swap[1]	= CR->Specialized.N_List[3];
							swap[2]	= grid.Data.faces[f].Specialized.N_List[2];
							swap[3]	= CR->Specialized.N_List[1];
							swap[4]	= CR->Specialized.N_List[2];
							swap[5]	= grid.Data.faces[f].Specialized.N_List[3];
						}
						else if(CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[2] &&
								CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[1])
						{
							swap[0]	= CR->Specialized.N_List[0];
							swap[1]	= CR->Specialized.N_List[3];
							swap[2]	= grid.Data.faces[f].Specialized.N_List[3];
							swap[3]	= CR->Specialized.N_List[1];
							swap[4]	= CR->Specialized.N_List[2];
							swap[5]	= grid.Data.faces[f].Specialized.N_List[0];
						}
						else if(CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[3] &&
								CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[2])
						{
							swap[0]	= CR->Specialized.N_List[0];
							swap[1]	= CR->Specialized.N_List[3];
							swap[2]	= grid.Data.faces[f].Specialized.N_List[0];
							swap[3]	= CR->Specialized.N_List[1];
							swap[4]	= CR->Specialized.N_List[2];
							swap[5]	= grid.Data.faces[f].Specialized.N_List[1];
						}
						else if(CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[0] &&
								CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[3])
						{
							swap[0]	= CR->Specialized.N_List[3];
							swap[1]	= CR->Specialized.N_List[2];
							swap[2]	= grid.Data.faces[f].Specialized.N_List[2];
							swap[3]	= CR->Specialized.N_List[0];
							swap[4]	= CR->Specialized.N_List[1];
							swap[5]	= grid.Data.faces[f].Specialized.N_List[1];
						}
						else if(CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[1] &&
								CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[0])
						{
							swap[0]	= CR->Specialized.N_List[3];
							swap[1]	= CR->Specialized.N_List[2];
							swap[2]	= grid.Data.faces[f].Specialized.N_List[3];
							swap[3]	= CR->Specialized.N_List[0];
							swap[4]	= CR->Specialized.N_List[1];
							swap[5]	= grid.Data.faces[f].Specialized.N_List[2];
						}
						else if(CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[2] &&
								CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[1])
						{
							swap[0]	= CR->Specialized.N_List[3];
							swap[1]	= CR->Specialized.N_List[2];
							swap[2]	= grid.Data.faces[f].Specialized.N_List[0];
							swap[3]	= CR->Specialized.N_List[0];
							swap[4]	= CR->Specialized.N_List[1];
							swap[5]	= grid.Data.faces[f].Specialized.N_List[3];
						}
						else if(CR->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[3] &&
								CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[2])
						{
							swap[0]	= CR->Specialized.N_List[3];
							swap[1]	= CR->Specialized.N_List[2];
							swap[2]	= grid.Data.faces[f].Specialized.N_List[1];
							swap[3]	= CR->Specialized.N_List[0];
							swap[4]	= CR->Specialized.N_List[1];
							swap[5]	= grid.Data.faces[f].Specialized.N_List[0];
						}
						else if(CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[0] &&
								CR->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[3])
						{
							swap[0]	= CR->Specialized.N_List[0];
							swap[1]	= CR->Specialized.N_List[3];
							swap[2]	= grid.Data.faces[f].Specialized.N_List[2];
							swap[3]	= CR->Specialized.N_List[1];
							swap[4]	= CR->Specialized.N_List[2];
							swap[5]	= grid.Data.faces[f].Specialized.N_List[1];
						}
						else if(CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[1] &&
								CR->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[0])
						{
							swap[0]	= CR->Specialized.N_List[0];
							swap[1]	= CR->Specialized.N_List[3];
							swap[2]	= grid.Data.faces[f].Specialized.N_List[3];
							swap[3]	= CR->Specialized.N_List[1];
							swap[4]	= CR->Specialized.N_List[2];
							swap[5]	= grid.Data.faces[f].Specialized.N_List[2];
						}
						else if(CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[2] &&
								CR->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[1])
						{
							swap[0]	= CR->Specialized.N_List[0];
							swap[1]	= CR->Specialized.N_List[3];
							swap[2]	= grid.Data.faces[f].Specialized.N_List[0];
							swap[3]	= CR->Specialized.N_List[1];
							swap[4]	= CR->Specialized.N_List[2];
							swap[5]	= grid.Data.faces[f].Specialized.N_List[3];
						}
						else if(CR->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[3] &&
								CR->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[2])
						{
							swap[0]	= CR->Specialized.N_List[0];
							swap[1]	= CR->Specialized.N_List[3];
							swap[2]	= grid.Data.faces[f].Specialized.N_List[1];
							swap[3]	= CR->Specialized.N_List[1];
							swap[4]	= CR->Specialized.N_List[2];
							swap[5]	= grid.Data.faces[f].Specialized.N_List[0];
						}
						else if(CR->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[0] &&
								CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[3])
						{
							swap[0]	= CR->Specialized.N_List[3];
							swap[1]	= CR->Specialized.N_List[2];
							swap[2]	= grid.Data.faces[f].Specialized.N_List[1];
							swap[3]	= CR->Specialized.N_List[0];
							swap[4]	= CR->Specialized.N_List[1];
							swap[5]	= grid.Data.faces[f].Specialized.N_List[2];
						}
						else if(CR->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[1] &&
								CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[0])
						{
							swap[0]	= CR->Specialized.N_List[3];
							swap[1]	= CR->Specialized.N_List[2];
							swap[2]	= grid.Data.faces[f].Specialized.N_List[2];
							swap[3]	= CR->Specialized.N_List[0];
							swap[4]	= CR->Specialized.N_List[1];
							swap[5]	= grid.Data.faces[f].Specialized.N_List[3];
						}
						else if(CR->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[2] &&
								CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[1])
						{
							swap[0]	= CR->Specialized.N_List[3];
							swap[1]	= CR->Specialized.N_List[2];
							swap[2]	= grid.Data.faces[f].Specialized.N_List[3];
							swap[3]	= CR->Specialized.N_List[0];
							swap[4]	= CR->Specialized.N_List[1];
							swap[5]	= grid.Data.faces[f].Specialized.N_List[0];
						}
						else if(CR->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[3] &&
								CR->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[2])
						{
							swap[0]	= CR->Specialized.N_List[3];
							swap[1]	= CR->Specialized.N_List[2];
							swap[2]	= grid.Data.faces[f].Specialized.N_List[0];
							swap[3]	= CR->Specialized.N_List[0];
							swap[4]	= CR->Specialized.N_List[1];
							swap[5]	= grid.Data.faces[f].Specialized.N_List[1];
						}
						else
						{
							std::ostringstream error_message;
							error_message << "Cell ID:" << CR->geometry.id << " has problem during cell mesh construction. It is impossible configuration for prism cell.";
							OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NotSupportedType());
						}

						CR->Specialized.N_List[0]	= swap[0];
						CR->Specialized.N_List[1]	= swap[1];
						CR->Specialized.N_List[2]	= swap[2];
						CR->Specialized.N_List[3]	= swap[3];
						CR->Specialized.N_List[4]	= swap[4];
						CR->Specialized.N_List[5]	= swap[5];
						filled_nodes[cr] = 6;
					}
				}
				break;

			}
		}

		// For Left-cell
		cl = -1;
		if (CL != NULL)
		{
			cl	= grid.Map.c_ID_to_pos[grid.Data.faces[f].Specialized.cl->geometry.id];
			switch (CL->geometry.type)
			{
			case c_triangle:
				if (grid.Data.faces[f].geometry.type == f_line)
				{
					if (filled_nodes[cl] == 0) // FIRST FILLING
					{
						CL->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
						CL->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[1];
						filled_nodes[cl] = 2;
					}
					else if (filled_nodes[cl] == 2) // Second filling
					{
						if (grid.Data.faces[f].Specialized.N_List[0] == CL->Specialized.N_List[1])
						{
							CL->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cl]	= 3;
						}
						else if (grid.Data.faces[f].Specialized.N_List[1] == CL->Specialized.N_List[0])
						{
							CL->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[0];
							filled_nodes[cl]	= 3;
						}
						else
						{
							std::ostringstream error_message;
							error_message << "Cell ID:" << CL->geometry.id << " has problem during cell mesh construction";
							OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NotSupportedType());
						}
					}
				}
				else
				{
					std::ostringstream error_message;
					error_message << "Cell ID:" << CL->geometry.id << " has problem during cell mesh construction. For triangle cell, only line-type face is allowed";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NotSupportedType());
				}
				break;

			case c_quadrilateral:
				if (grid.Data.faces[f].geometry.type == f_line)
				{
					if (filled_nodes[cl] == 0)		// FIRST FILLING
					{
						CL->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
						CL->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[1];
						filled_nodes[cl] = 2;
					}
					else if (filled_nodes[cl] == 2)
					{
						if (grid.Data.faces[f].Specialized.N_List[0] != CL->Specialized.N_List[0] && grid.Data.faces[f].Specialized.N_List[0] != CL->Specialized.N_List[1] &&
							grid.Data.faces[f].Specialized.N_List[1] != CL->Specialized.N_List[0] && grid.Data.faces[f].Specialized.N_List[1] != CL->Specialized.N_List[1])
						{
							CL->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[0];
							CL->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cl] = 4;
						}
					}
				}
				else
				{
					std::ostringstream error_message;
					error_message << "Cell ID:" << CL->geometry.id << " has problem during cell mesh construction. For quadrilateral cell, only line-type face is allowed";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NotSupportedType());
				}
				break;


			case c_tetrahedron:
				if (grid.Data.faces[f].geometry.type == f_triangle)
				{
					if (filled_nodes[cl] == 0) // FIRST FILLING
					{
						CL->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
						CL->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[2];
						CL->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[1];
						filled_nodes[cl] = 3;
					}
					else if (filled_nodes[cl] == 3)
					{
						if (grid.Data.faces[f].Specialized.N_List[0] != CL->Specialized.N_List[0] &&
							grid.Data.faces[f].Specialized.N_List[0] != CL->Specialized.N_List[1] &&
							grid.Data.faces[f].Specialized.N_List[0] != CL->Specialized.N_List[2])
						{
							CL->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[0];
							filled_nodes[cl]++;
						}
						else if(grid.Data.faces[f].Specialized.N_List[1] != CL->Specialized.N_List[0] &&
								grid.Data.faces[f].Specialized.N_List[1] != CL->Specialized.N_List[1] &&
								grid.Data.faces[f].Specialized.N_List[1] != CL->Specialized.N_List[2])
						{
							CL->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cl]++;
						}
						else if(grid.Data.faces[f].Specialized.N_List[2] != CL->Specialized.N_List[0] &&
								grid.Data.faces[f].Specialized.N_List[2] != CL->Specialized.N_List[1] &&
								grid.Data.faces[f].Specialized.N_List[2] != CL->Specialized.N_List[2])
						{
							CL->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[2];
							filled_nodes[cl]++;
						}
						else
						{
							std::ostringstream error_message;
							error_message << "Cell ID:" << CL->geometry.id << " has problem during cell mesh construction. It is impossible configuration for tetrahedron cell.";
							OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NotSupportedType());
						}
					}
				}
				else
				{
					std::ostringstream error_message;
					error_message << "Cell ID:" << CL->geometry.id << " has problem during cell mesh construction. For tetrahedron cell, only triangle-type face is allowed";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NotSupportedType());
				}
				break;

			case c_hexahedron:
				if (grid.Data.faces[f].geometry.type == f_quadrilateral)
				{
					if (filled_nodes[cl] == 0) // FIRST FILLING
					{
						CL->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
						CL->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[3];
						CL->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
						CL->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[1];
						filled_nodes[cl] = 4;
					}
					else if (filled_nodes[cl] == 4 || filled_nodes[cl] == 6)
					{
						if (CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[0] &&
							CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[1])
						{
							CL->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[3];
							CL->Specialized.N_List[5] = grid.Data.faces[f].Specialized.N_List[2];
							filled_nodes[cl] += 2;
						}
						else if(CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[1] &&
								CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[2])
						{
							CL->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[0];
							CL->Specialized.N_List[5] = grid.Data.faces[f].Specialized.N_List[3];
							filled_nodes[cl] += 2;
						}
						else if(CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[2] &&
								CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[3])
						{
							CL->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[1];
							CL->Specialized.N_List[5] = grid.Data.faces[f].Specialized.N_List[0];
							filled_nodes[cl] += 2;
						}
						else if(CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[3] &&
								CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[0])
						{
							CL->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[2];
							CL->Specialized.N_List[5] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cl] += 2;
						}
						else if(CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[0] &&
								CL->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[1])
						{
							CL->Specialized.N_List[6] = grid.Data.faces[f].Specialized.N_List[3];
							CL->Specialized.N_List[7] = grid.Data.faces[f].Specialized.N_List[2];
							filled_nodes[cl] += 2;
						}
						else if(CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[0] &&
								CL->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[1])
						{
							CL->Specialized.N_List[6] = grid.Data.faces[f].Specialized.N_List[3];
							CL->Specialized.N_List[7] = grid.Data.faces[f].Specialized.N_List[2];
							filled_nodes[cl] += 2;
						}
						else if(CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[1] &&
								CL->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[2])
						{
							CL->Specialized.N_List[6] = grid.Data.faces[f].Specialized.N_List[0];
							CL->Specialized.N_List[7] = grid.Data.faces[f].Specialized.N_List[3];
							filled_nodes[cl] += 2;
						}
						else if(CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[2] &&
								CL->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[3])
						{
							CL->Specialized.N_List[6] = grid.Data.faces[f].Specialized.N_List[1];
							CL->Specialized.N_List[7] = grid.Data.faces[f].Specialized.N_List[0];
							filled_nodes[cl] += 2;
						}
						else if(CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[3] &&
								CL->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[0])
						{
							CL->Specialized.N_List[6] = grid.Data.faces[f].Specialized.N_List[2];
							CL->Specialized.N_List[7] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cl] += 2;
						}
					}
				}
				else
				{
					std::ostringstream error_message;
					error_message << "Cell ID:" << CL->geometry.id << " has problem during cell mesh construction. For hexahedron cell, only quadrilateral-type face is allowed";
					OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NotSupportedType());
				}
				break;
				break;

			case c_pyramid:
				if (grid.Data.faces[f].geometry.type == f_quadrilateral)
				{
					if (filled_nodes[cl] == 0) // FIRST FILLING
					{
						CL->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
						CL->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[3];
						CL->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
						CL->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[1];
						filled_nodes[cl] = 4;
					}
					else if (filled_nodes[cr] == 3)
					{
						if (CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[0] &&
							CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[1])
						{
							CL->Specialized.N_List[4] = CL->Specialized.N_List[2];

							CL->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
							CL->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[3];
							CL->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
							CL->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cl] = 5;
						}
						else if(CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[1] &&
								CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[2])
						{
							CL->Specialized.N_List[4] = CL->Specialized.N_List[2];

							CL->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
							CL->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[3];
							CL->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
							CL->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cl] = 5;
						}
						else if(CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[2] &&
								CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[3])
						{
							CL->Specialized.N_List[4] = CL->Specialized.N_List[2];

							CL->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
							CL->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[3];
							CL->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
							CL->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cl] = 5;
						}
						else if(CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[3] &&
								CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[0])
						{
							CL->Specialized.N_List[4] = CL->Specialized.N_List[2];

							CL->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
							CL->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[3];
							CL->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
							CL->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cl] = 5;
						}
						else if(CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[0] &&
								CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[1])
						{
							CL->Specialized.N_List[4] = CL->Specialized.N_List[0];

							CL->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
							CL->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[3];
							CL->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
							CL->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cl] = 5;
						}
						else if(CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[1] &&
								CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[2])
						{
							CL->Specialized.N_List[4] = CL->Specialized.N_List[0];

							CL->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
							CL->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[3];
							CL->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
							CL->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cl] = 5;
						}
						else if(CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[2] &&
								CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[3])
						{
							CL->Specialized.N_List[4] = CL->Specialized.N_List[0];

							CL->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
							CL->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[3];
							CL->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
							CL->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cl] = 5;
						}
						else if(CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[3] &&
								CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[0])
						{
							CL->Specialized.N_List[4] = CL->Specialized.N_List[0];

							CL->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
							CL->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[3];
							CL->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
							CL->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cl] = 5;
						}
						else if(CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[0] &&
								CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[1])
						{
							CL->Specialized.N_List[4] = CL->Specialized.N_List[1];

							CL->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
							CL->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[3];
							CL->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
							CL->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cl] = 5;
						}
						else if(CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[1] &&
								CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[2])
						{
							CL->Specialized.N_List[4] = CL->Specialized.N_List[1];

							CL->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
							CL->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[3];
							CL->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
							CL->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cl] = 5;
						}
						else if(CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[2] &&
								CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[3])
						{
							CL->Specialized.N_List[4] = CL->Specialized.N_List[1];

							CL->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
							CL->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[3];
							CL->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
							CL->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cl] = 5;
						}
						else if(CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[3] &&
								CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[0])
						{
							CL->Specialized.N_List[4] = CL->Specialized.N_List[1];

							CL->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
							CL->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[3];
							CL->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
							CL->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cl] = 5;
						}
					}
				}
				else if (grid.Data.faces[f].geometry.type == f_triangle)
				{
					if (filled_nodes[cl] == 0) // FIRST FILLING
					{
						CL->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
						CL->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[2];
						CL->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[1];
						filled_nodes[cl] = 3;
					}
					else if (filled_nodes[cl] == 4)
					{
						if (CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[0] &&
							CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[1])
						{
							CL->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[2];
							filled_nodes[cl] += 1;
						}
						else if(CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[1] &&
								CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[2])
						{
							CL->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[0];
							filled_nodes[cl] += 1;
						}
						else if(CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[2] &&
								CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[0])
						{
							CL->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cl] += 1;
						}
						else if(CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[0] &&
								CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[1])
						{
							CL->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[2];
							filled_nodes[cl] += 1;
						}
						else if(CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[1] &&
								CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[2])
						{
							CL->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[0];
							filled_nodes[cl] += 1;
						}
						else if(CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[2] &&
								CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[0])
						{
							CL->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cl] += 1;
						}
						else if(CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[0] &&
								CL->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[1])
						{
							CL->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[2];
							filled_nodes[cl] += 1;
						}
						else if(CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[1] &&
								CL->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[2])
						{
							CL->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[0];
							filled_nodes[cl] += 1;
						}
						else if(CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[2] &&
								CL->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[0])
						{
							CL->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cl] += 1;
						}
						else if(CL->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[0] &&
								CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[1])
						{
							CL->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[2];
							filled_nodes[cl] += 1;
						}
						else if(CL->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[1] &&
								CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[2])
						{
							CL->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[0];
							filled_nodes[cl] += 1;
						}
						else if(CL->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[2] &&
								CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[0])
						{
							CL->Specialized.N_List[4] = grid.Data.faces[f].Specialized.N_List[1];
							filled_nodes[cl] += 1;
						}
					}
				}
				break;

			case c_prism:
				if (grid.Data.faces[f].geometry.type == f_quadrilateral)
				{
					if (filled_nodes[cl] == 0) // FIRST FILLING
					{
						CL->Specialized.N_List[0] = grid.Data.faces[f].Specialized.N_List[0];
						CL->Specialized.N_List[1] = grid.Data.faces[f].Specialized.N_List[3];
						CL->Specialized.N_List[2] = grid.Data.faces[f].Specialized.N_List[2];
						CL->Specialized.N_List[3] = grid.Data.faces[f].Specialized.N_List[1];
						filled_nodes[cl] = 4;
					}
					else if(filled_nodes[cl] == 4)
					{
						vector<c_Node*> swap(6, NULL);

						if (CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[0] &&
							CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[1])
						{
							swap[0]	= CL->Specialized.N_List[0];
							swap[1]	= CL->Specialized.N_List[3];
							swap[2]	= grid.Data.faces[f].Specialized.N_List[3];
							swap[3]	= CL->Specialized.N_List[1];
							swap[4]	= CL->Specialized.N_List[2];
							swap[5]	= grid.Data.faces[f].Specialized.N_List[2];
						}
						else if(CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[1] &&
								CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[2])
						{
							swap[0]	= CL->Specialized.N_List[0];
							swap[1]	= CL->Specialized.N_List[3];
							swap[2]	= grid.Data.faces[f].Specialized.N_List[0];
							swap[3]	= CL->Specialized.N_List[1];
							swap[4]	= CL->Specialized.N_List[2];
							swap[5]	= grid.Data.faces[f].Specialized.N_List[3];
						}
						else if(CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[2] &&
								CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[3])
						{
							swap[0]	= CL->Specialized.N_List[0];
							swap[1]	= CL->Specialized.N_List[3];
							swap[2]	= grid.Data.faces[f].Specialized.N_List[1];
							swap[3]	= CL->Specialized.N_List[1];
							swap[4]	= CL->Specialized.N_List[2];
							swap[5]	= grid.Data.faces[f].Specialized.N_List[0];
						}
						else if(CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[3] &&
								CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[0])
						{
							swap[0]	= CL->Specialized.N_List[0];
							swap[1]	= CL->Specialized.N_List[3];
							swap[2]	= grid.Data.faces[f].Specialized.N_List[2];
							swap[3]	= CL->Specialized.N_List[1];
							swap[4]	= CL->Specialized.N_List[2];
							swap[5]	= grid.Data.faces[f].Specialized.N_List[1];
						}
						else if(CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[0] &&
								CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[1])
						{
							swap[0]	= CL->Specialized.N_List[0];
							swap[1]	= grid.Data.faces[f].Specialized.N_List[3];
							swap[2]	= CL->Specialized.N_List[1];
							swap[3]	= CL->Specialized.N_List[3];
							swap[4]	= grid.Data.faces[f].Specialized.N_List[2];
							swap[5]	= CL->Specialized.N_List[2];
						}
						else if(CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[1] &&
								CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[2])
						{
							swap[0]	= CL->Specialized.N_List[0];
							swap[1]	= grid.Data.faces[f].Specialized.N_List[0];
							swap[2]	= CL->Specialized.N_List[1];
							swap[3]	= CL->Specialized.N_List[3];
							swap[4]	= grid.Data.faces[f].Specialized.N_List[3];
							swap[5]	= CL->Specialized.N_List[2];
						}
						else if(CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[2] &&
								CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[3])
						{
							swap[0]	= CL->Specialized.N_List[0];
							swap[1]	= grid.Data.faces[f].Specialized.N_List[1];
							swap[2]	= CL->Specialized.N_List[1];
							swap[3]	= CL->Specialized.N_List[3];
							swap[4]	= grid.Data.faces[f].Specialized.N_List[0];
							swap[5]	= CL->Specialized.N_List[2];
						}
						else if(CL->Specialized.N_List[1] == grid.Data.faces[f].Specialized.N_List[3] &&
								CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[0])
						{
							swap[0]	= CL->Specialized.N_List[0];
							swap[1]	= grid.Data.faces[f].Specialized.N_List[2];
							swap[2]	= CL->Specialized.N_List[1];
							swap[3]	= CL->Specialized.N_List[3];
							swap[4]	= grid.Data.faces[f].Specialized.N_List[1];
							swap[5]	= CL->Specialized.N_List[2];
						}
						else if(CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[0] &&
								CL->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[1])
						{
							swap[0]	= CL->Specialized.N_List[0];
							swap[1]	= CL->Specialized.N_List[3];
							swap[2]	= grid.Data.faces[f].Specialized.N_List[2];
							swap[3]	= CL->Specialized.N_List[1];
							swap[4]	= CL->Specialized.N_List[2];
							swap[5]	= grid.Data.faces[f].Specialized.N_List[3];
						}
						else if(CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[1] &&
								CL->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[2])
						{
							swap[0]	= CL->Specialized.N_List[0];
							swap[1]	= CL->Specialized.N_List[3];
							swap[2]	= grid.Data.faces[f].Specialized.N_List[3];
							swap[3]	= CL->Specialized.N_List[1];
							swap[4]	= CL->Specialized.N_List[2];
							swap[5]	= grid.Data.faces[f].Specialized.N_List[0];
						}
						else if(CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[2] &&
								CL->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[3])
						{
							swap[0]	= CL->Specialized.N_List[0];
							swap[1]	= CL->Specialized.N_List[3];
							swap[2]	= grid.Data.faces[f].Specialized.N_List[0];
							swap[3]	= CL->Specialized.N_List[1];
							swap[4]	= CL->Specialized.N_List[2];
							swap[5]	= grid.Data.faces[f].Specialized.N_List[1];
						}
						else if(CL->Specialized.N_List[2] == grid.Data.faces[f].Specialized.N_List[3] &&
								CL->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[0])
						{
							swap[0]	= CL->Specialized.N_List[0];
							swap[1]	= CL->Specialized.N_List[3];
							swap[2]	= grid.Data.faces[f].Specialized.N_List[1];
							swap[3]	= CL->Specialized.N_List[1];
							swap[4]	= CL->Specialized.N_List[2];
							swap[5]	= grid.Data.faces[f].Specialized.N_List[2];
						}
						else if(CL->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[0] &&
								CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[1])
						{
							swap[0]	= CL->Specialized.N_List[0];
							swap[1]	= grid.Data.faces[f].Specialized.N_List[2];
							swap[2]	= CL->Specialized.N_List[1];
							swap[3]	= CL->Specialized.N_List[3];
							swap[4]	= grid.Data.faces[f].Specialized.N_List[3];
							swap[5]	= CL->Specialized.N_List[2];
						}
						else if(CL->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[1] &&
								CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[2])
						{
							swap[0]	= CL->Specialized.N_List[0];
							swap[1]	= grid.Data.faces[f].Specialized.N_List[3];
							swap[2]	= CL->Specialized.N_List[1];
							swap[3]	= CL->Specialized.N_List[3];
							swap[4]	= grid.Data.faces[f].Specialized.N_List[0];
							swap[5]	= CL->Specialized.N_List[2];
						}
						else if(CL->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[2] &&
								CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[3])
						{
							swap[0]	= CL->Specialized.N_List[0];
							swap[1]	= grid.Data.faces[f].Specialized.N_List[0];
							swap[2]	= CL->Specialized.N_List[1];
							swap[3]	= CL->Specialized.N_List[3];
							swap[4]	= grid.Data.faces[f].Specialized.N_List[1];
							swap[5]	= CL->Specialized.N_List[2];
						}
						else if(CL->Specialized.N_List[3] == grid.Data.faces[f].Specialized.N_List[3] &&
								CL->Specialized.N_List[0] == grid.Data.faces[f].Specialized.N_List[0])
						{
							swap[0]	= CL->Specialized.N_List[0];
							swap[1]	= grid.Data.faces[f].Specialized.N_List[1];
							swap[2]	= CL->Specialized.N_List[1];
							swap[3]	= CL->Specialized.N_List[3];
							swap[4]	= grid.Data.faces[f].Specialized.N_List[2];
							swap[5]	= CL->Specialized.N_List[2];
						}
						else
						{
							std::ostringstream error_message;
							error_message << "Cell ID:" << CL->geometry.id << " has problem during cell mesh construction. It is impossible configuration for prism cell.";
							OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NotSupportedType());
						}

						CL->Specialized.N_List[0]	= swap[0];
						CL->Specialized.N_List[1]	= swap[1];
						CL->Specialized.N_List[2]	= swap[2];
						CL->Specialized.N_List[3]	= swap[3];
						CL->Specialized.N_List[4]	= swap[4];
						CL->Specialized.N_List[5]	= swap[5];
						filled_nodes[cl] = 6;
					}
				}
				break;
			}
		}
	} // End for filling node list

	// 2.2 ASSIGN FACE ID ON CELL
	vector<int>face_counter(grid.Info.NCM, 0);
	for (int f = 0; f <= grid.Info.NFM-1; f++)
	{
		unsigned int c;
		if (grid.Data.faces[f].Specialized.cl != NULL)
		{
			c	= grid.Map.c_ID_to_pos[grid.Data.faces[f].Specialized.cl->geometry.id];
			grid.Data.cells[c].Specialized.F_List[face_counter[c]] = &grid.Data.faces[f];
			face_counter[c]++;
		}

		if (grid.Data.faces[f].Specialized.cr != NULL)
		{
			c	= grid.Map.c_ID_to_pos[grid.Data.faces[f].Specialized.cr->geometry.id];
			grid.Data.cells[c].Specialized.F_List[face_counter[c]] = &grid.Data.faces[f];
			face_counter[c]++;
		}
	}

	// 3. Find cell centroid and area/volume
#pragma ivdep
	for (int c = 0; c <= grid.Info.NCM-1; c++)
	{
		// a. Calculate location of cell-center
		for (int d = 0; d <= grid.Info.DIM-1; d++)
		{
			grid.Data.cells[c].geometry.x[d]	= 0.0;
			int nn	= grid.Data.cells[c].Specialized.N_List.size();

			for (int n = 0; n <= nn-1; n++)
			{
				grid.Data.cells[c].geometry.x[d] += grid.Data.cells[c].Specialized.N_List[n]->geometry.x[d];
			}
			grid.Data.cells[c].geometry.x[d] /= nn;

			if (grid.Data.cells[c].geometry.x[d] != grid.Data.cells[c].geometry.x[d])
			{
				std::ostringstream error_message;
				error_message << "Cell ID:" << grid.Data.cells[c].geometry.id << ", Direction:" << d << "  has problem in calculating position: NaN value";
				OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NaNValue());
			}

			if (grid.Data.cells[c].geometry.x[d] == numeric_limits<double>::infinity())
			{
				std::ostringstream error_message;
				error_message << "Cell ID:" << grid.Data.cells[c].geometry.id << ", Direction:" << d << "  has problem in calculating possition: Inf value";
				OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::InfValue());
			}
		}


		// b. Calculate S (Area/ Volume)
		switch (grid.Data.cells[c].geometry.type)
		{
		case c_triangle:
			grid.Data.cells[c].geometry.S	= OP2A::MATH::CalAreaTriangle(grid.Data.cells[c].Specialized.N_List[0]->geometry.x,
																		grid.Data.cells[c].Specialized.N_List[1]->geometry.x,
																		grid.Data.cells[c].Specialized.N_List[2]->geometry.x);
			break;

		case c_tetrahedron:
					grid.Data.cells[c].geometry.S	= OP2A::MATH::CalVolumeTetrahedron(grid.Data.cells[c].Specialized.N_List[0]->geometry.x,
																					grid.Data.cells[c].Specialized.N_List[1]->geometry.x,
																					grid.Data.cells[c].Specialized.N_List[2]->geometry.x,
																					grid.Data.cells[c].Specialized.N_List[3]->geometry.x);
					break;


		case c_quadrilateral:
			grid.Data.cells[c].geometry.S	= OP2A::MATH::CalAreaQuadrilateral(grid.Data.cells[c].Specialized.N_List[0]->geometry.x,
																			grid.Data.cells[c].Specialized.N_List[1]->geometry.x,
																			grid.Data.cells[c].Specialized.N_List[2]->geometry.x,
																			grid.Data.cells[c].Specialized.N_List[3]->geometry.x);
			break;

		case c_hexahedron:
			grid.Data.cells[c].geometry.S	= OP2A::MATH::CalVolumeHexahedron(grid.Data.cells[c].Specialized.N_List[0]->geometry.x,
																			grid.Data.cells[c].Specialized.N_List[1]->geometry.x,
																			grid.Data.cells[c].Specialized.N_List[2]->geometry.x,
																			grid.Data.cells[c].Specialized.N_List[3]->geometry.x,
																			grid.Data.cells[c].Specialized.N_List[4]->geometry.x,
																			grid.Data.cells[c].Specialized.N_List[5]->geometry.x,
																			grid.Data.cells[c].Specialized.N_List[6]->geometry.x,
																			grid.Data.cells[c].Specialized.N_List[7]->geometry.x);
			break;

		case c_pyramid:
			grid.Data.cells[c].geometry.S	= OP2A::MATH::CalVolumePyramid(grid.Data.cells[c].Specialized.N_List[0]->geometry.x,
																			grid.Data.cells[c].Specialized.N_List[1]->geometry.x,
																			grid.Data.cells[c].Specialized.N_List[2]->geometry.x,
																			grid.Data.cells[c].Specialized.N_List[3]->geometry.x,
																			grid.Data.cells[c].Specialized.N_List[4]->geometry.x);
			break;

		case c_prism:
			grid.Data.cells[c].geometry.S	= OP2A::MATH::CalVolumeWedge(grid.Data.cells[c].Specialized.N_List[0]->geometry.x,
																			grid.Data.cells[c].Specialized.N_List[1]->geometry.x,
																			grid.Data.cells[c].Specialized.N_List[2]->geometry.x,
																			grid.Data.cells[c].Specialized.N_List[3]->geometry.x,
																			grid.Data.cells[c].Specialized.N_List[4]->geometry.x,
																			grid.Data.cells[c].Specialized.N_List[5]->geometry.x);
			break;
		}


		if (grid.Data.cells[c].geometry.S != grid.Data.cells[c].geometry.S)
		{
			std::ostringstream error_message;
			error_message << "Cell ID:" << grid.Data.cells[c].geometry.id << " has problem in calculating area: NaN value";
			OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NaNValue());
		}

		if (grid.Data.cells[c].geometry.S == numeric_limits<double>::infinity())
		{
			std::ostringstream error_message;
			error_message << "Cell ID:" << grid.Data.cells[c].geometry.id << " has problem in calculating area: Inf value";
			OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::InfValue());
		}

		if (grid.Data.cells[c].geometry.S < 0.0)
		{
			std::ostringstream error_message;
			error_message << "Cell ID:" << grid.Data.cells[c].geometry.id << " has problem in calculating area: Negative value";
			OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NegativeValue());
		}
	}


	// 4. Calculating characteristic length
#pragma ivdep
	for (int c = 0; c <= grid.Info.NCM-1; c++)
	{
		double xf[4][3];
		double length, aux;

		switch (grid.Data.cells[c].geometry.type)
		{
		case c_triangle:
			length	= grid.Data.cells[c].geometry.S;
			grid.Data.cells[c].Specialized.charcteristic_lentgh	= sqrt(length);
			break;

		case c_tetrahedron:
			for (int d = 0; d <= grid.Info.DIM-1; d++)
			{
				xf[0][d] = (grid.Data.cells[c].Specialized.N_List[0]->geometry.x[d]
				          + grid.Data.cells[c].Specialized.N_List[1]->geometry.x[d]
				          + grid.Data.cells[c].Specialized.N_List[2]->geometry.x[d]) / 3.0;

				xf[1][d] = (grid.Data.cells[c].Specialized.N_List[0]->geometry.x[d]
						  + grid.Data.cells[c].Specialized.N_List[1]->geometry.x[d]
						  + grid.Data.cells[c].Specialized.N_List[3]->geometry.x[d]) / 3.0;

				xf[2][d] = (grid.Data.cells[c].Specialized.N_List[1]->geometry.x[d]
						  + grid.Data.cells[c].Specialized.N_List[2]->geometry.x[d]
						  + grid.Data.cells[c].Specialized.N_List[3]->geometry.x[d]) / 3.0;

				xf[3][d] = (grid.Data.cells[c].Specialized.N_List[0]->geometry.x[d]
						  + grid.Data.cells[c].Specialized.N_List[4]->geometry.x[d]
						  + grid.Data.cells[c].Specialized.N_List[2]->geometry.x[d]) / 3.0;
			}

			aux	= 0.0;
			for (int d = 0; d <= grid.Info.DIM-1; d++)	aux += pow(grid.Data.cells[c].geometry.x[d] - xf[0][d], 2.0);
			length	= sqrt(aux);

			for (int j = 1; j <= 3; j++)
			{
				aux = 0.0;
				for (int d = 0; d <= grid.Info.DIM-1; d++)	aux += pow(grid.Data.cells[c].geometry.x[d] - xf[j][d], 2.0);
				aux 	= sqrt(aux);

				length	= fmin(length, aux);
			}

			grid.Data.cells[c].Specialized.charcteristic_lentgh	= 2.0 *length;
			break;

		case c_quadrilateral:
			for (int d = 0; d <= grid.Info.DIM-1; d++)
			{
				xf[0][d] = grid.Data.cells[c].Specialized.N_List[1]->geometry.x[d] - grid.Data.cells[c].Specialized.N_List[0]->geometry.x[d];
				xf[1][d] = grid.Data.cells[c].Specialized.N_List[3]->geometry.x[d] - grid.Data.cells[c].Specialized.N_List[0]->geometry.x[d];
			}

			length	= 0.0;
			aux		= 0.0;
			for (int d = 0; d <= grid.Info.DIM-1; d++)
			{
				length	+= pow(xf[0][d], 2.0);
				aux		+= pow(xf[1][d], 2.0);
			}

			length	= fmin(length, aux);
			grid.Data.cells[c].Specialized.charcteristic_lentgh	= sqrt(length);
			break;

		case c_hexahedron:
			for (int d = 0; d <= grid.Info.DIM-1; d++)
			{
				xf[0][d] = grid.Data.cells[c].Specialized.N_List[1]->geometry.x[d] - grid.Data.cells[c].Specialized.N_List[0]->geometry.x[d];
				xf[1][d] = grid.Data.cells[c].Specialized.N_List[2]->geometry.x[d] - grid.Data.cells[c].Specialized.N_List[0]->geometry.x[d];
				xf[2][d] = grid.Data.cells[c].Specialized.N_List[3]->geometry.x[d] - grid.Data.cells[c].Specialized.N_List[0]->geometry.x[d];
			}

			length	= 0.0;
			aux		= 0.0;
			for (int d = 0; d <= grid.Info.DIM-1; d++)
			{
				length	+= pow(xf[0][d], 2.0);
				aux		+= pow(xf[1][d], 2.0);
			}
			length	= fmin(length, aux);

			aux		= 0.0;
			for (int d = 0; d <= grid.Info.DIM-1; d++)	aux += pow(xf[2][d], 2.0);
			length	= fmin(length, aux);

			grid.Data.cells[c].Specialized.charcteristic_lentgh	= sqrt(length);
			break;

		case c_pyramid:
			length = pow(grid.Data.cells[c].geometry.S, 1.0/3.0);
			grid.Data.cells[c].Specialized.charcteristic_lentgh	= length;
			break;

		case c_prism:
			for (int d = 0; d <= grid.Info.DIM-1; d++)
			{
				xf[0][d] = grid.Data.cells[c].Specialized.N_List[1]->geometry.x[d] - grid.Data.cells[c].Specialized.N_List[0]->geometry.x[d];
				xf[1][d] = grid.Data.cells[c].Specialized.N_List[2]->geometry.x[d] - grid.Data.cells[c].Specialized.N_List[0]->geometry.x[d];
				xf[2][d] = grid.Data.cells[c].Specialized.N_List[3]->geometry.x[d] - grid.Data.cells[c].Specialized.N_List[0]->geometry.x[d];
			}

			aux = 	pow(0.5*(xf[0][1]*xf[1][2] - xf[0][2]*xf[1][1]), 2.0);
			aux	+= 	pow(-0.5*(xf[0][0]*xf[1][2] - xf[0][2]*xf[1][0]), 2.0);
			aux	+=	pow(0.5*(xf[0][0]*xf[1][1] - xf[0][1]*xf[1][0]), 2.0);
			length	= pow(aux, 0.25);

			aux	= 0.0;
			for (int d = 0; d <= grid.Info.DIM-1; d++) aux	+= pow(xf[2][d], 2.0);
			aux = sqrt(aux);

			length	= fmin(length, aux);
			grid.Data.cells[c].Specialized.charcteristic_lentgh	= length;
			break;
		}


		if (grid.Data.cells[c].Specialized.charcteristic_lentgh != grid.Data.cells[c].Specialized.charcteristic_lentgh)
		{
			std::ostringstream error_message;
			error_message << "Cell ID:" << grid.Data.cells[c].geometry.id << " has problem in calculating Characteristic length: NaN value";
			OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NaNValue());
		}

		if (grid.Data.cells[c].Specialized.charcteristic_lentgh == numeric_limits<double>::infinity())
		{
			std::ostringstream error_message;
			error_message << "Cell ID:" << grid.Data.cells[c].geometry.id << " has problem in Characteristic length: Inf value";
			OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::InfValue());
		}

		if (grid.Data.cells[c].Specialized.charcteristic_lentgh < 0.0)
		{
			std::ostringstream error_message;
			error_message << "Cell ID:" << grid.Data.cells[c].geometry.id << " has problem in cCharacteristic length: Negative value";
			OP2A::Common::ExceptionGeneral(FromHere(), error_message.str(), OP2A::Common::ErrorCode::NegativeValue());
		}
	}



	// 5. Assigning Neighboring cells on node
	for (int n = 0; n <= grid.Info.NNM-1; n++)
	{
		grid.Data.nodes[n].Specialized.C_List.resize(0);
		grid.Data.nodes[n].Specialized.Wc.resize(0);
	}

	for (int c = 0; c <= grid.Info.NCM-1; c++)
	{
		for (int n = 0; n <= grid.Data.cells[c].Specialized.N_List.size()-1; n++)
		{
			grid.Data.cells[c].Specialized.N_List[n]->Specialized.C_List.push_back(&grid.Data.cells[c]);
			grid.Data.cells[c].Specialized.N_List[n]->Specialized.Wc.push_back(1.0);
		}
	}



	// 6. Find Neighboring cells
	c_Node* curr_Node;
	for (int c = 0; c <= grid.Info.NCM-1; c++)
	{
		grid.Data.cells[c].Specialized.Neighbor_List.resize(0);

		// First allocation of neighbor cells from node1
		curr_Node = grid.Data.cells[c].Specialized.N_List[0];
		for (int cc = 0; cc <= curr_Node->Specialized.C_List.size()-1; cc++)
		{
			if (curr_Node->Specialized.C_List[cc] != &grid.Data.cells[c])
			{
				grid.Data.cells[c].Specialized.Neighbor_List.push_back(curr_Node->Specialized.C_List[cc]);
			}
		}

		for (int n = 1; n <= grid.Data.cells[c].Specialized.N_List.size()-1; n++)
		{
			curr_Node = grid.Data.cells[c].Specialized.N_List[n];
			for (int cc = 0; cc <= curr_Node->Specialized.C_List.size()-1; cc++)
			{
				if (curr_Node->Specialized.C_List[cc] != &grid.Data.cells[c])
				{
					OP2A::Common::addPointerInVector<c_Cell>(grid.Data.cells[c].Specialized.Neighbor_List, curr_Node->Specialized.C_List[cc]);
				}
			}
		}
	}

}




}
