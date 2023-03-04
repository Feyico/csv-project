#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

//txt文件的路径
string file_path = "D:\\workSpace\\330108002-0661-7517.txt";
//CSV输出文件路径
string csv_path = "D:\\output.csv";

void WriteCsvFile(const string& line_head, const string& line_combo)
{
	ofstream outFile;
	outFile.open(csv_path, ios::out | ios::app);

	// 写入字符串
	outFile << line_head << ',' << line_combo << std::endl;
	outFile.close();
}


/*
* 参数
* const string& line      输入的行字符串
* const char split        分割符
* const int split_num     开始分割的个数（例如该值为28即从第28个开始分割）
* const int combo_num     一个组合内数据个数（例如该值为4即4个为一组）
*/
void ProcessLine(const string& line, const char split, const int split_num, const int combo_num)
{
	//用于存储组合
	string line_combo = "";
	//用于缓存单个数据
	string line_buff = "";
	//行头数据（时间戳）
	string line_head = "";
	//字符串输入流
	istringstream iss(line);
	//分割计数
	int split_count = 1;
	//组合计数
	int combo_count = 0;
	//开始组合flag
	bool combo_start = false;
	while (getline(iss, line_buff, split))
	{
		//处理行头数据
		if (split_count <= split_num)
		{
			line_head = line_head + " " + line_buff;
			split_count = split_count++;
		}
		else
		{
			combo_start = true;
		}

		//开始处理组合数据
		if (combo_start)
		{
			line_combo = line_combo + "," + line_buff;
			combo_count = combo_count++;
			if (combo_count == combo_num)
			{
				//删除字符串首位的","
				line_combo.erase(0,1);
				cout << "Combo data is: " << line_combo << endl;
				//写入CSV文件
				WriteCsvFile(line_head, line_combo);
				//组合清空
				line_combo = "";
				//计数清空
				combo_count = 0;
			}
		}	
	}
	cout << "Head data is: " << line_head << endl;
}

int ProcessFile()
{
	string line;
	ifstream infile;
	infile.open(file_path);
	while (getline(infile, line))
	{
		//按行处理
		ProcessLine(line, ' ', 28, 4);
	}
	infile.close();
	return 0;
}

int main()
{
	int ret = ProcessFile();
}