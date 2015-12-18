/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * Nomenclatures.hpp
 *
 *  Created on: Nov 6, 2015
 *      Author: minkwan
 */

#ifndef NOMENCLATURES_HPP_
#define NOMENCLATURES_HPP_

#include "COMMON/Common.hpp"


namespace OP2A {



/*
 * Scalar variables
 */

static const std::string	Cv			= "SpecificHeat";
static const std::string	Cv_mix		= "MixtureSpecificHeat";
static const std::string	Cv_s		= "SpeciesSpecificHeat";

static const std::string	Cv_tra		= "TranslationalSpecificHeat";
static const std::string	Cv_tra_mix	= "TrnaslationalMixtureSpecificHeat";
static const std::string	Cv_tra_s	= "TranslationalSpeciesSpecificHeat";

static const std::string	Cv_rot		= "RotationalSpecificHeat";
static const std::string	Cv_rot_mix	= "RotationalMixtureSpecificHeat";
static const std::string	Cv_rot_s	= "RotationalSpeciesSpecificHeat";

static const std::string	Cv_vib		= "VibrationalSpecificHeat";
static const std::string	Cv_vib_mix	= "VibrationalMixtureSpecificHeat";
static const std::string	Cv_vib_s	= "VibrationalSpeciesSpecificHeat";

static const std::string	Cv_tr		= "TranslationRotationalSpecificHeat";
static const std::string	Cv_tr_mix	= "TranslationRotationalMixtureSpecificHeat";
static const std::string	Cv_tr_s		= "TranslationRotationalSpeciesSpecificHeat";

static const std::string	epsilon_EM	= "Permittivity";

static const std::string	kappa		= "ThermalConductivity";
static const std::string	kappa_tra	= "TranslationalThermalConductivity";
static const std::string	kappa_rot	= "RotationalThermalConductivity";
static const std::string	kappa_vib	= "VibrationThermalConductivity";
static const std::string	kappa_tr	= "TranslationalRotationalThermalConductivity";

static const std::string	mu_EM		= "Permeability";

static const std::string	phi			= "Potential";

static const std::string	rho_s		= "SpeciesDensity";
static const std::string	rho_mix		= "MixtureDensity";

static const std::string	sigma		= "Conductivity";
static const std::string	sigma_m		= "MagneticConductivity";

static const std::string	T			= "Temperature";
static const std::string	T_tra		= "TranslationalTemperature";
static const std::string	T_rot		= "RotationalTemperature";
static const std::string	T_vib		= "VibrationTemperature";
static const std::string	T_e			= "ElectronTemperature";
static const std::string	T_tr		= "TranslationalRotationalTemperature";


/*
 * Vector Variables
 */
static const std::string	B	= "MagneticFluxDensity";
static const std::string	D	= "ElectricFluxDensity";
static const std::string	E	= "ElectricField";
static const std::string	H	= "MagneticField";
static const std::string	J	= "CurrentDensity";
static const std::string	K	= "SurfaceCurrentDensity";
static const std::string	Q	= "ConservativeVariables";
static const std::string	U	= "Velocity";
static const std::string	V	= "PremitiveVariables";
static const std::string	W	= "PremitiveVariablesWithPressure";

static const std::string	CoeffE	= "CoefficientForElectricFieldUpdate";
static const std::string	CoeffH	= "CoefficientForMagneticFieldUpdate";

static const std::string	M_source = "SourceofMagneticField";




/*
 * Matrix variables
 */
static const std::string	tau			= "ShearStressTensor";
static const std::string	Jvis		= "ViscousJacovian";
static const std::string	J_vis_p		= "ViscousJacovianPlus";
static const std::string	J_vis_m		= "ViscousJacovianMinus";
static const std::string	J_inv		= "InviscidJacovian";
static const std::string	J_inv_p		= "InviscidJacovianPlus";
static const std::string	J_inv_m		= "InviscidJacovianMinus";



}


#endif /* NOMENCLATURES_HPP_ */
