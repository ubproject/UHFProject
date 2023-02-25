//============================================================================
// Name        : UHF.cpp
// Author      : Sanae
// Version     : 1.0.3
//============================================================================

#include <iostream>
#include "UHF/Sanae.h"


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
void SanaeStrc() {
	STRC sample = STRC_Init_Value;

	//������̊m��&������̏�������
	{
		if (FALSE == STRC_ALLOC(&sample, 6)) {
			printf("�������̊m�ۂɎ��s���܂����B\n");
			return;
		}
		STRC_WRITE(&sample, "hello", BASICW);
	}
	/*STRC_COPY(&sample, "hello");*/

	//������̒ǉ�
	STRC_ADD(&sample,"world");

	//������؂蔲��
	RANGE buf = {0,4};
	STRC_SUB(&sample,sample._str,buf);
	//sample._str=hello

	//���������ւ�
	STRC_COPY(&sample,"Hello World");//sample=Hello World
	STRC_REPLACE(&sample,"World","Sanae",0);//sample=Hello Sanae

	//�������̊J��
	STRC_FREE(&sample);

	return;
}
int main() {
	
	SanaeStrc();
	SanaeStr();
	
	matrix test = {5,5};

	test[{0, 0}] = 1;
	test[{1, 0}] = 2;
	test[{2, 0}] = 3;
	test[{3, 0}] = 4;
	test[{4, 0}] = 5;

	test[{0, 1}] = 6;
	test[{1, 1}] = 7;
	test[{2, 1}] = 8;
	test[{3, 1}] = 9;
	test[{4, 1}] = 10;

	test[{0, 2}] = 11;
	test[{1, 2}] = 12;
	test[{2, 2}] = 13;
	test[{3, 2}] = 14;
	test[{4, 2}] = 15;
	
	test[{0, 3}] = 16;
	test[{1, 3}] = 17;
	test[{2, 3}] = 18;
	test[{3, 3}] = 19;
	test[{4, 3}] = 20;

	test[{0, 4}] = 21;
	test[{1, 4}] = 22;
	test[{2, 4}] = 23;
	test[{3, 4}] = 24;
	test[{4, 4}] = 25;

	printf("�s��:%lg\n",test.det());
	return 0;
}
