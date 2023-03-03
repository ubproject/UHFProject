/*
 ============================================================================
 Name        : UHF-SanaeStatistics
 Author      : Sanae
 Version     : 1.0.3(Beta)
 Copyright   : CopyRight 2022 SanaeProject.
 ============================================================================
 */

#ifndef SANAESTATISTICS_H
#define SANAESTATISTICS_H


#include <vector>
#include <stdexcept>
#include "UHFC/SanaeTypes.h"


//素因数分解を行います。
template<typename T=Uint>
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

//回帰
namespace Regression {
	template<typename T, typename FITED_A = double, typename FITED_B = double>
	class Base_Regression{
	protected:
		std::vector<T>               SR_DATAS;
		S_PAIR<FITED_A, FITED_B>     FITED_DATA = {0, 0};

		void VEC_COPY(std::vector<T>& to, std::vector<T>& from) {
			to.erase(to.begin(), to.end());

			for (T i : from)
				to.push_back(i);

			return;
		}
		void VEC_ADD(std::vector<T>& to, std::vector<T>& from) {
			for (T i : from)
				to.push_back(i);

			return;
		}

		Base_Regression(T& data) {
			VEC_COPY(SR_DATAS, data);
		}
		Base_Regression(){}
		~Base_Regression(){}

		Base_Regression& operator =(T& data) {
			VEC_COPY(SR_DATAS, data);
			return *this;
		}
		Base_Regression& operator +=(T& data) {
			VEC_ADD(SR_DATAS, data);
			return *this;
		}

		virtual void fit(){}
	};

	//y=ax+b
	template<typename Tx, typename Ty>
	class Simple : private Base_Regression<S_PAIR<Tx,Ty>>{
	public:
		double& A = Simple::FITED_DATA.front;
		double& B = Simple::FITED_DATA.back;

		Simple(std::vector<S_PAIR<Tx, Ty>>& data)    :Simple::Base_Regression(data){}
		Simple()                                     :Simple::Base_Regression(){}
		~Simple(){};

		Simple& operator =(std::vector<S_PAIR<Tx, Ty>>& data) {
			Simple::VEC_COPY(Simple::SR_DATAS, data);
			return *this;
		}
		Simple& operator +=(std::vector<S_PAIR<Tx, Ty>>& data) {
			Simple::VEC_ADD(Simple::SR_DATAS, data);
			return *this;
		}
		Simple& operator +=(S_PAIR<Tx, Ty> data) {
			Simple::SR_DATAS.push_back(data);
			return *this;
		}

		void fit() override{
			//(ave(xy)-ave(x)*ave(y))
			double ave_xy = 0;
			double ave_x = 0;
			double ave_y = 0;

			//fron:x back:y

			//ave_xy
			for (S_PAIR<Tx, Ty> i : Simple::SR_DATAS)
				ave_xy += i.back * i.front;
			ave_xy /= Simple::SR_DATAS.size();

			//ave_x
			for (S_PAIR<Tx, Ty> i : Simple::SR_DATAS)
				ave_x += i.front;
			ave_x /= Simple::SR_DATAS.size();

			//ave_y
			for (S_PAIR<Tx, Ty> i : Simple::SR_DATAS)
				ave_y += i.back;
			ave_y /= Simple::SR_DATAS.size();

			//ave(x^2)-ave(x)^2
			double ave_sqrx = 0;
			for (S_PAIR<Tx, Ty> i : Simple::SR_DATAS)
				ave_sqrx += (i.front * i.front);
			ave_sqrx /= Simple::SR_DATAS.size();

			//a = (ave(xy)-ave(x)*ave(y))/(ave(x^2)-ave(x)^2)
			Simple::FITED_DATA.front = (ave_xy - (ave_x * ave_y)) / (ave_sqrx - (ave_x * ave_x));
			//b = ave(y)-a*ave(x)
			Simple::FITED_DATA.back = (ave_y - (Simple::FITED_DATA.front * ave_x));

			return;
		}
		Ty predict(Tx data){
			return (Ty)(A * data + B);
		}
		void show(){
			printf("y=%lfx+(%lf)", A, B);
		}
	};

}
#endif
