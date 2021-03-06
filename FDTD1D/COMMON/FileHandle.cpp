/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 *
 * 		Copyright (c) 2015 MINKWAN KIM
 *
 * FileHandle.cpp
 *
 *  Created on: Dec 2, 2015
 *      Author: minkwan
 */

#include <COMMON/FileHandle.hpp>

using namespace std;

namespace OP2A {
namespace Common {

void FileHandle::merge (const std::string& file1, const std::string& file2, const std::string& file3)
{
	// Create output file
	std::ofstream outFile(file3.c_str(), ios::out);

	// Open input file 1, if can't be opened, exit
	std::ifstream in1(file1.c_str());
	std::string line;

	if(!in1)
	{
		cerr << "[File Merge]: Open Failure - Cannot file 1st file" << endl;
		exit(1);
	}
	else
	{
		while(std::getline(in1, line))
		{
			outFile << line << "\n";
		}
	}
	in1.close();

	//Open input file 2, if can't be opened, exit
	ifstream in2(file2.c_str());
	if(!in2)
	{
		cerr << "[File Merge]: Open Failure - Cannot file 2nd file" << endl;
		exit(1);
	}
	else
	{
		while(std::getline(in2, line))
		{
			outFile << line << "\n";
		} //end while
	} //end else
	in2.close();

	outFile.close();
}


void FileHandle::merge (const std::string& file1, const std::string& file2, const std::string& file3, const std::string& file4)
{
	// Create output file
	std::ofstream outFile(file4.c_str(), ios::out);

	// Open input file 1, if can't be opened, exit
	std::ifstream in1(file1.c_str());
	std::string line;

	if(!in1)
	{
		cerr << "[File Merge]: Open Failure - Cannot file 1st file" << endl;
		exit(1);
	}
	else
	{
		while(std::getline(in1, line))
		{
			outFile << line << "\n";
		}
	}
	in1.close();

	//Open input file 2, if can't be opened, exit
	ifstream in2(file2.c_str());
	if(!in2)
	{
		cerr << "[File Merge]: Open Failure - Cannot file 2nd file" << endl;
		exit(1);
	}
	else
	{
		while(std::getline(in2, line))
		{
			outFile << line << "\n";
		} //end while
	} //end else
	in2.close();

	//Open input file 3, if can't be opened, exit
	ifstream in3(file3.c_str());
	if(!in3)
	{
		cerr << "[File Merge]: Open Failure - Cannot file 3rd file" << endl;
		exit(1);
	}
	else
	{
		while(std::getline(in3, line))
		{
			outFile << line << "\n";
		} //end while
	} //end else
	in3.close();

	outFile.close();
}

void FileHandle::Xmerge (const std::string& file1, const std::string& file2, const std::string& file3)
{
	merge(file1, file2, file3);
	remove(file1.c_str());
	remove(file2.c_str());
}

void FileHandle::Xmerge (const std::string& file1, const std::string& file2, const std::string& file3, const std::string& file4)
{
	merge(file1, file2, file3, file4);

	remove(file1.c_str());
	remove(file2.c_str());
	remove(file3.c_str());
}



} /* namespace Common */
} /* namespace OP2A */
