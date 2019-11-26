#include "Removecontrol.h"

Removecontrol::Removecontrol() {};

bool Removecontrol::search(SolidSphere s, SolidSphere sph) {
	return (
		   sqrt(dotProduct(s.getCenter() - sph.getCenter(), s.getCenter() - sph.getCenter())) <= 2 * s.getProperties()[0]+5
		&& sqrt(dotProduct(s.getCenter() - sph.getCenter(), s.getCenter() - sph.getCenter())) >= 2 * s.getProperties()[0]-5
		&& s.getMTL() == sph.getMTL()
		&& s.getremovesearch() == false);
};

void Removecontrol::operator()(vector<SolidSphere>& sphes ,SolidSphere& sph, vector<int> &removenum) {
	sph.setremovesearch();
	for (int i = 0; i < sphes.size()-1; i++)
	{
		if (sphes[i].getremovesearch() == false)
		{
			if (search(sphes[i], sph) == 1) {
				removenum.push_back(i);
				sphes[i].setremovesearch();
			};
		}
	}
};
