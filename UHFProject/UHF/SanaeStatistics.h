/*
 ============================================================================
 Name        : UHF-SanaeStatistics
 Author      : Sanae
 Version     : 1.0.3(Beta)
 Copyright   : CopyRight 2022 SanaeProject.
 Description : Master include file.
 ============================================================================
 */

#ifndef SANAESTATISTICS_H
#define SANAESTATISTICS_H


#include <vector>
#include <stdexcept>
#include "UHFC/SanaeTypes.h"


template<typename T=double>
constexpr auto SABSOLUTE(T X)      { return X < 0 ? X * -1 : X; }

#define SANAEMATH_ERROR 1.0E-6    //0.000001までの誤差であれば許容する。

template<typename T=double>
constexpr bool IS_EQUAL(T A, T B)  { return SABSOLUTE(A - B) <= SANAEMATH_ERROR; }

template<typename T1,typename T2>
struct S_PAIR {
	T1 front;
	T2 back;
};


//行列の計算を行う。
//失敗した場合0を返します。
Ulong Get_ArrayNumber(Ulong _width, S_PAIR<Ulong, Ulong> _XYNum) {
	Ulong& _x = _XYNum.front;
	Ulong& _y = _XYNum.back;

	if (_x >= _width)
		return 0;

	return (_width * (_y)) + (_x);
}
//失敗した場合0を返します。
S_PAIR<Ulong,Ulong> Get_XYNumber(Ulong _width,Ulong _ArrayNum) {
	Ulong _x = _ArrayNum % _width;
	Ulong _y = (_ArrayNum - _x) / _width;

	if (_x >= _width)
		return {0,0};

	return { _x , _y };
}

template<typename _DataType = double>
class matrix {
private:
	_DataType* _main = NULL;

	S_PAIR<Ulong,Ulong> _size  = {0,0};
	Ulong&              _width = _size.front;
	Ulong&              _height= _size.back;

	void _error(const char* _text) {
		throw std::exception(_text);
	}

	void _set_val(S_PAIR<Ulong,Ulong> _from,S_PAIR<Ulong,Ulong> _to,_DataType _data) {
		for (Ulong i = Get_ArrayNumber(_width, _from);i<=Get_ArrayNumber(_width,_to);i++)
			*(_main + i) = _data;
	}

	bool _allocate(_DataType** _data,Ulong _size) {
		_DataType* buf = (_DataType*)realloc(*_data,_size*sizeof(_DataType));
		
		if (buf == NULL) {
			free(*_data);
			*_data = NULL;

			return false;
		}

		*_data = buf;

		memset(*_data,0,_size*sizeof(_DataType));

		return true;
	}
public:
	//Constructor
	//行列の幅、高さを指定します。
	matrix(Ulong width,Ulong height) {
		_size = {width,height};

		if (!_allocate(&_main, width*height))
			_error("Failed to allocate.");
	}
	//Destructor
	~matrix() {
		free(_main);
	}

	//operator
	_DataType& operator [](S_PAIR<Ulong, Ulong> _data) {
		Ulong _buf = Get_ArrayNumber(_width, _data);
		if (_buf >= _width * _height)
			_error("Tried to out of range");

		return *(_main + _buf);
	}

	matrix& add(const matrix<_DataType>& _data) {
		if (_data._height != _height || _data._width != _width)
			_error("different size.");

		for (Ulong i = 0; i < _width * _height; i++)
			*(_main + i) += *(_data._main + i);

		return *this;
	}
	matrix& sub(const matrix<_DataType>& _data) {
		if (_data._height != _height || _data._width != _width)
			_error("different size.");

		for (Ulong i = 0; i < _width * _height; i++)
			*(_main + i) -= *(_data._main + i);

		return *this;
	}

	matrix& scalar_mul(_DataType _d) {
		for (Ulong i = 0; i < _height * _width;i++)
			*(_main + i) *= _d;

		return *this;
	}

	//cij= Σ k=1,m (aik*bkj)を使用
	matrix& mul(const matrix<_DataType>& _data) {
		if (_width != _data._height) {
			_error("different size.");
		}

		_DataType* _buf = NULL;
		if (!this->_allocate(&_buf, (_height * _data._width))) {
			free(_main);
			_error("Failed to allocate.");
		}

		for (Ulong y = 0; y < _height; y++) {
			for (Ulong x = 0; x < _data._width; x++) {
				//それぞれの計算を行う
				for (Ulong k = 0; k < _width;k++) {
					_buf[Get_ArrayNumber(_data._width, { x,y })] += this->_main[Get_ArrayNumber(_width, { k,y })] * _data._main[Get_ArrayNumber(_data._width,{ x,k })];
				}
			}
		}

		free(_main);
		_main   = _buf;
		_width  = _data._width;

		return *this;
	}

	matrix& view_matrix() {
		for (Ulong i = 0; i < ((_width) * (_height));i++) {
			if (i % _width == 0)
				printf("\n");
			printf("%lg ",*(_main+i));
		}
		return *this;
	}

};

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
