
#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int real_word_num;
int char_judge(char c)//判断是否是字母，大写返回3，小写返回2，否则返回1
{
	if (c > 64 && c < 91) return 3;
	else if (c > 96 && c < 123) return 2;
	else return 1;
}
int word_judge(string t)//判断是否是单词，是则返回3，否则返回值小于3
{
	int i;
	for (i = 0; i < 3;)
	{
		if (char_judge(t[i]) != 1)
		{
			i++;
		}
		else
			break;
	}
	return i;
}
int c_char(string T)
{
	int num = 0, i;
	for (i = 0; T[i] != '\0'; i++)
	{
		if (T[i] > 0 && T[i] < 126)
		{
			num++;
		}
	}
	return num;
}
int c_word(string T, int char_num, string word[], string real_word[])
{
	int i, j, k, f, f1, word_num = 0;
	string t;
	for (i = 0; T[i] != '\0'; )
	{
		f = char_judge(T[i]);//判断首字符是否为字母，是则进入循环，否则判断下一个字母
		if (f == 1)
		{
			i++;
		}
		else
		{
			t = "";
			t += T[i + 1];
			t += T[i + 2];
			t += T[i + 3];
			f1 = word_judge(t);
			if (f1 == 3)//是单词
			{
				for (j = 0; char_judge(T[i + j]) == 2 || char_judge(T[i + j]) == 3 || (T[i + j] > 47 && T[i + j] < 58); j++)
				{
					if (T[i + j] > 64 && T[i + j] < 91) T[i + j] += 32;
					word[real_word_num] += T[i + j];
				}
				i += j;
				for (j = 0, k = 1; j < real_word_num; j++)
				{
					if (word[real_word_num] == word[j])
					{
						k = 0;
						break;
					}
				}
				if (k == 1)
				{
					real_word[word_num] = word[real_word_num];
					word_num++;
				}
				real_word_num++;
			}
			else
			{
				i += (f1 + 1);
			}
		}
	}
	return word_num;
}
int c_line(string path)
{
	ifstream f(path);
	string str;
	int line_num = 0;
	while (f)
	{
		getline(f, str);
		if (str.length() > 0) line_num++;
	}
	return line_num - 1;
}
void word_print(int word_num, string word[], string real_word[])
{
	int frequence[10000], val[10000];
	int i, j, fre;
	int temp, temp1;
	string str;
	for (i = 0; i < word_num; i++)//得到词频和字典值
	{
		for (j = 0, fre = 0; j <real_word_num; j++)
		{
			if (real_word[i] == word[j]) fre++;
		}
		frequence[i] = fre;
		for (j = 0; real_word[i][j] != '\0'; j++)
		{
			val[i] += real_word[i][j];
		}
	}
	//对real_word数组排序，数量是word_num
	for (i = 0; i < word_num - 1; i++)
	{
		for (j = 0; j < word_num - i - 1; j++)
		{
			if (frequence[j] < frequence[j + 1])
			{

				str = real_word[j]; real_word[j] = real_word[j + 1]; real_word[j + 1] = str;
				temp = frequence[j]; frequence[j] = frequence[j + 1]; frequence[j + 1] = temp;
				temp1 = val[j]; val[j] = val[j + 1]; val[j + 1] = temp1;
			}
			if (frequence[j] == frequence[j + 1])
			{
				if (val[j] < val[j + 1])
				{
					str = real_word[j]; real_word[j] = real_word[j + 1]; real_word[j + 1] = str;
					temp = frequence[j]; frequence[j] = frequence[j + 1]; frequence[j + 1] = temp;
					temp1 = val[j]; val[j] = val[j + 1]; val[j + 1] = temp1;
				}
			}
		}
	}
	if (word_num < 10) j = word_num;
	else j = 10;
	for (i = 0; i < j; i++)
	{
		cout << "<" << real_word[i] << ">: ";
		printf("%d\n", frequence[i]);
	}
}
int main()
{
	string word[10000];//未去重复单词的集合
	string real_word[10000];//去重复单词的集合
	string path, T;
	fstream f;
	char c;
	int char_num, word_num, line_num;

	cin >> path;
	f.open(path, ios::in);

	if (!f)
	{
		cout << "打开文件出错" << endl;
		return 0;
	}
	else
	{
		while (EOF != (c = f.get()))
		{
			T += c;
		}

	}
	//字符数统计输出
	char_num = c_char(T);
	printf("characters: %d\n", char_num);
	//单词数统计输出
	word_num = c_word(T, char_num, word, real_word);
	printf("words: %d\n", word_num);

	//行数统计输出
	line_num = c_line(path);
	printf("lines：%d\n", line_num);

	//词频统计输出
	word_print(word_num, word, real_word);


	return 0;

}
//C:\Users\后敬甲\Desktop\测试用例一.txt
