#include "dropcontrol.h"

Dropcontrol::Dropcontrol(int h) { height = h; };

bool Dropcontrol::search(SolidSphere s, SolidSphere sph) {
	return (
		sqrt(dotProduct(s.getCenter() - sph.getCenter(), s.getCenter() - sph.getCenter())) <= 2 * s.getProperties()[0] + 5
		&& sqrt(dotProduct(s.getCenter() - sph.getCenter(), s.getCenter() - sph.getCenter())) >= 2 * s.getProperties()[0] - 5
		&& s.getmarked() == false);
};


void Dropcontrol::operator()(vector<SolidSphere>& sphes, SolidSphere& sph, vector<int>& dnum) {

	for (int i = 0; i < sphes.size() - 1; i++)
	{
		if (search(sphes[i], sph)) {
			dnum.push_back(i);
			sphes[i].setmarked();
		};
	}
};