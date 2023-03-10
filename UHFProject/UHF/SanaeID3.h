/*
 ============================================================================
 Name        : UHF-SanaeID3.h
 Author      : Sanae
 Version     : 1.0.3(Beta)
 Copyright   : CopyRight 2022 SanaeProject.
 ============================================================================
 */

#ifndef SANAEID3_H
#define SANAEID3_H


/*INCLUDE*/
#include <vector>
#include <stdexcept>

#include "UHFC/SanaeTypes.h"
#include "SanaeStr.h"
#include "SanaeFile.h"
#include "SanaeStatistics.h"
#include "UHFC/SanaeMathc.h"
#include "UHFC/SanaeUtilc.h"


typedef struct {
	std::vector<str> _parameter;
	str              _classification;
}DATAS_ID3;

typedef S_PAIR<DATAS_ID3,std::vector<DATAS_ID3>> IN_ID3;
typedef std::vector<DATAS_ID3>                   IN_ID3_NoTitle;


class ID3 {
private:
	bool                   _readonly = false;
	DATAS_ID3              _title;
	std::vector<DATAS_ID3> _main;
	std::vector<str>       _tree;

	void _error(int    , const char*);
	void _view (IN_ID3&, const char*);

	template<typename Tb> Ulong _count      (std::vector<Tb>*, Tb);
	template<typename Tb> bool  _is_existing(std::vector<Tb>*, Tb);
	
	std::vector<str>    _get_kinds      (std::vector<str>*);//�w�肳�ꂽ�z����̃_�u�肪�Ȃ��悤�ɏo�͂��܂��B
	Ulong               _get_kinds_count(std::vector<str>*);//��ސ���Ԃ��܂��B
	std::vector<str>    _get_parameters (std::vector<DATAS_ID3>*, Ulong);//�w�肳�ꂽ�z����擾���܂��B
	std::vector<str>    _get_class      (std::vector<DATAS_ID3>*);       //���ނ��擾���܂��B
	std::vector<str>    _get_byname     (std::vector<DATAS_ID3>*, str, DATAS_ID3*);//���O����z����󂯎��܂��B

	double _get_entropy                 (std::vector<str>*);                    //���Ϗ��ʂ����߂܂��B
	double _get_expected                (std::vector<str>* , std::vector<str>*);//�w�肳�ꂽ�ӏ��̊��Ғl�����߂܂�
	Ulong  _get_select                  (IN_ID3_NoTitle*);                      //�n���ꂽ�p�����[�^�̒��łǂꂪ�œK���ǂ����Ԃ��܂��B
	
	IN_ID3_NoTitle   _get_choice        (IN_ID3_NoTitle*, Ulong, str);//�n���ꂽ�f�[�^����Y��������̂̂ݐ؂���܂��B(��j��)
	std::vector<str> _quarry            (IN_ID3*        , str);       //����؂�Ԃ��܂��B
public:
	ID3(IN_ID3        );//�����ǂݍ���
	ID3(IN_ID3_NoTitle);//...
	ID3(const ID3&    );//�ǂݍ��ݐ�p
	ID3();              //...

	ID3& add  (DATAS_ID3             );//�f�[�^��ǉ�
	ID3& add  (std::vector<DATAS_ID3>);//...
	
	ID3& write(const char*);//������������؂��t�@�C���֏������݂܂��B
	ID3& read (const char*);//�������܂ꂽ����؂�ǂݍ��݂܂��B

	ID3& fit  ();                //����؂𐶐����܂��B 
	str  get  (std::vector<str>);//�ǂݍ��܂ꂽ����؂����Ƃɓ��͂��ꂽ�f�[�^�ɑΉ����镪�ނ�Ԃ��܂��B

	ID3& view (const char*);//�f�[�^��\�����܂��B
	ID3& view_tree();       //������������؂�\�����܂��B
};


/*private*/
//�G���[�o��
void ID3::_error(int num , const char* _error_text   ) {
	switch (num) {
	case 0:
		throw std::exception(_error_text);
	case 1:
		throw std::range_error(_error_text);
	case 2:
		throw std::runtime_error(_error_text);
	case 3:
		throw std::out_of_range(_error_text);
	}
}
//�n���ꂽ�f�[�^�����ׂĕ\�����܂��B
void ID3::_view (IN_ID3& t, const char* text = "%10s ") {
	for (str i : t.front._parameter)
		printf(text, i.c_str());
	printf(text, t.front._classification.c_str());
	printf("\n\n");

	for (DATAS_ID3 i : t.back) {
		for (str j : i._parameter)
			printf(text, j.c_str());

		printf(text, i._classification.c_str());
		printf("\n");
	}

	return;
}
//�������̒l�������邩�Ԃ��܂��B
template<typename Tb> Ulong ID3::_count(std::vector<Tb>* _data, Tb _count) {
	Ulong _ret = 0;

	for (Ulong i = 0; i < _data->size(); i++)
		_ret += (*_data)[i] == _count ? 1 : 0;

	return _ret;
}
//�������̒l���z�񒆂ɂ��邩���ׂ܂��B
template<typename Tb> bool  ID3::_is_existing(std::vector<Tb>* _data, Tb _d) {
	for (Ulong i = 0; i < _data->size(); i++) {
		if ((*_data)[i] == _d)
			return true;
	}

	return false;
}

