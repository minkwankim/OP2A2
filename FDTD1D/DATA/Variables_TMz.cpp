/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Variables_TMz.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: minkwan
 */


#include "DATA/Variables.hpp"

using namespace std;

namespace OP2A{
namespace DATA{


void VariableTMz_face(Common::Map1D<string, unsigned int>& data_map, std::vector<double>& data_storage)
{
	unsigned int i = 0;

	data_map.clear();
	data_map.insert(H, 					i);	i++;
	data_map.insert(sigma_m, 			i);	i++;
	data_map.insert(mu_EM, 				i);	i++;
	data_map.insert(M_source, 			i);	i++;
	data_map.insert("dt_sigma_2mu", 	i);	i++;
	data_map.insert("dt_mu", 			i);	i++;

	data_storage.resize(i);
}

void VariableTMz_node(Common::Map1D<string, unsigned int>& data_map, std::vector<double>& data_storage)
{
	unsigned int i = 0;

	data_map.clear();
	data_map.insert(E, 					i);	i++;
	data_map.insert(sigma, 				i);	i++;
	data_map.insert(epsilon_EM, 		i);	i++;
	data_map.insert(J, 					i);	i++;
	data_map.insert("dt_sigma_2eps", 	i);	i++;
	data_storage.resize(i);
}

void VariableTMz_cell(Common::Map1D<string, unsigned int>& data_map, std::vector<double>& data_storage)
{
	unsigned int i = 0;

	data_map.clear();
	data_map.insert(E, 					i);	i++;
	data_map.insert(sigma, 				i);	i++;
	data_map.insert(epsilon_EM, 		i);	i++;
	data_map.insert(J, 					i);	i++;
	data_map.insert("dt_sigma_2eps", 	i);	i++;
	data_storage.resize(i);
}

}
}

