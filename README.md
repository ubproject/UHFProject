# UHFProject目標
・使いやすく安全に使えるよう保守性を重視してプログラミングを行うようにする。  
・標準ライブラリをあまり使わずできるだけ自分で考えたアルゴリズムを使うようにする。
# 詳細
Project:UHF  
Version:1.0.3  
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
- UHF/SanaeFile.h  
  * SanaeStr.h
  * stdexcept
  * UHFC/SanaeFilec.h  
    1.  stdio.h
    2.  SanaeStrc.h
	3.	SanaeTypes.h

# 型/メンバ紹介
## C言語
### Sanae.h
	UHFC/SanaeC.h
	SanaeFile.h
	SanaeStatistics.h
	SanaeStr.h
	をインクルードします。

### SanaeStr.h
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

### SanaeFile.h
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

### SanaeMathc.h
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

### SanaeStatistics.h
	//92を素因数分解
	UINT a = 92;
	std::vector<UINT> test;
	
	factorization(test,a);
	
	for(UINT i:test)
		printf("%u",i);
		
### SanaeUtilc.h
	//1~9までの整数を出力
	printf("1~9:%u\n",random(1,9));
	
	//year:2022  day:286  23:21:29
	printf("year:%u  day:%u  %u:%u:%u\n",get_year(),get_day(),get_hour(),get_minutes(),get_second());

## C言語
### UHFC/SanaeC.h
	SanaeStrc.h
	SanaeWchar.h
	SanaeFilec.h
	SanaeMathc.h
	SanaeUtilc.h
	をインクルードする。
### UHFC/SanaeTypes.h
	以下のものを定義します。

	Ulong (unsigned _int64)
	Slong (signed   _int64)
	Uint  (unsigned int)

	//返り値として使われます。
	RETNUM(unsigned char)

	MINI  (unsigned char)

	TRUE,FALSE (enum)

	RANGE     (struct)
	WRITE_INFO(struct)

	//文字列操作用構造体
	STRC      (struct)
	//wchar_tの文字列操作用構造体
	WSTRC     (struct)
	//シード値自動設定用
	LCGsT     (struct)
	//整数を配列へ変換する
	num_array (struct)
	//ファイル操作用
	FILEC     (struct)
	//ストップウォッチ(struct)
	StopWatch
	//時間の定義
	TIME      (enum)

	//LCGs関数で乱数生成用
	SM_RANDOM_A
	SM_RANDOM_m
	//範囲のデフォルト値(すべて選択)
	RANGE_DEFAULT
	//文字列書き込みのデフォルト値
	BASICW
	//STRC構造体初期値
	STRC_Init_Value
	//WSTRC構造体初期値
	WSTRC_Init_Value
	//FILEC構造体初期値
	FILEC_Init_Value
	//StopWatch構造体初期値
	StopWatch_Init_Value
	//シード値自動設定用
	LCGs_INFO


### UHFC/SanaeStrc.h
#### 初期化する
	//STRC構造体を使用する際は必ず初期化してください。
	void   STRC_init   (STRC* _data);
#### メモリを解放する
	//メモリを解放します。メモリリーク回避のため必ず最後にメモリを解放してください。
	void   STRC_FREE   (STRC* _data);
#### メモリを確保する
	//第二引数だけメモリを確保します。
	RETNUM STRC_ALLOC  (STRC* _data  , Ulong       _alloc_count);
#### メモリを再確保する
	RETNUM STRC_REALLOC(STRC* _data  , Ulong       _alloc_count);
#### 文字列をコピーする
	//文字列をコピーします。_CopyToは最初にメモリを解放されます。
	RETNUM STRC_COPY   (STRC* _CopyTo, const char* _text);
#### 文字列を追加する
	RETNUM STRC_ADD    (STRC* _data  , const char* _text);
#### 特定文字の個数をカウントする
	Ulong  STRC_COUNTC (STRC* _data  , char        _cchar);
#### 文字列を書き込む
	/*
	_dataに_textの文字列を書き込みます。
	書き込むためにはあらかじめメモリを確保する必要があります。
	WRITE_INFO構造体には
	・start_point
	・_range
	があります。
	start_pointは書き込む位置(配列番号)
	_rangeには_textの範囲を指定可能です。
	指定しない場合は
	BASICWを引数に渡してください。
	*/
	RETNUM STRC_WRITE  (STRC* _data  , const char* _text , WRITE_INFO  _info);
#### 文字を書き込む
	//文字をpointへ書き込みます。
	RETNUM STRC_WRITEC (STRC* _data  , char        _dchar, Ulong       point);
#### 文字列と文字列をつなげる
	RETNUM STRC_CONNECT(STRC* _CopyTo, const char* _data1, const char* _data2);
#### 文字列を切り抜く
	/*_CopyToへ_textから切り抜いた文字列が格納されます。
	_rangeは切り抜く範囲を指定可能です。
	*/
	RETNUM STRC_SUB    (STRC* _CopyTo, const char* _text , RANGE       _range);
#### 文字を探す
	/*_throughは指定された回数だけ見つけても無視します。
	見つからなかった場合は0が返り値として返されSTRC_NOTFOUND_FLAGがTRUEにされます。
	*/
	Ulong  STRC_FINDC  (STRC* _data  , char        _fchar, Ulong       _through);
#### 文字列を探す
	/*_throughは指定された回数だけ見つけても無視します。
	見つからなかった場合は0が返り値として返されSTRC_NOTFOUND_FLAGがTRUEにされます。
	*/
	Ulong  STRC_FIND   (STRC* _data  , const char* _text , Ulong       _through);
#### 文字列と文字列を入れ替える
	RETNUM STRC_REPLACE(STRC* _data  , const char* _from , const char* _to     , Ulong _through);
#### 文字が小文字か大文字かどうか調べる
	RETNUM IS_UPPERCASE(char  _data);
	RETNUM IS_LOWERCASE(char  _data);
#### 文字列を指定した範囲だけ大文字/小文字に変換する
	void   STRC_TO_UPPERCASE(STRC* _data, RANGE _range);
	void   STRC_TO_LOWERCASE(STRC* _data, RANGE _range);