#include "SolidShape3D.h"

SolidShape3D::SolidShape3D() {
	center.setXYZ(0, 0, 0);
	velocity.setXYZ(0, 0, 0);

	setMTL();
}

SolidShape3D::SolidShape3D(const SolidShape3D& sh3d) {
	setCenter(sh3d.center);
	setVelocity(sh3d.velocity);
	mtl.setMTL(sh3d.mtl);
}

void SolidShape3D::setCenter(float x, float y, float z) {
	center[0] = x;
	center[1] = y;
	center[2] = z;
}

void SolidShape3D::setCenter(const Vector3& c) {
	center = c;
}

Vector3 SolidShape3D::getCenter() const {
	return center;
}

void SolidShape3D::setVelocity(float x, float y, float z) {
	velocity[0] = x;
	velocity[1] = y;
	velocity[2] = z;
}

void SolidShape3D::setVelocity(const Vector3& v) {
	velocity = v;
}

Vector3 SolidShape3D::getVelocity() const {
	return velocity;
}

void SolidShape3D::move() {
	center = center + velocity;
}

void SolidShape3D::setMTL() {
	mtl.setEmission(0.1, 0.1, 0.1, 1);
	mtl.setAmbient(0.3, 0.3, 0.3, 1);
	mtl.setDiffuse(0.5, 0.5, 0.5, 1);
	mtl.setSpecular(1.0, 1.0, 1.0, 1);
	mtl.setShininess(10);
}

void SolidShape3D::setRandomMTL() {
	switch (rand() % 4 + 1)
	{
		case 1: 
			Material mtl1;
			//emerald
			mtl1.setEmission(0.1, 0.1, 0.1, 1);
			mtl1.setAmbient(0.0215, 0.1745, 0.0215, 1.0);
			mtl1.setDiffuse(0.07568, 0.61424, 0.07568, 1);
			mtl1.setSpecular(0.633, 0.727811, 0.633, 1);
			mtl1.setShininess(76.8);
			setMTL(mtl1); break;
		case 2:
			Material mtl2;
			//gold
			mtl2.setEmission(0.1, 0.1, 0.1, 1);
			mtl2.setAmbient(0.24725, 0.1995, 0.0745, 1.0);
			mtl2.setDiffuse(0.75164, 0.60648, 0.22648, 1);
			mtl2.setSpecular(0.628281, 0.555802, 0.366065, 1);
			mtl2.setShininess(51.2);
			setMTL(mtl2); break;
		case 3:
			Material mtl3;
			//pearl
			mtl3.setEmission(0.1, 0.1, 0.1, 1);
			mtl3.setAmbient(0.25, 0.20725, 0.20725, 1.0);
			mtl3.setDiffuse(1, 0.829, 0.829, 1);
			mtl3.setSpecular(0.296648, 0.296648, 0.296648, 1);
			mtl3.setShininess(11.264);
			setMTL(mtl3); break;
		case 4:
			Material mtl4;
			//ruby
			mtl4.setEmission(0.1, 0.1, 0.1, 1);
			mtl4.setAmbient(0.1745, 0.01175, 0.01175, 1.0);
			mtl4.setDiffuse(0.61424, 0.04136, 0.04136, 1);
			mtl4.setSpecular(0.727811, 0.626959, 0.626959, 1);
			mtl4.setShininess(76.8);
			setMTL(mtl4); break;
	}
};

Material SolidShape3D::getMTL() const { return mtl; };

void SolidShape3D::setMTL(Material mat) {
	mtl = mat;
};