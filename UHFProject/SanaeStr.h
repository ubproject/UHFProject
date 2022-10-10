#ifndef SANAESTR_H
#define SANAESTR_H


/*INCLUDE*/
#include "SanaeStrc.h"
#include "SanaeWchar.h"
#include <stdexcept>
#include <vector>


typedef char ID;


class str {
private:


	/*char*/
	STRC STR;
	STRC view_buf;
	
	/*wchar_t*/
	WSTRC WSTR;


	void setnull(){
		STR      STRC_init;
		view_buf STRC_init;
		WSTR     WSTRC_init;
	}

	/*if mode 0 then throw runtime_error.
	* else if mode 1 then throw range_error.
	*/
	inline void error(const char* error_text,ID mode=0) {
		switch (mode) {
		case 0:
			throw std::runtime_error(error_text);
			break;
		case 1:
			throw std::range_error  (error_text);
			break;
		default:
			{
			STRC error STRC_init;
			equal(&error, "Injustice of mode. ErrorMessage:");
			CONNECTSTRC(&error, error.str, error_text);
			throw std::logic_error(error.str);
			STRC_fin(error);
			}
			break;
		}
	}

	/*debug*/
	inline void view_info(UINT ID=0) {
		printf("\ninfo(%u):\nSTR=(STRC)%s,(ALLOCATE)%u\nview_buf=(STRC)%s,(ALLOCATE)%u\n",ID,STR.str,STR.alloced,view_buf.str,view_buf.alloced);
	}
public:


	/*Constructor*/
	str() {
		setnull();
	}
	str(const char* text) {
		setnull();
		if (!equal(&STR, text))
			error("Failed to process of STRC type.(Constructor)", 1);
	}
	str(const wchar_t* wtext) {
		setnull();
		if (!to_char(&STR, wtext))
			error("Failed to process of WSTRC type.(Constructor)",1);
	}
	//CopyConstructor
	str(const str& text) {
		setnull();
		if (!equal(&this->STR, text.STR.str))
			error("Failed to process of STRC type.(CopyConstructor)");
	}


	/*Destructor*/
	~str() {
		/*CHAR*/
		STRC_fin(STR);
		STRC_fin(view_buf);
		/*WCHAR_T*/
		WSTRC_fin(WSTR);
	}


	/*Operator*/
	char& operator [](UINT location) {
		if (STR.alloced<=location)
			error("Failed to access to mem.Too many num to access.");
		return *(STR.str + location);
	}
	str& operator =(const char* text) {
		if (!equal(&STR, text))
			error("Failed to process of STRC type.(equal)");
		return *this;
	}
	str& operator =(const str& text) {
		if (!equal(&this->STR, text.STR.str))
			error("Failed to process of STRC type.(equal)");
		return *this;
	}
	str operator +=(const char* text) {
		return add(text);
	}
	str operator +=(const str& text) {
		return add(text);
	}


	/*if*/
	bool operator ==(const str& text) {
		return is_equal((STRC*)&text.STR, &this->STR);
	}
	bool operator !=(const str& text) {
		return !is_equal((STRC*)&text.STR, &this->STR);
	}


