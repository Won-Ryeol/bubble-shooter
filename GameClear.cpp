#include "GameClear.h"

GameClear::GameClear() { clear = false; };

void GameClear::operator()(vector<SolidSphere> sphes)
{
	if (sphes.size()==1)
		clear = true;
}

bool GameClear::getclear() { return clear; };

void GameClear::reset() { clear =false; };