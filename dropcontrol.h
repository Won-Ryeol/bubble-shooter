#pragma once

#include "SolidSphere.h"
#include <vector>

using namespace std;

class Dropcontrol {
public:
	Dropcontrol(int h);
	bool search( SolidSphere s, SolidSphere sph);
	void operator()(vector<SolidSphere>& sphes, SolidSphere& sph, vector<int>& dnum);

private:
	int height;
};