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

	system("pause");
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

	system("pause");
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

	//乱数を生成
	UINT d = random(2, 10000);
	printf("%uを素因数分解します。\n", d);
	//コンテナを用意
	std::vector<UINT> l;
	factorization(l, d);
	//出力
	for (UINT i : l) {
		printf("%u\n", i);
	}

	//スピード比較
	printf("ここから時間のかかる処理を行います。\n");
	//一時停止
	wint_t none = _getwch();


	printf("標準ファイルのsqrt関数での処理を行います。\n");
	//一時停止
	none = _getwch();
	
	//sqrt関数の処理をする時間を測る。
	time_t defm = time(NULL);
	for (UINT i = 1; i <= 10000; i++) {
		volatile double data = sqrt(i);
		printf("%u^1/2=%lf\n", i, data);
	}
	defm = time(NULL) - defm;
	printf("sqrt関数では10000回の計算に%lld秒かかりました。\n",defm);

	//一回の処理の時間を計算
	double bufm = (double)defm / 10000;
	printf("一回の計算に:%lfミリ秒かかりました\n",bufm*1000);

	system("pause");

	printf("Sanaemath.hでのroot関数での処理をおこないます。\n");
	//一時停止
	none = _getwch();

	//root関数の処理する時間を測る。
	time_t defs = time(NULL);
	for (UINT i = 1; i <= 10000; i++) {
		volatile double data = root(i,2,6);
		printf("%u^1/2=%lf\n", i, data);
	}
	defs = time(NULL) - defs;

	printf("SanaeMathのroot関数では%lld秒かかりました。\n",defs);


	//一回の処理の時間を計算
	double bufs = (double)defs / 10000;
	printf("一回の計算に%lfミリ秒かかりました。\n",bufs*1000);
	
	system("pause");

	printf("\n\nSanaeMathは%lfミリ秒かかりました\nMathは%lfミリ秒かかりました。\n\n", bufs*1000, bufm*1000);

	system("pause");
	return;
}
void test_util() {
	printf("1~9:%u\n",random(1,9));
	printf("year:%u  day:%u  %u:%u:%u\n", get_year(), get_day(), get_hour(), get_minutes(), get_second());

	system("pause");
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