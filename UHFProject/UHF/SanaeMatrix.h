/*
 ============================================================================
 Name        : UHF-SanaeMatrix
 Author      : Sanae
 Version     : 1.0.3(Beta)
 Copyright   : CopyRight 2022 SanaeProject.
 ============================================================================
 */

#ifndef SANAEMATRIX_H
#define SANAEMATRIX_H


#include <vector>
#include <stdexcept>
#include "UHFC/SanaeTypes.h"


template<typename T = double>
constexpr auto ABS_SANAE_CPP(T X) { return X < 0 ? X * -1 : X; }

template<typename T1, typename T2>
struct S_PAIR {
	T1 front;
	T2 back;
};

typedef S_PAIR<Ulong, Ulong> size_matrix;


//行列の計算を行う。
template<typename _DataType = double>
class matrix {
private:
	_DataType*  _main = NULL;   //行列の格納先
	size_matrix _size = { 0,0 };//列と行を格納する。

	Ulong& _width  = _size.front;//列
	Ulong& _height = _size.back;//行


	/*関数一覧:private
	Ulong       Get_ArrayNumber         (Ulong, size_matrix);
	size_matrix Get_XYNumber            (Ulong, Ulong      );

	void        _error                  (const char*       );
	bool        _allocate               (_DataType**, Ulong);

	//行列操作
	void        copy                    (_DataType**, _DataType**, size_matrix);
	void        view                    (_DataType**, size_matrix, const char*);
	void        _replace_line           (_DataType**, size_matrix, Ulong      , Ulong);
	void        _replace_column         (_DataType**, size_matrix, Ulong      , Ulong);
	bool        to_identity_matrix      (_DataType**, size_matrix             );

	//演算
	void        _a_matrix               (size_matrix, _DataType**, _DataType**);
	_DataType   _det_2                  (_DataType**, _DataType  , size_matrix);
	S_PAIR<std::vector<matrix<_DataType>>, std::vector<_DataType>>
	            _cofactor_expansion_to_2(_DataType**, size_matrix, Ulong      , _DataType);
	void        _mul                    (_DataType**, size_matrix, _DataType**, size_matrix , _DataType**, size_matrix*);
	void        _cofactor_expansion     (_DataType**, size_matrix, std::vector<matrix<_DataType>>*, std::vector<_DataType>*, Ulong);
	*/
	

	/*実装*/
	//配列番号を取得します。第一引数に列数を第二引数に{列数,行数}を入れてください。
	Ulong       Get_ArrayNumber(Ulong width, size_matrix _XYNum) {
		Ulong& _x = _XYNum.front;
		Ulong& _y = _XYNum.back;

		if (_x >= width)
			return 0;

		return (width * (_y)) + (_x);
	}
	//配列番号を{列数,行列}に変換します。 第一引数に列数を第二引数に配列番号を入れてください。
	size_matrix Get_XYNumber(Ulong width, Ulong _ArrayNum) {
		Ulong _x = _ArrayNum % width;
		Ulong _y = (_ArrayNum - _x) / width;

		if (_x >= width)
			return { 0,0 };

		return { _x , _y };
	}

	//error出力用
	void _error(const char* _text) {
		throw std::exception(_text);
	}
	//配列を確保します。返り値として成功:true,失敗:falseを返します。
	bool _allocate(_DataType** _data, Ulong size) {
		//メモリの割り当てを増やす場合があるのでreallocを使う。
		_DataType* buf = (_DataType*)realloc(*_data, size * sizeof(_DataType));

		if (buf == NULL) {
			free(*_data);
			*_data = NULL;

			return false;
		}

		*_data = buf;

		//データの初期化
		memset(*_data, 0, size * sizeof(_DataType));

		return true;
	}
	
