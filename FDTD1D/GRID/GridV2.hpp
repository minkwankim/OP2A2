/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GridV2.hpp
 *
 *  Created on: Nov 30, 2015
 *      Author: minkwan
 */

#ifndef GRIDV2_HPP_
#define GRIDV2_HPP_


#include "./COMMON/Map1D.hpp"
#include "./COMMON/Map2D.hpp"
#include "./COMMON/Map3D.hpp"
#include "./COMMON/ExceptionGeneral.hpp"
#include "./COMMON/VectorMultiDimension.hpp"


#include "NodeV2.hpp"
#include "FaceV2.hpp"
#include "CellV2.hpp"
#include "GridSetupParameter.hpp"




using namespace std;



namespace OP2A {
namespace GRID {

class IJK
{
public:
	IJK(unsigned int Nx, unsigned int Ny, unsigned int Nz)
	: m_Nx(Nx) , m_Ny(Ny), m_Nz(Nz), m_MaxLvl(CONST_MAX_REFINEMENT_LEVEL)
	{
		m_aux1 = pow(2.0, m_MaxLvl);
		m_MaxNx	= m_Nx * m_aux1 + 1;
		m_MaxNy	= m_Ny * m_aux1 + 1;
		m_MaxNz	= m_Nz * m_aux1 + 1;

		m_aux2	= m_MaxNx*m_MaxNy;

		if (Nz == 0)	m_MaxID = ID(Nx, Ny);
		else			m_MaxID = ID(Nx, Ny, Nz);
	}

	IJK(unsigned int Nx, unsigned int Ny)
	: m_Nx(Nx) , m_Ny(Ny), m_Nz(0), m_MaxLvl(CONST_MAX_REFINEMENT_LEVEL)
	{
		m_aux1 = pow(2.0, m_MaxLvl);
		m_MaxNx	= m_Nx * m_aux1 + 1;
		m_MaxNy	= m_Ny * m_aux1 + 1;
		m_MaxNz	= m_Nz * m_aux1 + 1;

		m_aux2	= m_MaxNx*m_MaxNy;

		m_MaxID = ID(Nx, Ny);
	}




	~IJK()
	{

	}

private:
	const unsigned int m_Nx;
	const unsigned int m_Ny;
	const unsigned int m_Nz;
	const int m_MaxLvl;
	unsigned int m_MaxNx;
	unsigned int m_MaxNy;
	unsigned int m_MaxNz;
	unsigned int m_aux1;
	unsigned int m_aux2;
	unsigned int m_MaxID;

public:
	unsigned int ID(double i, double j)
	{
		unsigned int ip	= i * m_aux1;
		unsigned int jp = j * m_aux1;

		return (ip + jp *m_MaxNx);
	}

	unsigned int ID(double i, double j, double k)
	{
		unsigned int ip	= i * m_aux1;
		unsigned int jp = j * m_aux1;
		unsigned int kp = k * m_aux1;

		return (ip + jp *m_MaxNx + kp*m_aux2);
	}

	unsigned int max()
	{
		return (m_MaxID);
	}
};



class IJK_face
{
public:
	IJK_face(unsigned int Nx, unsigned int Ny, unsigned int Nz)
	: m_Nx(Nx) , m_Ny(Ny), m_Nz(Nz), m_MaxLvl(CONST_MAX_REFINEMENT_LEVEL)
	{
		m_aux1 = pow(2.0, m_MaxLvl+1);
		m_MaxNx	= m_Nx * m_aux1 + 1;
		m_MaxNy	= m_Ny * m_aux1 + 1;
		m_MaxNz	= m_Nz * m_aux1 + 1;
		m_aux2	= m_MaxNx * m_MaxNy;

		if (Nz == 0)	m_MaxID = ID(Nx, Ny);
		else			m_MaxID = ID(Nx, Ny, Nz);
	}

	IJK_face(unsigned int Nx, unsigned int Ny)
	: m_Nx(Nx) , m_Ny(Ny), m_Nz(0), m_MaxLvl(CONST_MAX_REFINEMENT_LEVEL)
	{
		m_aux1 = pow(2.0, m_MaxLvl+1);
		m_MaxNx	= m_Nx * m_aux1 + 1;
		m_MaxNy	= m_Ny * m_aux1 + 1;
		m_MaxNz	= m_Nz * m_aux1 + 1;
		m_aux2	= m_MaxNx*m_MaxNy;

		m_MaxID = ID(Nx, Ny);
	}

	~IJK_face()
	{

	}

private:
	const unsigned int m_Nx;
	const unsigned int m_Ny;
	const unsigned int m_Nz;
	const int m_MaxLvl;
	unsigned int m_MaxNx;
	unsigned int m_MaxNy;
	unsigned int m_MaxNz;
	unsigned int m_aux1;
	unsigned int m_aux2;
	unsigned int m_MaxID;

public:
	unsigned int ID(double i, double j)
	{
		unsigned int ip	= i * m_aux1;
		unsigned int jp = j * m_aux1;

		return (ip + jp *m_MaxNx);
	}

	unsigned int ID(double i, double j, double k)
	{
		unsigned int ip	= i * m_aux1;
		unsigned int jp = j * m_aux1;
		unsigned int kp = k * m_aux1;

		return (ip + jp *m_MaxNx + kp*m_aux2);
	}

