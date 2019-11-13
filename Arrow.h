#pragma once

#include "SolidShape3D.h"

class Arrow : public SolidShape3D
{
public:
	Arrow();
	void setArrow(float cornbase, float cornheight, float cylinderbase, float cylindertop, float cylinderheight);
	~Arrow();
	float* getProperties() const;
	float getAngleOfArrow() const;
	void setAngleOfArrow(float angle);
	void draw() const;

private:
	float* properties;
	float AngleOfArrow;
};

