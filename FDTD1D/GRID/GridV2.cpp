/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GridV2.cpp
 *
 *  Created on: Nov 30, 2015
 *      Author: minkwan
 */

#include <GRID/GridV2.hpp>
#include <COMMON/ExceptionGeneral.hpp>
#include <COMMON/ErrorCode.hpp>



namespace OP2A {
namespace GRID {

Grid_V2::Grid_V2(unsigned int Nx, unsigned int Ny, unsigned int Nz):
		DIM(3), m_Max_Refine_Level(0), NNM(0), NFM(0), NCM(0),
		m_Unstructured(false),
		m_IJK_node(Nx, Ny, Nz),	m_whereisNode(m_IJK_node.max(), -1),
		m_IJK_face(Nx, Ny, Nz),	m_whereisFace(m_IJK_face.max(), -1),
		m_IJK_cell(Nx, Ny, Nz),	m_whereisCell(m_IJK_cell.max(), -1)
{


}

Grid_V2::Grid_V2(unsigned int Nx, unsigned int Ny):
		DIM(2), m_Max_Refine_Level(0), NNM(0), NFM(0), NCM(0),
		m_Unstructured(false),
		m_IJK_node(Nx, Ny), m_whereisNode(m_IJK_node.max(), -1),
		m_IJK_face(Nx, Ny),	m_whereisFace(m_IJK_face.max(), -1),
		m_IJK_cell(Nx, Ny),	m_whereisCell(m_IJK_cell.max(), -1)
{

}



Grid_V2::~Grid_V2()
{


}


/*
 * Functions
 */
void Grid_V2::Set_Refine_Level(unsigned int lvl)
{
	m_Max_Refine_Level	= lvl;

	if (lvl != 0)
	{
		Face_List_Parent.resize(lvl);
		Cell_List_Parent.resize(lvl);
	}
}

void Grid_V2::Update_Number_Info()
{
	NNM	= Node_List.size();
	NFM	= Face_List.size();
	NCM	= Cell_List.size();
}






c_Node* Grid_V2::NODE(double i, double j, double k)
{
	int pos_n	= m_IJK_node.ID(i, j, k);

	if (pos_n > 0)
	{
		if (typeid(m_Node_Data[pos_n]) != typeid(c_Node*))
		{
			Common::ExceptionGeneral(FromHere(), "NODE:: corresponding position of node ID is not the pointer of Node", Common::ErrorCode::NotMatchTypeofPointer());
		}

		return (&m_Node_Data[pos_n]);
	}
	else
	{
		return (NULL);
	}
}

c_Node* Grid_V2::NODE(double i, double j)
{
	int pos_n	= m_IJK_node.ID(i, j);

	if (pos_n > 0)
	{
		if (typeid(m_Node_Data[pos_n]) != typeid(c_Node*))
		{
			Common::ExceptionGeneral(FromHere(), "NODE:: corresponding position of node ID is not the pointer of Node", Common::ErrorCode::NotMatchTypeofPointer());
		}

		return (&m_Node_Data[pos_n]);
	}
	else
	{
		return (NULL);
	}
}


c_Node* Grid_V2::NODE(double i)
{
	int pos_n	= m_IJK_node.ID(i, 0.0);

	if (pos_n > 0)
	{
		if (typeid(m_Node_Data[pos_n]) != typeid(c_Node*))
		{
			Common::ExceptionGeneral(FromHere(), "NODE:: corresponding position of node ID is not the pointer of Node", Common::ErrorCode::NotMatchTypeofPointer());
		}

		return (&m_Node_Data[pos_n]);
	}
	else
	{
		return (NULL);
	}
}





c_Face* Grid_V2::FACE(double i, double j, double k)
{
	int pos_n	= m_IJK_face.ID(i, j, k);

	if (pos_n > 0)
	{
		if (typeid(m_Face_Data[pos_n]) != typeid(c_Face*))
		{
			Common::ExceptionGeneral(FromHere(), "Face:: corresponding position of node ID is not the pointer of Face", Common::ErrorCode::NotMatchTypeofPointer());
		}

		return (&m_Face_Data[pos_n]);
	}
	else
	{
		return (NULL);
	}
}

c_Face* Grid_V2::FACE(double i, double j)
{
	int pos_n	= m_IJK_face.ID(i, j);

	if (pos_n > 0)
	{
		if (typeid(m_Face_Data[pos_n]) != typeid(c_Face*))
		{
			Common::ExceptionGeneral(FromHere(), "Face:: corresponding position of node ID is not the pointer of Face", Common::ErrorCode::NotMatchTypeofPointer());
		}

		return (&m_Face_Data[pos_n]);
	}
	else
	{
		return (NULL);
	}
}

c_Face* Grid_V2::FACE(double i)
{
	int pos_n	= m_IJK_face.ID(i, 0.0);

	if (pos_n > 0)
	{
		if (typeid(m_Face_Data[pos_n]) != typeid(c_Face*))
		{
			Common::ExceptionGeneral(FromHere(), "Face:: corresponding position of node ID is not the pointer of Face", Common::ErrorCode::NotMatchTypeofPointer());
		}

		return (&m_Face_Data[pos_n]);
	}
	else
	{
		return (NULL);
	}
}



c_Cell* Grid_V2::CELL(double i, double j, double k)
{
	int pos_n	= m_IJK_cell.ID(i, j, k);

	if (pos_n > 0)
	{
		if (typeid(m_Cell_Data[pos_n]) != typeid(c_Cell*))
		{
			Common::ExceptionGeneral(FromHere(), "CELL:: corresponding position of cell ID is not the pointer of Cell", Common::ErrorCode::NotMatchTypeofPointer());

		}
		return (&m_Cell_Data[pos_n]);
	}
	else
	{
		return (NULL);
	}
}

c_Cell* Grid_V2::CELL(double i, double j)
{
	int pos_n	= m_IJK_cell.ID(i, j);

	if (pos_n > 0)
	{
		if (typeid(m_Cell_Data[pos_n]) != typeid(c_Cell*))
		{
			Common::ExceptionGeneral(FromHere(), "CELL:: corresponding position of cell ID is not the pointer of Cell", Common::ErrorCode::NotMatchTypeofPointer());

		}
		return (&m_Cell_Data[pos_n]);
	}
	else
	{
		return (NULL);
	}
}

c_Cell* Grid_V2::CELL(double i)
{
	int pos_n	= m_IJK_cell.ID(i, 0.0);

	if (pos_n > 0)
	{
		if (typeid(m_Cell_Data[pos_n]) != typeid(c_Cell*))
		{
			Common::ExceptionGeneral(FromHere(), "CELL:: corresponding position of cell ID is not the pointer of Cell", Common::ErrorCode::NotMatchTypeofPointer());

		}
		return (&m_Cell_Data[pos_n]);
	}
	else
	{
		return (NULL);
	}
}


} /* namespace FDTD */
} /* namespace OP2A */
