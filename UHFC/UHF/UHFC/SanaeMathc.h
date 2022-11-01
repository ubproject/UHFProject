#ifndef SANAEMATHC_H
#define SANAEMATHC_H


/*INCLUDE*/
#include <stdlib.h>
#include <time.h>


/*Define Types*/
typedef unsigned int  UINT;
typedef unsigned char MINI;
typedef long long     long64;

/*整数を配列へ変換する際に使用する。*/
typedef struct {
	MINI*   data;
	long64  len;
}NUMS;

/*分数処理を行う際に使用する。*/
typedef struct {
	//分子
	UINT molecule;
	//分母
	UINT denominator;
}fraction;

//乱数生成時使用
#define S_RANDOM_A 48271
#define S_RANDOM_M 2147483648-1

//乱数生成時に使用する。
struct LCGsT {
	int  seed;
	int  count;
	bool is_set_seed;
}LCGS_INFO = { 0, 0, false };


/*Define Function*/
/*累乗の計算*/
double    exponentiation(double, double, UINT);

/*分数の計算*/
fraction& to_min      (fraction&);
double    fraction_num(fraction);

/*素数判定*/
bool      is_primenum (UINT);

/*線形合同法による乱数生成*/
//シード値を設定する。
void      SLCGs (int, int);
//乱数生成
long64    LCGs  (int, int);

/*互いに素か判定する。*/
bool      is_relatively_prime(UINT, UINT);
UINT      relatively_prime   (UINT, UINT);

/*フィボナッチ数列を求める。*/
UINT      fibonacci          (UINT);

/*累乗根の計算*/
double    root     (long64 ,MINI ,MINI );

/*整数を配列へ変換*/
void      MATH_FREE(NUMS*);
bool      to_array (NUMS*,long64);
UINT      getnum   (UINT ,UINT);


/*累乗の計算をします。(double)
fromをcount(double)回かけた数を返します。
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


/*dataと互いに素な値を出力します。(min以上も求めることができます。)*/
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


/*互いに素か評価する*/
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


//seedに負の数が入力された場合自動で決めます。
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


/*乱数生成を行います。
出典:
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


//count目の値を返します。
long64 fibonacci(long64 count) {
	if (count<=2)
		return 1;

	return fibonacci(count-1)+fibonacci(count-2);
}


/*rootnum乗根dataの値を求めます。
digitnum桁まで少数を求めます。
*/
double root(long64 data, MINI rootnum = 2, MINI digitnum = 3) {
	if (digitnum > 6) digitnum = 6;
	/*整数を見つける*/
	//retdataに値を格納
	double retdata = 0;

	for (long64 i = 1; i <= data; i++) {
		//iをrootnum乗した物がdataと同じ場合
		if (exponentiation((double)i, (double)rootnum) == data) {
			return (double)i;
		}
		//iをrootnum乗した物がdataを超えてしまった場合i-1を格納
		else if (exponentiation((double)i, (double)rootnum) > data) {
			retdata = (double)(i - 1);
			break;
		}
	}

	//整数部のみ求めることが指定されている場合
	if (digitnum == 0)
		return retdata;

	//最小値
	double min_digit = ((double)1 / ((double)exponentiation((double)10, (double)digitnum)));
	//繰り上げ繰り下げを行う際に使用
	long64 count = 1;

	/*細かい桁を見つける*/
	//0.1->0.01->0.001のように桁数を減らしていく
	for (double digit = 0.1; digit >= min_digit; digit /= 10,count++) {
		//0.01->0.02->0.03と増やしていく
		for (double num = 0; num < ((double)10 * digit); num += digit) {

			//整数部.小数第一位+小数第二位...の値
			double buf = exponentiation((double)retdata + num, rootnum);
			
			//整数部と同じように2乗して元の値を超えた場合num-1した値をretdataへ入れる。
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

		//繰り上げ繰り下げを行う
		if (count == digitnum) {
			//1.414213->14.14213
			double buf_ret = retdata * 10;
			//14.142135
			double buf = exponentiation((double)buf_ret + (5*digit), rootnum);
			
			//2乗の値を超えてしまった場合5以上なので繰り上げ
			if (buf <= (data * exponentiation(10,rootnum))) {
				retdata += digit;
			}
		}
	}
	return retdata;
}


/*NUMS用*/
void MATH_FREE(NUMS* d) {
	free(d->data);
	d->len = 0;
}


/*整数を配列へ変換します。*/
bool to_array(NUMS* toarray, long64 data) {
	MATH_FREE(toarray);
	
	/*桁数を求める*/
	long64 digit = 1;
	for (long64 i = 10; (i - 1) < data; i *= 10, i += 1,digit++);
	
	/*桁数分確保する*/
	if ((toarray->data=(MINI*)calloc(digit,sizeof(MINI)))==NULL)return false;
	toarray->len = digit;

	/*ここから格納していく*/
	for (long64 i = 0; i < digit-1;i++) {
		/*下の桁から取り出していく*/
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


/*指定した桁の値を入手します。
失敗した場合0を返します。
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