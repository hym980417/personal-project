// WordCount.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<stdio.h>
#include <iostream>
#include <fstream>
#include "CharNum.h"
#include "LineNum.h"
#include"WordNum.h"
#include "Word_Fre.h"
using namespace std;

//int argc, char *argv[])
int main(int argc, char *argv[])
{
	
	if (argv[1] == NULL)
	{
		
		printf("please input file!\n");
		return -1;

	}
	std::fstream file;
	file.open(argv[1]);
 if (!file) {
		
		printf("the file cannot open or no exist!\n");
		return -1;
	}
		
	file.close();

		//char fi[30] = "D:\\input.txt";
		int Char_Number = CharNum(argv[1]);
		int Lines_Number = LineNum(argv[1]);
		int Words_Number = WordNum(argv[1]);

		printf("characters: %d\n", Char_Number);
		printf("lines: %d\n", Lines_Number);
		printf("words: %d\n", Words_Number);

		Word_Fre(argv[1]);			//Word frequency statistics


	
	
	return 0;
}
