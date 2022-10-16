#include "Sanae.h"

void test_str() {
	//代入
	str _str = "Hello";  //Hello

	//文字列・数字の追加
	_str.add("Hello");   //HelloHell
	_str.add(2022);      //HelloHello2022

	//0~4までの文字列を削除
	_str.erase({ 0,4 }); //Hello2022

	//表示
	printf("%s\n", _str.c_str());    //Hello2022
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
	printf("%u\n", _str.count('a')); //4
	return;
}
void test_file() {
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
void test_math() {
	//2の5乗を計算
	printf("%u\n", exponentiation((UINT)2, 5));  //32

	//2の0.5乗を計算
	printf("%lf\n", exponentiation(2, 0.5, 3));  //1.414

	//11は素数か判定
	printf("%d\n", is_primenum(11));             //true(1)

	//2^1/2を計算(下三桁)
	printf("2^1/2=%lf\n", root(2, 2, 3));          //2^1/2=1.414

	//2^1/2を計算(下六桁)
	printf("2^1/2=%lf\n", root(2, 2, 6));          //2^1/2=1.414213

	//2^1/5を計算(下三桁)
	printf("2^1/5=%lf\n", root(2, 5, 3));          //2^1/5=1.148

	printf("Sanaemath.h");
	time_t defs = time(NULL);
	for (UINT i = 1; i <= 10000; i++) {
		printf("%u^1/2=%lf\n", i, root(i, 2, 6));
	}
	defs = time(NULL) - defs;
	double bufs = (double)defs / 10000;

	printf("math.h");
	time_t defm = time(NULL);
	for (UINT i = 1; i <= 10000; i++) {
		printf("%u^1/2=%lf\n", i, sqrt(i));
	}
	defm = time(NULL) - defm;
	double bufm = (double)defm / 10000;

	printf("SanaeMathは%lf秒かかりました\nMathは%lf秒かかりました。\n", bufm, bufs);

	return;
}
void test_util() {
	printf("1~9:%u\n",random(1,9));
	printf("year:%u  day:%u  %u:%u:%u\n", get_year(), get_day(), get_hour(), get_minutes(), get_second());
}

int main(void){
	printf("str型\n");
	test_str();

	printf("file型\n");
	test_file();

	printf("math関数群\n");
	test_math();

	printf("util関数群\n");
	test_util();

	return 0;
}