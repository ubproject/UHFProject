#ifndef SANAEMATHC_H
#define SANAEMATHC_H


/*INCLUDE*/
#include <stdlib.h>
#include <time.h>


/*Define Types*/
typedef unsigned int  UINT;
typedef unsigned char MINI;
typedef long long     long64;

/*������z��֕ϊ�����ۂɎg�p����B*/
typedef struct {
	MINI*   data;
	long64  len;
}NUMS;

/*�����������s���ۂɎg�p����B*/
typedef struct {
	//���q
	UINT molecule;
	//����
	UINT denominator;
}fraction;

//�����������g�p
#define S_RANDOM_A 48271
#define S_RANDOM_M 2147483648-1

//�����������Ɏg�p����B
struct LCGsT {
	int  seed;
	int  count;
	bool is_set_seed;
}LCGS_INFO = { 0, 0, false };


/*Define Function*/
/*�ݏ�̌v�Z*/
double    exponentiation(double, double, UINT);

/*�����̌v�Z*/
fraction& to_min      (fraction&);
double    fraction_num(fraction);

/*�f������*/
bool      is_primenum (UINT);

/*���`�����@�ɂ�闐������*/
//�V�[�h�l��ݒ肷��B
void      SLCGs (int, int);
//��������
long64    LCGs  (int, int);

/*�݂��ɑf�����肷��B*/
bool      is_relatively_prime(UINT, UINT);
UINT      relatively_prime   (UINT, UINT);

/*�t�B�{�i�b�`��������߂�B*/
UINT      fibonacci          (UINT);

/*�ݏ捪�̌v�Z*/
double    root     (long64 ,MINI ,MINI );

/*������z��֕ϊ�*/
void      MATH_FREE(NUMS*);
bool      to_array (NUMS*,long64);
UINT      getnum   (UINT ,UINT);


/*�ݏ�̌v�Z�����܂��B(double)
from��count(double)�񂩂�������Ԃ��܂��B
*/
double exponentiation(double from, double count,UINT digitnum=3) {
	if (count == 0)return 1;
	
	if ((count-(long64)count)==0) {
		if (count == 0) 
			return 1;
		double buf = from;
		for (UINT i = 1; i < count; i++)
			buf *= from;

		return buf;
	}

	double retdata = from;
	/*���ꕪ�q������*/
	fraction b = {0,0};
	
	for (b.denominator = 1; ((count * b.denominator) - (UINT)(count*b.denominator)) != 0; b.denominator *= 10);
	b.molecule = (UINT)((double)count * (double)b.denominator);

	to_min(b);

	UINT d = (UINT)exponentiation(from,b.molecule);
	return root(d,b.denominator,digitnum);
}


