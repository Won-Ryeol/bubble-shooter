#pragma once
#include "SolidSphere.h"
class GameOver 
{
public:
	bool GameOverDetection(SolidSphere sph, float height);
private:
	bool over = false;
};