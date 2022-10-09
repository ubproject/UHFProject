#ifndef SANAESTRC_H
#define SANAESTRC_H


/*INCLUDE*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#define STRC_init      ={NULL,0}
#define STRC_fin(data) SFREE(&data)


/*Define Types*/
typedef unsigned int  UINT;
typedef unsigned char MINI;
typedef long long     long64;


/*Copy range of text*/
typedef struct {
	UINT from;
	UINT to;
}RANGE;

/*MAIN class*/
typedef struct {
	char* str;     //Store of pointer
	UINT  alloced; //Allocated
}STRC;


/*Define Function*/
/*Base Function*/
void SFREE (STRC*);
bool ADD   (STRC*, const char*);
bool ALLOC (STRC*, UINT);
bool WRITE (STRC*, const char*, UINT, RANGE);
bool WRITE (STRC*, char, UINT);
bool COPYSTRC    (STRC*, const char*);
bool CONNECTSTRC (STRC*, const char*, const char*);
bool SUBSTRC     (STRC*, STRC*, RANGE);

/*Utility Function*/
bool equal(STRC*, const char*);


/*BaseFunctions*/

/*Free up memory.
* Base Function.
*/
void SFREE(STRC* data) {
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
bool ALLOC(STRC* data,UINT size) {
	if (size==0) {
		*data STRC_init;
		return false;
	}
	SFREE(data);
	data->str = (char*)calloc(size,sizeof(char));
	data->alloced = { (data->str == NULL) ? 0 : size };
	return (data->str == NULL) ? false : true;
}

/*Write to STRC type variable.
* Write as much as allocated.
* Base Function.
* This function will not free of memory.
*/
bool WRITE(STRC* data, const char* text, UINT startpoint = 0, RANGE range = {0,0}) {
	if (data->alloced == 0)
		return false;
	range.to = { (range.to == 0) ? (UINT)strlen(text) : range.to };
	for (UINT i = startpoint, j = range.from; (i < (data->alloced)) && (j <= range.to) && (j < strlen(text)); i++, j++)
		data->str[i] = text[j];
	data->str[data->alloced - 1] = 0;
	return true;
}

bool WRITE(STRC* data, char d, UINT point) {
	if (data->alloced == 0 || point >= data->alloced)
		return false;
	data->str[point] = d;
	data->str[data->alloced - 1] = 0;
	return true;
}
/*Copy String.
* Base Function.
*/
bool COPYSTRC(STRC* CopyTo, const char* from) {
	if (!ALLOC(CopyTo, (UINT)strlen(from) + 1))return false;
	if (!WRITE(CopyTo, from))return false;
	return  true;
}

/*Connect String.
* Base Function
*/
bool CONNECTSTRC(STRC* CopyTo, const char* data1, const char* data2) {
	if(data1==NULL&&data2==NULL){
		return false;
	}
	else if (data1==NULL) {
		if (!equal(CopyTo, data2))return false;
		return true;
	}
	else if (data2==NULL) {
		if (!equal(CopyTo, data1))return false;
		return true;
	}
		
	STRC data1_buf STRC_init;
	STRC data2_buf STRC_init;
	
	//1:I’[•¶Žš—p
	UINT size = (UINT)strlen(data1) + (UINT)strlen(data2) + 1;

	if (!equal(&data1_buf, data1)) return false;
	if (!equal(&data2_buf, data2)) return false;

	if (!ALLOC(CopyTo, size))      return false;
	
	if (!WRITE(CopyTo, data1_buf.str))return false;
	if (!WRITE(CopyTo, data2_buf.str,data1_buf.alloced-1)) return false;

	//Free of buf memory
	SFREE(&data1_buf);
	SFREE(&data2_buf);
	
	return true;
}

/*ADD
* Base Function.
*/
bool ADD(STRC* data,const char* text) {
	if (data->str == NULL) {
		return equal(data,text);
	}
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

	if (!equal(&buf, from->str)) {
		STRC_fin(buf);
		return false;
	}

	/*Initialization of 'to'*/
	SFREE(to);
	
	/*For blank and reserve(1)*/
	MINI blank = 2;

	long64 size = (long64)(range.to - range.from) + (long64)blank;
	if (size < 0)
		return false;
	if (!ALLOC(to, (UINT)size))
		return false;
	if (!WRITE(to, buf.str, 0, { range.from,range.to }))
		return false;

	/*Release of buffer.*/
	STRC_fin(buf);
	return true;
}


/*Utility Function*/

/*Allocate and write.*/
bool equal(STRC* data,const char* text) {
	if (text==NULL)return false;
	bool is_success = ALLOC(data, (UINT)strlen(text) + 1);
	return (is_success==true)&&WRITE(data,text)==true;
}
bool is_equal(STRC* data1,STRC* data2) {
	if (strlen(data1->str) != strlen(data2->str)) return false;
	for (UINT i = 0; i < strlen(data1->str);i++) 
		if (data1->str[i] != data2->str[i])return false;
	return true;
}
#endif