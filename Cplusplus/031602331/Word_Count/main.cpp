#include "pch.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<iterator>
#include<cctype>
#include<unordered_map>
#include "countchar.h"
#include "COUNTWORD.h"
#include"rankword.h"
using namespace std;


int main()
{
	char filename[1000];
	cout << "please input your filename:" << endl; 

	cin.getline(filename, 100000);
	fstream outfile(filename, ios::in);
	count_charandline(outfile);
	cout<<"word: "<<count_word(filename);
	auto ten =  RankWord((scaner(filename)));
	Output(ten);
	return 0;
}
