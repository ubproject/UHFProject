/*
 ============================================================================
 Name        : UHF-SanaeStr
 Author      : Sanae
 Version     : 1.0.3(Beta)
 Copyright   : CopyRight 2022 SanaeProject.
 ============================================================================
 */

#ifndef SANAESTR_H_
#define SANAESTR_H_


/*INCLUDE*/
#include <stdexcept>
#include <vector>

#include "UHFC/SanaeStrc.h"
#include "UHFC/SanaeWchar.h"
#include "UHFC/SanaeTypes.h"


/*class*/
class str{
private:
	STRC  _data    = STRC_Init_Value;
	STRC  _view_buf= STRC_Init_Value;
	WSTRC _wdata   = WSTRC_Init_Value;

	void error(int num,const char* _error_text){
		switch(num){
		case 1:
			throw std::range_error  (_error_text);
		case 2:
			throw std::runtime_error(_error_text);
		case 3:
			throw std::out_of_range (_error_text);
		}
	}

	void num_to_str(STRC* _data,Ulong _num) {
		STRC_FREE(_data);

		num_array _d_buf = { NULL,0 };
		to_array(&_d_buf, _num);

		if (_d_buf._data == NULL)
			error(2, "Failed to allocate.");

		Ulong digit_buf = get_digit(_num);
		_data->_str = (char*)calloc(digit_buf + 1, sizeof(char));

		if (_data->_str == NULL) {
			MATH_FREE(&_d_buf);
			error(2, "Failed to allocate.");
		}

		_data->_allocated = digit_buf + 1;

		for (Ulong i = 0, j = (digit_buf - 1); i < _data->_allocated && j >= 0; i++, j--)
			this->_data._str[i] = ('0' + (MINI)_d_buf._data[j]);

		//終端文字列設定
		this->_data._str[this->_data._allocated - 1] = 0;
		MATH_FREE(&_d_buf);

		return;
	}
public:
	//constructor
	str(){}
	str(const char* _text){
		if(FALSE == STRC_COPY(&_data,_text))
			error(2,"Failed to Copy of _text.");
	}
	str(const wchar_t* _wtext){
		if(FALSE == TO_STRC(&_data,_wtext))
			error(2,"Failed to convert.");
	}
	str(Ulong _num) {
		num_to_str(&this->_data,_num);
	}
	str(const str& _text){
		if(FALSE == STRC_COPY(&_data,_text._data._str))
			error(2,"Failed to copy of _text.");
	}
	//Destructor
	~str(){
		STRC_FREE (&_data);
		STRC_FREE (&_view_buf);
		WSTRC_FREE(&_wdata);
	}

	//operator
	char& operator [](Ulong location) {
		if (this->_data._allocated<=location)
			error(3,"Failed to access to mem.Too many num to access.");

		return *(this->_data._str + location);
	}
	str& operator =(const char* _text){
		if(FALSE == STRC_COPY(&this->_data,_text))
			error(2,"Failed to copy of _text");

		return *this;
	}
	str& operator =(Ulong _num) {
		num_to_str(&this->_data, _num);

		return *this;
	}
	str& operator =(const str& _text){
		if(FALSE == STRC_COPY(&this->_data,_text._data._str))
			error(2,"Failed to copy of _text");

		return *this;
	}
	str& operator +=(const char* _text) {
		if(FALSE == STRC_ADD(&this->_data,_text))
			error(2,"Failed to add.");
		return *this;
	}
	str& operator +=(Ulong _data){
		this->add(_data);
		return *this;
	}
	str& operator +=(const str& _text) {
		if(FALSE == STRC_ADD(&this->_data,_text._data._str))
			error(2,"Failed to add.");
		return *this;
	}

	/*if*/
	bool operator ==(const str& text) {
		return IS_EQUAL(text._data._str, this->_data._str);
	}
	bool operator !=(const str& text) {
		return !IS_EQUAL(text._data._str, this->_data._str);
	}

