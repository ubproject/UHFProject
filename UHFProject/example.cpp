#include "Sanae.h"

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

	system("pause");
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

	system("pause");
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

	//�����𐶐�
	UINT d = random(2, 10000);
	printf("%u��f�����������܂��B\n", d);
	//�R���e�i��p��
	std::vector<UINT> l;
	factorization(l, d);
	//�o��
	for (UINT i : l) {
		printf("%u\n", i);
	}

	//�X�s�[�h��r
	printf("�������玞�Ԃ̂����鏈�����s���܂��B\n");
	//�ꎞ��~
	wint_t none = _getwch();


	printf("�W���t�@�C����sqrt�֐��ł̏������s���܂��B\n");
	//�ꎞ��~
	none = _getwch();
	
	//sqrt�֐��̏��������鎞�Ԃ𑪂�B
	time_t defm = time(NULL);
	for (UINT i = 1; i <= 10000; i++) {
		volatile double data = sqrt(i);
		printf("%u^1/2=%lf\n", i, data);
	}
	defm = time(NULL) - defm;
	printf("sqrt�֐��ł�10000��̌v�Z��%lld�b������܂����B\n",defm);

	//���̏����̎��Ԃ��v�Z
	double bufm = (double)defm / 10000;
	printf("���̌v�Z��:%lf�~���b������܂���\n",bufm*1000);

	system("pause");

	printf("Sanaemath.h�ł�root�֐��ł̏����������Ȃ��܂��B\n");
	//�ꎞ��~
	none = _getwch();

	//root�֐��̏������鎞�Ԃ𑪂�B
	time_t defs = time(NULL);
	for (UINT i = 1; i <= 10000; i++) {
		volatile double data = root(i,2,6);
		printf("%u^1/2=%lf\n", i, data);
	}
	defs = time(NULL) - defs;

	printf("SanaeMath��root�֐��ł�%lld�b������܂����B\n",defs);


	//���̏����̎��Ԃ��v�Z
	double bufs = (double)defs / 10000;
	printf("���̌v�Z��%lf�~���b������܂����B\n",bufs*1000);
	
	system("pause");

	printf("\n\nSanaeMath��%lf�~���b������܂���\nMath��%lf�~���b������܂����B\n\n", bufs*1000, bufm*1000);

	system("pause");
	return;
}
void test_util() {
	printf("1~9:%u\n",random(1,9));
	printf("year:%u  day:%u  %u:%u:%u\n", get_year(), get_day(), get_hour(), get_minutes(), get_second());

	system("pause");
}


int main(void){
	printf("str�^\n");
	test_str();

	printf("file�^\n");
	test_file();

	printf("math�֐��Q\n");
	test_math();

	printf("util�֐��Q\n");
	test_util();

	return 0;
}