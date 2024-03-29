/*
 ============================================================================
 Name        : UHF-SanaeFile
 Author      : Sanae
 Version     : 1.0.3(Beta)
 Copyright   : CopyRight 2022 SanaeProject.
 ============================================================================
 */

#ifndef SANAEFILE_H
#define SANAEFILE_H


#include "UHFC/SanaeFilec.h"
#include "SanaeStr.h"
#include <stdexcept>


typedef char ID;


class file {
private:

	bool  did_in = false;
	FILEC fv;
	/*if mode 0 then throw runtime_error.
	* else if mode 1 then throw range_error.
	*/
	inline void _error(const char* error_text) {
		throw std::exception(error_text);
	}
public:
	file(const char* filename) {
		if (FILEC_IS_EXISTING(filename) == FALSE)
			FILEC_MAKE(filename);

		fv = FILEC_Init_Value;
		FILEC_START(&fv, filename);
		did_in = true;
	}
	file() {
		fv = FILEC_Init_Value;
	}
	file(const file& data) {
		STRC_COPY(&fv.filename,data.fv.filename._str);
		fv = data.fv;

		did_in = true;
	}
	~file() {
		FILEC_FINISH(&fv);
	}

	file& operator =(const char* filename) {
		if (FILEC_IS_EXISTING(filename) == FALSE)
			FILEC_MAKE(filename);

		STRC_FREE(&fv.filename);

		fv = FILEC_Init_Value;
		if (FILEC_START(&fv, filename) == FALSE)
			_error("Open Error");

		did_in = true;

		return *this;
	}

	file& write(const char* text) {
		if (!did_in)
			_error("Filename not entered.");

		if (FILEC_WRITE(&fv, text, "w")==FALSE)
			_error("WriteError");

		return *this;
	}
	file& add(const char* text) {
		if (!did_in)
			_error("Filename not entered.");

		if (FILEC_WRITE(&fv, text, "a")==FALSE)
			_error("AddError");

		return *this;
	}
	str read() {
		if (!did_in)
			_error("Filename not entered.");

		STRC to = STRC_Init_Value;
		if (FILEC_READ(&fv, &to)==FALSE)
			_error("ReadError");

		str ret = to._str;
		return ret;
	}
};
#endif