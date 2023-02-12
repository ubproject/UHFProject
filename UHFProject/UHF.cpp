//============================================================================
// Name        : UHF.cpp
// Author      : Sanae
// Version     : 1.0.3
//============================================================================

#include <iostream>
#include "UHF/Sanae.h"


void SanaeStr() {
	/*SanaeStr.hサンプルプログラム*/
	//Samapleで初期化
	str sample_str = "Sample";
	printf("文字列:%s\n", sample_str.c_str());	//文字列:Sample


	//ワイド文字を代入
	sample_str = L"Hello\n";
	wprintf(sample_str.c_wstr());				//Hello


	//数値を代入
	sample_str = 1234;
	printf("%s\n", sample_str.c_str());			//1234


	//文字追加									//1234です。12
	sample_str += "です。12";
	//sample_str.add("です。12");

	//数値に変換(最初から最後まで)
	Ulong i = sample_str.to_ulong(RANGE_DEFAULT);
	printf("数値は:%llu\n", i);					//123412


	//文字列を入れ替える World->Sanae
	sample_str = "HelloWorld";
	sample_str.replace("World", "Sanae");
	printf("入れ替え後:%s\n", sample_str.c_str());//HelloSanae


	//文字列を特定文字で分割する。(',')
	sample_str = "alpha,bravo,delta,eco";
	std::vector<str> test;
	sample_str.division(&test, ',');
	//表示する
	for (str i : test)
		printf("%s\n", i.c_str());
	/*
	alpha
	bravo
	delta
	eco
	*/


	//最初から最後まで削除する。
	sample_str.erase({ 0,strlen(sample_str.c_str()) });
	//sample_str.erase(RANGE_DEFAULT);


	//比較演算子 == !=
	sample_str = "HelloWorld";
	if (sample_str == "HelloWorld")			//true
		printf("一致しました。\n");

	return;
}
void SanaeStrc() {
	STRC sample = STRC_Init_Value;

	//文字列の確保&文字列の書き込み
	{
		if (FALSE == STRC_ALLOC(&sample, 6)) {
			printf("メモリの確保に失敗しました。\n");
			return;
		}
		STRC_WRITE(&sample, "hello", BASICW);
	}
	/*STRC_COPY(&sample, "hello");*/

	//文字列の追加
	STRC_ADD(&sample,"world");

	//文字列切り抜き
	RANGE buf = {0,4};
	STRC_SUB(&sample,sample._str,buf);
	//sample._str=hello

	//文字列入れ替え
	STRC_COPY(&sample,"Hello World");//sample=Hello World
	STRC_REPLACE(&sample,"World","Sanae",0);//sample=Hello Sanae

	//メモリの開放
	STRC_FREE(&sample);

	return;
}
int main() {
	SanaeStrc();
	SanaeStr();
	return 0;
}
