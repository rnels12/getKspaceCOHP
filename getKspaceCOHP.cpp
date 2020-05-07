/*
 *  Created by Ryky Nelson March 2019
 */

#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <math.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <boost/format.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <algorithm>

using namespace std;
using namespace Eigen;

void Usage(string exe_name){    
    cerr << "ERROR: please specify atom-orbital pairs and KspaceCOHP file(s)!\n";
    cerr << "E.g.: " << exe_name << " Na1 3s Cl2 3p_x KspaceCOHPBand2.lobster KspaceCOHPBand6.lobster\n"; 
}

void author(){    
    cerr << "Program is created by Ryky Nelson.\n"
	 << "The use of the program is free for non-commercial use only!\n";
}

int main(int argc, char* argv[]){

    try{
	string flag(argv[1]);
	if (flag == "-c" || flag == "-C") {
	    author();
	    return 0;
	}
    }
    catch(...){
	Usage(argv[0]);
	return 0;
    }

    try{
	if (argc < 6 ) throw "ERROR!\n";
    }
    catch(const char* msg){
	Usage(argv[0]);
	return 0;
    }

    string mu = argv[1]; mu += '_'; mu += argv[2];
    string nu = argv[3]; nu += '_'; nu += argv[4];

    for(int ifb=5; ifb < argc; ++ifb) {
	ifstream bsfile( argv[ifb] );
	string line; stringstream ss;
	string trash, keyword;

	getline(bsfile, line);
	getline(bsfile, line);
	ss.str(line); ss.clear();
	ss >> keyword;

	if (keyword != "COHP_munujk") {
	    cerr << argv[ifb] << " seems not a KspaceCOHP file, please check! \n";
	    cerr << "Exiting now!\n";
	    return 0;
	}

	//get eigenVal
	double eval;
	ss >> trash >> trash >> trash >> trash >> trash >> eval;
	ss >> trash >> trash >> trash >> trash;

	//get the kpt vector data
	Vector3d kpt_prev;
	ss >> kpt_prev(0) >> kpt_prev(1) >> kpt_prev(2);

	double kcoord(0);
	cout << kpt_prev.transpose() << ' '
	     << kcoord << ' ' << eval << ' ';

	getline(bsfile, line);
	ss.str(string()); ss.str(line); ss.clear();
	ss >> keyword;
	if (keyword != "basisfunction") {
	    cerr << argv[ifb] << " seems not a KspaceCOHP file, please check! \n";
	    cerr << "Exiting now!\n";
	    return 0;
	}
	string foo;
	vector<string> basisF;
	while (getline(ss, foo, ' ')) {
	    boost::trim(foo);
	    std::stringstream stream(foo);
	    if(stream >> trash) {
		if (!foo.empty()) basisF.push_back(foo);
	    }
	}

	int norb = basisF.size();	
	// getting orbital mu index
	vector<string>::iterator itBF = find(basisF.begin(), basisF.end(), mu);
	if ( itBF == basisF.end() ) {
	    cerr << "basis function is not part of the projection.\n";
	    cerr << "Exiting now!\n";
	    return 0;
	}
	int imu = distance(basisF.begin(),itBF);

	// getting orbital nu index
	itBF = find(basisF.begin(), basisF.end(), nu);
	if ( itBF == basisF.end() ) {
	    cerr << "basis function is not part of the projection.\n";
	    cerr << "Exiting now!\n";
	    return 0;
	}
	int inu = distance(basisF.begin(),itBF);

	//getting the value for the first kpt
	for (int i = 0; i <= imu; ++i) getline(bsfile, line);
	ss.str(string()); ss.str(line); ss.clear();
	for (int i = 0; i <= (inu+1); ++i) {
	    while(getline(ss, foo, ' ')){
		boost::trim(foo);
		std::stringstream stream(foo);
		if(stream >> trash) break;
	    }
	}
	double CohpMuNu;
	if (!foo.empty()) {
	    stringstream ssFoo(foo);
	    ssFoo >> CohpMuNu;
	    cout << CohpMuNu << endl;
	}
	
	while (getline(bsfile, line)) {
	    Vector3d kpt;	    
	    ss.str(string()); ss.str(line); ss.clear();
	    ss >> keyword;
	    if (keyword == "COHP_munujk") {
		ss >> trash >> trash >> trash >> trash >> trash >> eval;
		ss >> trash >> trash >> trash >> trash;
		ss >> kpt(0) >> kpt(1) >> kpt(2);
		
		kcoord +=  (kpt-kpt_prev).norm();
		cout << kpt.transpose() << ' ' 
		     << kcoord << ' ' << eval << ' ';
		kpt_prev = kpt;		
	    }
	    else if (keyword == "basisfunction") {
		//getting the value for the given kpt
		for (int i = 0; i <= imu; ++i) getline(bsfile, line);
		ss.str(string()); ss.str(line); ss.clear();
		for (int i = 0; i <= (inu+1); ++i) {
		    while(getline(ss, foo, ' ')){
			boost::trim(foo);
			std::stringstream stream(foo);
			if(stream >> trash) break;
		    }
		}
		double CohpMuNu;
		if (!foo.empty()) {
		    stringstream ssFoo(foo);
		    ssFoo >> CohpMuNu;
		    cout << CohpMuNu << endl;
		}

	    }
	}

	cout << endl;
    } //for ifb
    
    return 0;
}
