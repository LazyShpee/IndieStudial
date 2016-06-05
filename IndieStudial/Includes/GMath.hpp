#ifndef GMATH_HPP_
# define GMATH_HPP_ value

# include <cmath>

namespace GMath {

	template<typename T>
	T sign(T n) {
		return (T)(n < 0 ? -1 : n > 0 ? 1: 0);
	}

	template<typename T>
	T min(T a, T b) {
		return (a > b ? b : a);
	}

	template<typename T>
	T max(T a, T b) {
		return (a < b ? b : a);
	}

	template<typename T>
	T clamp(T n, T min, T max) {
		return GMath::max(GMath::min(n, max), min);
	}

	template<typename T>
	T mod(T n, T m) {
		T s = sign(n);

		while (n > m && n < -m)
			n -= m * s;
		return (n);
	}

	template<typename T>
	T pmod(T n, T m) {
		return (GMath::mod(GMath::mod(n, m) + m, m));
	}
}

#endif