#ifndef SANAEWCHAR_H
#define SANAEWCHAR_H


/*INCLUDE*/
#include "SanaeStrc.h"
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>


#define WSTRC_init      ={NULL,0}
#define WSTRC_fin(data) SFREE(&data)


/*Define types*/
typedef struct {
	wchar_t* wstr;
	UINT     alloced;
}WSTRC;
typedef unsigned int UINT;


/*Define Functions*/
/*Base*/
void SFREE(WSTRC*);
bool ALLOC(WSTRC*, UINT);
bool ADD  (WSTRC*, const wchar_t*);
bool WRITE(WSTRC*, const wchar_t*, UINT, RANGE);
bool CONNECTSTRC(WSTRC*, const wchar_t*, const wchar_t*);

/*Utility*/
bool to_char (STRC* , const wchar_t*);
bool to_wchar(WSTRC*, const char*);
bool wequal  (WSTRC*, const wchar_t*);


/*BaseFunctions*/

/*Free up memory.
* Base Function.
*/
void SFREE(WSTRC* data) {
	free(data->wstr);
	data->alloced = 0;
}

/*Allocate Memory.
* If success then return true.
* Else then return false.
* Base Function.
* This Function will free of memory.
*/
bool ALLOC(WSTRC* data, UINT count){
	if (count == 0) { count += 1; }
	SFREE(data);
	data->wstr = (wchar_t*)calloc(count, sizeof(wchar_t));
	data->alloced = data->wstr == NULL ? 0 : count;
	return data->alloced == 0 ? false : true;
}

/*Write to WSTRC type variable.
* Write as much as allocated.
* Base Function.
* This function will not free of memory.
*/
bool WRITE(WSTRC* data, const wchar_t* text, UINT startpoint = 0, RANGE range = { 0,0 }) {
	if (data->alloced == 0)
		return false;
	range.to = { (range.to == 0) ? (UINT)wcslen(text) : range.to };
	for (UINT i = startpoint, j = range.from; (i < (data->alloced)) && (j <= range.to) && (j < wcslen(text)); i++, j++)
		data->wstr[i] = text[j];
	data->wstr[data->alloced - 1] = 0;
	return true;
}

/*Connect String.
* Base Function
*/
bool CONNECTSTRC(WSTRC* CopyTo, const wchar_t* data1, const wchar_t* data2) {
	WSTRC data1_buf STRC_init;
	WSTRC data2_buf STRC_init;

	//1:I’[•¶Žš—p
	UINT size = (UINT)wcslen(data1) + (UINT)wcslen(data2) + 1;
	if (!wequal(&data1_buf, data1)) return false;
	if (!wequal(&data2_buf, data2)) return false;

	if (!ALLOC(CopyTo, size))      return false;

	if (!WRITE(CopyTo, data1_buf.wstr))return false;
	if (!WRITE(CopyTo, data2_buf.wstr, data1_buf.alloced - 1)) return false;

	//Free of buf memory
	SFREE(&data1_buf);
	SFREE(&data2_buf);

	return true;
}

/*ADD
* Base Function.
*/
bool ADD(WSTRC* wstr, const wchar_t* wtext) {
	if (!CONNECTSTRC(wstr, wstr->wstr, wtext))
		return false;
	return true;
}


/*Utility Functions*/

/*Convert to char* type from wchar_t* type
* Utility Function.
*/
bool to_char(STRC* str,const wchar_t *text) {
	STRC_fin(*str);
	setlocale(LC_ALL, "");

	size_t err = 0;
	size_t buffer = wcslen(text) + 1;

	if (!ALLOC(str, buffer*sizeof(wchar_t)))return false;

	wcstombs_s(&err, str->str, str->alloced, text, _TRUNCATE);
	return true;
}

/*Convert to wchar_t* type from char* type.
* Utility Function.
*/
bool to_wchar(WSTRC* wstr,const char* text) {
	WSTRC_fin(*wstr);
	setlocale(LC_ALL, "");

	size_t ret = 0;
	unsigned long long num = sizeof(wchar_t);

	if (!ALLOC(wstr, (UINT)strlen(text)+1))return false;

	mbstowcs_s(&ret, wstr->wstr, wstr->alloced, text, _TRUNCATE);
	return true;
}

/*Allocate and write.*/
bool wequal(WSTRC* data, const wchar_t* text) {
	bool is_success = ALLOC(data, (UINT)wcslen(text) + 1);
	return (is_success == true) && WRITE(data, text) == true;
}
#endif