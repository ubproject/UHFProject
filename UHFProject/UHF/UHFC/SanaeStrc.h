/*
 ============================================================================
 Name        : UHFC-Strc-C
 Author      : Sanae
 Version     : 1.0.3(Beta)
 Copyright   : CopyRight 2022 SanaeProject.
 ============================================================================
 */

#ifndef UHFC_SANAESTRC_H_
#define UHFC_SANAESTRC_H_


/*INCLUDE*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SanaeTypes.h"


/*STRC_FINDC,STRC_FIND関数を使用時値が更新されます。
 * 上記の関数の返り値は見つからなかった場合"0"なので発見したかできなかったかどうかを
 * この変数により判別します。
　*/
RETNUM		STRC_NOTFOUND_FLAG	= FALSE;


/*Define Function*/
void   STRC_init   (STRC* _data);
void   STRC_FREE   (STRC* _data);
RETNUM STRC_ALLOC  (STRC* _data  , Ulong       _alloc_count);
RETNUM STRC_REALLOC(STRC* _data  , Ulong       _alloc_count);
RETNUM STRC_COPY   (STRC* _CopyTo, const char* _text);
RETNUM STRC_ADD    (STRC* _data  , const char* _text);
Ulong  STRC_COUNTC (STRC* _data  , char        _cchar);
RETNUM STRC_WRITE  (STRC* _data  , const char* _text , WRITE_INFO  _info);
RETNUM STRC_WRITEC (STRC* _data  , char        _dchar, Ulong       point);
RETNUM STRC_CONNECT(STRC* _CopyTo, const char* _data1, const char* _data2);
RETNUM STRC_SUB    (STRC* _CopyTo, const char* _text , RANGE       _range);
Ulong  STRC_FINDC  (STRC* _data  , char        _fchar, Ulong       _through);
Ulong  STRC_FIND   (STRC* _data  , const char* _text , Ulong       _through);
RETNUM STRC_REPLACE(STRC* _data  , const char* _from , const char* _to     , Ulong _through);

RETNUM IS_UPPERCASE(char  _data);
RETNUM IS_LOWERCASE(char  _data);

void   STRC_TO_UPPERCASE(STRC* _data, RANGE _range);
void   STRC_TO_LOWERCASE(STRC* _data, RANGE _range);


/*Functions*/
/*STRC型を初期化する。
 * 注意:
 * この関数ではfreeを実行しないため関数使用前にfreeすること。
 *
 * 例:
 * STRC test;
 * STRC_init(&test);
 */
void STRC_init(STRC* _data){
	_data->_str       = NULL;
	_data->_allocated = 0;
}

/*メモリを解放する。
 * メモリを解放した後値を初期値に戻す。
 *
 * 例:
 * STRC test;
 * STRC_init(&test);         //初期化
 * equal(&test,"helloworld");//確保&書き込み
 * STRC_FREE(&test);         //メモリを解放
 */
void STRC_FREE(STRC* _data){
	free     (_data->_str);
	STRC_init(_data);
}

/*メモリを割り当てる。
 * _alloc_countだけメモリを確保する。
 * この関数では最初にメモリを解放する。
 *
 * 失敗した場合はFALSE(0)を返す。
 * 成功した場合はTRUE(1)を返す。
 *
 * 例:
 * STRC test;
 * STRC_init(&test);   //初期化
 * STRC_ALLOC(&test,5);//5バイト分確保
 */
RETNUM STRC_ALLOC(STRC* _data,Ulong _alloc_count){
	STRC_FREE(_data);

	if(_alloc_count==0)
		return FALSE;
	_data->_str       = (char*)calloc(_alloc_count,sizeof(char));
	_data->_allocated = (_data->_str == NULL) ? 0: _alloc_count;

	return (_data->_str == NULL) ? FALSE: TRUE;
}

