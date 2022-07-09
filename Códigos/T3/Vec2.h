#ifndef VEC2_H
#define VEC2_H

// Classe "Vec2" que expressa um vetor no R2
class Vec2 {
	public:
		float x;
		float y;

		Vec2();
		Vec2(float a, float b);
		Vec2 Rotate(float rad);
		static Vec2 Soma(Vec2 v1, Vec2 v2);
		static Vec2 Subt(Vec2 v1, Vec2 v2);
		static Vec2 Mult(Vec2 v1, float e);
		static float Mag(Vec2 v);
		static Vec2 Norm(Vec2 v);
		static float Dist(Vec2 v1, Vec2 v2);

		Vec2 operator+(Vec2 const &outro);
};

#endif // VEC2_H
