/*
 ============================================================================
 Name        : UHFC-Types-C
 Author      : Sanae
 Version     : 1.0.3(Beta)
 Copyright   : CopyRight 2022 SanaeProject.
 ============================================================================
 */

#ifndef UHFC_SANAETYPES_H_
#define UHFC_SANAETYPES_H_


/*Define Types*/
/*Unsigned long integer type*/
typedef unsigned __int64  Ulong;
typedef signed   __int64  Slong;

/*Unsigned integer type*/
typedef unsigned int      Uint;

/*Unsigned char type*/
typedef unsigned char     RETNUM;
typedef unsigned char     MINI;


/*多目的用*/
/*True or False*/
enum boolean{
	TRUE = 1,
	FALSE= 0
};


/*文字列をコピーするときなどに使用する。
 * frontがbackより大きい場合初期値(デフォルト)として動作する。
 */
typedef struct{
	Ulong front;
	Ulong back;
}RANGE;
//文字列コピーや書き込みをするときに使用(デフォルト)
const RANGE RANGE_DEFAULT = {1,0};


/*書き込みをする際に使用。
 * start_point:書き込み開始地点
 * _range     :書き込む文字列の範囲
 */
typedef struct{
	Ulong start_point;
	RANGE _range;
}WRITE_INFO;
//書き込みをする際に使用(デフォルト)
const WRITE_INFO BASICW = {0,RANGE_DEFAULT};


/*SanaeStrc.h*/
typedef struct{
	char* _str;       //Store the pointer
	Ulong _allocated; //Stores allocated length
}STRC;
//STRC type's init value
const STRC	STRC_Init_Value	= {NULL,0};


/*SanaeWchar.h*/
typedef struct{
	wchar_t* _wstr;
	Ulong    _allocated;
}WSTRC;
//WSTRC type's init value
const WSTRC WSTRC_Init_Value = {NULL,0};


/*SanaeMathc.h*/
/*マクロ*/
//絶対値に直します。
#define   ABS_SANAE    (A)   ((A<0)?(-1*A): A)
//誤差
#define ERROR_SANAE    1.0e-6

//整数か実数か判定します。
#define IS_INT         (A)   ((A - (Ulong)A)==0)
//誤差の範囲内かどうか調べます。
#define IS_EQUAL_DOUBLE(A,B) (ABS_SANAE(A-B) <= ERROR_SANAE)

//ルートを求める際ニュートン法を使用します。
#define USE_NEWTON_METHOD TRUE

//LCGs関数用
#define SM_RANDOM_A 48271
#define SM_RANDOM_M 2147483648-1

//log関数用
typedef struct {
	//分子
	Ulong molecule;
	//分母
	Ulong denominator;
}FRACTION_LOG;

struct LCGsT{
	Ulong seed;
	Ulong count;
	MINI  is_set_seed;
}LCGs_INFO = {0,0,FALSE};

/*数列変換用*/
#ifdef UHFC_SANAESTRC_H_
typedef struct{
	MINI* _data;
	Ulong _length;
}num_array;
#endif


/*SanaeFilec.h*/
typedef struct{
	STRC  filename;
	FILE* file_pointer;
}FILEC;
//FILEC type's init value.
const FILEC FILEC_Init_Value = {STRC_Init_Value, NULL};


/*SanaeUtilc.h*/
typedef struct{
	time_t _start;
	time_t _finish;
}StopWatch;
const time_t NOW = 0;

enum  TIME{
	MIN  = 60,
	HOUR = MIN  * 60,
	DAY  = HOUR * 24,
	YEAR = DAY  * 365,
	GMT  = 9
};
const StopWatch StopWatch_Init = {0,0};


#endif /* UHFC_SANAETYPES_H_ */
