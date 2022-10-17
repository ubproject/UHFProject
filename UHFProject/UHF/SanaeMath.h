#ifndef SANAEMATH_H
#define SANAEMATH_H


/*INCLUDE*/
#include "UHFC/SanaeMathc.h"
#include <vector>


/*‘fˆö”•ª‰ğ‚ğ‚µ‚Ü‚·B*/
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