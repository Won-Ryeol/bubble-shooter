#include "SolidSphere.h"
#include <math.h>

SolidSphere::SolidSphere(float r, int sl, int st) : SolidShape3D() {
	properties.setXYZ(r, sl, st);
	moved = false;
}

SolidSphere::SolidSphere(const SolidSphere& sph) : SolidShape3D(sph) {
	properties = sph.properties;
	moved = sph.moved;
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

		Vector3 zero(0,0,0);
		sph.velocity = zero;
		
		Vector3 d = center - sph.center;
		Vector3 xaxis(1, 0, 0);
		float r = properties[0];
		float k = sqrt(3) / 2;

		if (k <= (dotProduct(d, xaxis) / (2 * r)) && (dotProduct(d, xaxis) / (2 * r)) <= 1) {
			Vector3 left(-2 * r, 0, 0);
			sph.setCenter(center + left);
		}
		else if (0 <= (dotProduct(d, xaxis) / (2 * r)) && (dotProduct(d, xaxis) / (2 * r)) <= k && d.getXYZ()[1]>0) {
			Vector3 downleft(-r, -2*r*k, 0);
			sph.setCenter(center + downleft);
		}
		else if ( - k<= (dotProduct(d, xaxis) / (2 * r)) && (dotProduct(d, xaxis) / (2 * r)) <= 0 && d.getXYZ()[1] > 0) {
			Vector3 downright(r, -2*r*k, 0);
			sph.setCenter(center + downright);
		}
		else if (0 <= (dotProduct(d, xaxis) / (2 * r)) && (dotProduct(d, xaxis) / (2 * r)) <= k && d.getXYZ()[1] < 0) {
			Vector3 upleft(-r, 2 * r * k, 0);
			sph.setCenter(center + upleft);
		}
		else if (-k <= (dotProduct(d, xaxis) / (2 * r)) && (dotProduct(d, xaxis) / (2 * r)) <= 0 && d.getXYZ()[1] < 0) {
			Vector3 upright(r, 2 * r * k, 0);
			sph.setCenter(center + upright);
		}
		else if ( -1 <= (dotProduct(d, xaxis) / (2 * r)) && (dotProduct(d, xaxis) / (2 * r)) <= -k) {
			Vector3 right(2 * r, 0, 0);
			sph.setCenter(center + right);
		};
		sph.moved = true;
	};
}

void SolidSphere::aftercollision() { moved = true; }

bool SolidSphere::getmoved() const { return moved; }

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