#include "GameOver.h"

GameOver::GameOver() { over = false; };

void GameOver::operator()(SolidSphere sph, float height)
{
	if (sph.getmoved() == true && (sph.getCenter()[1] - sph.getProperties()[0]) < -height / 2 + 120)
		over = true;
}

bool GameOver::getover() { return over; };

void GameOver::reset() { over=false; };