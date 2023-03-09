//============================================================================
// Name        : UHF.cpp
// Author      : Sanae
// Version     : 1.0.3
//============================================================================

#include <iostream>
#include "UHF/Sanae.h"
#include "UHF/SanaeID3.h"

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
	STRC_COPY   (&sample,"Hello World"    );//sample=Hello World
	STRC_REPLACE(&sample,"World","Sanae",0);//sample=Hello Sanae

	//メモリの開放
	STRC_FREE(&sample);

	return;
}
void SanaeMatrix() {
	//行列を扱う5*5行列
	matrix test = { 5,5 };

	test.write_line(0, { 3, 1, 1, 3, 0 });
	test.write_line(1, { 5, 1, 3, 2, 2 });
	test.write_line(2, { 2, 0, 1, 8, 1 });
	test.write_line(3, { 0, 1, 3, 9, 3 });
	test.write_line(4, { 2, 2, 5, 1, 5 });

	test.view("%5.0lf ");

	printf("行列式:%lg\n", test.det());//86

	matrix buf = test;

	//逆行列にする。
	test.inverse();

	//元の式と逆行列を掛けると単位行列になる。A*A^-1=1
	(buf * test).view("%5.0lf");

	//9x+2y=13
	//5x+9y=33をx,yについて解く
	/*
	9 2 * x = 13
	5 9   y   33
	   ↓
	A * x = Z
		y

	A^-1*A=1より

	x = A^-1*Z
	y

	これを解くことでx,yについて求めることができる。
	*/
	matrix z = { 1,2 };
	z[{0, 0}] = 13;
	z[{0, 1}] = 33;

	matrix A = { 2,2 };
	A.write_line(0, { 3,2 });
	A.write_line(1, { 5,9 });

	(A.inverse() * z).view();
	// 3
	// 2
	//よってx=3,y=2である。
}
void id3() {
	//データ:https://ja.wikipedia.org/wiki/ID3
	ID3 test = IN_ID3_NoTitle
	{
		{{"肉食","卵生","恒温"},"鳥類"  },
		{{"肉食","胎生","恒温"},"哺乳類"},
		{{"草食","胎生","恒温"},"哺乳類"},
		{{"肉食","卵生","変温"},"爬虫類"},
		{{"草食","卵生","恒温"},"鳥類"  }
	};
	//学習
	test.fit();
	//学習した決定木を出力する。
	test.view_tree();
	//学習したデータをファイルに出力
	test.write();
	//学習データに基づき判定する。
	printf("判定:%s",test.get({"草食","卵生","変温"}).c_str());//爬虫類
	
	system("pause");

	//他の例
	//データ:https://www.saedsayad.com/decision_tree.htm
	ID3 test2 = IN_ID3{
	{
		{"Outlook","temp","Humidity","Windy"},"PlayGolf"
	},{
		{{"rainy"   ,"hot" ,"high"  ,"false"},"no"},
		{{"rainy"   ,"hot" ,"high"  ,"true" },"no"},
		{{"overcast","hot" ,"high"  ,"false"},"yes"},
		{{"sunny"   ,"mild","high"  ,"false"},"yes"},
		{{"sunny"   ,"cool","normal","false"},"yes"},
		{{"sunny"   ,"cool","normal","true" },"no" },
		{{"overcast","cool","normal","true" },"yes"},
		{{"rainy"   ,"mild","high"  ,"false"},"no" },
		{{"rainy"   ,"cool","normal","false"},"yes"},
		{{"sunny"   ,"mild","normal","false"},"yes"},
		{{"rainy"   ,"mild","normal","true" },"yes"},
		{{"overcast","mild","high"  ,"true" },"yes"},
		{{"overcast","hot" ,"normal","false"},"yes"},
		{{"sunny"   ,"mild","high"  ,"true" },"no" }
	}
	};
	//学習
	test2.fit();
	//学習した決定木を出力する。
	test2.view_tree();
	//学習データに基づき判定する。
	printf("判定:%s",test2.get({"sunny","mild","high","true"}).c_str());//no
	//学習データをファイルへ書き出し
	test2.write();

	system("pause");

	//書き込んだデータを取り込む
	ID3 test3;
	test3.read();
	printf("読み取ったデータ。\n");
	test3.view_tree();
	//学習データに基づき判定する。
	printf("判定:%s", test3.get({ "sunny","mild","high","true" }).c_str());//no
}
int main() {
	SanaeStrc();
	SanaeStr ();
	SanaeMatrix();
	id3();

	return 0;
}
