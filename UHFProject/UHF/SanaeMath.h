#ifndef SANAEMATH_H
#define SANAEMATH_H


/*INCLUDE*/
#include "UHFC/SanaeMathc.h"
#include <vector>


template<typename T=double>
constexpr auto SABSOLUTE(T X)     { return X < 0 ? X * -1 : X; }

template<typename T=double>
constexpr bool IS_EQUAL(T X, T Y) { return SABSOLUTE(X - Y) < DBL_EPSILON; }


/*素因数分解をします*/
template<typename T=UINT>
std::vector<T>& factorization(std::vector<T>& data,T from) {
	for (T i = 2;i<from;i+=1) {
		if (is_primenum(i)) {

			if (from%i==0) {

				data.push_back(i);
				from /= i;

				i = 2;
			}

		}
	}

	if (is_primenum(from)&&from>=2)
		data.push_back(from);
	
	return data;
}


#endif
