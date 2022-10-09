#ifndef SANAEFILEC_H_
#define SANAEFILEC_H_


/*INCLUDE*/
#include <stdio.h>
#include "SanaeStrc.h"


/*Define types*/
typedef unsigned int uint;
typedef struct {
	FILE* filepointer;
	bool is_exist;
	STRC name;
	STRC str;
}FILEC;


#define FILEC_init ={NULL,false,{NULL,0},{NULL,0}};
#define FILEC_fin(data) fileclose(&data)


/*Define functions*/
bool filemake (FILEC*, const char*);
bool fileopen (FILEC*, const char*);
void fileclose(FILEC*);
bool filewrite(FILEC*, const char*, const char*);
bool fileadd  (FILEC*, const char*);
bool fileread (FILEC*);


bool filemake(FILEC* data, const char* filename) {
	fopen_s(&data->filepointer, filename, "w");
	if (data->filepointer == NULL) {
		return data->is_exist = false;
	}
	fclose(data->filepointer);
	return data->is_exist = true;
}
bool fileopen(FILEC* data, const char* filename) {
	equal(&data->name, filename);
	fopen_s(&data->filepointer, filename, "r+");
	if (data->filepointer == NULL) {
		return filemake(data,filename);
	}
	fclose(data->filepointer);
	return data->is_exist = true;
}

void fileclose(FILEC* data) {
	STRC_fin(data->str);
	STRC_fin(data->name);
	data->is_exist = false;
	return;
}

bool filewrite(FILEC* data, const char* text, const char* mode = "w") {
	if (!data->is_exist)return false;
	fopen_s(&data->filepointer, data->name.str, mode);
	if (data->filepointer == NULL) {
		data->is_exist = false;
		return false;
	}
	fprintf(data->filepointer, text);
	fclose(data->filepointer);
	fopen_s(&data->filepointer, data->name.str, "r+");
	if (data->filepointer == NULL) {
		data->is_exist = false;
		return false;
	}
	fclose(data->filepointer);
	return true;
}

bool fileadd(FILEC* data, const char* text) {
	return filewrite(data, text, "a");
}

bool fileread(FILEC* data) {
	STRC_fin(data->str);
	if (!data->is_exist)return false;
	fopen_s(&data->filepointer, data->name.str, "r+");
	if (data->filepointer == NULL) {
		data->is_exist = false;
		return false;
	}
	if (!data->is_exist)return false;
	while (1) {
		char* buf = (char*)calloc(256, sizeof(char));
		if (buf == NULL)return false;
		for (uint i = 0; i < 256; i++) {
			if ((buf[i] = getc(data->filepointer)) == EOF) {
				buf[i] = 0;
				ADD(&data->str, buf);
				*(data->str.str + (strlen(data->str.str) - 1)) = 0;
				free(buf);
				fclose(data->filepointer);
				return true;
			}
		}
		ADD(&data->str, buf);
		free(buf);
	}
}
#endif /* SANAEFILEC_H_ */