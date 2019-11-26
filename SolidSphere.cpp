#include "SolidSphere.h"
#include <math.h>

SolidSphere::SolidSphere(float r, int sl, int st) : SolidShape3D() {
	properties.setXYZ(r, sl, st);
	moved = false;
	removesearch = false;
}

SolidSphere::SolidSphere(const SolidSphere& sph) : SolidShape3D(sph) {
	properties = sph.properties;
	moved = sph.moved;
	removesearch = sph.removesearch;
}

Vector3 SolidSphere::getProperties() const{
	return properties;
}

bool SolidSphere::collisionDetection(const SolidSphere& sph) {
	Vector3 d = center - sph.center;
	return (sqrt(dotProduct(d,d)) <= (properties[0] + sph.properties[0]));
}

void SolidSphere::collisionHandling(SolidSphere& sph) {
	if (collisionDetection(sph) && sph.moved != true) {

		sph.setVelocity(0,0,0);
		
		Vector3 d = center - sph.center;
		float cosvalue = d[0] / sqrt(dotProduct(d, d));
		float r = properties[0];
		float k = sqrt(3) / 2;
		if      (sph.center[0] < -9 * r) { sph.setCenter(center + Vector3(r, -2 * r * k, 0)); }  //left boundary
		else if (sph.center[0] > 9 * r)  { sph.setCenter(center + Vector3(-r, -2 * r * k, 0)); } //right boundary

		else if	  (k <= cosvalue && cosvalue <= 1)			    	{sph.setCenter(center + Vector3(-2 * r, 0, 0));}		//left
		else if   (0 <= cosvalue && cosvalue <= k && d[1] > 0)		{sph.setCenter(center + Vector3(-r, -2 * r * k, 0));}   //downleft
		else if   (0 <= cosvalue && cosvalue <= k && d[1] < 0)      {sph.setCenter(center + Vector3(-r, 2 * r * k, 0)); }   //upleft
		else if   (-k <= cosvalue && cosvalue <= 0 && d[1] > 0)     {sph.setCenter(center + Vector3(r, -2 * r * k, 0));}    //downright
		else if   (-k <= cosvalue && cosvalue <= 0 && d[1] < 0)     {sph.setCenter(center + Vector3(r, 2 * r * k, 0));}     //upright
		else if   ( -1 <= cosvalue && cosvalue <= -k)				{sph.setCenter(center + Vector3(2 * r, 0, 0));};	    //right
		sph.moved = true;
	};
}

void SolidSphere::aftercollision() { moved = true; }

bool SolidSphere::getmoved() const { return moved; }

void SolidSphere::setremovesearch() { removesearch = true; }

void SolidSphere::resetremovesearch() { removesearch = false; }

bool SolidSphere::getremovesearch() const { return removesearch; };

void SolidSphere::draw() const {
	glPushMatrix();

	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_EMISSION, mtl.getEmission());
	glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.getAmbient());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.getDiffuse());
	glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.getSpecular());
	glMaterialfv(GL_FRONT, GL_SHININESS, mtl.getShininess());

	glTranslatef(center[0], center[1], center[2]);
	glutSolidSphere(properties[0], properties[1], properties[2]);
	glPopMatrix();
}