/*再割り当てを行う。
 * 失敗した場合FALSE(0)を返す。
 * 成功した場合TRUE(1)を返す。
 */
RETNUM STRC_REALLOC(STRC* _data,Ulong _alloc_count){
	char* buf_ptr     = _data->_str;

	buf_ptr           = (char*)realloc(_data->_str,_alloc_count);
	_data->_allocated = buf_ptr == NULL ? 0: _alloc_count;

	if (buf_ptr == NULL) {
		STRC_FREE(_data);
		return FALSE;
	}

	_data->_str = buf_ptr;
	return (_data->_str == NULL) ? FALSE: TRUE;
}

/*文字列をSTRC型の変数に書き込む。
 * 通常書き込みを行う場合は三つ目のパラメータに"BASICW"を入れること。
 * 指定する:
 * WRITE_INFO test = {書き込み開始地点,{書き込む文字列の範囲}}
 *
 * 注意:
 * この関数では文字列の確保及び解放を行わない。
 * 確保されている領域分だけ書き込む。
 *
 * 例:
 * STRC test = STRC_Init_Value; //初期化
 * STRC_ALLOC(&test,6);         //"hello"のバイト数を確保
 */
RETNUM STRC_WRITE(STRC* _data,const char* _text,WRITE_INFO _info){
	if(_data->_allocated == 0)
		return FALSE;

	if(_info._range.front == RANGE_DEFAULT.front && _info._range.back == RANGE_DEFAULT.back)
	{
		_info._range.front = 0;
		_info._range.back  = strlen(_text);
	}

	for(Ulong i = _info.start_point,j=_info._range.front;(i<_data->_allocated)&&(j <= _info._range.back) && (j <= strlen(_text)); i++, j++)
		_data->_str[i] = _text[j];

	//終端文字列追加
	_data->_str[_data->_allocated - 1] = '\0';

	return TRUE;
}

/*char型の変数をpointに書き込む。
 */
RETNUM STRC_WRITEC(STRC* _data,char _dchar,Ulong point){
	if(_data->_allocated == 0 || point >= _data->_allocated)
		return FALSE;

	_data->_str[point] = _dchar;
	_data->_str[_data->_allocated - 1] = 0;

	return TRUE;
}

/*第二パラメータに指定された文字列を_CopyToに書き込む。
 * 確保及び解放を行う。
 */
RETNUM STRC_COPY(STRC* _CopyTo, const char* _text){
	if (_text == NULL)
		return FALSE;

	RETNUM is_success = STRC_ALLOC(_CopyTo,strlen(_text)+1);
	if(is_success==TRUE)
		STRC_WRITE(_CopyTo,_text,BASICW);

	return is_success;
}

/*代入する。
 */
RETNUM (*equal)(STRC*,const char*) = STRC_COPY;

/*_data1と_data2の文字列を結合し_CopyToに挿入する。
 */
RETNUM STRC_CONNECT(STRC* _CopyTo, const char* _data1, const char* _data2){
	if(_data1 == NULL || _data2 == NULL)
		return FALSE;

	STRC _buf_data1_str = STRC_Init_Value,_buf_data2_str = STRC_Init_Value;

	if (_CopyTo->_str == _data1) {
		if (FALSE == STRC_COPY(&_buf_data1_str, _data1))
			return FALSE;
	}
	if (_CopyTo->_str == _data2) {
		if (FALSE == STRC_COPY(&_buf_data2_str, _data2))
			return FALSE;
	}

	char* _buf_data1 = _buf_data1_str._str == NULL ? (char*)_data1 : _buf_data1_str._str;
	char* _buf_data2 = _buf_data2_str._str == NULL ? (char*)_data2 : _buf_data2_str._str;

	STRC_FREE(_CopyTo);
	
	Ulong length_data1 = strlen(_buf_data1);

	if (FALSE == STRC_ALLOC(_CopyTo, length_data1 + strlen(_buf_data2) + 1))
		return FALSE;

	STRC_WRITE(_CopyTo,_buf_data1,BASICW);
	WRITE_INFO buf = { length_data1,{RANGE_DEFAULT} };

	STRC_WRITE(_CopyTo,_buf_data2,buf);
	
	//解放
	STRC_FREE(&_buf_data1_str);
	STRC_FREE(&_buf_data2_str);

	return TRUE;
}

