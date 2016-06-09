#ifndef VECTOR_HPP_
# define VECTOR_HPP_

# include <cmath>

namespace Vector {
	class Vec2 {
	public:
		float x;
		float y;

		Vec2(float x = 0.f, float y = 0.f);
		~Vec2();

		Vec2(const Vec2 & v);
		Vec2 & operator=(const Vec2 & v);

		void set(float x, float y);

		float getX() const;
		void setX(float x);

		float getY() const;
		void setY(float x);

		float len() const;
		float dot(const Vec2 & v) const;
		float det(const Vec2 & v) const;
		void rotate( float r);
		float angle() const;
		void setLen(float l);
		void normalize();
	};
	float len(float x, float y);
	float angle(float x, float y);
}

#endif