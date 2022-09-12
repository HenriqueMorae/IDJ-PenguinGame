#include "Rect.h"

Rect::Rect(){
	x = 0;
	y = 0;
	w = 0;
	h = 0;
}

Rect::Rect(float a, float b, float c, float d) {
	x = a;
	y = b;
	w = c;
	h = d;
}

void Rect::MaisVec2(Vec2 v) {
	x += v.x;
	y += v.y;
}

Vec2 Rect::Centro() {
	Vec2 coordenadas;
	coordenadas.x = x + w/2;
	coordenadas.y = y + h/2;
	return coordenadas;
}

float Rect::DistCentro(Rect r1, Rect r2) {
	float distancia;
	distancia = Vec2::Dist(r1.Centro(), r2.Centro());
	return distancia;
}

bool Rect::EstaDentro(Vec2 v) {
	if (v.x >= x && v.x <= x+w && v.y >= y && v.y <= y+h) {
		return true;
	} else {
		return false;
	}
}
