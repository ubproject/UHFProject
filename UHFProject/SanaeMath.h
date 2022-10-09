#ifndef SANAEMATH_H
#define SANAEMATH_H


/*INCLUDE*/
#include <stdio.h>
#include <stdlib.h>


/*Define Types*/
typedef unsigned int  UINT;
typedef unsigned char MINI;
typedef long long     long64;

typedef struct {
	UINT* data;
	UINT len;
}NUMS;


/*Define Function*/
UINT   exponentiation(UINT  , UINT);
double exponentiation(double, UINT);
bool   is_primenum   (UINT);
double root    (UINT ,MINI,MINI);
void   SFREE   (NUMS*);
bool   to_array(NUMS*,UINT);
UINT   getnum  (UINT ,UINT);


/*累乗の計算をします。(unsigned int)
fromをcount回かけた数を返します。
*/
UINT exponentiation(UINT from, UINT count) {
	UINT retdata = from;
	for (UINT i = 1; i < count; i++) {
		retdata *= from;
	}
	return retdata;
}


/*累乗の計算をします。(double)
fromをcount回かけた数を返します。
*/
double exponentiation(double from, UINT count) {
	double retdata = from;
	for (UINT i = 1; i < count; i++) {
		retdata *= from;
	}
	return retdata;
}


/*素数か素数でないかを判定します。*/
bool is_primenum(UINT data) {
	if (data == 1 || data == 2)return true;
	if (data % 2 == 0)return false;
	for (UINT i = 3; i < data; i += 2)
		if (data % i == 0)return false;
	return true;
}


/*rootnum乗根dataの値を求めます。
digitnum桁まで少数を求めます。
*/
double root(UINT data, MINI rootnum = 2, MINI digitnum = 3) {
	if (digitnum > 6) digitnum = 6;
	/*一桁目を見つける*/
	double retdata = 0;
	for (UINT i = 1; i <= data; i++) {
		if (exponentiation(i, rootnum) == data) {
			retdata = i;
			return retdata;
		}
		else if (exponentiation(i, rootnum) > data) {
			retdata = (i - 1);
			break;
		}
	}
	/*細かい桁を見つける*/
	for (double digit = 0.1; digit > (1 / (exponentiation((double)10, digitnum))); digit *= 0.1) {
		for (double num = 0 * digit; num <= (9 * digit); num += (1 * digit)) {
			if ((exponentiation(retdata + num, rootnum)) >= data) {
				num -= 1 * digit;
				retdata += num;
				break;
			}
		}
	}
	return retdata;
}


void SFREE(NUMS* d) {
	free(d->data);
	d->len = 0;
}


/*整数を配列へ変換します。*/
bool to_array(NUMS* toarray, UINT data) {
	SFREE(toarray);
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
		SFREE(&buf);
		return 0;
	}

	UINT retdata = buf.data[digitnum - 1];

	SFREE(&buf);
	return retdata;
}

#endif