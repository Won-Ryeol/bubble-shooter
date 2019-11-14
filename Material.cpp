#include "Material.h"

void Material::setMTL(const Material& mtl) {
	setEmission(mtl.getEmission());
	setAmbient(mtl.getAmbient());
	setDiffuse(mtl.getDiffuse());
	setSpecular(mtl.getSpecular());
	setShininess(mtl.getShininess());
}

void Material::setEmission(float r, float g, float b, float a) {
	emission[0] = r;
	emission[1] = g;
	emission[2] = b;
	emission[3] = a;
}

void Material::setEmission(const float* rgba) {
	setEmission(rgba[0], rgba[1], rgba[2], rgba[3]);
}

void Material::setAmbient(float r, float g, float b, float a) {
	ambient[0] = r;
	ambient[1] = g;
	ambient[2] = b;
	ambient[3] = a;
}

void Material::setAmbient(const float* rgba) {
	setAmbient(rgba[0], rgba[1], rgba[2], rgba[3]);
}

void Material::setDiffuse(float r, float g, float b, float a) {
	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	diffuse[3] = a;
}

void Material::setDiffuse(const float* rgba) {
	setDiffuse(rgba[0], rgba[1], rgba[2], rgba[3]);
}

void Material::setSpecular(float r, float g, float b, float a) {
	specular[0] = r;
	specular[1] = g;
	specular[2] = b;
	specular[3] = a;
}

void Material::setSpecular(const float* rgba) {
	setSpecular(rgba[0], rgba[1], rgba[2], rgba[3]);
}

void Material::setShininess(float sh) {
	shininess[0] = sh;
}

void Material::setShininess(const float* sh) {
	setShininess(sh[0]);
}

const float* Material::getEmission() const {
	return emission;
}

const float* Material::getAmbient() const {
	return ambient;
}

const float* Material::getDiffuse() const {
	return diffuse;
}

const float* Material::getSpecular() const {
	return specular;
}

const float* Material::getShininess() const {
	return shininess;
}

bool  Material::operator==(Material a) {
	return (
		emission[0] == a.emission[0] && ambient[0] == a.ambient[0] && diffuse[0] == a.diffuse[0] && specular[0] == a.specular[0] && shininess[0] == a.shininess[0] &&
		emission[1] == a.emission[1] && ambient[1] == a.ambient[1] && diffuse[1] == a.diffuse[1] && specular[1] == a.specular[1] &&
		emission[2] == a.emission[2] && ambient[2] == a.ambient[2] && diffuse[2] == a.diffuse[2] && specular[2] == a.specular[2] &&
		emission[3] == a.emission[3] && ambient[3] == a.ambient[3] && diffuse[3] == a.diffuse[3] && specular[3] == a.specular[3] 
		);
};