//============================================================================
// Name        : UHF.cpp
// Author      : Sanae
// Version     : 1.0.3
//============================================================================

#include <iostream>
#include "UHF/Sanae.h"

using namespace std;


void SanaeStr() {
	/*SanaeStr.h�T���v���v���O����*/
	//Samaple�ŏ�����
	str sample_str = "Sample";
	printf("������:%s\n", sample_str.c_str());	//������:Sample


	//���C�h��������
	sample_str = L"Hello\n";
	wprintf(sample_str.c_wstr());				//Hello


	//���l����
	sample_str = 1234;
	printf("%s\n", sample_str.c_str());			//1234


	//�����ǉ�									//1234�ł��B12
	sample_str += "�ł��B12";
	//sample_str.add("�ł��B12");


	//���l�ɕϊ�(�ŏ�����Ō�܂�)
	Ulong i = sample_str.to_ulong(RANGE_DEFAULT);
	printf("���l��:%llu\n", i);					//123412


	//����������ւ��� World->Sanae
	sample_str = "HelloWorld";
	sample_str.replace("World", "Sanae");
	printf("����ւ���:%s\n", sample_str.c_str());//HelloSanae


	//���������蕶���ŕ�������B(',')
	sample_str = "alpha,bravo,delta,eco";
	std::vector<str> test;
	sample_str.division(&test, ',');
	//�\������
	for (str i : test)
		printf("%s\n", i.c_str());
	/*
	alpha
	bravo
	delta
	eco
	*/


	//�ŏ�����Ō�܂ō폜����B
	sample_str.erase({ 0,strlen(sample_str.c_str()) });
	//sample_str.erase(RANGE_DEFAULT);


	//��r���Z�q == !=
	sample_str = "HelloWorld";
	if (sample_str == "HelloWorld")			//true
		printf("��v���܂����B\n");

	return;
}

int main() {
	SanaeStr();

	return 0;
}