	//function
	str& add(const char* text) {
		STRC_ADD(&this->_data, text);

		return *this;
	}
	str& add(const wchar_t* wtext) {
		STRC _buf = STRC_Init_Value;
		if(FALSE == TO_STRC(&_buf,wtext))
			error(2,"Failed to convert.");

		if(STRC_ADD(&this->_data,_buf._str))
			error(2,"Failed to add.");

		STRC_FREE(&_buf);
		return *this;
	}
	str& add(Ulong _num) {
		STRC _buf = STRC_Init_Value;
		num_to_str(&_buf, _num);

		if (STRC_ADD(&this->_data, _buf._str) == FALSE) {
			STRC_FREE(&_buf);
			error(2, "Failed to connect.");
		}
		STRC_FREE(&_buf);

		return *this;
	}
	str& add(const str& text) {
		return add(text._data._str);
	}
	//Get to Text.
	const char* c_str(RANGE range = RANGE_DEFAULT) {
		bool is_default = range.front > range.back;
		if (is_default) {
			range.back  = strlen(this->_data._str);
			range.front = 0;
		}

		if (STRC_SUB(&_view_buf,_data._str,range)==FALSE){
			error(2,"Failed to process of STRC type.(c_str)");
		}

		return _view_buf._str;
	}
	//Get to Text
	const wchar_t* c_wstr() {
		if (FALSE == TO_WSTRC(&_wdata,(const char*)_data._str))
			error(2,"Failed to process of STRC type.(c_wstr)");

		return _wdata._wstr;
	}
	Slong find(char _c,Ulong _through=0){
		Ulong ret = STRC_FINDC(&_data,_c,_through);

		if(STRC_NOTFOUND_FLAG == TRUE && ret == 0)
			return -1;

		return ret;
	}
	Slong find(const char* _text,Ulong _through = 0){
		Ulong ret = STRC_FIND(&_data,_text,_through);

		if(STRC_NOTFOUND_FLAG == TRUE)
			return -1;

		return ret;
	}
	/*最前列からtopointまで削除します。*/
	str& erase_front(Ulong topoint) {
		STRC_SUB(&_data, _data._str, {topoint+1,strlen(_data._str)+1});
		//ret
		return *this;
	}
	/*最後尾からtopointまで削除します。*/
	str& erase_back(Ulong topoint) {
		STRC_SUB(&_data, _data._str, { 0,topoint-1 });
		//ret
		return *this;
	}
	//fromのほうがtoより大きい場合すべて削除します。(初期値)
	str& erase(RANGE range = {1,0}) {
		//PreProcessing
		bool is_default = range.front > range.back;
		if (is_default)
			range = {0,this->_data._allocated-1};

		STRC buf_front = STRC_Init_Value;
		STRC buf_back  = STRC_Init_Value;

		//MainProcess
		if (range.front == 0) {
			STRC_COPY(&buf_front, "");
		}else {
			STRC_SUB(&buf_front, _data._str, { 0,range.front });
		}

		if (range.back + 1 == this->_data._allocated) {
			STRC_COPY(&buf_back, "");
		}else {
			STRC_SUB(&buf_back, _data._str, { range.back+1,this->_data._allocated});
		}

		//FinallyProcess
		STRC_CONNECT(&_data,buf_front._str,buf_back._str);

		//Post-Processing
		STRC_FREE(&buf_front);
		STRC_FREE(&buf_back);

		return *this;
	}

	str& replace(const char* _from,const char* _to,Ulong _through=0){
		if(FALSE == STRC_REPLACE(&_data,_from,_to,_through))
			error(2,"Failed to Replace.");

		return *this;
	}

	str& division(std::vector<str>* to, char divchr) {
			//PreProcessing
			STRC buf_STR = STRC_Init_Value;
			STRC_COPY(&buf_STR, this->_data._str);

			Slong i = 0;
			while ((i = this->find(divchr)) != -1) {
				STRC buf = STRC_Init_Value;

				STRC_SUB(&buf, (const char*)this->_data._str, { 0,(Ulong)i - 1 });
				this->erase_front(i);
				str bufstr = (const char*)buf._str;
				to->push_back(bufstr);

				STRC_FREE(&buf);
			}

			str buf = this->_data._str;
			to->push_back(buf);

			STRC_COPY(&this->_data, buf_STR._str);
			STRC_FREE(&buf_STR);

			return *this;
	}

	Ulong to_ulong(RANGE _range) {
		if (_range.back>=this->_data._allocated)
			error(3, "Failed to access to mem.Too many num to access.");

		if (_range.front > _range.back) {
			_range.front = 0;
			_range.back  = this->_data._allocated - 1;
		}

		Ulong retnum = 0;
		Ulong j = 1;

		for (Ulong i = _range.back; (i + 1) != _range.front; i--) {
			char buf = this->_data._str[i];

			//数値の以外の場合無視する。
			if ('0' <= buf && buf <= '9') {
				retnum += ((Ulong)buf - (Ulong)'0') * j;
				j *= 10;
			}
		}
		return retnum;
	}
};
#endif /* SANAESTR_H_ */
