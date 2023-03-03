/*
 ============================================================================
 Name        : UHFC-Filec-C
 Author      : Sanae
 Version     : 1.0.3(Beta)
 Copyright   : CopyRight 2022 SanaeProject.
 ============================================================================
 */

#ifndef UHFC_SANAEFILEC_H_
#define UHFC_SANAEFILEC_H_


/*INCLUDE*/
#include <stdio.h>

#include "SanaeTypes.h"
#include "SanaeStrc.h"


/*Define Functions*/
void   FILEC_FINISH     (FILEC*      _data);
void   FILEC_MAKE       (const char* _filename);
RETNUM FILEC_IS_EXISTING(const char* _filename);
RETNUM FILEC_START      (FILEC*      _data    , const char* _filename);
RETNUM FILEC_READ       (FILEC*      _data    , STRC*       _CopyTo);
RETNUM FILEC_WRITE      (FILEC*      _data    , const char* _text    , const char* _mode);


/*Functions*/
/*指定されたファイルがあるかどうか判定します。
 */
RETNUM FILEC_IS_EXISTING(const char* _filename){
	FILE* _data = NULL;
	fopen_s(&_data,_filename,"r");
		
	if(_data == NULL)
		return FALSE;

	fclose(_data);
	return TRUE;
}

/*指定された名前のファイルをモード"w"で開きます。
 */
void FILEC_MAKE(const char* _filename){
	FILE* _data = NULL;
	
	fopen_s(&_data,_filename,"w");
	if (_data == NULL)
		return;

	fclose(_data);

	return;
}

/*_dataにファイル名をコピーします。
 * 一番最初にこの関数を設定してください。
 */
RETNUM FILEC_START(FILEC* _data,const char* _filename){
	if(STRC_COPY(&_data->filename,_filename) == FALSE){
		fclose(_data->file_pointer);
		return FALSE;
	}
	return TRUE;
}

/*FILEC.filenameのメモリを解放します。
 */
void FILEC_FINISH(FILEC* _data){
	STRC_FREE(&_data->filename);
	return;
}

/*文字列を指定されたファイルに書き込みます。
 * 第一引数にはFILEC_START関数でファイル名をコピーした変数を入力してください。
 * 第三引数には"w"または"a"を入力してください。
 */
RETNUM FILEC_WRITE(FILEC* _data,const char* _text,const char* _mode){
	if(FILEC_IS_EXISTING(_data->filename._str) == FALSE)
		return FALSE;

	fopen_s(&_data->file_pointer,_data->filename._str,_mode);
	if (_data->file_pointer == NULL)
		return FALSE;

	fprintf(_data->file_pointer,_text);
	fclose(_data->file_pointer);

	return TRUE;
}

/*ファイルの内容を読み取ります。
 */
RETNUM FILEC_READ(FILEC* _data,STRC* _CopyTo){
	Ulong buf_size = 256;

	if(FILEC_IS_EXISTING(_data->filename._str) == FALSE)
			return FALSE;

	fopen_s(&_data->file_pointer,_data->filename._str,"r+");

	while(TRUE){
		char* buf = (char*)calloc(buf_size,sizeof(char));

		if(buf==NULL){
			fclose(_data->file_pointer);
			return FALSE;
		}
		for(Ulong i = 0;i<buf_size;i++){
			if((buf[i] = getc(_data->file_pointer)) == EOF){
				buf[i] = 0;
				STRC_ADD(_CopyTo,buf);
				free(buf);
				fclose(_data->file_pointer);

				return FALSE;
			}
		}

	}
}
#endif /* UHFC_SANAEFILEC_H_ */
