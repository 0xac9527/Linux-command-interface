// Linux_Cmd.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include"Command.h"

string folderpath[8];
void Analizepath(string* str)
{
	int ptr = 0;
	for (int i = 0; !str[i].empty(); i++)
	{
		if (str[i].find(":", 0) != string::npos|| strcmp(str[i].c_str(), ".") == 0 || strcmp(str[i].c_str(), "..")==0)//若为全局路径
			folderpath[ptr++] = str[i];
		else if (str[i].find("\\", 0) != string::npos)//若为相对路径
			folderpath[ptr++] = cwd + str[i];
		else if (str[i].find(".", 0) != string::npos)//若为文件
		{
			folderpath[ptr] = cwd;
			folderpath[ptr++].append("\\").append("\\").append(str[i]);//为啥append两次？
		}
	}
	if (ptr == 0 && str[1].empty())
		folderpath[ptr++] = cwd;
}

 
int main()
{
	//mkdir -m 700 F:\\test\\test.txt
	cout << "*********************************************" << endl;
	cout << "**  操作系统课设：兼容Linux的命令接口      **" << endl;
	cout << "**ls、mkdir、cp、cd、rm、touch、rmdir、cat **" << endl;
	cout << "**           Author：shao  xh              **" << endl;
	cout << "*********************************************" << endl;
	string StrCmd;
	string str[8];
	int i = 0;
	struct retval
	{
		int ret1;
		int ret2;
	};

	char CurrentWorkDirectory[128];
	GetCurrentDirectoryA(128, CurrentWorkDirectory);
	cout << "$ "<<(string)CurrentWorkDirectory << ">";
	cwd = CurrentWorkDirectory;
	
	while (cin.get() != '\n')
	{
		cin.unget();
		cin >> str[i];
		i++;
	}
	while (true)
	{
		folderpath[0] = cwd;
		if (str[0] == "mkdir")
		{
			if (str[1] == "-p") { Analizepath(str); for (int i = 0; !folderpath[i].empty(); i++) Mkdir_p(folderpath[i]); }
			else if (str[1] == "-m") { Analizepath(str); for (int i = 0; !folderpath[i].empty(); i++)Mkdir_m(folderpath[i], str[2]); }
			else if (str[1].find("-", 0) == string::npos)
				cout << "\"mkdir\" has no such option" << endl;
			else if (!str[1].empty()) { Analizepath(str); for (int i = 0; !folderpath[i].empty(); i++)Mkdir(folderpath[i]); }
			else { cout << "The input is incorrect!  mkdir ([选项]) [参数]" << endl; }
		}
		else if (str[0] == "cd")
		{
			if (!str[1].empty()) { Analizepath(str); cd(folderpath[0]); }
			else { cout << "The input is incorrect!  cd ([选项]) [参数]" << endl; }
		}
		else if (str[0] == "ls")
		{
			if (str[1] == "-l") { Analizepath(str);			ls_l(folderpath[0]); }
			else if (str[1] == "-a") { Analizepath(str);	ls_a(folderpath[0]); }
			else if (str[1] == "-d") { Analizepath(str);	ls_d(folderpath[0]); }
			else if (str[1] == "-A") { Analizepath(str);	ls_A(folderpath[0]); }
			else if (str[1] == "-R") { Analizepath(str);	ls_R(folderpath[0]); }
			else if (str[1] == "-m") { Analizepath(str);	ls_m(folderpath[0]); }
			else if (str[1].find("-", 0) == string::npos) { Analizepath(str);	ls(folderpath[0]); }
			else { cout << "The input is incorrect!  ls ([选项]) [参数]" << endl; }
		}
		else if (str[0] == "touch")
		{
			if (str[1] == "-a") { Analizepath(str); for (int i = 0; !folderpath[i].empty(); i++) touch_a(folderpath[i]); }
			else if (str[1] == "-m") { Analizepath(str); for (int i = 0; !folderpath[i].empty(); i++) touch_m(folderpath[i]); }
			else if (str[1] == "-r") { Analizepath(str); for (int i = 0; !folderpath[i].empty(); i++) touch_r(folderpath[i]); }
			else if (str[1] == "-d") { Analizepath(str); for (int i = 0; !folderpath[i].empty(); i++) touch_d(folderpath[i], str[2].c_str()); }
			else if (!str[1].empty()) { Analizepath(str); touch(folderpath[0]); }
			else { cout << "The input is incorrect!  touch ([选项]) [参数]" << endl; }
		}
		else if (str[0] == "rm")
		{
			if (str[1] == "-R") { Analizepath(str); rm_R(folderpath[0]); }
			else if (str[1] == "-i") { Analizepath(str); rm_i(folderpath[0]); }
			else if (!str[1].empty()) { Analizepath(str); rm(folderpath[0]); }
			else { cout << "The input is incorrect!  rm ([选项]) [参数]" << endl; }
		}

		else if (str[0] == "rmdir")
		{
			if (str[1] == "-p") { Analizepath(str); for (int i = 0; !folderpath[i].empty(); i++) rmdir_p(folderpath[i]); }
			else if (!str[1].empty()) { Analizepath(str); for (int i = 0; !folderpath[i].empty(); i++) rmdir(folderpath[i]); }
			else { cout << "The input is incorrect!  rmdir ([选项]) [参数]" << endl; }
		}

		else if (str[0] == "cp")
		{
			if (str[1] == "-R") {
				Analizepath(str);
				cp_R(folderpath[0], folderpath[1]);
			}
			else if (str[1].find(".", 0) != string::npos && !str[2].empty()) {
				Analizepath(str); for (int j = 0; !folderpath[j + 1].empty(); j++) { string temp = folderpath[i - 2]; cp(folderpath[j], temp.append("\\").append(str[j + 1])); }
			}
			else if (!str[1].empty() && str[2].empty()) { Analizepath(str); cp(folderpath[0], cwd); }
			else { cout << "The input is incorrect!  cp ([选项]) [参数]" << endl; }
		}
		else if (str[0] == "cat")
		{
			if (str[1].find("-", 0) == string::npos)
			{
				Analizepath(str); cat(folderpath[0], FALSE);
			}
			else if (str[1] == "-n")
			{
				Analizepath(str); cat(folderpath[0], TRUE);
			}
			else { cout << "The input is incorrect!  cp ([选项]) [参数]" << endl; }
		}
		else if (str[0] == "mv")
		{


			WIN32_FIND_DATAA FindFileData_source = { 0 };
			WIN32_FIND_DATAA FindFileData_goal = { 0 };
			HANDLE hFind_source = INVALID_HANDLE_VALUE;
			HANDLE hFind_goal = INVALID_HANDLE_VALUE;


			string p;

			Analizepath(str);




			hFind_source = FindFirstFileA(p.assign(folderpath[0]).append("\\*").c_str(), &FindFileData_source);
			hFind_goal = FindFirstFileA(p.assign(folderpath[i - 2]).append("\\*").c_str(), &FindFileData_goal);


			/*Analizepath(str); mv(folderpath[0], folderpath[1]);*/
			if (str[1].find(".", 0) != string::npos && !str[2].empty())
			{
				if (!(FindFileData_source.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (FindFileData_goal.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))// source为文件 goal为目录


				{

					for (int j = 0; !folderpath[j + 1].empty(); j++) {
						string temp = folderpath[i - 2];

						cp(folderpath[j], temp.append("\\").append(str[j + 1]));
						rm(folderpath[j]);
					}



				}
				else if ((FindFileData_source.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (FindFileData_goal.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))

				{
					cp_R(folderpath[0], folderpath[1]);
				}




				else
				{
					mv(folderpath[0], folderpath[1]);
				}

			}

			else { cout << "The input is incorrect!  mv ([选项]) [参数]" << endl; }
		}
		else if (str[0] == "find")//find   path   -option   [   -print ]   [ -exec   -ok   command ]   {} \;
		{
			string find_path;
			string option;
			string temp;
			int temp_time;
			string parameter;
			if (i == 1||i == 2 && str[1] == ".")//find  find.
			{
		       ls_R(cwd);
			}
			else if (i == 2 && str[1]!= ".")
			{
				find_path = cwd;
				parameter = str[1];
				direct_find(find_path, parameter);
			
			}
			else if (i == 3 && str[2] == "-empty")
			{
				
				
				if (str[1].find(":", 0) != string::npos)//若为全局路径
					find_path = str[1];
				else
				
					find_path = cwd + str[1];
				   option = str[2];
				   parameter = "null";
                short_find(find_path, option, parameter);
			}

			else	if (i == 4)//short find
			{
				if (str[1].find(":", 0)!= string::npos )//若为全局路径
					find_path = str[1];
				else
					find_path = cwd + str[1];
                option = str[2];
            	temp = str[3];
				if(strcmp(str[2].c_str(), "-name") == 0)
				{
					temp.erase(0, 3);
					temp.erase(temp.end() - 1);
				}
				

				if (strcmp(str[2].c_str(), "-iname") == 0)
				{
                    temp.erase(0, 3);
					temp.erase(temp.end() - 1);
					char *p;
					char *q = (char*)(temp.c_str());

					p = strlwr(q);
					string temp = p;
				}
				parameter = temp;
				if (strcmp(str[2].c_str(), "-newer") == 0)
					find_newerfile(find_path,parameter);
				else if (strcmp(str[2].c_str(), "-maxdepth")==0)
					find_maxdepth_1(find_path,parameter);
				else if (strcmp(str[2].c_str(), "-mindepth") == 0)
					find_mindepth_1(find_path, parameter);
				else
			    short_find(find_path, option, parameter);


				}

			else if (i > 4)
			{
				string name = NULL;
				string size = NULL;
				for (int j = 0; j <=i; j++)
				{
					if (strcmp(str[j].c_str(), "-name") == 0)
						 name = str[j + 1];
					    name.erase(0, 3);
					      name.erase(name.end() - 1);
				
					if (strcmp(str[j].c_str(), "-size") == 0)
						 size = str[j + 1];
				 }

			      
				 
			 
				
				
		        
              



			}
		else
			{
				cout << "The input is incorrect!   find   path   -option   [   -print ]   [ -exec   -ok   command ]   {} \ " << endl;
			}
			
		

	}
		
		cout << "$ " << cwd << ">";
		for (int j = 0; j < 8; j++)
		{
			str[j].erase(0, str[j].length());
			folderpath[j].erase(0, folderpath[j].length());
			i++;
		}

		i = 0;
		
		while (cin.get() != '\n')
		{
			cin.unget();//回退一个字符
			cin >> str[i];
			i++;
		}
	}
	 return 0;
}