	//配列の値をコピーします。
	void copy(_DataType** _from, _DataType** _to, size_matrix size) {
		//データの初期化
		free(*_to);
		*_to = NULL;

		//メモリ割り当て
		if (!_allocate(_to, (size.front * size.back)))
			_error("Failed to allocate:copy.");

		//値をコピー
		for (Ulong i = 0; i < (size.back * size.front); i++)
			(*_to)[i] = (*_from)[i];

		return;
	}
	//行列を表示します。
	void view(_DataType** _data, size_matrix size, const char* _text = "%3.0lg ") {
		for (Ulong i = 0; i < ((size.front) * (size.back)); i++) {
			if (i % size.front == 0)
				printf("\n");
			printf(_text, (*_data)[i]);
		}

		return;
	}
	//指定された行を入れ替えます。
	void _replace_line(_DataType** _d, size_matrix size, Ulong _data1, Ulong _data2) {
		Ulong& width = size.front;

		for (Ulong x = 0; x < width; x++) {
			_DataType _buf = (*_d)[Get_ArrayNumber(width, { x,_data1 })];

			(*_d)[Get_ArrayNumber(width, { x,_data1 })] = (*_d)[Get_ArrayNumber(width, { x,_data2 })];
			(*_d)[Get_ArrayNumber(width, { x,_data2 })] = _buf;
		}

		return;
	}
	//列を入れ替えます。
	void _replace_column(_DataType** _d, size_matrix size, Ulong _data1, Ulong _data2) {
		for (Ulong y = 0; y < size.back; y++) {
			_DataType _buf = (*_d)[Get_ArrayNumber(size.front, { _data1,y })];

			(*_d)[Get_ArrayNumber(size.front, { _data1,y })] = (*_d)[Get_ArrayNumber(size.front, { _data2,y })];
			(*_d)[Get_ArrayNumber(size.front, { _data2,y })] = _buf;
		}

		return;
	}
	//第一引数の配列のポインタ先を単位行列にセットします。
	bool to_identity_matrix(_DataType** _data, size_matrix size) {
		if (size.back != size.front)
			return false;

		//データをすべて0にする。
		memset(*_data, 0, size.front * size.back * sizeof(_DataType));

		//単位行列にする。
		for (Ulong i = 0; i < size.front; i++)
			(*_data)[Get_ArrayNumber(size.front, { i,i })] = 1;

		return true;
	}

