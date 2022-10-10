#ifndef SANAEMATH_H
#define SANAEMATH_H


/*INCLUDE*/
#include <stdio.h>
#include <stdlib.h>


/*Define Types*/
typedef unsigned int  UINT;
typedef unsigned char MINI;
typedef long long     long64;

/*������z��֕ϊ�����ۂɎg�p����B*/
typedef struct {
	UINT* data;
	UINT len;
}NUMS;

/*�����������s���ۂɎg�p����B*/
typedef struct {
	//���q
	UINT molecule;
	//����
	UINT denominator;
}fraction;


/*Define Function*/
/*�ݏ�̌v�Z*/
UINT   exponentiation(UINT  , UINT);
double exponentiation(double, UINT);
double exponentiation(double from, double count);

/*�����̌v�Z*/
fraction& to_min(fraction&);
double    fraction_num(fraction);

/*�f������*/
bool   is_primenum   (UINT);
/*�ݏ捪�̌v�Z*/
double root    (UINT ,MINI,MINI);
/*������z��֕ϊ�*/
void   SFREE   (NUMS*);
bool   to_array(NUMS*,UINT);
UINT   getnum  (UINT ,UINT);


/*�ݏ�̌v�Z�����܂��B(unsigned int)
from��count�񂩂�������Ԃ��܂��B
*/
UINT exponentiation(UINT from, UINT count) {
	if (count == 0)return 1;
	UINT retdata = from;
	for (UINT i = 1; i < count; i++) {
		retdata *= from;
	}
	return retdata;
}


/*�ݏ�̌v�Z�����܂��B(double)
from��count�񂩂�������Ԃ��܂��B
*/
double exponentiation(double from, UINT count) {
	if (count == 0)return 1;
	double retdata = from;
	for (UINT i = 1; i < count; i++) {
		retdata *= from;
	}
	return retdata;
}


/*�ݏ�̌v�Z�����܂��B(double)
from��count(double)�񂩂�������Ԃ��܂��B
*/
double exponentiation(double from, double count) {
	if (count == 0)return 1;
	double retdata = from;
	/*���ꕪ�q������*/
	fraction b = {0,0};
	
	for (b.denominator = 1; ((count * b.denominator) - (UINT)(b.denominator * count)) != 0; b.denominator *= 10);
	b.molecule = (UINT)count * b.denominator;
	to_min(b);

	/*2^0.5=2^5/10*/
	UINT d = (UINT)exponentiation(from,b.molecule);
	return root(d,b.denominator,3);
}


/*�񕪂��s���܂��B*/
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
		}
	}
	return data;
}


/*�����̌v�Z���s���܂��B*/
double fraction_num(fraction data) {
	return (double)data.molecule / (double)data.denominator;
}


/*�f�����f���łȂ����𔻒肵�܂��B*/
bool is_primenum(UINT data) {
	if (data == 1 || data == 2)return true;
	if (data % 2 == 0)return false;
	for (UINT i = 3; i < data; i += 2)
		if (data % i == 0)return false;
	return true;
}


/*rootnum�捪data�̒l�����߂܂��B
digitnum���܂ŏ��������߂܂��B
*/
double root(UINT data, MINI rootnum = 2, MINI digitnum = 3) {
	if (digitnum > 6) digitnum = 6;
	/*�ꌅ�ڂ�������*/
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
	/*�ׂ�������������*/
	for (double digit = 0.1; digit > (1 / (exponentiation((UINT)10, (UINT)digitnum))); digit *= 0.1) {
		for (double num = 0 * digit; num <= (9 * digit); num += (1 * digit)) {
			if ((exponentiation((double)retdata + num, (UINT)rootnum)) >= data) {
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


/*������z��֕ϊ����܂��B*/
bool to_array(NUMS* toarray, UINT data) {
	SFREE(toarray);
	/*���������߂�*/
	UINT digit = 1;
	for (UINT i = 10; (i - 1) < data; i *= 10, i += 1,digit++);
	/*�������m�ۂ���*/
	if ((toarray->data=(UINT*)calloc(digit,sizeof(UINT)))==NULL)return false;
	toarray->len = digit;
	/*��������i�[���Ă���*/
	for (UINT i = 0; i < digit-1;i++) {
		/*���̌�������o���Ă���*/
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


/*�w�肵�����̒l����肵�܂��B
���s�����ꍇ0��Ԃ��܂��B
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