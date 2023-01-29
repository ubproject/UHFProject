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
	FILEC fv;
	/*if mode 0 then throw runtime_error.
	* else if mode 1 then throw range_error.
	*/
	inline void error(const char* error_text, ID mode = 0) {
		switch (mode) {
		case 0:
			throw std::runtime_error(error_text);
			break;
		case 1:
			throw std::range_error(error_text);
			break;
		}
	}
public:
	file(const char* filename) {
		fv = FILEC_Init_Value;
		FILEC_START(&fv, filename);
	}
	~file() {
		FILEC_FINISH(&fv);
	}
	file& write(const char* text) {
		if (!FILEC_WRITE(&fv, text, "w"))
			error("WriteError");
		return *this;
	}
	file& add(const char* text) {
		FILEC_ADD(&fv, text);
		return *this;
	}
	file& read(STRC* to) {
		FILEC_READ(&fv, to);
		return *this;
	}

#ifdef SANAESTR_H_
	file& read(str* to) {
		STRC buf = STRC_Init_Value;
		if (!FILEC_READ(&fv, &buf))
			error("ReadError");
		*to = buf._str;
		return *this;
	}
#endif
};
#endif