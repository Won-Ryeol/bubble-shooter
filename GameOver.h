#pragma once
#include "SolidSphere.h"
class GameOver 
{
public:
	GameOver();
	void operator()(SolidSphere sph, float height);
	bool getover();
	void reset();
private:
	bool over = false;
};