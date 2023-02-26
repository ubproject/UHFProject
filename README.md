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
- UHF/SanaeStatistics.h
	1.	vector
	2.	stdexcept
	3.	SanaeTypes.h

# 型/メンバ紹介
# C++言語
## Sanae.h
	UHFC/SanaeC.h
	SanaeFile.h
	SanaeStatistics.h
	SanaeStr.h
	をインクルードします。

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

## SanaeStatistics.h
	//行列を扱う5*5行列
	matrix test = {5,5};
	
	test.write_line(0, {  3, 1, 1, 3, 0 });
	test.write_line(1, {  5, 1, 3, 2, 2 });
	test.write_line(2, {  2, 0, 1, 8, 1 });
	test.write_line(3, {  0, 1, 3, 9, 3 });
	test.write_line(4, {  2, 2, 5, 1, 5 });

	test.view_matrix("%5.0lf ");

	printf("行列式:%lg\n",test.det());//86

	matrix buf = test;

	//逆行列にする。
	test.matrix_inverse();

	//元の式と逆行列を掛けると単位行列になる。A*A^-1=1
	(buf * test).view_matrix();
	
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
	matrix z = {1,2};
	z[{0, 0}] = 13;
	z[{0, 1}] = 33;

	matrix A = {2,2};
	A.write_line(0, {3,2});
	A.write_line(1, {5,9});

	(A.matrix_inverse()*z).view_matrix();
	// 3
	// 2
	//よってx=3,y=2である。

	//92を素因数分解
	UINT a = 92;
	std::vector<UINT> test;
	
	factorization(test,a);
	
	for(UINT i:test)
		printf("%u",i);

# C言語
## UHFC/SanaeC.h
	SanaeStrc.h
	SanaeWchar.h
	SanaeFilec.h
	SanaeMathc.h
	SanaeUtilc.h
	をインクルードする。

## UHFC/SanaeTypes.h
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


## UHFC/SanaeStrc.h
### 初期化する
	//STRC構造体を使用する際は必ず初期化してください。
	void   STRC_init   (STRC* _data);
### メモリを解放する
	//メモリを解放します。メモリリーク回避のため必ず最後にメモリを解放してください。
	void   STRC_FREE   (STRC* _data);
### メモリを確保する
	//第二引数だけメモリを確保します。
	RETNUM STRC_ALLOC  (STRC* _data  , Ulong       _alloc_count);
### メモリを再確保する
	RETNUM STRC_REALLOC(STRC* _data  , Ulong       _alloc_count);
### 文字列をコピーする
	//文字列をコピーします。_CopyToは最初にメモリを解放されます。
	RETNUM STRC_COPY   (STRC* _CopyTo, const char* _text);
### 文字列を追加する
	RETNUM STRC_ADD    (STRC* _data  , const char* _text);
### 特定文字の個数をカウントする
	Ulong  STRC_COUNTC (STRC* _data  , char        _cchar);
### 文字列を書き込む
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
### 文字を書き込む
	//文字をpointへ書き込みます。
	RETNUM STRC_WRITEC (STRC* _data  , char        _dchar, Ulong       point);
### 文字列と文字列をつなげる
	RETNUM STRC_CONNECT(STRC* _CopyTo, const char* _data1, const char* _data2);
### 文字列を切り抜く
	/*_CopyToへ_textから切り抜いた文字列が格納されます。
	_rangeは切り抜く範囲を指定可能です。
	*/
	RETNUM STRC_SUB    (STRC* _CopyTo, const char* _text , RANGE       _range);
### 文字を探す
	/*_throughは指定された回数だけ見つけても無視します。
	見つからなかった場合は0が返り値として返されSTRC_NOTFOUND_FLAGがTRUEにされます。
	*/
	Ulong  STRC_FINDC  (STRC* _data  , char        _fchar, Ulong       _through);
### 文字列を探す
	/*_throughは指定された回数だけ見つけても無視します。
	見つからなかった場合は0が返り値として返されSTRC_NOTFOUND_FLAGがTRUEにされます。
	*/
	Ulong  STRC_FIND   (STRC* _data  , const char* _text , Ulong       _through);
### 文字列と文字列を入れ替える
	RETNUM STRC_REPLACE(STRC* _data  , const char* _from , const char* _to     , Ulong _through);
