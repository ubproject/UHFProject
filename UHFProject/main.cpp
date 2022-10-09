#include "Sanae.h"

int main(void){

	/*SanaeStr*/
	str _str = "Hello";  //Hello
	
	_str.add("Hello");   //HelloHell
	_str.add(2022);      //HelloHello2022
	
	_str.erase({0,4});   //Hello2022

	printf("%s\n",   _str.c_str());  //Hello2022
	wprintf(L"%s\n", _str.c_wstr()); //Hello2022

	_str = "Alpha,Bravo,Charlie,Delta";
	std::vector<str> str_array;
	_str.division(&str_array,',');
	for (str i:str_array) {
		printf("%s\n",i.c_str());
	}
	/*
	Alpha
	Bravo
	Charlie
	Delta
	*/

	printf("%u\n", _str.count('a')); //4


	/*SanaeFile*/
	file _file = "SanaeProject.log";
	
	_file.write("Copyright 2016");
	
	_file.add(" SanaeProject.");
	
	str text;
	
	_file.read(&text);
	
	printf("%s\n",text.c_str());     //Copyright 2016 SanaeProject


	/*SanaeMath*/
	printf("%u\n",exponentiation((UINT)2, 5));  //32

	printf("%d\n",is_primenum(11));             //true(1)
	
	printf("2^1/2=%lf\n",root(2,2,3));          //2^1/2=1.414
	
	printf("2^1/2=%lf\n",root(2,2,6));          //2^1/2=1.414213
	
	printf("2^1/5=%lf\n",root(2,5,3));          //2^1/5=1.148


	return 0;
}