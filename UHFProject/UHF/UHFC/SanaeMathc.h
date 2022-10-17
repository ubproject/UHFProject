#ifndef SANAEMATHC_H
#define SANAEMATHC_H


/*INCLUDE*/
#include <stdio.h>
#include <stdlib.h>


/*Define Types*/
typedef unsigned int  UINT;
typedef unsigned char MINI;
typedef long long     long64;

/*整数を配列へ変換する際に使用する。*/
typedef struct {
	UINT* data;
	UINT  len;
}NUMS;

/*分数処理を行う際に使用する。*/
typedef struct {
	//分子
	UINT molecule;
	//分母
	UINT denominator;
}fraction;


/*Define Function*/
/*累乗の計算*/
UINT   exponentiation(UINT  , UINT);
double exponentiation(double, UINT);
double exponentiation(double from, double count,UINT);

/*分数の計算*/
fraction& to_min(fraction&);
double    fraction_num(fraction);

/*素数判定*/
bool   is_primenum(UINT);

/*累乗根の計算*/
double root(UINT ,MINI,MINI);

/*整数を配列へ変換*/
void   MATH_FREE(NUMS*);
bool   to_array (NUMS*,UINT);
UINT   getnum   (UINT ,UINT);


/*累乗の計算をします。(unsigned int)
fromをcount回かけた数を返します。
*/
UINT exponentiation(UINT from, UINT count) {
	if (count == 0)return 1;

	UINT retdata = from;
	for (UINT i = 1; i < count; i++)
		retdata *= from;

	return retdata;
}


/*累乗の計算をします。(double)
fromをcount回かけた数を返します。
*/
double exponentiation(double from, UINT count) {
	if (count == 0)return 1;

	double retdata = from;
	for (UINT i = 1; i < count; i++)
		retdata *= from;
	
	return retdata;
}


/*累乗の計算をします。(double)
fromをcount(double)回かけた数を返します。
*/
double exponentiation(double from, double count,UINT digitnum=3) {
	if (count == 0)return 1;
	
	double retdata = from;
	/*分母分子を決定*/
	fraction b = {0,0};
	
	for (b.denominator = 1; ((count * b.denominator) - (UINT)(count*b.denominator)) != 0; b.denominator *= 10);
	b.molecule = (UINT)((double)count * (double)b.denominator);

	to_min(b);

	UINT d = (UINT)exponentiation(from,b.molecule);
	return root(d,b.denominator,digitnum);
}


/*約分を行います。*/
fraction& to_min(fraction& data) {
	double buf = (double)data.molecule / (double)data.denominator;
	
	if (buf == (UINT)buf) {
		data.molecule = (UINT)buf;
		data.denominator = 1;
		return data;
	}
	
	buf = (double)data.denominator / (double)data.molecule;
	if (buf == (UINT)buf) {
		data.molecule = 1;
		data.denominator = (UINT)buf;
		return data;
	}
	for (double i = 2; i < data.denominator && i < data.molecule; i++) {
		double bufden = data.denominator / i;
		double bufmol = data.molecule    / i;

		if ((bufden - (UINT)bufden) == 0 && (bufmol - (UINT)bufmol) == 0) {
			data.denominator /= (UINT)i;
			data.molecule    /= (UINT)i;
			i = 2;
		}
	}
	return data;
}


/*分数の計算を行います。*/
double fraction_num(fraction data) {
	return (double)data.molecule / (double)data.denominator;
}


/*素数か素数でないかを判定します。*/
bool is_primenum(UINT data) {
	if (data == 1 || data == 2) return true;
	if (data % 2 == 0)          return false;

	for (UINT i = 3; i < data; i += 2)
		if (data % i == 0)      return false;

	return true;
}


/*rootnum乗根dataの値を求めます。
digitnum桁まで少数を求めます。
*/
double root(UINT data, MINI rootnum = 2, MINI digitnum = 3) {
	if (digitnum > 6) digitnum = 6;
	/*整数を見つける*/
	double retdata = 0;
	for (UINT i = 1; i <= data; i++) {
		if (exponentiation(i, (UINT)rootnum) == data) {
			retdata = i;
			return retdata;
		}
		else if (exponentiation(i, (UINT)rootnum) > data) {
			retdata = (i - 1);
			break;
		}
	}
	/*細かい桁を見つける*/
	for (double digit = 0.1; digit >= ((double)1 / ((double)exponentiation((UINT)10, (UINT)digitnum))); digit /= 10) {
		for (double num = 0; num < ((double)10 * digit); num += digit) {
			double buf = exponentiation((double)retdata + num, (UINT)rootnum);
			
			if (buf > data) {
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
	}
	return retdata;
}


void MATH_FREE(NUMS* d) {
	free(d->data);
	d->len = 0;
}


/*整数を配列へ変換します。*/
bool to_array(NUMS* toarray, UINT data) {
	MATH_FREE(toarray);
	/*桁数を求める*/
	UINT digit = 1;
	for (UINT i = 10; (i - 1) < data; i *= 10, i += 1,digit++);
	/*桁数分確保する*/
	if ((toarray->data=(UINT*)calloc(digit,sizeof(UINT)))==NULL)return false;
	toarray->len = digit;
	/*ここから格納していく*/
	for (UINT i = 0; i < digit-1;i++) {
		/*下の桁から取り出していく*/
		UINT buf = data;
		data /= 10;
		data *= 10;
		toarray->data[i] = buf - data;
		data /= 10;

		if (data<10) {
			toarray->data[i + 1] = data;
			return true;
		}
	}
	return false;
}


/*指定した桁の値を入手します。
失敗した場合0を返します。
*/
UINT getnum(UINT from,UINT digitnum) {
	if (digitnum == 0)return 0;

	NUMS buf = {NULL,0};

	if (!to_array(&buf, from))return 0;
	if ((digitnum-1) >= buf.len) {
		MATH_FREE(&buf);
		return 0;
	}

	UINT retdata = buf.data[digitnum - 1];

	MATH_FREE(&buf);
	return retdata;
}

#endif