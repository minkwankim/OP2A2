/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * TimeFunctions.cpp
 *
 *  Created on: Oct 28, 2015
 *      Author: minkwan
 */

#include "TimeFunctions.hpp"

//////////////////////////////////////////////////////////////////////////////
namespace OP2A {
namespace Common{


/*
 * Data for time
 *
 * @author	Minkwan
 * @version 1.0 15/5/2015
 */
const double	TimeData::secPerHour	= 1.0/3600.0;
const double	TimeData::secPerMin		= 1.0/60.0;
const double	TimeData::usecPerSec	= 1.0e-6;
const double	TimeData::nsecPerSec	= 1.0e-9;

// Constructor
TimeData::TimeData(): m_h(0.0), m_m(0.0), m_s(0.0)	{	}
TimeData::TimeData(const double &sec)
{
	set(sec);
}

// Destructor
TimeData::~TimeData()	{	}

// setting time
void TimeData::set(double t_in_sec)
{
	m_h = floor(t_in_sec * secPerHour);
	m_m = floor((t_in_sec - m_h * 3600.) * secPerMin);
	m_s = t_in_sec - m_h * 3600. - m_m * 60.;
}

// String of time information
std::string TimeData::str() const
{
	std::ostringstream	oss;
	if (m_h > 0)	oss << m_h << " h ";
	if (m_m > 0)	oss << m_m << "min ";
	oss << m_s << "sec";

	return oss.str();
}


/*
 * Function to express current time in seconds
 */
double dtime()
{
	double tseconds	= 0.0;
	struct timeval	mytime;

	gettimeofday(&mytime, (struct timezone*)0);

	tseconds	= (double)(mytime.tv_sec	+ mytime.tv_usec*1.0e-6);
	return	(tseconds);
};



/*
 * Class for Time usages check
 *
 * 	@author	Minkwan Kim
 * 	@version 1.0	15/5/2015
 */

// Constructor
TimeInfoUsage::TimeInfoUsage() : m_StartTime(0.0), m_StopTime(0.0) { }


// Get time info in second
double TimeInfoUsage::seconds() const
{
	rusage usg;
	getrusage(RUSAGE_SELF, &usg);

	timeval usertime = usg.ru_utime;
	return (usertime.tv_sec + (usertime.tv_usec * TimeData::usecPerSec));
}

// set initial time info in seconds
void TimeInfoUsage::initStartTime()
{
	m_StartTime	= seconds();
}

// Set time info
void TimeInfoUsage::takeStopTime()
{
	m_StopTime	= seconds();
}

// Accummurate time elapsed
void TimeInfoUsage::accumulateTime(double& accTime)
{
	accTime	+= (m_StopTime - m_StartTime);
}

// Calculate time elapsed from start
double TimeInfoUsage::getDeltaT() const
{
	return (seconds() - m_StartTime);
}





/*
 * Class for Time usages check using Clock
 *
 * 	@author	Minkwan Kim
 * 	@version 1.0	15/5/2015
 */
// Constructor
TimeInfoClock::TimeInfoClock() : m_StartTime(0.0), m_StopTime(0.0) { }


double TimeInfoClock::seconds() const
{
	const double	secs_per_tick = 1.0 / CLOCKS_PER_SEC;
	return ( static_cast<double>(clock()) ) * secs_per_tick;
}


void TimeInfoClock::initStartTime()
{
	m_StartTime	= seconds();
}

void TimeInfoClock::takeStopTime()
{
	m_StopTime	= seconds();
}

void TimeInfoClock::accumulateTime(double& accTime)
{
	accTime	+= (m_StopTime - m_StartTime);
}

double TimeInfoClock::getDeltaT() const
{
	return (seconds() - m_StartTime);
}



}
}
