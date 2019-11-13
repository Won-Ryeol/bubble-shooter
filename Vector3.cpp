#include "Vector3.h"

Vector3::Vector3() {
	xyz[0] = xyz[1] = xyz[2]= 0;
};

Vector3::Vector3(float x, float y, float z) {
	xyz[0] = x; xyz[1] = y; xyz[2] = z;
};
void Vector3::setXYZ(float x, float y, float z) {
	xyz[0] = x; xyz[1] = y; xyz[2] = z;
};
const float* Vector3::getXYZ() const { return xyz; };

Vector3& Vector3::operator=(const Vector3& vec3) {
	xyz[0] = vec3.xyz[0]; xyz[1] = vec3.xyz[1]; xyz[2] = vec3.xyz[2];
	return (*this);
};

float& Vector3::operator[](const int i) { return xyz[i]; };
float Vector3::operator[](const int i) const { return xyz[i]; };

Vector3 operator+(const Vector3& v1, const Vector3& v2) {
	Vector3 v;
	v[0] = v1[0]+ v2[0]; v[1] = v1[1]+ v2[1]; v[2] = v1[2]+ v2[2];
	return v;
};

Vector3 operator-(const Vector3& v1, const Vector3& v2) {
	Vector3 v;
	v[0] = v1[0] - v2[0]; v[1] = v1[1] - v2[1]; v[2] = v1[2] - v2[2];
	return v;
};

Vector3 operator-(const Vector3& v) {
	Vector3 v0;
	v0[0] = -v[0];
	v0[1] = -v[1];
	v0[2] = -v[2];
	return v0;
};

Vector3 operator*(const float s, const Vector3& vec3) {
	Vector3 v;
	v[0] = vec3[0] * s;
	v[1] = vec3[1] * s;
	v[2] = vec3[2] * s;
	return v;
};

float dotProduct(const Vector3& v1, const Vector3& v2) {
	return (v1[0]*v2[0] + v1[1]*v2[1]);
};