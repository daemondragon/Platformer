#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <cmath>

template <typename T>
class Vector2
{
	public:
		T	x;
		T	y;

		Vector2() : x(0), y(0) {}
		Vector2(T x, T y) : x(x), y(y) {}

		T		squareLength()
		{
			return (x * x + y * y);
		}
		T		length()
		{
			return (sqrt(squareLength()));
		}
		void	normalize()
		{
			T l = length();
			x /= l;
			y /= l;
		}
		Vector2<T>	normalized()
		{
			Vector2<T> norm(x, y);
			norm.normalize();

			return (norm);
		}
		void	invert()
		{
			x = -x;
			y = -y;
		}
		Vector2<T>	inverse()
		{
			return (Vector2<T>(-x, -y));
		}


		void		add(const Vector2<T> &add)
		{
			x += add.x;
			y += add.y;
		}
		void		add(T add)
		{
			x += add;
			y += add;
		}
		void		sub(const Vector2<T> &sub)
		{
			x -= sub.x;
			y -= sub.y;
		}
		void		sub(T sub)
		{
			x -= sub;
			y -= sub;
		}
		void		mul(const Vector2<T> &mul)
		{
			x *= mul.x;
			y *= mul.y;
		}
		void		mul(T mul)
		{
			x *= mul;
			y *= mul;
		}
		void		div(const Vector2<T> &div)
		{
			x /= div.x;
			y /= div.y;
		}
		void		div(T div)
		{
			x /= div;
			y /= div;
		}


		T		dot(const Vector2<T> &v)
		{
			return (x * v.x + y * v.y);
		}


		void		operator+=(const Vector2<T> &add)
		{
			this->add(add);
		}
		Vector2<T>	operator+(const Vector2<T> &add)
		{
			return (Vector2<T>(x + add.x, y + add.y));
		}
		void		operator-=(const Vector2<T> &sub)
		{
			this->sub(sub);
		}
		Vector2<T>	operator-(const Vector2<T> &sub)
		{
			return (Vector2<T>(x - sub.x, y - sub.y));
		}
		void		operator*=(const Vector2<T> &mul)
		{
			this->mul(mul);
		}
		Vector2<T>	operator*(const Vector2<T> &mul)
		{
			return (Vector2<T>(x * mul.x, y * mul.y));
		}
		void		operator*=(const T mul)
		{
			this->mul(mul);
		}
		Vector2<T>	operator*(const T mul)
		{
			return (Vector2<T>(x * mul, y * mul));
		}

		void		clear()
		{
			x = 0;
			y = 0;
		}
};

typedef Vector2<int>	Vector2i;
typedef Vector2<float>	Vector2f;
typedef Vector2<double>	Vector2d;

#endif
