#pragma once
#include "SolidSphere.h"
#include <vector>

using namespace std;

class Removecontrol {
public :
	Removecontrol();

	bool search(SolidSphere sph, SolidSphere s);
	void operator()(vector<SolidSphere>& sphes, SolidSphere& sph, vector<int> & removenum);

};