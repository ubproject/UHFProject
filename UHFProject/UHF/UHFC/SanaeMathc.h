/*
 ============================================================================
 Name        : UHFC-Math-C
 Author      : Huku
 Version     : 1.0.3(Beta)
 Copyright   : CopyRight 2022 SanaeProject.
 ============================================================================
 */

#ifndef UHFC_SANAEMATHC_H_
#define UHFC_SANAEMATHC_H_


/*INCLUDE*/
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#include "SanaeTypes.h"


/*Define Function*/
Ulong  get_digit     (Ulong  _data);
RETNUM IS_PRIMENUM   (Ulong  _data);
double exponentiation(double _data, Slong  _count);
double _log_s        (Ulong _data , Ulong  low_num,  Ulong accuracy);
double log_s         (double _data, Ulong  low_num,  Ulong accuracy);
double root_newton   (Uint   _data, MINI   rootnum,  Ulong digitnum);
double root          (Uint   _data, MINI   rootnum,  MINI  digitnum);
void   SLCGs         (Ulong  _seed, Ulong  _count);
Ulong  LCGs          (Ulong  _seed, Ulong  _count);
Ulong  fibonacci     (Ulong  _count);

#ifdef UHFC_SANAESTRC_H_
	void   MATH_FREE(num_array* _data);
	RETNUM to_array (num_array* _array, Ulong _data);
	MINI   getnum   (MINI       from  , MINI  digitnum);
#endif


/*Functions*/
/*桁数を返します。*/
Ulong get_digit(Ulong _data){
	Ulong digit_buf = 1;
	for(Ulong i = 10;i <= _data;i*=10,digit_buf++);

	return digit_buf;
}

/*素数かどうか判定します。
 * 素数の場合TRUEを返します。
 * 素数じゃない場合FALSEを返します。
 */
RETNUM IS_PRIMENUM(Ulong _data){
	if((_data == 1) or (_data == 2))
		return TRUE;

	if((_data % 2) == 0)
		return FALSE;

	for(Uint i = 3;i<_data;i+=2)
		if((_data % i) == 0)
			return TRUE;

	return FALSE;
}

/*べき乗*/
double exponentiation(double _data,Slong _count){
	if (_count == 0)
		return 1;

	double _buf = _data;

	for(Uint i = 1; i < (_count < 0 ? -1*_count : _count); i++)
		_buf *= _data;

	return _count < 0 ? 1/_buf : _buf;
}

/*対数を求めます。
log low_num低の_dataを求めます。
accuracyを精度として設定します。

第三引数へ0を入れられた場合40に設定されます。
無限小数の場合大きな誤差が生まれる可能性があります。
・要修正。
*/
double log_s (double _data, Ulong low_num,Ulong accuracy) {
	if (_data == (Ulong)_data)
		return _log_s((Ulong)_data,low_num,accuracy);

	Ulong _buf = 1;

	for (; _data != (Ulong)_data && _buf<=100000; _data *= 10, _buf *= 10);
	
	return _log_s((Ulong)_data, low_num, accuracy) - _log_s(_buf,low_num,accuracy);
}
double _log_s(Ulong _data, Ulong low_num, Ulong accuracy) {
	double _buffer         = (double)_data;

	double _retdata        = 0;
	Slong  minus_buf       = 0;

	for (; _buffer >= low_num; _buffer /= low_num, _retdata += 1);

	if (_buffer == 1)
		return _retdata;

	if (accuracy == 0)
		accuracy = 40;

	for (Ulong i = 0; i <= accuracy; i++) {
		if (_buffer >= low_num)
		{
			_retdata += exponentiation((double)_data, minus_buf);
			_buffer  /= low_num;
		}
		else
		{
			minus_buf -= 1;
			_buffer    = exponentiation(_buffer, _data);
		}
	}

	return _retdata;
}

/*
* ニュートン法によりk乗根の値を求めます。
* 第三引数の値を増やせば増やすほど精度が上がります。
* 
* 1:Xn+1 =Xn-(f(Xn)/f'(Xn))
* 2:f(Xn)=X^k-θとする。
* 
* 1の式に2を入れると以下のようになる。
* Xn+1 = Xn - (Xn^k-θ)/(kXn^(k-1))
* k-1  = ωと置く。
* 
* Xn+1=kXn^(ω+1)/(kXn^ω)-(Xn^k-θ)/(kXn^ω)
* ={(k-1)Xn^(ω+1)+θ)}/kXn^ω
* ={(1-(1/k))Xn+(θ/kXn^ω)}
* ={(k-1)/k}Xn+(θ/kXn^ω)
* 
* =(1/k)*{(k-1)Xn+(θ/Xn^(k-1))}
* となる。
*/
double root_newton(Uint _data,MINI rootnum,Ulong _count) {
	double Xn = _data;

	for (Ulong i = 0; i < _count+1;i++)
		Xn = ((rootnum-1)*Xn+(_data/exponentiation(Xn,rootnum-1)))/rootnum;
	
	return Xn;
}

/*ルートを求めます。
 * 第二引数に根号数を入れてください。
 */