	void _a_matrix(size_matrix size, _DataType** _data, _DataType** _to) {
		//単位行列にする。
		to_identity_matrix(_to, size);

		//_pos:基準
		for (Ulong _pos = 0; _pos < size.front; _pos++) {
			for (Ulong y = 0; y < size.back; y++) {
				if (_pos != y) {
					_DataType div = 0;

					//基準が0の場合行を入れ替える。
					if ((*_data)[Get_ArrayNumber(size.front, { _pos,_pos })] == 0) {
						for (Ulong findy = 0; findy < size.back; findy++) {
							if ((*_data)[Get_ArrayNumber(size.front, { _pos,findy })] != 0) {
								_replace_line(_data, size, _pos, findy);
								_replace_line(_to, size, _pos, findy);
							}
						}
					}

					//ax+b=0 x -= b/a  
					div = ((*_data)[Get_ArrayNumber(size.front, { _pos,y })] / (*_data)[Get_ArrayNumber(size.front, { _pos,_pos })]);

					//その他列への適用
					for (Ulong x = 0; x < size.front; x++) {
						(*_data)[Get_ArrayNumber(size.front, { x,y })] -= div * ((*_data)[Get_ArrayNumber(size.front, { x,_pos })]);
						(*_to)[Get_ArrayNumber(size.front, { x,y })] -= div * ((*_to)[Get_ArrayNumber(size.front, { x,_pos })]);
					}
				}
			}
		}

		//基準が1になっていない場合その行へ適用し1にする。
		for (Ulong _pos = 0; _pos < size.front; _pos++) {
			for (Ulong _x = 0; _x < size.front; _x++) {
				_DataType _is_zero_buf = (*_data)[Get_ArrayNumber(size.front, { _pos,_pos })];
				if (_is_zero_buf != 0)
					(*_to)[Get_ArrayNumber(size.front, { _x,_pos })] /= _is_zero_buf;
			}
		}

		return;
	}
	//サラスの方式で解きます。2次元
	_DataType _det_2(_DataType** _data, _DataType _coeff, size_matrix size) {
		if (size.back != size.front)
			_error("Different size:_det_2_3");

		if (size.front != 2)
			_error("Must pass 2 as argument:_det_2_3");

		//サラスの方式で解く
		return  _coeff * ((*_data)[Get_ArrayNumber(size.front, { 0,0 })] * (*_data)[Get_ArrayNumber(size.front, { 1,1 })] - ((*_data)[Get_ArrayNumber(size.front, { 1,0 })] * (*_data)[Get_ArrayNumber(size.front, { 0,1 })]));
	}
	//余因子展開をして行列を一次元下げます。下げた値は_storeに格納されます。係数はcoeffcientに格納されます。
	void _cofactor_expansion(_DataType** _data, size_matrix size, std::vector<matrix<_DataType>>* _store, std::vector<_DataType>* coefficient, Ulong column = 0) {
		if (size.back != size.front)
			_error("Different size:_cofactor_expansion.");

		//格納先の初期化
		_store->erase(_store->begin(), _store->end());

		//余因子展開をした結果格納先のメモリを確保します。
		for (Ulong _count = 0; _count < size.back; _count++)
			_store->push_back({ size.front - 1,size.back - 1 });

		for (Ulong _y_pos = 0; _y_pos < size.back; _y_pos++) {
			//_bufsに格納していく。
			//全配列参照
			for (Ulong i = 0, _bufs_pos = 0; i < size.front * size.back; i++) {
				//iの地点がxまたはyでない場合格納する。
				size_matrix pos = Get_XYNumber(size.front, i);
				if (pos.front != column && pos.back != _y_pos) {
					((*_store)[_y_pos])[Get_XYNumber(size.front - 1, _bufs_pos)] = (*_data)[i];
					_bufs_pos++;
				}
			}

			coefficient->push_back((*_data)[Get_ArrayNumber(size.front, { column,_y_pos })] * exponentiation(-1, column + _y_pos));
		}

		return;
	}
	/*二次元まで次元を落とします。再帰で求めます。
	* 4次元->2次元
	* 4*4行列:
	*
	* 1   2  3  4
	* 5   6  7  8
	* 9  10 11 12
	* 13 14 15 16
	*
	* 3*3行列に変換しそれを2*2行列に変換する。
	*      6  7  8
	* 1*  10 11 12 =>(1*6)*  11 12 + (1*-10)*   7  8 + (1*14)*   7  8
	*     14 15 16           15 16             15 16            11 12
	*
	*      2  3  4
	* -5* 10 11 12 =>(-5*2)* 11 12 + (-5*-10)*  3  4 + (-5*14)*  7  8
	*     14 15 16           15 16             15 16            11 12
	*
	*      2  3  4
	* 9*   6  7  8 =>(9*2)*   7  8 + (9*-6)*   3   4 + (9*14)*   3  4
	*     14 15 16           15 16            15  16             7  8
	*
	*      2  3  4
	* -13* 6  7  8 =>(-13*2)* 7  8 + (-13*-6)*  3  4 + (-13*10)*  3  4
	*     10 11 12           11 12             11 12              7  8
	*/
	S_PAIR<std::vector<matrix<_DataType>>, std::vector<_DataType>> _cofactor_expansion_to_2(_DataType** _data, size_matrix size, Ulong column = 0, _DataType in_coeff = 1) {
		if (size.back != size.front)
			_error("Different size:_cofactor_expansion_to_2.");

		if (size.front < 3)
			_error("Must pass above 3  as argument:_cofactor_expansion_to_2.");

		//行列格納用可変配列
		std::vector<matrix<_DataType>> _buf;
		//係数格納用
		std::vector<_DataType>         _coeff;

		//一次元下げる
		this->_cofactor_expansion(_data, size, &_buf, &_coeff, column);

		//回帰で計算するので前回の係数を自分に掛ける。
		for (Ulong i = 0; i < _coeff.size(); i++)
			_coeff[i] *= in_coeff;

		//3*3行列だった場合1次元下げたので2*2行列になるそのためそのまま返す。
		if (size.front == 3)
			return { _buf ,_coeff };

		//自分自身を呼び出すので呼び出し結果をここに入れる。
		std::vector<S_PAIR<std::vector<matrix<_DataType>>, std::vector<_DataType>>> _bufs;
		for (Ulong i = 0; i < _buf.size(); i++)
			_bufs.push_back(this->_cofactor_expansion_to_2((_DataType**)_buf[i].show_main, *(_buf[i].show_size), column, _coeff[i]));

		//行列と係数の格納
		S_PAIR<std::vector<matrix<_DataType>>, std::vector<_DataType>> _retdata;

		for (Ulong i = 0; i < _bufs.size(); i++) {
			for (Ulong j = 0; j < _bufs[i].front.size(); j++) {
				_retdata.front.push_back(_bufs[i].front[j]);
				_retdata.back.push_back(_bufs[i].back[j]);
			}
		}
		return _retdata;
	}
	void _mul(_DataType** _num1, size_matrix _num1_size, _DataType** _num2, size_matrix _num2_size, _DataType** _store, size_matrix* _store_size_p) {
		if (_num1 == _store || _num2 == _store)
			_error("Must pass different pointer as argument.");

		if (_num1_size.front != _num2_size.back)
			_error("Different size:_mul");

		free(*_store);
		*_store = NULL;

		if (!this->_allocate(_store, (_num1_size.back * _num2_size.front)))
			_error("Failed to allocate:mul");

		for (Ulong y = 0; y < _num1_size.back; y++) {
			for (Ulong x = 0; x < _num2_size.front; x++) {
				//それぞれの計算を行う
				for (Ulong k = 0; k < _num1_size.front; k++)
					(*_store)[Get_ArrayNumber(_num2_size.front, { x,y })] += (*_num1)[Get_ArrayNumber(_num1_size.front, { k,y })] * (*_num2)[Get_ArrayNumber(_num2_size.front, { x,k })];

				//誤差の修正(無限小数対策)
				if (ABS_SANAE_CPP((*_store)[Get_ArrayNumber(_num2_size.front, { x,y })]) <= ERROR_SANAE)
					(*_store)[Get_ArrayNumber(_num2_size.front, { x,y })] = 0;
			}
		}

		_store_size_p->front = _num2_size.front;
		_store_size_p->back = _num1_size.back;
		return;
	}
public:
	//参照用
	const _DataType**  show_main = (const _DataType** ) &_main;
	const size_matrix* show_size = (const size_matrix*) & _size;