/*�񕪂��s���܂��B*/
fraction& to_min(fraction& data) {
	if (is_primenum(data.denominator) || is_primenum(data.molecule))
		return data;

	if (data.denominator%data.molecule == 0) 
	{	
		data.denominator /= data.molecule;
		data.molecule     = 1;
		
		return data;
	}
	else if(data.molecule%data.denominator == 0) 
	{
		data.molecule    /= data.denominator;
		data.denominator  = 1;

		return data;
	}

	for (UINT i = 2; i < data.denominator && i < data.molecule;i++) {
		if (data.denominator%i==0 && data.molecule%i==0) 
		{
			data.denominator /= i;
			data.molecule    /= i;

			i = 2;
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
	if (data == 1 || data == 2) return true;
	if (data % 2 == 0)          return false;

	for (UINT i = 3; i < data; i += 2)
		if (data % i == 0)      return false;

	return true;
}


/*data�ƌ݂��ɑf�Ȓl���o�͂��܂��B(min�ȏ�����߂邱�Ƃ��ł��܂��B)*/
UINT relatively_prime(UINT data,UINT min=2) {
	UINT retdata = min;

	if (is_primenum(data)) {
		if (data!=retdata)
			return retdata;

		for (retdata = 3;;retdata+=2) {
			if (data != retdata && is_primenum(retdata))
				return retdata;
		}
	}

	for (retdata = min;;retdata++) {
		if (is_relatively_prime(retdata,data)) {
			return retdata;
		}
	}
}


/*�݂��ɑf���]������*/
bool is_relatively_prime(UINT data1,UINT data2) {
	if (data1 % 2 == 0 && data2 % 2 == 0)
		return false;

	for (UINT i = 3; i <= data1 && i <= data2;i+=2) {
		if (is_primenum(i)) {
			if (data1%i==0 && data2%i==0) {
				return false;
			}
		}
	}

	return true;
}


//seed�ɕ��̐������͂��ꂽ�ꍇ�����Ō��߂܂��B
void SLCGs(int seed=-1,int count=10) {
	LCGsT* lp       = &LCGS_INFO;

	if (seed<0) {
		union bufT{
			time_t time;
			UINT   show[sizeof time_t / sizeof UINT];
		}gets = {time(NULL)};

		seed = (int)gets.show[0] < 0 ? gets.show[0] * -1 : gets.show[0];
	}

	lp->seed        = seed;
	lp->count       = count;
	lp->is_set_seed = true;
}


/*�����������s���܂��B
�o�T:
https://ja.wikipedia.org/wiki/%E7%B7%9A%E5%BD%A2%E5%90%88%E5%90%8C%E6%B3%95
*/
long64 LCGs(int seed=-1,int count=LCGS_INFO.count) {
	if (!LCGS_INFO.is_set_seed)
		SLCGs(seed,count);

	if (seed == -1)
		seed = LCGS_INFO.seed;

	for (int i = 0; i < count; i++) {
		seed = (S_RANDOM_A * seed) % S_RANDOM_M;
		if (seed<0) 
			seed += S_RANDOM_M+1;
	}

	LCGS_INFO.count++;
	return seed;
}


//count�ڂ̒l��Ԃ��܂��B
long64 fibonacci(long64 count) {
	if (count<=2)
		return 1;

	return fibonacci(count-1)+fibonacci(count-2);
}


/*rootnum�捪data�̒l�����߂܂��B
digitnum���܂ŏ��������߂܂��B
*/
double root(long64 data, MINI rootnum = 2, MINI digitnum = 3) {
	if (digitnum > 6) digitnum = 6;
	/*������������*/
	//retdata�ɒl���i�[
	double retdata = 0;

	for (long64 i = 1; i <= data; i++) {
		//i��rootnum�悵������data�Ɠ����ꍇ
		if (exponentiation((double)i, (double)rootnum) == data) {
			return (double)i;
		}
		//i��rootnum�悵������data�𒴂��Ă��܂����ꍇi-1���i�[
		else if (exponentiation((double)i, (double)rootnum) > data) {
			retdata = (double)(i - 1);
			break;
		}
	}

	//�������̂݋��߂邱�Ƃ��w�肳��Ă���ꍇ
	if (digitnum == 0)
		return retdata;

	//�ŏ��l
	double min_digit = ((double)1 / ((double)exponentiation((double)10, (double)digitnum)));
	//�J��グ�J�艺�����s���ۂɎg�p
	long64 count = 1;

	/*�ׂ�������������*/
	//0.1->0.01->0.001�̂悤�Ɍ��������炵�Ă���
	for (double digit = 0.1; digit >= min_digit; digit /= 10,count++) {
		//0.01->0.02->0.03�Ƒ��₵�Ă���
		for (double num = 0; num < ((double)10 * digit); num += digit) {

			//������.��������+��������...�̒l
			double buf = exponentiation((double)retdata + num, rootnum);
			
			//�������Ɠ����悤��2�悵�Č��̒l�𒴂����ꍇnum-1�����l��retdata�֓����B
			if (buf > data) {
				num     -= digit;
				retdata += num;
				break;
			}
			//�Ō�܂ōs���Ă��܂�����9�ɂ���B
			else if (num >= (9 * digit)) {
				retdata += num;
				break;
			}
		}

		//�J��グ�J�艺�����s��
		if (count == digitnum) {
			//1.414213->14.14213
			double buf_ret = retdata * 10;
			//14.142135
			double buf = exponentiation((double)buf_ret + (5*digit), rootnum);
			
			//2��̒l�𒴂��Ă��܂����ꍇ5�ȏ�Ȃ̂ŌJ��グ
			if (buf <= (data * exponentiation(10,rootnum))) {
				retdata += digit;
			}
		}
	}
	return retdata;
}


/*NUMS�p*/
void MATH_FREE(NUMS* d) {
	free(d->data);
	d->len = 0;
}


/*������z��֕ϊ����܂��B*/
bool to_array(NUMS* toarray, long64 data) {
	MATH_FREE(toarray);
	
	/*���������߂�*/
	long64 digit = 1;
	for (long64 i = 10; (i - 1) < data; i *= 10, i += 1,digit++);
	
	/*�������m�ۂ���*/
	if ((toarray->data=(MINI*)calloc(digit,sizeof(MINI)))==NULL)return false;
	toarray->len = digit;

	/*��������i�[���Ă���*/
	for (long64 i = 0; i < digit-1;i++) {
		/*���̌�������o���Ă���*/
		long64 buf = data;
		data /= 10;
		data *= 10;
		toarray->data[i] = (MINI)(buf - data);
		data /= 10;

		if (data<10) {
			toarray->data[i + 1] = (MINI)data;
			return true;
		}
	}
	return false;
}


/*�w�肵�����̒l����肵�܂��B
���s�����ꍇ0��Ԃ��܂��B
*/
MINI getnum(MINI from,MINI digitnum) {
	if (digitnum == 0)return 0;

	NUMS buf = {NULL,0};

	if (!to_array(&buf, from))return 0;
	if ((digitnum-1) >= buf.len) {
		MATH_FREE(&buf);
		return 0;
	}
	if (buf.data==NULL) 
		return 0;
	
	MINI retdata = buf.data[digitnum - 1];

	MATH_FREE(&buf);
	return retdata;
}

#endif