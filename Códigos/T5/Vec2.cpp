#include "Vec2.h"
#include <math.h>

Vec2::Vec2() {
	x = 0;
	y = 0;
}

Vec2::Vec2(float a, float b) {
	x = a;
	y = b;
}

Vec2 Vec2::Rotate(float rad) {
	float xlinha;
	float ylinha;

	xlinha = x*cos(rad) - y*sin(rad);
	ylinha = y*cos(rad) + x*sin(rad);

	return Vec2(xlinha, ylinha);
}

Vec2 Vec2::Soma(Vec2 v1, Vec2 v2) {
	Vec2 resultado;
	resultado.x = v1.x + v2.x;
	resultado.y = v1.y + v2.y;
	return resultado;
}

Vec2 Vec2::Subt(Vec2 v1, Vec2 v2) {
	Vec2 resultado;
	resultado.x = v1.x - v2.x;
	resultado.y = v1.y - v2.y;
	return resultado;
}

Vec2 Vec2::Mult(Vec2 v1, float e) {
	Vec2 resultado;
	resultado.x = v1.x * e;
	resultado.y = v1.y * e;
	return resultado;
}

float Vec2::Mag(Vec2 v) {
	float magnitude;
	magnitude = sqrt((v.x*v.x)+(v.y*v.y));
	return magnitude;
}

Vec2 Vec2::Norm(Vec2 v) {
	Vec2 normalizado;
	float magnitudeDeV;
	magnitudeDeV = Mag(v);

	if (magnitudeDeV == 0) {
		normalizado.x = 0;
		normalizado.y = 0;
	} else {
		normalizado.x = v.x/magnitudeDeV;
		normalizado.y = v.y/magnitudeDeV;
	}

	return normalizado;
}

float Vec2::Dist(Vec2 v1, Vec2 v2) {
	float distancia;
	distancia = Mag(Subt(v1, v2));
	return distancia;
}

Vec2 Vec2::operator+(Vec2 const &outro) {
	return Vec2(x+outro.x, y+outro.y);
}

Vec2 Vec2::operator*(Vec2 const &outro) {
	return Vec2(x*outro.x, y*outro.y);
}

Vec2 Vec2::operator-(Vec2 const &outro) {
	return Vec2(x-outro.x, y-outro.y);
}