	unsigned int max()
	{
		return (m_MaxID);
	}
};



class IJK_cell
{
public:
	IJK_cell(unsigned int Nx, unsigned int Ny, unsigned int Nz)
	: m_Nx(Nx) , m_Ny(Ny), m_Nz(Nz), m_MaxLvl(CONST_MAX_REFINEMENT_LEVEL)
	{
		m_aux1 = pow(2.0, m_MaxLvl+1);
		m_MaxNx	= m_Nx * m_aux1 + 1;
		m_MaxNy	= m_Ny * m_aux1 + 1;
		m_MaxNz	= m_Nz * m_aux1 + 1;
		m_aux2	= m_MaxNx * m_MaxNy;

		if (Nz == 0)	m_MaxID = ID(Nx, Ny);
		else			m_MaxID = ID(Nx, Ny, Nz);
	}

	IJK_cell(unsigned int Nx, unsigned int Ny)
	: m_Nx(Nx) , m_Ny(Ny), m_Nz(0), m_MaxLvl(CONST_MAX_REFINEMENT_LEVEL)
	{
		m_aux1 = pow(2.0, m_MaxLvl+1);
		m_MaxNx	= m_Nx * m_aux1 + 1;
		m_MaxNy	= m_Ny * m_aux1 + 1;
		m_MaxNz	= m_Nz * m_aux1 + 1;
		m_aux2	= m_MaxNx*m_MaxNy;

		m_MaxID = ID(Nx, Ny);
	}

	~IJK_cell()
	{

	}

private:
	const unsigned int m_Nx;
	const unsigned int m_Ny;
	const unsigned int m_Nz;
	const int m_MaxLvl;
	unsigned int m_MaxNx;
	unsigned int m_MaxNy;
	unsigned int m_MaxNz;
	unsigned int m_aux1;
	unsigned int m_aux2;
	unsigned int m_MaxID;

public:
	unsigned int ID(double i, double j)
	{
		unsigned int ip	= i * m_aux1;
		unsigned int jp = j * m_aux1;

		return (ip + jp *m_MaxNx);
	}

	unsigned int ID(double i, double j, double k)
	{
		unsigned int ip	= i * m_aux1;
		unsigned int jp = j * m_aux1;
		unsigned int kp = k * m_aux1;

		return (ip + jp *m_MaxNx + kp*m_aux2);
	}

	unsigned int max()
	{
		return (m_MaxID);
	}
};






class Grid_V2 {
public:
	Grid_V2(unsigned int Nx, unsigned int Ny, unsigned int Nz);
	Grid_V2(unsigned int Nx, unsigned int Ny);
	~Grid_V2();



public:
	// Data Index Section
	Common::Map1D<string, unsigned int>	Node_Data_Map;
	Common::Map1D<string, unsigned int>	Face_Data_Map;
	Common::Map1D<string, unsigned int>	Cell_Data_Map;


	// Basic DATA Section
	unsigned int DIM;
	unsigned int NNM;
	unsigned int NFM;
	unsigned int NCM;


	// List Data
	vector<c_Node*>	Node_List;
	vector<c_Face*>	Face_List;
	vector<c_Cell*>	Cell_List;
	vector< vector<c_Face*>	> Face_List_Parent;
	vector< vector<c_Cell*>	> Cell_List_Parent;
	vector<c_Face*>	Face_List_Boundary;
	vector<c_Cell*>	Cell_List_Ghost;


	vector<unsigned int>	whereisGhost;	// [Ghost ID]	==> gives actual location in cell data array


	//Common::Map3D<double, double, double, unsigned int>		Node_Index_Map;
	//Common::Map3D<double, double, double, unsigned int>		Face_Index_Map;
	std::vector< std::vector< std::vector <Cell_IJK> > >	Cell_Index_Map;



protected:
	// Actual Data Section
	vector<c_Cell>	m_Ghost_Data;

	// Node
	IJK						m_IJK_node;
	vector<int>				m_whereisNode;		// [Node ID] 	==> gives actual location in node data array
	vector<c_Node>			m_Node_Data;

	// Face
	IJK_face				m_IJK_face;
	vector<int>				m_whereisFace;		// [Face ID] 	==> gives actual location in node data array
	vector<c_Face>			m_Face_Data;

	// Cell
	IJK_cell				m_IJK_cell;
	vector<int>				m_whereisCell;		// [Cell ID] 	==> gives actual location in node data array
	vector<c_Cell>			m_Cell_Data;



protected:
	unsigned int m_Max_Refine_Level;
	unsigned int m_Unstructured;




public:
	void Set_Refine_Level(unsigned int lvl);
	void Update_Number_Info();

	c_Node* NODE(double i, double j, double k);
	c_Node* NODE(double i, double j);
	c_Node* NODE(double i);

	c_Face* FACE(double i, double j, double k);
	c_Face* FACE(double i, double j);
	c_Face* FACE(double i);

	c_Cell* CELL(double i, double j, double k);
	c_Cell* CELL(double i, double j);
	c_Cell* CELL(double i);

};












} /* namespace GRID */
} /* namespace OP2A */

#endif /* GRIDV2_HPP_ */
