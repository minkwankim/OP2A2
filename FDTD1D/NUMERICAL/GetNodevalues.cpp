/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * GetNodevalues.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: minkwan
 */


#include "GRID/GridV2.hpp"

namespace OP2A {



void GetNodeVariables(GRID::c_Grid& grid, const std::vector<unsigned int>& variableFlagCell, const std::vector<unsigned int>& variableFlagNode, unsigned int method)
{
	switch (method)
	{
	case 0:
#pragma ivdep
		for (int n = 0; n <= grid.NNM-1; n++)
		{
			for (int v = 0; v <= variableFlagCell.size()-1; v++)
			{

				double sumValue = 0.0;
				for (int c = 0; c <= grid.NODE_data(n).C_List.size()-1; c++)
				{
					sumValue	+= grid.NODE_data(n).C_List[c]->data[variableFlagCell[v]];
				}


				grid.NODE_data(n).data[variableFlagNode[v]]	= sumValue / grid.NODE_data(n).C_List.size();
			}
		}

		break;

	case 1:
#pragma ivdep
		for (int n = 0; n <= grid.NNM-1; n++)
		{
			for (int v = 0; v <= variableFlagCell.size()-1; v++)
			{
				double sumValue = 0.0;
				for (int c = 0; c <= grid.NODE_data(n).C_List.size()-1; c++)
				{
					sumValue	+= grid.NODE_data(n).Wc[c] * grid.NODE_data(n).C_List[c]->data[variableFlagCell[v]];
				}

				grid.NODE_data(n).data[variableFlagNode[v]]	= sumValue;
			}
		}
		break;
	}
}




}
