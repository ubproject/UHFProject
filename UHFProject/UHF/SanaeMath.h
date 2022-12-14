#ifndef SANAEMATH_H
#define SANAEMATH_H


/*INCLUDE*/
#include "UHFC/SanaeMathc.h"
#include <vector>


template<typename T=double>
constexpr auto SABSOLUTE(T X)     { return X < 0 ? X * -1 : X; }

#define SANAEMATH_ERROR 1.0E-6    //0.000001までの誤差であれば許容する。

template<typename T=double>
constexpr bool IS_EQUAL(T A, T B) { return SABSOLUTE(A - B) <= SANAEMATH_ERROR; }


//素因数分解を行います。
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
