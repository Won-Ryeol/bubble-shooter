#include "GameOver.h"

bool GameOver::GameOverDetection(SolidSphere sph, float height)
{
	if (sph.getmoved() == true && (sph.getCenter()[1] - sph.getProperties()[0]) < -height / 2 + 120)
		over = true;
	else
		over = false;
	return over;
}
//if (spheres[spheres.size() - (size(spheres) > 1 ? 2 : 1)].getVelocity()[1] == 0)