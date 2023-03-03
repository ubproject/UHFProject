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
	STRC_COPY   (&sample,"Hello World"    );//sample=Hello World
	STRC_REPLACE(&sample,"World","Sanae",0);//sample=Hello Sanae

	//�������̊J��
	STRC_FREE(&sample);

	return;
}
void SanaeMatrix() {
	//�s�������5*5�s��
	matrix test = { 5,5 };

	test.write_line(0, { 3, 1, 1, 3, 0 });
	test.write_line(1, { 5, 1, 3, 2, 2 });
	test.write_line(2, { 2, 0, 1, 8, 1 });
	test.write_line(3, { 0, 1, 3, 9, 3 });
	test.write_line(4, { 2, 2, 5, 1, 5 });

	test.view("%5.0lf ");

	printf("�s��:%lg\n", test.det());//86

	matrix buf = test;

	//�t�s��ɂ���B
	test.inverse();

	//���̎��Ƌt�s����|����ƒP�ʍs��ɂȂ�BA*A^-1=1
	(buf * test).view("%5.0lf");

	//9x+2y=13
	//5x+9y=33��x,y�ɂ��ĉ���
	/*
	9 2 * x = 13
	5 9   y   33
	   ��
	A * x = Z
		y

	A^-1*A=1���

	x = A^-1*Z
	y

	������������Ƃ�x,y�ɂ��ċ��߂邱�Ƃ��ł���B
	*/
	matrix z = { 1,2 };
	z[{0, 0}] = 13;
	z[{0, 1}] = 33;

	matrix A = { 2,2 };
	A.write_line(0, { 3,2 });
	A.write_line(1, { 5,9 });

	(A.inverse() * z).view();
	// 3
	// 2
	//�����x=3,y=2�ł���B
}
int main() {
	SanaeStrc();
	SanaeStr ();
	SanaeMatrix();

	return 0;
}
