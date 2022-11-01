#ifndef SANAEFILE_H
#define SANAEFILE_H


#include "UHFC/SanaeFilec.h"
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
		fv FILEC_init;
		fileopen(&fv,filename);
	}
	~file() {
		FILEC_fin(fv);
	}
	file& write(const char* text) {
		if (!filewrite(&fv, text))
			error("WriteError");
		return *this;
	}
	file& add(const char* text) {
		fileadd(&fv, text);
		return *this;
	}
	file& read(STRC* to) {
		fileread(&fv);
		equal(to,fv.str.str);
		return *this;
	}
#ifdef SANAESTR_H
	file& read(str* to) {
		if (!fileread(&fv))
			error("ReadError");
		*to = fv.str.str;
		return *this;
	}
#endif
};
#endif