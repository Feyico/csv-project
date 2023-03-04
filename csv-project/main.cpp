#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

//txt�ļ���·��
string file_path = "D:\\workSpace\\330108002-0661-7517.txt";
//CSV����ļ�·��
string csv_path = "D:\\output.csv";

void WriteCsvFile(const string& line_head, const string& line_combo)
{
	ofstream outFile;
	outFile.open(csv_path, ios::out | ios::app);

	// д���ַ���
	outFile << line_head << ',' << line_combo << std::endl;
	outFile.close();
}


/*
* ����
* const string& line      ��������ַ���
* const char split        �ָ��
* const int split_num     ��ʼ�ָ�ĸ����������ֵΪ28���ӵ�28����ʼ�ָ
* const int combo_num     һ����������ݸ����������ֵΪ4��4��Ϊһ�飩
*/
void ProcessLine(const string& line, const char split, const int split_num, const int combo_num)
{
	//���ڴ洢���
	string line_combo = "";
	//���ڻ��浥������
	string line_buff = "";
	//��ͷ���ݣ�ʱ�����
	string line_head = "";
	//�ַ���������
	istringstream iss(line);
	//�ָ����
	int split_count = 1;
	//��ϼ���
	int combo_count = 0;
	//��ʼ���flag
	bool combo_start = false;
	while (getline(iss, line_buff, split))
	{
		//������ͷ����
		if (split_count <= split_num)
		{
			line_head = line_head + " " + line_buff;
			split_count = split_count++;
		}
		else
		{
			combo_start = true;
		}

		//��ʼ�����������
		if (combo_start)
		{
			line_combo = line_combo + "," + line_buff;
			combo_count = combo_count++;
			if (combo_count == combo_num)
			{
				//ɾ���ַ�����λ��","
				line_combo.erase(0,1);
				cout << "Combo data is: " << line_combo << endl;
				//д��CSV�ļ�
				WriteCsvFile(line_head, line_combo);
				//������
				line_combo = "";
				//�������
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
		//���д���
		ProcessLine(line, ' ', 28, 4);
	}
	infile.close();
	return 0;
}

int main()
{
	int ret = ProcessFile();
}