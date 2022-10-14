#include "Sanae.h"
#include "SanaeUtil.h"


void test_str() {
	//���
	str _str = "Hello";  //Hello

	//������E�����̒ǉ�
	_str.add("Hello");   //HelloHell
	_str.add(2022);      //HelloHello2022

	//0~4�܂ł̕�������폜
	_str.erase({ 0,4 }); //Hello2022

	//�\��
	printf("%s\n", _str.c_str());    //Hello2022
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
	printf("%u\n", _str.count('a')); //4
	return;
}
void test_file() {
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
void test_math() {
	//2��5����v�Z
	printf("%u\n", exponentiation((UINT)2, 5));  //32

	//2��0.5����v�Z
	printf("%lf\n", exponentiation(2, 0.5, 3));  //1.414

	//11�͑f��������
	printf("%d\n", is_primenum(11));             //true(1)

	//2^1/2���v�Z(���O��)
	printf("2^1/2=%lf\n", root(2, 2, 3));          //2^1/2=1.414

	//2^1/2���v�Z(���Z��)
	printf("2^1/2=%lf\n", root(2, 2, 6));          //2^1/2=1.414213

	//2^1/5���v�Z(���O��)
	printf("2^1/5=%lf\n", root(2, 5, 3));          //2^1/5=1.148
	return;
}

int main(void){
	printf("str�^\n");
	test_str();

	printf("file�^\n");
	test_file();

	printf("math�֐��Q\n");
	test_math();

	return 0;
}