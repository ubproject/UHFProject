# UHFProject目標
・使いやすく安全に使えるよう保守性を重視してプログラミングを行うようにする。  
・標準ライブラリをあまり使わずできるだけ自分で考えたアルゴリズムを使うようにする。  
# 構成
ベースとしてC言語で記述したプログラムを集積しstr型やfile型を作成する。  
Sanae.hによりすべてのヘッダーファイルをインクルードする。  
Sanae.h  
- SanaeUtil.h  
  * time.h
  * stdlib.h
- SanaeMath.h  
  * stdlib.h  
- SanaeStr.h  
  * SanaeStrc.h  
    1.  string.h  
    2.  stdlib.h  
    3.  stdio.h  
  * SanaeWchar.h  
    1.  SanaeStrc.h  
    2.  wchar.h  
    3.  locale.h  
    4.  stdlib.h  
  * stdexcept  
  * vector  
- SanaeFile.h  
  * SanaeFilec.h  
    1.  stdio.h
    2.  SanaeStrc.h
# 型/メンバ紹介
## SanaeStr.h
	//代入
	str _str = "Hello";  //Hello
	
	//文字列・数字の追加
	_str.add("Hello");   //HelloHell
	_str.add(2022);      //HelloHello2022
	
	//0~4までの文字列を削除
	_str.erase({0,4});   //Hello2022
	
	//表示
	printf("%s\n",   _str.c_str());  //Hello2022
	wprintf(L"%s\n", _str.c_wstr()); //Hello2022
	
	//Alpha,Bravo,Charlie,Deltaを代入
	_str = "Alpha,Bravo,Charlie,Delta";
	//分割用のコンテナを用意
	std::vector<str> str_array;
	//特定の文字(',')で分割し分割したデータをstr_arrayに格納
	_str.division(&str_array,',');
	for (str i:str_array) {
		printf("%s\n",i.c_str());
	}
	/*
	Alpha
	Bravo
	Charlie
	Delta
	*/
	//'a'の数を調査
	printf("%u\n", _str.count('a')); //4

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


## SanaeMath.h
	//2の5乗を計算
	printf("%u\n",exponentiation((UINT)2, 5));  //32
	
	//11は素数か判定
	printf("%d\n",is_primenum(11));             //true(1)
	
	//2^1/2を計算(下三桁)
	printf("2^1/2=%lf\n",root(2,2,3));          //2^1/2=1.414
	
	//2^1/2を計算(下六桁)
	printf("2^1/2=%lf\n",root(2,2,6));          //2^1/2=1.414213
	
	//2^1/5を計算(下三桁)
	printf("2^1/5=%lf\n",root(2,5,3));          //2^1/5=1.148
