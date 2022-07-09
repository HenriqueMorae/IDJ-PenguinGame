#include "Vec2.h"

#ifndef RECT_H
#define RECT_H

// Classe "Rect" que expressa uma posicao e dimensoes
class Rect {
	public:
		float x;
		float y;
		float w;
		float h;

		Rect();
		Rect(float a, float b, float c, float d);
		void MaisVec2(Vec2 v);
		Vec2 Centro();
		static float DistCentro(Rect r1, Rect r2);
		bool EstaDentro(Vec2 v);
};

#endif // RECT_H
