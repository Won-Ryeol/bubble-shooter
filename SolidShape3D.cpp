#include "SolidShape3D.h"
#include <time.h>
//error  #include <iostream> 

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

Material SolidShape3D::getMTL() const { return mtl; };

void SolidShape3D::setMTL(Material mat) {
	mtl = mat;
}

/*
void SolidShape3D::setRandMTL4(Material a, Material b, Material c, Material d) {
		
	srand((unsigned int)time(0)); 
	
	switch (rand() % 4 + 1)
	{
	case 1: mtl = a; break;
	case 2: mtl = b; break;
	case 3: mtl = c; break;
	case 4: mtl = d; break;
	}
}
*/