/*文字列を追加する。
 */
RETNUM STRC_ADD(STRC* _data,const char* _text){
	if (_data->_str == NULL)
		STRC_COPY(_data,"");
		
	if (FALSE == STRC_REALLOC(_data, _data->_allocated + strlen(_text) + 1))
		return FALSE;

	WRITE_INFO buf = {(Ulong)strlen(_data->_str),RANGE_DEFAULT};
	STRC_WRITE(_data,_text,buf);

	return TRUE;
}

/*文字を切り抜く
 * _text[_range.front]~_text[_range.back]まで切り抜く。
 * 失敗した場合FALSE(0)を返す。
 *
 * 例:
 * STRC test = STRC_Init_Value; //初期化
 * equal(&test,"HelloSanae");   //HelloSanaeを代入
 *
 * STRC_SUB(&test,test._str,(RANGE){0,4}); //testに配列番号0~4までの値を挿入。
 * printf("%s",test._str);      //Hello
 */
RETNUM STRC_SUB(STRC* _CopyTo, const char* _text, RANGE _range){
	STRC buf_text_str = STRC_Init_Value;

	if (_CopyTo->_str==_text) {
		if (STRC_COPY(&buf_text_str, _text) == FALSE)
			return FALSE;
	}
	
	char* buf_text = (_CopyTo->_str == _text) ? (char*)buf_text_str._str : (char*)_text;

	STRC_FREE(_CopyTo);

	Ulong size = (Ulong)(_range.back-_range.front) + 2; //2=blank
	if(_range.back<_range.front)
		return FALSE;

	if(STRC_ALLOC(_CopyTo,size)==FALSE)
		return FALSE;

	WRITE_INFO _data = {0,_range};
	if(STRC_WRITE(_CopyTo,(const char*)buf_text,_data)==FALSE)
		return FALSE;

	STRC_FREE(&buf_text_str);

	return TRUE;
}

/*指定文字の個数を返します。
 */
Ulong  STRC_COUNTC(STRC*_data, char _cchar) {
	Ulong _count = 0;

	for (Ulong i = 0; i < _data->_allocated; i++)
		_count += _data->_str[i] == _cchar ? 1 : 0;

	return _count;
}

/*文字を検索します。
 * 見つからなかった場合0を返します。
 * この関数を使用した場合 STRC_NOTFOUND が更新されます。
 * 見つからなかった場合STRC_NOTFOUNDがTRUEになります。
 * 初期値ではFALSEです。
 */
Ulong STRC_FINDC(STRC* _data,char _fchar,Ulong _through){
	for(Ulong i = 0;i < _data->_allocated;i++){
		if(_data->_str[i] == _fchar){
			if(_through==0){
				STRC_NOTFOUND_FLAG = FALSE;
				return i;
			}else{
				_through -= 1;
			}
		}
	}

	STRC_NOTFOUND_FLAG = TRUE;
	return 0;
}

/*文字列を検索します。
 * 見つからなかった場合0を返します。
 * この関数を使用した場合 STRC_NOTFOUND が更新されます。
 * 見つからなかった場合STRC_NOTFOUNDがTRUEになります。
 * 初期値ではFALSEです。
 */