//��ވꗗ��Ԃ��܂��B
std::vector<str>    ID3::_get_kinds(std::vector<str>* _data) {
	if (_data->size() == 0)
		return {};

	std::vector<str> _buf;
	_buf.push_back((*_data)[0]);

	for (Ulong i = 1; i < _data->size(); i++) {
		if (!_is_existing<str>(&_buf, (*_data)[i]))
			_buf.push_back((*_data)[i]);
	}

	return _buf;
}
//��ސ���Ԃ��܂��B
Ulong               ID3::_get_kinds_count(std::vector<str>* _data) {
	return _get_kinds(_data).size();
}
//�w�肳�ꂽparameter�̒l��z��Ɋi�[���܂��B
std::vector<str>    ID3::_get_parameters(std::vector<DATAS_ID3>* _data, Ulong _parameter_num) {
	std::vector<str> _buf;

	for (Ulong i = 0; i < _data->size(); i++)
		_buf.push_back((*_data)[i]._parameter[_parameter_num]);

	return _buf;
}
//���ނ̒l��z��Ɋi�[���܂��B
std::vector<str>    ID3::_get_class(std::vector<DATAS_ID3>* _data) {
	std::vector<str> _buf;

	for (Ulong i = 0; i < _data->size(); i++)
		_buf.push_back((*_data)[i]._classification);

	return _buf;
}
std::vector<str>    ID3::_get_byname(std::vector<DATAS_ID3>* _data, str name, DATAS_ID3* title) {
	if (title->_classification == name)
		return this->_get_class(_data);

	for (Ulong i = 0; i < title->_parameter.size(); i++) {
		if (title->_parameter[i] == name)
			return this->_get_parameters(_data, i);
	}

	_error(0, "Not Found Data:_get_byname.");
	return {};
}

//���ʂ����߂܂��B
double ID3::_get_entropy(std::vector<str>* _class) {
	std::vector<str> _buf = this->_get_kinds(_class);

	double retnum = 0;
	for (Ulong i = 0; i < _buf.size(); i++) {
		Ulong  _count = this->_count<str>(_class, _buf[i]);
		double _coff = (double)_count / _class->size();

		retnum += ((_coff)*log_s({_count, _class->size()}, 2,100) * -1);
	}

	return retnum;
}
//���Ғl�����߂܂��B
double ID3::_get_expected(std::vector<str>* _data, std::vector<str>* _class) {
	//�S�̂̕��Ϗ��ʂ����߂܂��B
	double              _entropy = this->_get_entropy(_class);

	//�����������Ϗ��ʂ��i�[����B
	std::vector<double> _buf;
	std::vector<str>    _data_buf_k = this->_get_kinds(_data);

	double              retnum = 0;

	for (Ulong i = 0; i < _data_buf_k.size(); i++) {
		//���������f�[�^���i�[
		std::vector<str> _data_buf_div;

		for (Ulong j = 0; j < _data->size(); j++) {
			if (_data_buf_k[i] == (*_data)[j])
				_data_buf_div.push_back((*_class)[j]);
		}
		_buf.push_back(this->_get_entropy(&_data_buf_div));
	}

	//���Ғl�����߂܂��B
	for (Ulong i = 0; i < _data_buf_k.size(); i++)
		retnum += _buf[i] * ((double)this->_count(_data, _data_buf_k[i]) / _data->size());

	return _entropy - retnum;
}
//���Ғl���ő��parameter�ԍ���Ԃ��܂��B
Ulong  ID3::_get_select(IN_ID3_NoTitle* _data) {
	std::vector<double> _buf;
	std::vector<str>    _class = this->_get_class(_data);

	for (Ulong i = 0; i < (*_data)[0]._parameter.size(); i++) {
		std::vector<str> _buf_par = this->_get_parameters(_data, i);
		_buf.push_back(this->_get_expected(&_buf_par, &_class));
	}

	S_PAIR<Ulong, double> _max = { 0,0 };
	for (Ulong i = 0; i < _buf.size(); i++) {
		if (_buf[i] > _max.back)
			_max = { i,_buf[i] };
	}
	return _max.front;
}