	/*Function*/
	//Add Text.
	str& add(const char* text) {
		if (!ADD(&this->STR, text))
			return *this;
		return *this;
	}
	str& add(const wchar_t* wtext) {
		if (!ADD(&this->WSTR, wtext))
			return *this;
		return *this;
	}
	str& add(const str& text) {
		return add(text.STR.str);
	}
	//Get to Text.
	const char* c_str(RANGE range = {0,0}) {
		range.to = range.to == 0 ? (UINT)strlen(STR.str) : range.to;
		if (!SUBSTRC(&view_buf,&STR,range))
			error("Failed to process of STRC type.(c_str)");
		return view_buf.str;
	}
	//Get to Text
	const wchar_t* c_wstr() {
		if (!to_wchar(&WSTR,STR.str))
			error("Failed to process of STRC type.(c_wstr)");
		return WSTR.wstr;
	}
	//Get to allocate size.
	UINT size() {
		return STR.alloced * sizeof(char);
	}
	//Search specified char
	long64 find(char data,UINT through=0) {
		for (long64 i = 0; i < (long64)strlen(STR.str); i++) {
			if (*(STR.str + i) == data) {
				if (through == 0)
					return i;
				if (through != 0)
					through -= 1;
			}
		}
		return -1;
	}
	long64 find(const char* data,UINT through=0) {
		for (long64 i = 0;;i++) {
			for (long64 j = 0, point = this->find(*(data + 0), (UINT)i); j < (long64)strlen(data); j++) {
				if (point == -1) 
					return -1;
				if (*(STR.str + point + j) != *(data + j))
					break;
				//Then process of through.
				if (j == (strlen(data) - 1)) {	
					if (through == 0)
						return point;
					if (through != 0)
						through -= 1;
				}
			}
		}
	}
	UINT count(char data) {
		UINT retdata = 0;
		for (UINT i = 0; i < STR.alloced;i++) if(STR.str[i] == data)retdata += 1;
		return retdata;
	}
	UINT count(const char* data) {
		UINT retdata = 0;
		UINT datalen = (UINT)strlen(data);
		for (UINT i = 0; i < STR.alloced;i++) {
			if (STR.str[i]==data[0]) {
				for (UINT j = 0; j < datalen;j++) {
					if (STR.str[i + j] != data[j])break;
					if (j==(datalen-1))retdata += 1;
				}
			}
		}
		return retdata;
	}
	/*最前列からtopointまで削除します。*/
	str& erase_front(UINT topoint) {
		SUBSTRC(&STR, &STR, {topoint+1,(UINT)strlen(STR.str)+1});
		return *this;
	}
	/*最後尾からtopointまで削除します。*/
	str& erase_back(UINT topoint) {
		SUBSTRC(&STR, &STR, { 0,topoint-1 });
		return *this;
	}
	str& erase(RANGE range = {0,0}) {
		range.to = range.to == 0 ? this->STR.alloced - 1 : range.to;

		STRC buf_front STRC_init;
		STRC buf_back  STRC_init;

		if (range.from == 0) {
			COPYSTRC(&buf_front, "");
		}else {
			SUBSTRC(&buf_front, &STR, { 0,range.from });
		}

		if (range.to + 1 == this->STR.alloced) {
			COPYSTRC(&buf_back, "");
		}else {
			SUBSTRC(&buf_back, &STR, { range.to+1,this->STR.alloced});
		}

		CONNECTSTRC(&STR,buf_front.str,buf_back.str);

		STRC_fin(buf_front);
		STRC_fin(buf_back);

		return *this;
	}

	str& replace(const char* from,const char* to,UINT through=0) {
		//find point and is existing
		UINT found = (UINT)this->find(from,through);
		if (found == -1) return *this;
		
		STRC buf_front STRC_init;
		STRC buf_back  STRC_init;

		STRC buffer    STRC_init;

		if (found != 0) {
			SUBSTRC(&buf_front, &this->STR, { 0,(UINT)found });
		}
		SUBSTRC(&buf_back , &this->STR, {(UINT)found+(UINT)strlen(from),this->STR.alloced-1});

		CONNECTSTRC(&buffer,buf_front.str,to);
		CONNECTSTRC(&STR,buffer.str,buf_back.str);

		STRC_fin(buf_front);
		STRC_fin(buf_back);
		STRC_fin(buffer);
		
		return *this;
	}
	str& division(std::vector<str>* to,char divchr) {
		STRC buf_STR STRC_init;
		equal(&buf_STR,this->STR.str);

		long64 i = 0;
		while ((i = this->find(divchr)) !=-1) {
			STRC buf STRC_init;
			SUBSTRC(&buf, &STR, {0,(UINT)i-1});
			this->erase_front((UINT)i);
			str bufstr = buf.str;
			to->push_back(bufstr);
			STRC_fin(buf);
		}
		str buf = this->STR.str;
		to->push_back(buf);

		equal(&this->STR,buf_STR.str);
		STRC_fin(buf_STR);

		return *this;
	}
#ifdef SANAEMATH_H
	str operator +=(UINT data) {
		return add(data);
	}
	str& add(UINT data) {
		/*dを配列へ変換しておく*/
		NUMS bufd = {NULL,0};
		if (!to_array(&bufd, data))
			return *this;
		/*charへ変換*/
		for (UINT i = 0; i < bufd.len;i++)
			bufd.data[i] += '0';
		
		STRC buf STRC_init;

		if (!equal(&buf, STR.str)) {
			SFREE(&bufd);
			return *this;
		}

		STRC_fin(STR);

		if (!ALLOC(&STR, buf.alloced + bufd.len)) {
			SFREE(&bufd);
			return *this;
		}

		WRITE(&STR,buf.str);

		for (UINT i = (bufd.len-1),j=buf.alloced-1; i != 0; i--,j++) {
			WRITE(&STR, (char)bufd.data[i], j);
			if ((i-1)==0)WRITE(&STR, (char)bufd.data[0], (j+1));
		}

		SFREE(&bufd);
		SFREE(&buf);
		return *this;
	}


#endif
};


#endif