	/*関数一覧:public
	//コンストラクタ
	matrix ();
	matrix (Ulong, Ulong );
	matrix (const matrix&);
	~matrix();
	
	//オペレータ
	_DataType& operator [](S_PAIR<Ulong, Ulong>);
	matrix&    operator  =(S_PAIR<Ulong, Ulong>);
	matrix&    operator  =(const matrix&);
	matrix&    operator +=(const matrix&);
	matrix&    operator -=(const matrix&);
	matrix&    operator *=(const matrix&);
	matrix     operator  +(const matrix&);
	matrix     operator  -(const matrix&);
	matrix     operator  *(const matrix&);
	//スカラー倍
	matrix     operator  *(_DataType);
	matrix&    operator *=(_DataType);

	//演算用関数
	matrix&   add              (const matrix<_DataType>&);
	matrix&   sub              (const matrix<_DataType>&);
	matrix&   scalar_mul       (_DataType);
	matrix&   mul              (const matrix<_DataType>&);
	//行列操作用関数
	matrix&   write_line       (Ulong, std::vector<_DataType>);
	matrix&   replace_column   (Ulong, Ulong);
	matrix&   replace_line     (Ulong, Ulong);
	matrix    inverse          (void);
	_DataType det              (void);
	matrix&   to_identity      (void);
	matrix    transpose        (void);
	matrix&   view             (const char*);
	matrix&   copy_matrix      (_DataType**);
	matrix&   copy_array       (_DataType**, size_matrix);
	
	bool      is_holomorphic   (void);
	*/


