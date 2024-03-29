﻿/*
 ============================================================================
 Name        : UHFC-Wchar-C
 Author      : Huku
 Version     : 1.0.3(Beta)
 Copyright   : CopyRight 2022 SanaeProject.
 ============================================================================
 */

#ifndef UHFC_SANAEWCHAR_H_
#define UHFC_SANAEWCHAR_H_


/*INCLUDE*/
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>

#include "SanaeTypes.h"
#include "SanaeStrc.h"


/*Define Function*/
void   WSTRC_init   (WSTRC* _data);
void   WSTRC_FREE   (WSTRC* _data);
RETNUM WSTRC_ALLOC  (WSTRC* _data  , Ulong          _alloc_count);
RETNUM WSTRC_WRITE  (WSTRC* _data  , const wchar_t* _text       , WRITE_INFO     _info);
RETNUM WSTRC_CONNECT(WSTRC* _CopyTo, const wchar_t* _data1      , const wchar_t* _data2);
RETNUM WSTRC_COPY   (WSTRC* _CopyTo, const wchar_t* _text);
RETNUM WSTRC_ADD    (WSTRC* _data  , const wchar_t* _text);

RETNUM TO_STRC      (STRC*  _data  , const wchar_t* _text);
RETNUM TO_WSTRC     (WSTRC* _wstr  , const char*    _text);


/*Functions*/
/*WSTRC型を初期化する。
 * 注意:
 * この関数ではfreeしないため関数使用前にfreeしてください。
 * メモリリークが発生する可能性があります。
 */
void WSTRC_init(WSTRC* _data){
	_data->_wstr      = NULL;
	_data->_allocated = 0;
}

/*メモリを解放します。
 * メモリを解放した後値を初期値に戻します。
 */
void WSTRC_FREE(WSTRC* _data){
	free      (_data->_wstr);
	WSTRC_init(_data);
}

/*メモリを割り当てます。
 * _alloc_countだけメモリを確保します。
 * この関数では最初にメモリを解放します。
 *
 * 失敗した場合はFALSEを返し
 * 成功した場合TRUEを返します。
 */
RETNUM WSTRC_ALLOC(WSTRC* _data, Ulong _alloc_count){
	if (_alloc_count == 0) { _alloc_count += 1; }
	WSTRC_FREE(_data);
	_data->_wstr      = (wchar_t*)calloc(_alloc_count, sizeof(wchar_t));
	_data->_allocated = _data->_wstr == NULL ? 0 : _alloc_count;
	return _data->_allocated == 0 ? FALSE : TRUE;
}

/*wchar_t型の文字列をWSTRC型の変数に書き込む
 * 通常書き込みを行う場合は三つ目のパラメータに"BASICW"を入れること。
 * 指定する:
 * WRITE_INFO test = {書き込み開始地点,{書き込む文字列の範囲}}
 *
 * 注意:
 * この関数では文字列の確保及び解放を行わない。
 * 確保されている領域分だけ書き込む。
 */
RETNUM WSTRC_WRITE(WSTRC* _data, const wchar_t* _text, WRITE_INFO _info) {
	if(_data->_allocated == 0)
			return FALSE;

	if(_info._range.front == RANGE_DEFAULT.front && _info._range.back == RANGE_DEFAULT.back)
	{
		_info._range.front = 0;
		_info._range.back  = (Ulong)wcslen(_text);
	}

	for(Ulong i = _info.start_point,j=_info._range.front;(i<_data->_allocated)&&(j <= _info._range.back) && (j <= (Ulong)wcslen(_text)); i++, j++)
		_data->_wstr[i] = _text[j];

	//終端文字列追加
	_data->_wstr[_data->_allocated - 1] = L'\0';

	return TRUE;
}

/*第二パラメータに指定された文字列を_CopyToに書き込む。
 * 確保及び解放を行う。
 */
RETNUM WSTRC_COPY(WSTRC* _CopyTo, const wchar_t* _text){
	if (_text == NULL)
		return FALSE;

	RETNUM is_success = WSTRC_ALLOC(_CopyTo,(Ulong)wcslen(_text)+1);
	if(is_success==TRUE)
		WSTRC_WRITE(_CopyTo,_text,BASICW);

	return is_success;
}

/*_data1と_data2の文字列を結合し_CopyToに挿入する。
 */
RETNUM WSTRC_CONNECT(WSTRC* _CopyTo, const wchar_t* _data1, const wchar_t* _data2){
	if(_data1 == NULL || _data2 == NULL)
		return FALSE;

	WSTRC buf_data1 = WSTRC_Init_Value;
	WSTRC buf_data2 = WSTRC_Init_Value;

	if(FALSE == WSTRC_COPY(&buf_data1,_data1))
		return FALSE;

	if(FALSE == WSTRC_COPY(&buf_data2,_data2)){
		WSTRC_FREE(&buf_data1);
		return FALSE;
	}

	Ulong size = (Ulong)wcslen(_data1) + (Ulong)wcslen(_data2) + 2;
	if(FALSE == WSTRC_ALLOC(_CopyTo,size))
		return FALSE;

	WSTRC_WRITE(_CopyTo,buf_data1._wstr,BASICW);
	WRITE_INFO connect = {buf_data1._allocated-1,RANGE_DEFAULT};
	WSTRC_WRITE(_CopyTo,buf_data2._wstr,connect);

	WSTRC_FREE(&buf_data1);
	WSTRC_FREE(&buf_data2);

	return TRUE;
}
/*文字列を追加する。*/
RETNUM WSTRC_ADD(WSTRC* _data,const wchar_t* _text){
	if(_data->_wstr == NULL)
		WSTRC_COPY(_data,(const wchar_t*)L"");
	return WSTRC_CONNECT(_data,_data->_wstr,_text);
}

/*wchar_t型の文字列をSTRC型の変数に書き込む。
 */
RETNUM TO_STRC(STRC* _data,const wchar_t* _text) {
	STRC_FREE(_data);
	setlocale(0, "");

	size_t _err = 0;
	size_t _buffer = wcslen(_text) + 1;

	if (!STRC_ALLOC(_data, _buffer*sizeof(wchar_t)))return FALSE;

	wcstombs_s(&_err, _data->_str, _data->_allocated, _text, _TRUNCATE);

	return TRUE;
}

/*charの文字列をwchar_t型に変換して書き込む。
 */
RETNUM TO_WSTRC(WSTRC* _wstr,const char* _text) {
	WSTRC_FREE(_wstr);
	setlocale(0, "");

	size_t ret = 0;

	if (!WSTRC_ALLOC(_wstr, strlen(_text)+1))
		return FALSE;
	mbstowcs_s(&ret, _wstr->_wstr, _wstr->_allocated, _text, _TRUNCATE);

	return TRUE;
}

RETNUM (*wequal)(WSTRC*,const wchar_t*) = WSTRC_COPY;
#endif /* UHFC_SANAEWCHAR_H_ */
