#include "Arrow.h"

Arrow::Arrow() : SolidShape3D() {};

void Arrow::setArrow(float cornbase, float cornheight, float cylinderbase, float cylindertop, float cylinderheight) {
	properties = new float[5];
	properties[0] = cornbase;
	properties[1] = cornheight;
	properties[2] = cylinderbase;
	properties[3] = cylindertop;
	properties[4] = cylinderheight;
};
Arrow::~Arrow() {
	delete[] properties;
};
float* Arrow::getProperties() const {
	return properties;
};
float Arrow::getAngleOfArrow() const {
	return AngleOfArrow;
};
void Arrow::setAngleOfArrow(float angle) {
	AngleOfArrow = angle;
};
void Arrow::draw() const {
	glPushMatrix();

	glTranslated(center[0], center[1], center[2]);

	glRotated(-90, 1, 0, 0);

	glRotated(AngleOfArrow, 0, 1, 0);

	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_EMISSION, mtl.getEmission());
	glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.getAmbient());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.getDiffuse());
	glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.getSpecular());
	glMaterialfv(GL_FRONT, GL_SHININESS, mtl.getShininess());

	glTranslated(0, 0, -0.5*properties[4]);
	GLUquadricObj* obj = gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_FILL);
	gluCylinder(obj, properties[2], properties[3], properties[4], 20, 20);
	glPopMatrix();

	glTranslated(0, 0, 0.5 * properties[4]);

	glutSolidCone(properties[0], properties[1], 20, 20);

	glPopMatrix();
	gluDeleteQuadric(obj); 
};