	//Constructor
	//行列の幅、高さを指定します。
	matrix() {
		_size = { 0,0 };
	}
	matrix(Ulong width, Ulong height) {
		_size = { width,height };

		if (!_allocate(&_main, width * height))
			_error("Failed to allocate.");
	}
	matrix(const matrix& _data) {
		copy((_DataType**)&_data._main, &_main, _data._size);
		_size = _data._size;
	}

	//Destructor
	~matrix() {
		free(_main);
	}

	//operator
	_DataType& operator [](size_matrix _data) {
		Ulong _buf = Get_ArrayNumber(_width, _data);
		if (_buf >= _width * _height)
			_error("Tried to out of range");

		return *(_main + _buf);
	}
	matrix& operator  =(const matrix& _data) {
		copy((_DataType**)&_data._main, &_main, _data._size);

		return *this;
	}
	matrix& operator  =(size_matrix size) {
		free(_main);
		_size = { size.front,size.back };

		if (!_allocate(&_main, _width * _height))
			_error("Failed to allocate.");
	}
	matrix& operator +=(const matrix& _data) {
		return add(_data);
	}
	matrix& operator -=(const matrix& _data) {
		return sub(_data);
	}
	matrix& operator *=(_DataType _data) {
		return scalar_mul(_data);
	}
	matrix& operator *=(const matrix& _data) {
		return mul(_data);
	}
	matrix operator   +(const matrix& _data) {
		if (_data._height != _height || _data._width != _width)
			_error("Different size:sub");

		_DataType* _buf = NULL;
		this->copy(&_main, &_buf, _size);

		for (Ulong i = 0; i < _width * _height; i++)
			*(_buf + i) += *(_data._main + i);

		matrix _ret;
		_ret.copy_array(&_buf, _size);

		free(_buf);

		return _ret;
	}
	matrix operator   -(const matrix& _data) {
		if (_data._height != _height || _data._width != _width)
			_error("Different size:sub");

		_DataType* _buf = NULL;
		this->copy(&_main, &_buf, _size);

		for (Ulong i = 0; i < _width * _height; i++)
			*(_buf + i) -= *(_data._main + i);

		matrix _ret;
		_ret.copy_array(&_buf, _size);

		free(_buf);

		return _ret;
	}
	matrix operator   *(_DataType _data) {
		_DataType* _buf = NULL;
		this->copy(&_main, &_buf, _size);

		for (Ulong i = 0; i < _height * _width; i++)
			*(_buf + i) *= _data;

		matrix _ret;
		_ret.copy_array(&_buf, _size);

		free(_buf);

		return _ret;
	}
	matrix operator   *(const matrix& _data) {
		_DataType*  _buf = NULL;
		size_matrix size;

		this->_mul(&_main, _size, (_DataType**)&_data._main, (size_matrix) _data._size, &_buf, &size);

		matrix _retdata;
		_retdata.copy_array(&_buf, size);

		free(_buf);

		return _retdata;
	}

	
	/*演算*/
	matrix& add(const matrix<_DataType>& _data) {
		if (_data._height != _height || _data._width != _width)
			_error("Different size:add");

		for (Ulong i = 0; i < _width * _height; i++)
			*(_main + i) += *(_data._main + i);

		return *this;
	}
	matrix& sub(const matrix<_DataType>& _data) {
		if (_data._height != _height || _data._width != _width)
			_error("Different size:sub");

		for (Ulong i = 0; i < _width * _height; i++)
			*(_main + i) -= *(_data._main + i);

		return *this;
	}
	matrix& scalar_mul(_DataType _d) {
		for (Ulong i = 0; i < _height * _width; i++)
			*(_main + i) *= _d;

		return *this;
	}
	//cij= Σ k=1,m (aik*bkj)を使用
	matrix& mul(const matrix<_DataType>& _data) {

		_DataType* _buf = NULL;
		this->copy(&_main, &_buf, _size);

		this->_mul(&_buf, _size, (_DataType**)&_data._main, (size_matrix) _data._size, &_main, &_size);

		free(_buf);

		return *this;
	}
	
