#pragma once
#include "SolidSphere.h"
#include <vector>
using namespace std;

class GameClear 
{
public:
	GameClear();
	void operator()(vector<SolidSphere> sphes);
	bool getclear();
	void reset();
private:
	bool clear = false;
};