# UHFProject目標
・使いやすく安全に使えるよう保守性を重視してプログラミングを行うようにする。  
・標準ライブラリをあまり使わずできるだけ自分で考えたアルゴリズムを使うようにする。
# 詳細
Project:UHF  
Version:1.0.2  
DEV:Sanae  

# 構成
ベースとしてC言語で記述したプログラムを集積しstr型やfile型を作成する。  
Sanae.hによりすべてのヘッダーファイルをインクルードする。  
Sanae.h  
- UHF/UHFC/SanaeUtilc.h  
  * time.h
  * stdio.h
  * stdlib.h
  * SanaeTypes.h
- UHF/UHFC/SanaeMath.h  
  * stdlib.h  
  * time.h
  * limits.h
  * SanaeTypes.h
- UHF/SanaeStr.h  
  * UHFC/SanaeStrc.h  
    1.  string.h  
    2.  stdlib.h  
    3.  stdio.h  
	4.	SanaeTypes.h
  * UHFC/SanaeWchar.h  
    1.  SanaeStrc.h
	2.	SanaeTypes.h
    3.  wchar.h  
    4.  locale.h  
    5.  stdlib.h  
  * stdexcept  
  * vector 
  * SanaeTypes.h

# 型/メンバ紹介
## SanaeStr.h
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

## SanaeFile.h
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
	printf("%s\n",text.c_str());     //Copyright 2016 SanaeProject

## SanaeMathc.h
	//2の5乗を計算
	printf("%llu\n",exponentiation((UINT)2, 5));  //32
	
	//11は素数か判定
	printf("%d\n",is_primenum(11));             //true(1)
	
	//2^1/2を計算(下三桁)
	printf("2^1/2=%lf\n",root(2,2,3));          //2^1/2=1.414
	
	//2^1/2を計算(下六桁)
	printf("2^1/2=%lf\n",root(2,2,6));          //2^1/2=1.414213
	
	//2^1/5を計算(下三桁)
	printf("2^1/5=%lf\n",root(2,5,3));          //2^1/5=1.148
	
	//LCGsによる乱数出力
	printf("%d\n",LCGs()%10);

## SanaeStatistics.h
	//92を素因数分解
	UINT a = 92;
	std::vector<UINT> test;
	
	factorization(test,a);
	
	for(UINT i:test)
		printf("%u",i);
		
## SanaeUtilc.h
	//1~9までの整数を出力
	printf("1~9:%u\n",random(1,9));
	
	//year:2022  day:286  23:21:29
	printf("year:%u  day:%u  %u:%u:%u\n",get_year(),get_day(),get_hour(),get_minutes(),get_second());