	/*行列操作*/
	//指定した行に書き込みます。
	matrix& write_line(Ulong pos, std::vector<_DataType> write) {
		if (write.size() != this->_size.front)
			_error("Different size:write_line.");

		for (Ulong i = 0; i < write.size(); i++)
			_main[Get_ArrayNumber(this->_size.front, { i, pos })] = write[i];

		return *this;
	}
	//列の入れ替え
	matrix& replace_column(Ulong num1, Ulong num2) {
		_replace_column(&_main, _size, num1, num2);
		return *this;
	}
	//行の入れ替え
	matrix& replace_line(Ulong num1, Ulong num2) {
		_replace_line(&_main, _size, num1, num2);
		return *this;
	}
	//逆行列を求めます。A*A^-1 = 1
	matrix inverse() {
		if (_width != _height)
			_error("Different size:a_matrix");

		if (this->det() == 0)
			_error("This equation has no real number solution:matrix_inverse.");

		_DataType* _buf = NULL;
		if (!_allocate(&_buf, _width * _height))
			_error("Failed to allocate:a_matrix");

		_DataType* _copy = NULL;
		this->copy(&_main, &_copy, _size);

		_a_matrix(_size, &_main, &_buf);

		matrix _retdata;
		_retdata.copy_array(&_buf, { _width, _height });

		free(_main);
		free(_buf);

		_main = NULL;
		copy(&_copy, &_main, _size);

		free(_copy);
		return _retdata;
	}
	//行列式を求めます。
	_DataType det() {
		if (_size.front != _size.back)
			_error("Different size:det.");

		switch (_size.front) {
		case 1:
			return _main[0];
		case 2:
			return this->_det_2(&_main, 1, { 2,2 });
		default:
			break;
		}

		S_PAIR<std::vector<matrix<_DataType>>, std::vector<_DataType>> test = this->_cofactor_expansion_to_2(&_main, _size);

		_DataType _t = 0;

		for (Ulong i = 0; i < test.front.size(); i++)
			_t += this->_det_2((_DataType**)test.front[i].show_main, (_DataType)test.back[i], (S_PAIR<Ulong, Ulong>) * (test.front[i].show_size));

		return _t;
	}
	//正則行列かどうか調べます。
	bool is_holomorphic() {
		if (this->det() == 0)
			return false;

		return true;
	}
	//単位行列にします。
	matrix& to_identity() {
		to_identity_matrix(&_main, { _width,_height });

		return *this;
	}
	//行列を表示します。
	matrix& view(const char* _text = "%3.0lg") {
		view(&_main, _size, _text);
		return *this;
	}
	//行列を配列にコピーします。(配列を初期化します。)
	matrix& copy_matrix(_DataType** _to) {
		free(*_to);
		*_to = NULL;

		if (!_allocate(_to, _width * _height))
			_error("Failed to allocate:copy_matrix.");

		for (Ulong _pos = 0; _pos < (_width * _height); _pos++)
			(*_to)[_pos] = _main[_pos];

		return *this;
	}
	//配列を自分にコピーします。
	matrix& copy_array(_DataType** _from, size_matrix size) {
		free(_main);
		_main = NULL;

		copy(_from, &_main, size);
		_size = size;

		return *this;
	}
	//転置を行います。
	matrix transpose() {
		//行列のコピー
		_DataType* _copy = NULL;

		this->_allocate(&_copy, _size.front * _size.back);

		for (Ulong x = 0; x < _size.front; x++) {
			for (Ulong y = 0; y < _size.back; y++) {
				_copy[Get_ArrayNumber(_size.back, { y,x })] = _main[Get_ArrayNumber(_size.front, { x,y })];
			}
		}

		matrix retdata;
		retdata.copy_array(&_copy, { _size.back,_size.front });

		free(_copy);

		return retdata;
	}
};
#endif