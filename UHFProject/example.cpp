#include <stdio.h>
#include "Sanae.h"

void str_test() {
	//���
	str _str = "Hello";  //Hello

	//������E�����̒ǉ�
	_str.add("Hello");   //HelloHell
	_str.add(2022);      //HelloHello2022

	//0~4�܂ł̕�������폜
	_str.erase({ 0,4 });   //Hello2022

	//�\��
	printf("%s\n", _str.c_str());  //Hello2022
	wprintf(L"%s\n", _str.c_wstr()); //Hello2022

	//Alpha,Bravo,Charlie,Delta����
	_str = "Alpha,Bravo,Charlie,Delta";

	//�����p�̃R���e�i��p��
	std::vector<str> str_array;

	//����̕���(',')�ŕ��������������f�[�^��str_array�Ɋi�[
	_str.division(&str_array, ',');
	for (str i : str_array) {
		printf("%s\n", i.c_str());
	}
	/*
	Alpha
	Bravo
	Charlie
	Delta
	*/
	//'a'�̐��𒲍�
	printf("%llu\n", _str.count('a')); //4

	return;
}
void file_test() {
	//�t�@�C����SanaeProject.log
	file _file = "SanaeProject.log";

	//��������
	_file.write("Copyright 2016");

	//�ǋL
	_file.add(" SanaeProject.");

	//�ǂݎ�����f�[�^�̊i�[����쐬
	str text;
	//�ǂݎ��
	_file.read(&text);
	//�o��
	printf("%s\n", text.c_str());     //Copyright 2016 SanaeProject
	
	return;
}
void mathc_test() {
	//2��5����v�Z
	printf("%lf\n", exponentiation(2, 5));  //32

	//11�͑f��������
	printf("%d\n", is_primenum(11));             //true(1)

	//2^1/2���v�Z(���O��)
	printf("2^1/2=%lf\n", root(2, 2, 3));          //2^1/2=1.414

	//2^1/2���v�Z(���Z��)
	printf("2^1/2=%lf\n", root(2, 2, 6));          //2^1/2=1.414213

	//2^1/5���v�Z(���O��)
	printf("2^1/5=%lf\n", root(2, 5, 3));          //2^1/5=1.148

	//LCGs�ɂ�闐���o��
	printf("%llu\n", LCGs() % 10);

	return;
}
void math_test() {
	//92��f��������
	UINT a = 92;
	std::vector<UINT> test;

	factorization(test, a);

	for (UINT i : test)
		printf("%u", i);

	return;
}
void util_test() {
	//1~9�܂ł̐������o��
	printf("1~9:%u\n", random(1, 9));

	//year:2022  day:286  23:21:29
	printf("year:%u  day:%u  %u:%u:%u\n", get_year(), get_day(), get_hour(), get_minutes(), get_second());

	return;
}

int main(int argc,char* argv[]) {
	void (*str  )() = str_test;
	void (*file )() = file_test;
	void (*mathc)() = mathc_test;
	void (*math )() = math_test;
	void (*util )() = util_test;

	printf("str.h\n");
	str();
	system("pause");

	printf("file.h\n");
	file();
	system("pause");

	printf("mathc.h\n");
	mathc();
	system("pause");

	printf("math.h\n");
	math();
	system("pause");

	printf("util.h\n");
	util();
	system("pause");
}