double root(Uint _data, MINI rootnum, MINI digitnum) {
	if (digitnum > 6)
		digitnum = 6;

	if (USE_NEWTON_METHOD == TRUE)
		return root_newton(_data,rootnum,digitnum);

	/*整数を見つける*/
	//retdataに値を格納
	double retdata = 0;

	for (Uint i = 1; i <= _data; i++) {
		//iをrootnum乗した物がdataと同じ場合
		if (exponentiation((double)i, (Uint)rootnum) == _data){
			return (double)i;
		}
		//iをrootnum乗した物がdataを超えてしまった場合i-1を格納
		else if (exponentiation((double)i, (Uint)rootnum) > _data) {
			retdata = (double)(i - 1);
			break;
		}
	}

	//整数部のみ求めることが指定されている場合
	if (digitnum == 0)
		return retdata;

	//最小値
	double min_digit = ((double)1 / ((double)exponentiation((double)10, (Uint)digitnum)));
	//繰り上げ繰り下げを行う際に使用
	Uint count = 1;

	/*細かい桁を見つける*/
	//0.1->0.01->0.001のように桁数を減らしていく
	for (double digit = 0.1; digit >= min_digit; digit /= 10,count++) {
		//0.01->0.02->0.03と増やしていく
		for (double num = 0; num < ((double)10 * digit); num += digit) {

			//整数部.小数第一位+小数第二位...の値
			double buf = exponentiation(retdata + num, rootnum);

			//整数部と同じように2乗して元の値を超えた場合num-1した値をretdataへ入れる。
			if (buf > _data) {
				num     -= digit;
				retdata += num;
				break;
			}
			//最後まで行ってしまったら9にする。
			else if (num >= (9 * digit)) {
				retdata += num;
				break;
			}
		}

		//繰り上げ繰り下げを行う
		if (count == (Uint)digitnum) {
			//1.414213->14.14213
			double buf_ret = retdata * 10;
			//14.142135
			double buf = exponentiation((double)buf_ret + (5*digit), rootnum);

			//2乗の値を超えてしまった場合5以上なので繰り上げ
			if (buf <= (_data * exponentiation(10,rootnum))) {
				retdata += digit;
			}
		}
	}
	return retdata;
}


/*RANDOM*/
/*シード値をセットします。
 * 第一引数に0が指定された場合、自動で設定。
 */
void SLCGs(Ulong _seed,Ulong _count){
	struct LCGsT* _Lp  = &LCGs_INFO;

	if(_seed == 0){
		union bufT{
			time_t time;
			Uint   show[sizeof(time_t) / sizeof(Uint)];
		}gets ={time(NULL)};

		_seed = (Ulong)gets.show[0];
		_count= (Ulong)gets.show[0] % 100;
	}

	_Lp->seed        = _seed;
	_Lp->count       = _count;
	_Lp->is_set_seed = TRUE;

	return;
}

/*seedに0が入力された場合自動で決めます。*/
Ulong LCGs(Ulong _seed,Ulong _count){
	if(LCGs_INFO.is_set_seed == FALSE)
		SLCGs(_seed,_count);

	if (_seed == 0) {
		_seed  = LCGs_INFO.seed;
		_count = LCGs_INFO.count;
	}

	Ulong retdata = (Ulong)_seed;

	for (Ulong i = 0; i < _count+LCGs_INFO.count; i++)
		retdata = (SM_RANDOM_A * retdata) % SM_RANDOM_M;

	LCGs_INFO.count++;

	return retdata;
}

/*フィボナッチ数列*/
Ulong fibonacci(Ulong _count){
	if(_count <= 2)
		return 1;
	return fibonacci(_count-1)+fibonacci(_count-2);
}

/*整数変換*/
#ifdef UHFC_SANAESTRC_H_

void MATH_FREE(num_array* _data) {
	free(_data->_data);
	_data->_length = 0;

	return;
}

/*整数を配列へ変換します。*/
RETNUM to_array(num_array* _array, Ulong _data) {
	MATH_FREE(_array);

	Ulong digit = get_digit(_data);

	/*桁数分確保する*/
	if ((_array->_data=(MINI*)calloc(digit,sizeof(MINI)))==NULL)
		return FALSE;

	_array->_length = digit;

	if (_data < 10) {
		_array->_data[0] = (MINI)_data;
		return TRUE;
	}

	/*ここから格納していく*/
	for (Ulong i = 0; i < digit-1;i++) {
		/*下の桁から取り出していく*/
		Ulong buf = _data;
		_data /= 10;
		_data *= 10;
		_array->_data[i] = (MINI)(buf - _data);
		_data /= 10;

		if (_data < 10) {
			_array->_data[i + 1] = (MINI)_data;
			return TRUE;
		}
	}

	return (RETNUM)FALSE;
}

/*指定した桁の値を入手します。
失敗した場合0を返します。
*/
MINI getnum(MINI from,MINI digitnum) {
	if (digitnum == 0)return 0;

	num_array buf = {NULL,0};

	if (!to_array(&buf, (Ulong)from))return 0;
	if ((Ulong)(digitnum-1) >= buf._length) {
		MATH_FREE(&buf);
		return 0;
	}
	if (buf._data==NULL)
		return 0;

	MINI retdata = buf._data[digitnum - 1];

	MATH_FREE(&buf);
	return retdata;
}

#endif
#endif /* UHFC_SANAEMATHC_H_ */