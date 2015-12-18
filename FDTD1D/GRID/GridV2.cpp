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
#include <COMMON/Assert.hpp>




namespace OP2A {
namespace GRID {

Grid_V2::Grid_V2(unsigned int Nx, unsigned int Ny, unsigned int Nz):
		DIM(3), m_Max_Refine_Level(0), NNM(0), NFM(0), NCM(0), NGM(0),
		m_Unstructured(false),
		m_IJK_node(Nx, Ny, Nz),	m_whereisNode(m_IJK_node.max()+1, -1),
		m_IJK_face(Nx, Ny, Nz),	m_whereisFace(m_IJK_face.max()+1, -1),
		m_IJK_cell(Nx, Ny, Nz),	m_whereisCell(m_IJK_cell.max()+1, -1)
{


}

Grid_V2::Grid_V2(unsigned int Nx, unsigned int Ny):
		DIM(2), m_Max_Refine_Level(0), NNM(0), NFM(0), NCM(0), NGM(0),
		m_Unstructured(false),
		m_IJK_node(Nx, Ny), m_whereisNode(m_IJK_node.max()+1, -1),
		m_IJK_face(Nx, Ny),	m_whereisFace(m_IJK_face.max()+1, -1),
		m_IJK_cell(Nx, Ny),	m_whereisCell(m_IJK_cell.max()+1, -1)
{
		m_Node_Data.reserve(Nx*Ny*100);
		m_Face_Data.reserve((2*Nx*Ny + Nx + Ny)*100);
		m_Cell_Data.reserve(Nx*Ny*100);
		m_Ghost_Data.reserve(2*(2*Nx + 2*Ny));
}



Grid_V2::~Grid_V2()
{


}


/*
 * Functions
 */
void Grid_V2::Update_Number_Info()
{
	NNM	= Node_List.size();
	NFM	= Face_List.size();
	NCM	= Cell_List.size();
}





/*
 * 1.1. Calling Functions
 */
//		Node
c_Node* Grid_V2::NODE(double i, double j, double k)
{
	int ID_n	= m_IJK_node.ID(i, j, k);
	int pos_n	= m_whereisNode[ID_n];

	if (pos_n >= 0)
	{
		if (typeid(&m_Node_Data[pos_n]) != typeid(c_Node*))
		{
			Common::ExceptionGeneral(FromHere(),
									"NODE:: corresponding position of node ID is not the pointer of Node",
									Common::ErrorCode::NotMatchTypeofPointer());
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

	int ID_n	= m_IJK_node.ID(i, j);
	int pos_n	= m_whereisNode[ID_n];

	if (pos_n >= 0)
	{
		if (typeid(&m_Node_Data[pos_n]) != typeid(c_Node*))
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
	int ID_n	= m_IJK_node.ID(i, 0.0);
	int pos_n	= m_whereisNode[ID_n];

	if (pos_n >= 0)
	{
		if (typeid(&m_Node_Data[pos_n]) != typeid(c_Node*))
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

c_Node& Grid_V2::NODE_data(unsigned int i)
{
	mk_assert(i <= m_Node_Data.size()-1);
	return (m_Node_Data[i]);
}


//		Face
c_Face* Grid_V2::FACE(double i, double j, double k)
{
	int ID_n	= m_IJK_face.ID(i, j, k);
	int pos_n	= m_whereisFace[ID_n];

	if (pos_n >= 0)
	{
		if (typeid(&m_Face_Data[pos_n]) != typeid(c_Face*))
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
	int ID_n	= m_IJK_face.ID(i, j);
	int pos_n	= m_whereisFace[ID_n];

	if (pos_n >= 0)
	{
		if (typeid(&m_Face_Data[pos_n]) != typeid(c_Face*))
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
	int ID_n	= m_IJK_face.ID(i, 0.0);
	int pos_n	= m_whereisFace[ID_n];


	if (pos_n >= 0)
	{
		if (typeid(&m_Face_Data[pos_n]) != typeid(c_Face*))
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

c_Face& Grid_V2::FACE_data(unsigned int i)
{
	mk_assert(i <= m_Face_Data.size()-1);
	return (m_Face_Data[i]);
}


//		Cell
c_Cell* Grid_V2::CELL(double i, double j, double k)
{
	int ID_n	= m_IJK_cell.ID(i, j, k);
	int pos_n	= m_whereisCell[ID_n];

	if (pos_n >= 0)
	{
		if (typeid(&m_Cell_Data[pos_n]) != typeid(c_Cell*))
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
	int ID_n	= m_IJK_cell.ID(i, j);
	int pos_n	= m_whereisCell[ID_n];


	if (pos_n >= 0)
	{
		if (typeid(&m_Cell_Data[pos_n]) != typeid(c_Cell*))
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
	int ID_n	= m_IJK_cell.ID(i, 0.0);
	int pos_n	= m_whereisCell[ID_n];

	if (pos_n >= 0)
	{
		if (typeid(&m_Cell_Data[pos_n]) != typeid(c_Cell*))
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

c_Cell& Grid_V2::CELL_data(unsigned int i)
{
	mk_assert(i <= m_Cell_Data.size()-1);
	return (m_Cell_Data[i]);
}


/*
 * 1.2.	Resize Functions
 */
void Grid_V2::NODE_resize(unsigned int n_size)
{
	m_Node_Data.resize(n_size);
}

void Grid_V2::FACE_resize(unsigned int f_size)
{
	m_Face_Data.resize(f_size);
}

void Grid_V2::CELL_resize(unsigned int c_size)
{
	m_Cell_Data.resize(c_size);
}

void Grid_V2::GHOST_resize(unsigned int c_size)
{
	m_Ghost_Data.resize(c_size);
}



/*
 * 1.3. Add Functions
 */

//		Node
void Grid_V2::NODE_add(double i, double j, double k, const c_Node& node)
{
	int ID_n	= m_IJK_node.ID(i, j, k);
	int pos_n	= m_whereisNode[ID_n];

	if (pos_n >= 0)
	{
		if (m_Node_Data.size() < pos_n + 1)	m_Node_Data.resize(pos_n+1);

		m_Node_Data[pos_n]		= node;
		m_Node_Data[pos_n].ID 	= ID_n;
	}
	else
	{
		m_Node_Data.push_back(node);
		m_whereisNode[ID_n]	= m_Node_Data.size() -1;
		m_Node_Data[m_whereisNode[ID_n]].ID = ID_n;
	}
}

void Grid_V2::NODE_add(double i, double j, double k)
{
	int ID_n	= m_IJK_node.ID(i, j, k);
	int pos_n	= m_whereisNode[ID_n];

	if (pos_n < 0)
	{
		m_Node_Data.resize(m_Node_Data.size()+1);
		m_whereisNode[ID_n]	= m_Node_Data.size() -1;
		m_Node_Data[m_whereisNode[ID_n]].ID = ID_n;
	}
}

void Grid_V2::NODE_add(double i, double j, const c_Node& node)	{NODE_add(i, j, 0.0, node); 	}
void Grid_V2::NODE_add(double i, const c_Node& node)			{NODE_add(i, 0.0, 0.0, node);	}
void Grid_V2::NODE_add(double i, double j)						{NODE_add(i, j, 0.0);			}
void Grid_V2::NODE_add(double i)								{NODE_add(i, 0.0, 0.0);			}

//		Face
void Grid_V2::FACE_add(double i, double j, double k, const c_Face& face)
{
	int ID_f	= m_IJK_face.ID(i, j, k);
	int pos_f	= m_whereisFace[ID_f];

	if (pos_f >= 0)
	{
		if (m_Face_Data.size() < pos_f + 1)	m_Face_Data.resize(pos_f+1);

		m_Face_Data[pos_f] 		= face;
		m_Face_Data[pos_f].ID 	= ID_f;
		m_Face_Data[pos_f].index.i = i;
		m_Face_Data[pos_f].index.j = j;
		m_Face_Data[pos_f].index.k = k;
	}
	else
	{
		int m_size = m_Face_Data.size();
		m_Face_Data.resize(m_size+1);
		m_whereisFace[ID_f]	= m_size;

		m_Face_Data[m_size]	= face;
		m_Face_Data[m_size].ID = ID_f;
		m_Face_Data[m_size].index.i = i;
		m_Face_Data[m_size].index.j = j;
		m_Face_Data[m_size].index.k = k;
	}
}

void Grid_V2::FACE_add(double i, double j, double k)
{
	int ID_f	= m_IJK_face.ID(i, j, k);
	int pos_f	= m_whereisFace[ID_f];

	if (pos_f < 0)
	{
		int m_size = m_Face_Data.size();
		m_Face_Data.resize(m_size+1);
		m_whereisFace[ID_f]	= m_size;

		m_Face_Data[m_size].ID = ID_f;
		m_Face_Data[m_size].index.i = i;
		m_Face_Data[m_size].index.j = j;
		m_Face_Data[m_size].index.k = k;
	}
}

void Grid_V2::FACE_add(double i, double j, const c_Face& face)	{FACE_add(i, j, 0.0, face);	}
void Grid_V2::FACE_add(double i, const c_Face& face)			{FACE_add(i, 0.0, face);	}
void Grid_V2::FACE_add(double i, double j)						{FACE_add(i, j, 0.0);		}
void Grid_V2::FACE_add(double i)								{FACE_add(i, 0.0, 0.0);		}

//		Cell
void Grid_V2::CELL_add(double i, double j, double k, const c_Cell& cell)
{
	int ID_c	= m_IJK_cell.ID(i, j, k);
	int pos_c	= m_whereisCell[ID_c];

	if (pos_c >= 0)
	{
		if (m_Cell_Data.size() < pos_c + 1)	m_Cell_Data.resize(pos_c+1);

		m_Cell_Data[pos_c] = cell;
		m_Cell_Data[pos_c].ID 	= ID_c;
	}
	else
	{
		m_Cell_Data.push_back(cell);
		m_whereisCell[ID_c]	= m_Cell_Data.size() -1;
		m_Cell_Data[m_whereisCell[ID_c]].ID = ID_c;
	}
}

void Grid_V2::CELL_add(double i, double j, double k)
{
	int ID_c	= m_IJK_cell.ID(i, j, k);
	int pos_c	= m_whereisCell[ID_c];

	if (pos_c < 0)
	{
		m_Cell_Data.resize(m_Cell_Data.size()+1);
		m_whereisCell[ID_c]	= m_Cell_Data.size() - 1;
		m_Cell_Data[m_whereisCell[ID_c]].ID = ID_c;
	}
}

void Grid_V2::CELL_add(double i, double j, const c_Cell& cell)	{CELL_add(i, j, 0.0, cell);		}
void Grid_V2::CELL_add(double i, const c_Cell& cell)			{CELL_add(i, 0.0, 0.0, cell);	}
void Grid_V2::CELL_add(double i, double j)						{CELL_add(i, j, 0.0);			}
void Grid_V2::CELL_add(double i)								{CELL_add(i, 0.0, 0.0);			}



/*
 * 1.4. Remove functions
 */
//		Node
void Grid_V2::NODE_remove(c_Node* node)
{
	if (node != NULL)
	{
		int ID_n	= node->ID;
		int pos_n	= m_whereisNode[ID_n];

		if (pos_n >= 0)
		{
			m_Node_Data.erase(m_Node_Data.begin()+pos_n);
			m_whereisNode[ID_n] = -1;

			for (int i_pos = pos_n; i_pos <= m_Node_Data.size()-1; i_pos++)
			{
				m_whereisNode[m_Node_Data[i_pos].ID]	= i_pos;
			}
		}
	}
}

void Grid_V2::NODE_remove(double i, double j, double k)
{
	int ID_n	= m_IJK_node.ID(i, j, k);
	int pos_n	= m_whereisNode[ID_n];

	if (pos_n >= 0)
	{
		m_Node_Data.erase(m_Node_Data.begin()+pos_n);
		m_whereisNode[ID_n] = -1;

		for (int i_pos = pos_n; i_pos <= m_Node_Data.size()-1; i_pos++)
		{
			m_whereisNode[m_Node_Data[i_pos].ID]	= i_pos;
		}
	}
}

void Grid_V2::NODE_remove(double i, double j)	{NODE_remove(i, j, 0.0);		}
void Grid_V2::NODE_remove(double i)				{NODE_remove(i, 0.0, 0.0);		}


//		Face
void Grid_V2::FACE_remove(c_Face* face)
{
	if (face != NULL)
	{
		int ID_f	= face->ID;
		int pos_f	= m_whereisFace[ID_f];

		if (pos_f >= 0)
		{
			m_Face_Data.erase(m_Face_Data.begin()+pos_f);
			m_whereisFace[ID_f] = -1;

			for (int i_pos = pos_f; i_pos <= m_Face_Data.size()-1; i_pos++)
			{
				m_whereisFace[m_Face_Data[i_pos].ID]	= i_pos;
			}
		}
	}
}

void Grid_V2::FACE_remove(double i, double j, double k)
{
	int ID_f	= m_IJK_face.ID(i, j, k);
	int pos_f	= m_whereisFace[ID_f];

	if (pos_f >= 0)
	{
		m_Face_Data.erase(m_Face_Data.begin()+pos_f);
		m_whereisFace[ID_f] = -1;

		for (int i_pos = pos_f; i_pos <= m_Face_Data.size()-1; i_pos++)
		{
			m_whereisFace[m_Face_Data[i_pos].ID]	= i_pos;
		}
	}
}

void Grid_V2::FACE_remove(double i, double j)	{FACE_remove(i, j, 0.0);	}
void Grid_V2::FACE_remove(double i)				{FACE_remove(i, 0.0, 0.0);	}


//		Cell
void Grid_V2::CELL_remove(c_Cell* cell)
{
	if (cell != NULL)
	{
		int ID_c	= cell->ID;
		int pos_c	= m_whereisCell[ID_c];

		if (pos_c >= 0)
		{
			m_Cell_Data.erase(m_Cell_Data.begin()+pos_c);
			m_whereisCell[ID_c] = -1;

			for (int i_pos = pos_c; i_pos <= m_Cell_Data.size()-1; i_pos++)
			{
				m_whereisCell[m_Cell_Data[i_pos].ID]	= i_pos;
			}
		}
	}
}

void Grid_V2::CELL_remove(double i, double j, double k)
{
	int ID_c	= m_IJK_cell.ID(i, j, k);
	int pos_c	= m_whereisCell[ID_c];

	if (pos_c >= 0)
	{
		m_Cell_Data.erase(m_Cell_Data.begin()+pos_c);
		m_whereisCell[ID_c] = -1;

		for (int i_pos = pos_c; i_pos <= m_Face_Data.size()-1; i_pos++)
		{
			m_whereisCell[m_Cell_Data[i_pos].ID]	= i_pos;
		}
	}
}

void Grid_V2::CELL_remove(double i, double j)	{CELL_remove(i, j, 0.0);	}
void Grid_V2::CELL_remove(double i)				{CELL_remove(i, 0.0, 0.0);	}



/*
 * 1.5. SetPosition
 */
void Grid_V2::NODE_setPos(double i, double j, double k, unsigned int pos)
{
	int ID_n	= m_IJK_node.ID(i, j, k);
	m_whereisNode[ID_n]	= pos;
}

void Grid_V2::FACE_setPos(double i, double j, double k, unsigned int pos)
{
	int ID_f	= m_IJK_face.ID(i, j, k);
	m_whereisFace[ID_f]	= pos;
}

void Grid_V2::CELL_setPos(double i, double j, double k, unsigned int pos)
{
	int ID_c	= m_IJK_cell.ID(i, j, k);
	m_whereisCell[ID_c]	= pos;
}




// 6. Update Node/Face/Cell List
void Grid_V2::NODE_ListUpdate()
{
	Node_List.clear();
	for (int n = 0; n <= m_Node_Data.size()-1; n++)
	{
		if (m_Node_Data[n].BC >= 1)	Node_List.push_back(&m_Node_Data[n]);
	}

	NNM	= m_Node_Data.size();
}

void Grid_V2::FACE_ListUpdate()
{
	Face_List.clear();
	for (int ii = 0; ii <= CONST_MAX_REFINEMENT_LEVEL; ii++)	Face_List_Parent[ii].clear();

	for (int f = 0; f <= m_Face_Data.size()-1; f++)
	{
		if (m_Face_Data[f].CL->type != -1 || m_Face_Data[f].CR->type != -1)
		{
			if (m_Face_Data[f].has_Child == false)
			{
				Face_List.push_back(&m_Face_Data[f]);
			}
			else
			{
				Face_List_Parent[m_Face_Data[f].index.lvl_refine].push_back(&m_Face_Data[f]);
			}
		}
	}

	NFM	= m_Face_Data.size();
}

void Grid_V2::CELL_ListUpdate()
{
	Cell_List.clear();
	for (int ii = 0; ii <= CONST_MAX_REFINEMENT_LEVEL; ii++)	Cell_List_Parent[ii].clear();

	for (int c = 0; c <= m_Cell_Data.size()-1; c++)
	{
		if (m_Cell_Data[c].type != -1)
		{
			if (m_Cell_Data[c].has_Child == false)
			{
				Cell_List.push_back(&m_Cell_Data[c]);
				m_Cell_Data[c].include();
			}
			else
			{
				Cell_List_Parent[m_Cell_Data[c].index.lvl_refine].push_back(&m_Cell_Data[c]);
				m_Cell_Data[c].remove();
			}
		}
		else
		{
			m_Cell_Data[c].remove();
		}
	}

	NCM	= m_Cell_Data.size();
}



// 7. Get Position of IDs
int Grid_V2::NODE_pos(unsigned int ID)
{
	if (ID <= m_whereisNode.size())	return (m_whereisNode[ID]);
	else							return (-1);
}

int Grid_V2::FACE_pos(unsigned int ID)
{
	if (ID <= m_whereisFace.size())	return (m_whereisFace[ID]);
	else							return (-1);
}

int Grid_V2::CELL_pos(unsigned int ID)
{
	if (ID <= m_whereisCell.size())	return (m_whereisCell[ID]);
	else							return (-1);
}


// 8. Add Ghost Cell
void Grid_V2::GHOST_add()
{
	m_Ghost_Data.resize(m_Ghost_Data.size() + 1);
	NGM	= m_Ghost_Data.size();

}

void Grid_V2::GHOST_add(const c_Cell& ghost)
{
	m_Ghost_Data.push_back(ghost);
	NGM	= m_Ghost_Data.size();
}

c_Cell& Grid_V2::GHOST_data(unsigned int i)
{
	mk_assert(i <= m_Ghost_Data.size()-1);
	return (m_Ghost_Data[i]);
}



} /* namespace FDTD */
} /* namespace OP2A */