//�w�肳�ꂽparameter�̂Ȃ��ň�v�����z���Ԃ��܂��B
IN_ID3_NoTitle   ID3::_get_choice(IN_ID3_NoTitle* _data, Ulong _num_par, str _search_par) {
	IN_ID3_NoTitle _buf;

	for (Ulong i = 0; i < _data->size(); i++) {
		if ((*_data)[i]._parameter[_num_par] == _search_par)
			_buf.push_back((*_data)[i]);
	}

	return _buf;
}
//����؂�Ԃ��܂��B(�ċA�֐�)
std::vector<str> ID3::_quarry    (IN_ID3* _data, str _root = "") {
	std::vector<str> _class = this->_get_class(&_data->back);

	if (this->_get_entropy(&_class) == 0 || _data->front._parameter.size() == 1)
		return { (_root + "\nret ") + (_class[0] + ";") };

	const Ulong _select = this->_get_select(&_data->back);
	std::vector<str> _par = this->_get_parameters(&_data->back, _select);
	std::vector<str> _par_k = this->_get_kinds(&_par);

	str    _name = _data->front._parameter[_select];

	std::vector<std::vector<str>> _get;

	_root += _root[0] == 0 ? "\n " : " and ";

	for (Ulong i = 0; i < _par_k.size(); i++) {
		IN_ID3_NoTitle _buf = this->_get_choice(&_data->back, _select, _par_k[i]);
		IN_ID3         _buf2 = { _data->front,_buf };

		_get.push_back(this->_quarry(&_buf2, _root + _name + "==" + _par_k[i]));
	}

	std::vector<str> _ret;
	for (Ulong i = 0; i < _get.size(); i++) {
		for (Ulong j = 0; j < _get[i].size(); j++)
			_ret.push_back(_get[i][j]);
	}

	return _ret;
}


//public
ID3::ID3(IN_ID3 _data) {
	_title = _data.front;
	_main = _data.back;
}
ID3::ID3(IN_ID3_NoTitle _data) {
	_main = _data;
	_title._classification = "class";

	for (Ulong i = 0; i < _data[0]._parameter.size(); i++)
		_title._parameter.push_back((str)i);
}
ID3::ID3()                 {_readonly = true;   }
ID3::ID3(const ID3& _data) {_main = _data._main;}

ID3& ID3::add(DATAS_ID3 _data) {
	if (!_readonly)
		_main.push_back(_data);

	return *this;
}
ID3& ID3::add(std::vector<DATAS_ID3> _data) {
	if (!_readonly) {
		for (Ulong i = 0; i < _data.size(); i++)
			_main.push_back(_data[i]);
	}

	return *this;
}

ID3& ID3::write(const char* _filename = "id3.data") {
	if (!_readonly) {
		file _buf = _filename;
		_buf.write("");

		for (Ulong i = 0; i < _tree.size(); i++)
			_buf.add(_tree[i].c_str());
	}
	return *this;
}
ID3& ID3::read (const char* _filename = "id3.data") {
	file _buf = _filename;
	str  _buf2 = _buf.read();
	_tree.erase(_tree.begin(), _tree.end());

	_buf2.division(&_tree, ';');
	for (Ulong i = 0; i < _tree.size(); i++)
		_tree[i].add(";");

	if (_tree[0].find("par:") != -1) {
		_tree[0].erase_front(3);
		_tree[0][strlen(_tree[0].c_str()) - 1] = 0;

		_tree[0].division(&this->_title._parameter, ',');
	}
	return *this;
}

ID3& ID3::fit  () {
	if (!_readonly) {
		IN_ID3           _buf = { _title,_main };
		std::vector<str> _ret;

		str _par = "par:";
		for (Ulong i = 0; i < _title._parameter.size(); i++) {
			_par += _title._parameter[i];
			if ((i + 1) < _title._parameter.size())
				_par += ",";
			else
				_par += ";";
		}

		_ret = this->_quarry(&_buf);
		_ret.insert(_ret.begin(), { _par });

		_tree = _ret;
	}
	return *this;
}
str  ID3::get  (std::vector<str> _data) {
	if (_data.size() != this->_title._parameter.size())
		return "Defferent size of parameter.";

	std::vector<str> _data_search;

	for (Ulong i = 0; i < _title._parameter.size() && i < _data.size(); i++)
		_data_search.push_back((_title._parameter[i] + "==") + _data[i]);

	for (str _buf : _tree) {
		bool disagree = false;
		bool hit = false;

		for (Ulong i = 0; i < _title._parameter.size(); i++) {
			Ulong pos = _buf.find(_title._parameter[i].c_str());
			if (pos != -1) {
				hit = true;
				Ulong _equal = _buf.find(_data_search[i].c_str());
				if (_equal == -1)
					disagree = true;
			}
		}
		if (!disagree && hit) {
			std::vector<str> _ret;
			_buf.division(&_ret, '\n');
			_ret[_ret.size() - 1].erase_front(3);
			for (Ulong i = 0; i < strlen(_ret[_ret.size() - 1].c_str()); i++) {
				if (_ret[_ret.size() - 1][i] == ';')
					_ret[_ret.size() - 1][i] = 0;
			}
			return _ret[_ret.size() - 1];
		}
	}

	return "No Data.";
}

ID3& ID3::view     (const char* text = "%10s ") {
	if (!_readonly) {
		IN_ID3 _buf = { _title,_main };
		this->_view(_buf);
	}
	return *this;
}
ID3& ID3::view_tree() {
	for (str i : _tree)
		printf("%s", i.c_str());

	return *this;
}


#endif