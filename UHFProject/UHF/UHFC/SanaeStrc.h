#ifndef SANAESTRC_H
#define SANAESTRC_H


/*INCLUDE*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#define STRC_init      ={NULL,0}
#define STRC_fin(data) STR_FREE(&data)


/*Define Types*/
typedef unsigned int  UINT;
typedef unsigned char MINI;
typedef long long     long64;
typedef unsigned long long ULONG64;

/*Copy range of text*/
typedef struct {
	ULONG64 from;
	ULONG64 to;
}RANGE;

/*MAIN class*/
typedef struct {
	char*    str;     //Store of pointer
	ULONG64  alloced; //Allocated
}STRC;


/*Define Function*/
/*Base Function*/
void STR_FREE (STRC*);
bool ALLOC    (STRC*, ULONG64);
bool ADD      (STRC*, const char*);
bool WRITE    (STRC*, const char*, ULONG64, RANGE);
bool WRITE    (STRC*, char, ULONG64);
bool COPYSTRC    (STRC*, const char*);
bool CONNECTSTRC (STRC*, const char*, const char*);
bool SUBSTRC     (STRC*, STRC*, RANGE);

/*Utility Function*/
bool equal(STRC*, const char*);


/*BaseFunctions*/

/*Free up memory.
* Base Function.
*/
void STR_FREE(STRC* data) {
	free(data->str);
	data->str     = NULL;
	data->alloced = 0;
	return;
}

/*Allocate Memory.
* If success then return true.
* Else then return false.
* Base Function.
* This Function will free of memory.
*/
bool ALLOC(STRC* data,ULONG64 size) {
	if (size==0) {
		*data STRC_init;
		return false;
	}
	STR_FREE(data);

	data->str = (char*)calloc(size, sizeof(char));
	data->alloced = { (data->str == NULL) ? 0 : size };

	return (data->str == NULL) ? false : true;
}

/*Write to STRC type variable.
* Write as much as allocated.
* Base Function.
* This function will not free of memory.
*/
bool WRITE(STRC* data, const char* text, ULONG64 startpoint = 0, RANGE range = {0,0}) {
	if (data->alloced == 0)
		return false;

	range.to = { (range.to == 0) ? strlen(text) : range.to };

	for (ULONG64 i = startpoint, j = range.from; (i < (data->alloced)) && (j <= range.to) && (j < strlen(text)); i++, j++)
		data->str[i] = text[j];

	data->str[data->alloced - 1] = 0;

	return true;
}

/*Write to STRC type variable.
* Write as much as allocated.
* Base Function.
* This function will not free of memory.
*/
bool WRITE(STRC* data, char d, ULONG64 point) {
	if (data->alloced == 0 || point >= data->alloced)
		return false;

	data->str[point] = d;
	data->str[data->alloced - 1] = 0;

	return true;
}

/*Copy String.
* Base Function.
* This function will free of "CopyTo" memory
*/
bool COPYSTRC(STRC* CopyTo, const char* from) {
	if (from == NULL)return false;

	bool is_success = ALLOC(CopyTo, strlen(from) + 1);

	return (is_success == true) && WRITE(CopyTo, from) == true;
}

/*Connect String.
* Base Function
*/
bool CONNECTSTRC(STRC* CopyTo, const char* data1, const char* data2) {
	if(data1==NULL&&data2==NULL){
		return false;
	}
	else if (data1==NULL) {
		if (!COPYSTRC(CopyTo, data2))return false;
		return true;
	}
	else if (data2==NULL) {
		if (!COPYSTRC(CopyTo, data1))return false;
		return true;
	}
		
	STRC data1_buf STRC_init;
	STRC data2_buf STRC_init;

	//1:I’[•¶Žš—p
	ULONG64 size = strlen(data1) + strlen(data2) + 1;

	if (!COPYSTRC(&data1_buf, data1)) return false;
	if (!COPYSTRC(&data2_buf, data2)) return false;

	if (!ALLOC(CopyTo, size))      return false;
	
	if (!WRITE(CopyTo, data1_buf.str))return false;
	if (!WRITE(CopyTo, data2_buf.str,data1_buf.alloced-1)) return false;

	//Free of buf memory
	STR_FREE(&data1_buf);
	STR_FREE(&data2_buf);
	
	return true;
}

/*ADD
* Base Function.
*/
bool ADD(STRC* data,const char* text) {
	if (data->str == NULL)
		return COPYSTRC(data,text);

	if (!CONNECTSTRC(data, data->str, text))
		return false;

	return true;
}

/*SubStr
* Base Function.
*/
bool SUBSTRC(STRC* to, STRC* from, RANGE range) {
	/*Process of buffer.*/
	STRC buf STRC_init;

	if (!COPYSTRC(&buf, from->str)) {
		STRC_fin(buf);
		return false;
	}

	/*Initialization of 'to'*/
	STR_FREE(to);
	
	/*For blank and reserve(1)*/
	MINI blank = 2;

	long64 size = (long64)(range.to - range.from) + (long64)blank;
	if (size < 0)
		return false;

	if (!ALLOC(to, (ULONG64)size))
		return false;

	if (!WRITE(to, buf.str, 0, { range.from,range.to }))
		return false;

	/*Release of buffer.*/
	STRC_fin(buf);
	return true;
}

bool IS_UPPERCASE(char _d) {
	if ('A' <= _d && _d <='Z')
		return true;
	return false;
}

bool IS_LOWERCASE(char _d) {
	if ('a' <= _d && _d <= 'z')
		return true;
	return false;
}


/*Utility Function*/

/*Allocate and write.*/
bool equal(STRC* data,const char* text) {
	if (text==NULL)return false;

	bool is_success = ALLOC(data, strlen(text) + 1);

	return (is_success==true)&&WRITE(data,text)==true;
}

bool is_equal(STRC* data1,STRC* data2) {
	if (strlen(data1->str) != strlen(data2->str)) return false;

	for (ULONG64 i = 0; i < strlen(data1->str);i++) 
		if (data1->str[i] != data2->str[i])return false;

	return true;
}
#endif