### 文字が小文字か大文字かどうか調べる
	RETNUM IS_UPPERCASE(char  _data);
	RETNUM IS_LOWERCASE(char  _data);
### 文字列を指定した範囲だけ大文字/小文字に変換する
	void   STRC_TO_UPPERCASE(STRC* _data, RANGE _range);
	void   STRC_TO_LOWERCASE(STRC* _data, RANGE _range);

## SanaeWchar.h
### 初期化します
	void   WSTRC_init   (WSTRC* _data);
### メモリを解放します
	void   WSTRC_FREE   (WSTRC* _data);
### メモリを確保します
	RETNUM WSTRC_ALLOC  (WSTRC* _data  , Ulong          _alloc_count);
### 文字列を書き込みます
	RETNUM WSTRC_WRITE  (WSTRC* _data  , const wchar_t* _text       , WRITE_INFO     _info);
### 文字列と文字列をつなげます
	RETNUM WSTRC_CONNECT(WSTRC* _CopyTo, const wchar_t* _data1      , const wchar_t* _data2);
### 文字列をコピーします
	RETNUM WSTRC_COPY   (WSTRC* _CopyTo, const wchar_t* _text);
### 文字列を追加します
	RETNUM WSTRC_ADD    (WSTRC* _data  , const wchar_t* _text);
### STRC構造体へ変換します
	RETNUM TO_STRC      (STRC*  _data  , const wchar_t* _text);
### STRC構造体をWSTRC構造体へ変換します
	RETNUM TO_WSTRC     (WSTRC* _wstr  , const char*    _text);

## SanaeMathc.h
### 2の5乗を計算
	printf("%llu\n",exponentiation((UINT)2, 5));  //32
### 11は素数か判定
	printf("%d\n",is_primenum(11));             //true(1)	
### 2^1/2を計算(下三桁)
	printf("2^1/2=%lf\n",root(2,2,3));          //2^1/2=1.414
### 2^1/2を計算(下六桁)
	printf("2^1/2=%lf\n",root(2,2,6));          //2^1/2=1.414213
### 2^1/5を計算(下三桁)
	printf("2^1/5=%lf\n",root(2,5,3));          //2^1/5=1.148
### シード値を設定
	SLCGs((Ulong)time(NULL),100);
### LCGsによる乱数出力
	printf("%d\n"  ,LCGs()%10);
### フィボナッチ数列の引数番目の値を求めます。
	printf("%llu\n"  ,fibonacci(9))				//34
### 桁数の取得
	printf("%llu\n",get_digit(999));			//3
### 数値を配列へ変換
	num_array _data = {NULL,0};
	to_array(&_data,123);

	printf("%u\n",(Uint)_data._data[0]);		//3
	printf("%u\n",(Uint)_data._data[1]);		//2
	printf("%u\n",(Uint)_data._data[2]);		//1

	MATH_FREE(&_data);

## SanaeUtilc.h
### 現在の秒数を取得
	time_t get_second (time_t);
### 現在の分数を取得
	time_t get_minutes(time_t);
### 現在の時間を取得
	time_t get_hour   (time_t);
### 現在の日数を取得
	time_t get_day    (time_t);
### 現在の年数を取得
	time_t get_year   (time_t);
### ストップウォッチをスタートします
	void   StopWatch_Start       (StopWatch*);
### ストップウォッチをストップします
	time_t StopWatch_Finish      (StopWatch*);
### 経過時間を取得します
	time_t StopWatch_elapsed_time(StopWatch*);

## SanaeFilec.h
### メモリを解放します
	void   FILEC_FINISH     (FILEC*      _data);
### ファイルを作成します
	void   FILEC_MAKE       (const char* _filename);
### ファイルが存在するかどうかを判定します
	RETNUM FILEC_IS_EXISTING(const char* _filename);
### ファイルを読み込みます
	RETNUM FILEC_START      (FILEC*      _data    , const char* _filename);
### ファイルの内容を読み取ります
	RETNUM FILEC_READ       (FILEC*      _data    , STRC*       _CopyTo);
### ファイルへ文字列を書き込みます
	RETNUM FILEC_WRITE      (FILEC*      _data    , const char* _text    , const char* _mode);