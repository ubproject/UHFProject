#include <stdio.h>
#include "Sanae.h"

void str_test() {
	//代入
	str _str = "Hello";  //Hello

	//文字列・数字の追加
	_str.add("Hello");   //HelloHell
	_str.add(2022);      //HelloHello2022

	//0~4までの文字列を削除
	_str.erase({ 0,4 });   //Hello2022

	//表示
	printf("%s\n", _str.c_str());  //Hello2022
	wprintf(L"%s\n", _str.c_wstr()); //Hello2022

	//Alpha,Bravo,Charlie,Deltaを代入
	_str = "Alpha,Bravo,Charlie,Delta";

	//分割用のコンテナを用意
	std::vector<str> str_array;

	//特定の文字(',')で分割し分割したデータをstr_arrayに格納
	_str.division(&str_array, ',');
	for (str i : str_array) {
		printf("%s\n", i.c_str());
	}
	/*
	Alpha
	Bravo
	Charlie
	Delta
	*/
	//'a'の数を調査
	printf("%llu\n", _str.count('a')); //4

	return;
}
void file_test() {
	//ファイル名SanaeProject.log
	file _file = "SanaeProject.log";

	//書き込み
	_file.write("Copyright 2016");

	//追記
	_file.add(" SanaeProject.");

	//読み取ったデータの格納先を作成
	str text;
	//読み取り
	_file.read(&text);
	//出力
	printf("%s\n", text.c_str());     //Copyright 2016 SanaeProject
	
	return;
}
void mathc_test() {
	//2の5乗を計算
	printf("%lf\n", exponentiation(2, 5));  //32

	//11は素数か判定
	printf("%d\n", is_primenum(11));             //true(1)

	//2^1/2を計算(下三桁)
	printf("2^1/2=%lf\n", root(2, 2, 3));          //2^1/2=1.414

	//2^1/2を計算(下六桁)
	printf("2^1/2=%lf\n", root(2, 2, 6));          //2^1/2=1.414213

	//2^1/5を計算(下三桁)
	printf("2^1/5=%lf\n", root(2, 5, 3));          //2^1/5=1.148

	//LCGsによる乱数出力
	printf("%llu\n", LCGs() % 10);

	return;
}
void math_test() {
	//92を素因数分解
	UINT a = 92;
	std::vector<UINT> test;

	factorization(test, a);

	for (UINT i : test)
		printf("%u", i);

	return;
}
void util_test() {
	//1~9までの整数を出力
	printf("1~9:%u\n", random(1, 9));

	//year:2022  day:286  23:21:29
	printf("year:%u  day:%u  %u:%u:%u\n", get_year(), get_day(), get_hour(), get_minutes(), get_second());

	return;
}

int main(int argc,char* argv[]) {
	void (*str  )() = str_test;
	void (*file )() = file_test;
	void (*mathc)() = mathc_test;
	void (*math )() = math_test;
	void (*util )() = util_test;

	printf("str.h\n");
	str();
	system("pause");

	printf("file.h\n");
	file();
	system("pause");

	printf("mathc.h\n");
	mathc();
	system("pause");

	printf("math.h\n");
	math();
	system("pause");

	printf("util.h\n");
	util();
	system("pause");
}