#include "stdafx.h"
using namespace std;
bool cmp(const struct WF& a, const struct WF& b)
{
	return a.value > b.value;
}
string Conventor(int src)//转换itos
{
	stringstream ss;
	string dst;
	ss.clear();
	ss << src;
	ss >> dst;
	return dst;
}
int DetectFileOpen(ifstream &infile)
{
	if (!infile.is_open())
	{
		cout << "Cannot open the file, please input right filename!";
		system("pause");
		return 0;
	}
}
int DetectOutfileOpen(ofstream &outfile)
{
	if (!outfile.is_open())
	{
		cout << "Cannot open the file!";
		system("pause");
		return 0;
	}
}
int Counter::LineCount()//统计行数
{
	ifstream infile;
	infile.open(sfn);
	DetectFileOpen(infile);
	string str[Linethreshold];
	int line = 0;
	while (infile)//文件处理 
	{
		getline(infile, str[line]);//按行读取
		if (str[line] != "\0")//统计行数，不计算空行
			line++;
	}
	//cout << "lines: " << line << endl;
	infile.close();
	return line;
}
int Counter::CharCount()
{
	ifstream infile;
	infile.open(sfn);
	DetectFileOpen(infile);
	string str[Linethreshold];
	int ch = 0, line = 0;

	while (infile)//文件处理 
	{
		getline(infile, str[line]);//按行读取
		line++;
	}
	line--;

	for (int i = 0; i < line; i++)
	{
		ch += str[i].size();
	}
	ch += line-1;
	//cout << "characters: " << ch << endl;
	infile.close();
	return ch;
}
int Counter::WordCount()
{
	ifstream infile;
	infile.open(sfn);
	DetectFileOpen(infile);
	string str[Linethreshold], str1[Wordthreshold];
	int ch = 0, line = 0;
	int words = 0;

	while (infile)//文件处理 
		getline(infile, str[line++]);//按行读取
	line--;
	for (int i = 0; i<line; i++)//特殊符号处理
	{
		int j = 0;
		while (str[i][j] != '\0')
		{
			if (ispunct(str[i][j]))str[i][j] = ' ';//特殊符号处理为空格
			else
			{
				str[i][j] = tolower(str[i][j]);//化为小写
			}
			j++;
		}
	}
	int j = 0;

	for (int i = 0; i<line; i++)//将空格处理后的文档转化为单词 
	{
		istringstream stream(str[i]);
		while (stream)stream >> str1[j++];
	}
	//for (int k = 0; k < line; k++)cout << str1[k] << endl;

	j --;
	words = 0;
	int k = 0;
	int isword = 1;
	for (int i = 0; i<j ; i++)//单词统计 
	{
		isword = 1; 
		if (isword)
		for (k = 0; k<4; k++)//除去数字开头
		{
			if (str1[i][0] == '\0')
			{
				isword = 0;
				break; 
			}
			if (str1[i][k] == '\0')break;
			else if (!isalpha(str1[i][k])) {
				isword = 0;
				break;
			}
		}

		if (isword) {
			words++;
		}
	}
	//for (int k = 0; k < line; k++)cout << str1[k] << endl;
	//cout << "words==" << words << endl;
	//for (int i = 0; i<j - 1; i++)
	//cout << str1[i] << endl;
	//cout << "words: " << words << endl;
	infile.close();
	return words;
}

string Counter::WordFreq()
{
	ifstream infile;
	infile.open(sfn);
	DetectFileOpen(infile);
	string str[Linethreshold], str1[Wordthreshold], result;
	int ch = 0, line = 0;
	int words = 0;
	bool isword = true;
	while (infile)//文件处理 
		getline(infile, str[line++]);//按行读取
	line--;
	for (int i = 0; i<line; i++)//特殊符号处理
	{
		int j = 0;
		while (str[i][j] != '\0')
		{
			if (ispunct(str[i][j]))str[i][j] = ' ';//特殊符号处理为空格
			else
			{
				str[i][j] = tolower(str[i][j]);//化为小写
			}
			j++;
		}
	}

	int j = 0;
	
	for (int i = 0; i<line; i++)//将空格处理后的文档转化为单词 
	{
		if (str[i]!="\0") {
			istringstream stream(str[i]);
			while (stream)stream >> str1[j];
			j++;
		}
	}

	//for (int k = 0; k < line; k++)cout << str1[k] << endl;
	
	words = 0;
	int k = 0;

	for (int i = 0; i<j; i++)//单词筛选
	{
		isword = true;
		for (k = 0; k<4; k++)//除去数字开头
		{
			if (str1[i][0] == '\0')
			{
				isword = false;
				break;
			}
			if (str1[i][k] == '\0')break;
			else if (!isalpha(str1[i][k])) {
				isword = false;
				break;
			}
		}
		if (!isword) {
			str1[i] = '\0';
		}
	}
	
	map<string, int> mymap;
	map<string, int>::iterator it;

	for (int i = 0; i<j ; i++)
	{
		//查找 是否有key 有的话 value++
		//否则加入这个key 
		it = mymap.find(str1[i]);
		if (it == mymap.end())
		{
			mymap.insert(map<string, int> ::value_type(str1[i], 1));
		}
		else
		{
			mymap[str1[i]]++;
		}
	}	

	//	for (; it != mymap.end(); it++)
	//	cout << '<'<<it->first << ">: " << it->second << endl;
	it = mymap.begin();

	string temps = "\0";
	stringstream ss;
	int i = 0;
	
	WF a[100];

	for (i = 0; it != mymap.end(); it++, i++)
	{	
		a[i].key = it->first;
		a[i].value = it->second;
	}
	
	stable_sort(&a[0], &a[i+1], cmp);
	for (j = 0; j<i;  j++)
	{
		ss.clear();
		temps = "\0";
		str[j] = "\0";
		ss << a[j].value;
		ss >> temps;
		str[j] = "<" + a[j].key + "" + ">: " + temps;
	}
	//cout << "i==" << i;

	//str[i] = "\0";
	//for (i = 0; str[i] != "\0"; i++)
		//cout << str[i] << endl<<endl;
	for (i = 0; str[i] != "\0"; i++)
	{
		if (i >= 10)break;
		if(str[i][0]=='<')
			result += str[i] + "\n";
		else break;
	}
	//cout << result;
	infile.close();
	return result;
}
void Counter::Write()
{
	stringstream ss;
	ifstream infile;

	string result, temp;
	int v = 0;

	infile.open(sfn);
	DetectFileOpen(infile);
	
	result += "characters: " + Conventor(CharCount()) + "\n";
	result += "words: " + Conventor(WordCount()) + "\n";
	result += "lines: " + Conventor(LineCount()) + "\n";
	result += WordFreq();
	infile.close();

	ofstream outfile;
	outfile.open(dfn,ios::out);
	DetectOutfileOpen(outfile);
	
	outfile << result << endl;
	outfile.close();
}
//int DetectFileOpen(ifstream &infile)
//int DetectOutfileOpen(ofstream &outfile)

int main(int argc, char* argv[])//
{
	if (argc != 2)
	{
		cout << "Uncorrect parameters, Please attach .exe and .txt file in order.";
		system("pause");
	}
	string sfn = argv[1];
	string dfn = "result.txt";
	Counter Cou(sfn, dfn);

	//Cou.CharCount();
	//cout<<"word="<<Cou.WordCount();
	//Cou.LineCount();
	//Cou.WordFreq();
	//cout << Cou.WordFreq();
	//for(int i=0;i<100;i++)
		Cou.Write();
	return 0;
}