Ulong STRC_FIND(STRC* _data,const char* _text,Ulong _through){
	size_t length_text = strlen(_text);
	Ulong buf_through  = 0;

	while(TRUE){
		Ulong i = STRC_FINDC(_data,_text[0],_through+buf_through);

		if(i == 0){
			for(Ulong k = 0; k < length_text; k++){
				if(_text[k] != _data->_str[k])
					STRC_NOTFOUND_FLAG = TRUE;
			}

			return 0;
		}

		for(Ulong j = 0;j<length_text;j++){
			if(_text[j] != _data->_str[i+j]){
				buf_through += 1;
				break;
			}
			if(j==length_text-1){
				if(_through == 0){
					STRC_NOTFOUND_FLAG = FALSE;
					return i;
				}else{
					_through --;
					buf_through += 1;
				}
			}
		}
	}

	STRC_NOTFOUND_FLAG = TRUE;
	return 0;
}

/*文字列を入れ替えます。
*/
RETNUM STRC_REPLACE(STRC* _data,const char* _from,const char* _to,Ulong _through){
	STRC buf_front = STRC_Init_Value;
	STRC buf_back  = STRC_Init_Value;

	Ulong pos = STRC_FIND(_data,_from,_through);

	if(STRC_NOTFOUND_FLAG == TRUE)
		return FALSE;

	RANGE buf = {0,pos-1};
	STRC_SUB(&buf_front,_data->_str,buf);

	buf = { pos + strlen(_from),_data->_allocated - 1 };
	STRC_SUB(&buf_back ,_data->_str,buf);

	STRC_FREE(_data);

	STRC_CONNECT(_data, buf_front._str, _to);
	STRC_CONNECT(_data, _data->_str   , buf_back._str);

	STRC_FREE(&buf_front);
	STRC_FREE(&buf_back);

	return TRUE;
}

/*大文字か判定します。
 * 大文字の場合 TRUE
 * それ以外の場合FALSE
 */
RETNUM IS_UPPERCASE(char _data){
	if('A'<=_data && _data <= 'Z')
		return TRUE;
	return FALSE;
}

/*小文字か判定します。
 * 小文字の場合 TRUE
 * それ以外の場合FALSE
 */
RETNUM IS_LOWERCASE(char _data){
	if ('a' <= _data && _data <= 'z')
			return TRUE;
	return FALSE;
}

/*同じ文か判定します。*/
RETNUM IS_EQUAL(const char* _text1,const char* _text2){
	Ulong length1 = strlen(_text1);
	Ulong length2 = strlen(_text2);

	if(length1 == length2){
		for(Ulong i = 0; i < length1; i++){
			if(_text1[i] != _text2[i])
				break;

			if(i == length1-1)
				return TRUE;
		}
	}

	return FALSE;
}

/*指定された範囲を大文字にします。
 * すべてを指定する場合RANGE_DEFAULTを使用してください。
 */
void STRC_TO_UPPERCASE(STRC* _data,RANGE _range){
	if(_data->_str==NULL)
		return;

	if(_range.front==RANGE_DEFAULT.front && _range.back == RANGE_DEFAULT.back){
		_range.front = 0;
		_range.back  = _data->_allocated;
	}

	unsigned char buf_range = 'a' - 'A';

	for(Ulong i = _range.front;(i<_data->_allocated)&&(i<=_range.back);i++){
		if(IS_LOWERCASE(_data->_str[i])==TRUE)
			_data->_str[i] -= buf_range;
	}

	return;
}

/*指定された範囲を小文字にします。
 * すべてを指定する場合RANGE_DEFAULTを使用してください。
 */
void STRC_TO_LOWERCASE(STRC* _data,RANGE _range){
	if(_data->_str==NULL)
		return;

	if(_range.front==RANGE_DEFAULT.front && _range.back == RANGE_DEFAULT.back){
		_range.front = 0;
		_range.back  = _data->_allocated;
	}

	unsigned char buf_range = 'a' - 'A';

	for(Ulong i = _range.front;(i<_data->_allocated)&&(i<=_range.back);i++){
		if(IS_UPPERCASE(_data->_str[i])==TRUE)
			_data->_str[i] += buf_range;
	}

	return;
}

#endif
