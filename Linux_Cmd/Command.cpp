#include "pch.h"
#include"Command.h"



int length = 0;

int flag_num = 0;
int cmp_time = 0;

string cwd = "0";

void ls(string path) {

	long hFile = 0;
	struct _finddata_t fileinfo;  //很少用的文件信息读取结构
	string p;
	int i = 0;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do {
			if ((fileinfo.attrib & _A_SUBDIR) && !(fileinfo.attrib &_A_HIDDEN)) {  //比较文件类型是否是文件夹
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					cout <<left<<setw(32)<< fileinfo.name ;
					i++;
					if (i % 4==0)
						cout << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					//files.push_back(p.append(fileinfo.name));
					//getAllFiles(p.assign(path).append("\\").append("\\").append(fileinfo.name), files);
				}
			}
			else if (!(fileinfo.attrib & _A_HIDDEN)) {
				//files.push_back(p.append(fileinfo.name));
				cout << left << setw(32) << fileinfo.name;
				i++;
				if (i % 4 == 0)
					cout << endl;
			}

		} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
		_findclose(hFile);
	}
	cout << endl;
}

string filetype(struct _finddata_t fileinfo)
{
	string temp; 
	temp.append(fileinfo.name);
	if (temp.find(".txt")!=string::npos)
		return "txt文档";
	else if (temp.find(".doc") != string::npos)
		return "doc文档";
	else if (temp.find(".rar") != string::npos)
		return "压缩文件";
	else if (temp.find(".avi") != string::npos)
		return "avi文件";
	else if (temp.find(".cpp") != string::npos)
		return "c++源文件";
	else if (temp.find(".h") != string::npos)
		return "c++头文件";
	else if (temp.find(".pdf") != string::npos)
		return "pdf文件";
	else if (temp.find("mp3") != string::npos|| temp.find("Mp3") != string::npos)
		return "音乐文件";
	else if (temp.find("mp4") != string::npos || temp.find("Mp4") != string::npos)
		return "视频文件";
	else if (temp.find(".exe") != string::npos)
		return "可执行文件";
	else
		return "其他文件";
}
void ls_l(string path)
{
	static int flag = 0;
	long hFile = 0;
	struct _finddata_t fileinfo;
	string p;
	string str_show;
	string filepath;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do {
			if (fileinfo.attrib & _A_SUBDIR) {
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					if (flag == 0)
					{
						cout << left << setw(48) << fileinfo.name;
					}
					flag++;

					//ls_l(p.assign(path).append("\\").append("\\").append(fileinfo.name));

					flag--;
					if (flag == 0) {
						//cout << left << setw(16) << length/1024+1<<"KB";
						cout << left << setw(16) << fileinfo.size;
						cout << left << setw(8) << fileinfo.attrib;
						time_t* m_sencodes = &fileinfo.time_access;
						tm* m_localTime = localtime(m_sencodes);
						str_show.append(to_string(m_localTime->tm_year + 1900)).append("/").append(to_string(m_localTime->tm_mon + 1)).append("/").append(to_string(m_localTime->tm_mday)).append(" ")
							.append(to_string(m_localTime->tm_hour)).append(":").append(to_string(m_localTime->tm_min)).append(":").append(to_string(m_localTime->tm_sec));
						cout << left << setw(32) << str_show;
						str_show.clear();
						length = 0;
						cout << "文件夹" << endl;
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
							FOREGROUND_BLUE);
					}
				}
			}

			else if (flag == 0) {
				cout << left << setw(48) << fileinfo.name;
				string temp;
				
				cout << left << setw(16) << temp.append(to_string((int)ceil(fileinfo.size/1024))).append("KB");
				cout << left << setw(8) << fileinfo.attrib;

				time_t* m_sencodes = &fileinfo.time_access;
				tm* m_localTime = localtime(m_sencodes);
				str_show.append(to_string(m_localTime->tm_year + 1900)).append("/").append(to_string(m_localTime->tm_mon + 1)).append("/").append(to_string(m_localTime->tm_mday)).append(" ")
					.append(to_string(m_localTime->tm_hour)).append(":").append(to_string(m_localTime->tm_min)).append(":").append(to_string(m_localTime->tm_sec));
				cout << setw(32) << str_show << setw(8);
				str_show.clear();
				cout << filetype(fileinfo) << endl;
			}
			else {
				length = length + fileinfo.size;
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

void ls_a(string path) {

	long hFile = 0;
	struct _finddata_t fileinfo;  //很少用的文件信息读取结构
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do {
			if ((fileinfo.attrib & _A_SUBDIR)) {  //比较文件类型是否是文件夹
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
					FOREGROUND_BLUE);
				cout << fileinfo.name << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
					FOREGROUND_BLUE);
			}
			else {
				cout << fileinfo.name << endl;
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

void ls_d(string path) {
	long hFile = 0;
	struct _finddata_t fileinfo;  //很少用的文件信息读取结构
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do {
			if ((fileinfo.attrib & _A_SUBDIR) && !(fileinfo.attrib &_A_HIDDEN)) {  //比较文件类型是否是文件夹
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
					cout << fileinfo.name << endl;
				}
			}
		} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
		_findclose(hFile);
	}
}
void ls_A(string path) {

	long hFile = 0;
	struct _finddata_t fileinfo;  //很少用的文件信息读取结构
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do {
			if ((fileinfo.attrib & _A_SUBDIR)) {  //比较文件类型是否是文件夹
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					cout << fileinfo.name << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
				}
			}
			else {
				cout << fileinfo.name << endl;
			}
		} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
		_findclose(hFile);
	}
}

int num = -1;
void ls_R(string path)
{
	long hFile = 0;
	struct _finddata_t fileinfo;  //很少用的文件信息读取结构
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		num++;
		do {
			if ((fileinfo.attrib & _A_SUBDIR) && !(fileinfo.attrib &_A_HIDDEN)) {  //比较文件类型是否是文件夹
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					if (num > 0)
						cout <<right<< setw(num * 2) << "|";
					cout << fileinfo.name << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					ls_R(p.assign(path).append("\\").append("\\").append(fileinfo.name));
					num--;
				}
			}
			else if (!(fileinfo.attrib & _A_HIDDEN)) {
				if (num > 0)
					cout << right << setw(num * 2) << "|";
				cout << fileinfo.name << endl;
			}

		} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
		_findclose(hFile);
	}
}
//按文件修改时间排序

void ls_m(string path)
{
	long hFile = 0;
	struct _finddata_t fileinfo;  //很少用的文件信息读取结构
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do {
			if ((fileinfo.attrib & _A_SUBDIR) && !(fileinfo.attrib &_A_HIDDEN)) {  //比较文件类型是否是文件夹
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
					cout << path << left << setw(4) << "," << fileinfo.name << endl;
					ls_m(p.assign(path).append("\\").append(fileinfo.name));
				}
			}
			else if (!(fileinfo.attrib & _A_HIDDEN)) {
				cout << path << left << setw(4) << "," << fileinfo.name << endl;
			}
		} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
		_findclose(hFile);
	}
}

void Mkdir(string folderpath)
{
	if (_access(folderpath.c_str(), 0) == -1)
	{
		if (!CreateDirectoryA(folderpath.c_str(), NULL))
			cout << "Fail to create directory!" << endl;
	}
	else
		cout << "The directory is existed!" << endl;
}

void Mkdir_p(string path)
{
	int lp = 0, rp = 0;
	string folderpath;
	rp = path.find("\\", 4);
	do
	{
		folderpath = folderpath + path.substr(lp, rp - lp);
		if (_access(folderpath.c_str(), 0) == -1)
		{
			if (!CreateDirectoryA(folderpath.c_str(), NULL))
				cout << "Fail to create file!" << endl;
		}
		lp = rp;
		if (rp < path.length())
		{
			rp = path.find('\\', rp + 2);
			if (rp == string::npos)
				rp = path.length();
		}
	} while (lp != rp);
}

//建立目录的同时设置目录的权限；
void Mkdir_m(string folderpath, string num)
{
	char *end;
	BOOL BFlag = CreateDirectoryA(folderpath.c_str(), NULL);
	if (BFlag == ERROR_ALREADY_EXISTS)
		cout << "The goal file has existed!" << endl;
	else if (BFlag == ERROR_PATH_NOT_FOUND)
		cout << "One or more intermediate directories do not exist" << endl;
	//1只读，2隐藏，3系统文件.4普通文件
	switch (strtol(num.c_str(), &end, 10))
	{
	case 1:
		SetFileAttributesA(folderpath.c_str(), FILE_ATTRIBUTE_READONLY);
		break;
	case 2:
		SetFileAttributesA(folderpath.c_str(), FILE_ATTRIBUTE_HIDDEN);
		break;
	case 3:
		SetFileAttributesA(folderpath.c_str(), FILE_ATTRIBUTE_SYSTEM);
		break;
	case 4:
		SetFileAttributesA(folderpath.c_str(), FILE_ATTRIBUTE_NORMAL);
		break;
	default:
		break;
	}
}

void touch(string filename)
{
	string folderpath = filename;
	HANDLE hFile = CreateFileA(folderpath.c_str(), GENERIC_WRITE | GENERIC_READ, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE)
		cout << "Fail to create the file!" << endl;
	CloseHandle(hFile);
}

void touch_a(string folderpath)
{
	FILETIME ft;
	SYSTEMTIME st;
	HANDLE hFile = CreateFileA(
		folderpath.c_str(),
		GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	GetSystemTime(&st);
	SystemTimeToFileTime(&st, &ft);
	SetFileTime(hFile,
		(LPFILETIME)NULL,
		&ft,
		(LPFILETIME)NULL);
	CloseHandle(hFile);
}

void touch_m(string folderpath)
{
	FILETIME ft;
	SYSTEMTIME st;
	HANDLE hFile = CreateFileA(
		folderpath.c_str(),
		GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	GetSystemTime(&st);
	SystemTimeToFileTime(&st, &ft);
	SetFileTime(hFile,
		(LPFILETIME)NULL,
		(LPFILETIME)NULL,
		&ft);
	CloseHandle(hFile);
}

void touch_r(string folderpath)
{
	HANDLE hFile = CreateFileA(
		folderpath.c_str(),
		GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	LPFILETIME lpCreationTime = { 0 };
	LPFILETIME lpLastAccessTime = { 0 };
	LPFILETIME lpLastWriteTime = { 0 };

	GetFileTime(
		hFile,
		lpCreationTime,
		lpLastAccessTime,
		lpLastWriteTime
	);

	SetFileTime(hFile,
		lpCreationTime,
		lpLastAccessTime,
		lpLastWriteTime);
	CloseHandle(hFile);
}

void TimetToFileTime(time_t t, FILETIME &pft)
{
	LONGLONG ll = Int32x32To64(t, 10000000) + 116444736000000000;
	pft.dwLowDateTime = (DWORD)ll;
	pft.dwHighDateTime = ll >> 32;
}

time_t DateToTimet(const char* ptime)
{
	struct tm stm;
	int iY, iM, iD, iH, iMin, iS;

	memset(&stm, 0, sizeof(stm));
	iY = atoi(ptime);
	iM = atoi(ptime + 5);
	iD = atoi(ptime + 8);
	iH = atoi(ptime + 11);
	iMin = atoi(ptime + 14);
	iS = atoi(ptime + 17);

	stm.tm_year = iY - 1900;
	stm.tm_mon = iM - 1;
	stm.tm_mday = iD;
	stm.tm_hour = iH;
	stm.tm_min = iMin;
	stm.tm_sec = iS;

	return mktime(&stm);
}

void touch_d(string filepath, const char* ptime)
{
	//const char *str_time = "2011-12-31 11:43:07";
	time_t t = DateToTimet(ptime);
	FILETIME pft = { 0 };
	TimetToFileTime(t, pft);
	HANDLE hFile = CreateFileA(
		filepath.c_str(),
		GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	SetFileTime(hFile,		        // Sets last-write time of the file 
		NULL,           // to the converted current system time 
		NULL,
		&pft);
	CloseHandle(hFile);
}
BOOL DisplayError(BOOL ReadFlag, BOOL WriteFlag, DWORD Readlength, DWORD Writtenlength)
{
	BOOL Flag = TRUE;
	if (FALSE == WriteFlag)
	{
		cout << "Terminal failure: Unable to write to  goal file.\n";
		Flag = FALSE;
	}
	else if (FALSE == ReadFlag)
	{
		Flag = FALSE;
		cout << "Terminal failure: Unable to read source file.\n";
	}
	else
	{
		if (Readlength != Writtenlength)
		{
			// This is an error because a synchronous write that results in
			// success (WriteFile returns TRUE) should write all data as
			// requested. This would not necessarily be the case for
			// asynchronous writes.

			{
				Flag = FALSE;
				cout << "Error: dwBytesWritten != dwBytesToWrite\n";
			}
		}
	}
	return Flag;
}
void cp(string sourcefile, string godlfile)
{
	BOOL FileFlag = TRUE;
	HANDLE m_hFile = (HANDLE)CreateFileA(sourcefile.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		NULL,
		NULL);
	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		m_hFile = NULL;
		FileFlag = FALSE;
		cout << "Fail to open the source file!"<<endl;
	}
	HANDLE hFile = (HANDLE)CreateFileA(godlfile.c_str(),                // name of the write
		GENERIC_WRITE,          // open for writing
		0,                      // do not share
		NULL,                   // default security
		CREATE_NEW,             // create new file only
		FILE_ATTRIBUTE_NORMAL,  // normal file
		NULL);

	DWORD dw = GetLastError();
	if (dw == 183)
		cout << "The file has already  existed!" << endl;

	if (hFile == INVALID_HANDLE_VALUE)
	{
		hFile = NULL;
		FileFlag = FALSE;
		cout << "Fail to create the goal file!" << endl;
	}

	DWORD filesize = GetFileSize(m_hFile, NULL);//源文件的长度
	DWORD dwFileSize = 1024;//每次读取的文件长度
	char *pBuffer = new char[dwFileSize];//接收读取的字节
	DWORD dwReadSize;//实际读取或写入字节数的指针，
	//指向一个DWORD类型变量的指针，用来接收读取的字节数。如果下一个参数为NULL，那么一定要传入这个参数
	DWORD dwBytesWritten=0;
	BOOL bWriteErrorFlag, bReadErrorFlag;

	while ((bReadErrorFlag = ReadFile(m_hFile,
		pBuffer,
		dwFileSize,
		&dwReadSize,
		NULL)) && dwReadSize > 0)
	{

		bWriteErrorFlag = WriteFile(
			hFile,           // open file handle
			pBuffer,      // start of data to write
			dwReadSize,  // number of bytes to write
			&dwBytesWritten, // number of bytes that were written
			NULL);            // no overlapped structure
		DisplayError(bReadErrorFlag,
			bWriteErrorFlag,
			dwReadSize,
			dwBytesWritten);
	}
	delete[]pBuffer;//释放资源
	CloseHandle(m_hFile);
	CloseHandle(hFile);
}
void cp_R(string sourcedir, string goaldir)
{
	WIN32_FIND_DATAA FindFileData = { 0 };
	HANDLE hFind = INVALID_HANDLE_VALUE;
	BOOL IsEmpty = FALSE;
	string p;
	string sfile, gfile;
	int pos = sourcedir.rfind("\\", sourcedir.length());
	if (pos != string::npos)
		goaldir.append("\\").append(sourcedir.substr(sourcedir.rfind("\\", sourcedir.length()), sourcedir.length()));
	else
		goaldir.append("/").append(sourcedir.substr(sourcedir.rfind("\\", sourcedir.length()), sourcedir.length()));
	HANDLE m_hFile = (HANDLE)CreateDirectoryA(goaldir.c_str(), NULL);
	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		cout << "Error" << endl;
		return;
	}
	if ((hFind = FindFirstFileA(p.assign(sourcedir).append("\\*").c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		do
		{
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0)
				{
					cp_R(p.assign(sourcedir).append("\\").append(FindFileData.cFileName), goaldir);
				}
			}
			else
			{
				sfile = sourcedir;
				gfile = goaldir;
				sfile.append("/").append(FindFileData.cFileName);
				gfile.append("/").append(FindFileData.cFileName);
				cp(sfile, gfile);
			}
		} while (FindNextFileA(hFind, &FindFileData) != 0);
		FindClose(hFind);
	}
	else {
		FindClose(hFind);
	}
}


void rm_R(string path)
{
	WIN32_FIND_DATAA FindFileData = { 0 };
	HANDLE hFind = INVALID_HANDLE_VALUE;
	BOOL IsEmpty = FALSE;
	string p;
	string dir, file;
	if ((hFind = FindFirstFileA(p.assign(path).append("\\*").c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		dir = path;
		do
		{
			if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				file = path;
				if (DeleteFileA(file.append("\\").append(FindFileData.cFileName).c_str()) == ERROR_ACCESS_DENIED)
					cout << "File don't exist:" << FindFileData.cFileName << endl;
			}
			else
			{
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0)
				{
					rm_R(p.assign(path).append("\\").append(FindFileData.cFileName));
				}
			}
		} while (FindNextFileA(hFind, &FindFileData) != 0);
		RemoveDirectoryA(dir.c_str());
		FindClose(hFind);
	}
	else {
		FindClose(hFind);
	}
}

void rm(string path)
{
	WIN32_FIND_DATAA FindFileData = { 0 };
	HANDLE hFind = INVALID_HANDLE_VALUE;
	if ((hFind = FindFirstFileA(path.c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			cout << "This is not a file,but a directory!Please use \"rmdir\"or \"rm -i(-R)\"" << endl;
		else
			DeleteFileA(path.c_str());
	}
}

void rm_i(string path)
{
	WIN32_FIND_DATAA FindFileData = { 0 };
	HANDLE hFind = INVALID_HANDLE_VALUE;
	string YN;
	if ((hFind = FindFirstFileA(path.c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			cout << "Remove " << FindFileData.cFileName << "?";
			cin >> YN;
			if (YN == "Y" || YN == "y")
			{
				RemoveDirectoryA(path.c_str());
				DWORD dw = GetLastError();
				if (dw == 145)
					cout << "The directory isn't empty!" << endl;
			}
			getchar();
		}
		else {
			cout << "Remove " << FindFileData.cFileName << "? Y or N";
			cin >> YN;
			if (YN == "Y" || YN == "y")

				DeleteFileA(path.c_str());
			getchar();//取出cin流末尾的换行符
		}
	}
}

void rmdir(string path)
{
	WIN32_FIND_DATAA FindFileData = { 0 };
	HANDLE hFind = INVALID_HANDLE_VALUE;
	BOOL IsEmpty = FALSE;
	string p;
	string  file;
	static string dir = path;
	if ((hFind = FindFirstFileA(p.assign(path).append("\\*").c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0)
					rmdir(p.assign(path).append("\\").append(FindFileData.cFileName));
			}
		} while (FindNextFileA(hFind, &FindFileData) != 0);
		if (dir != path)
		{
			RemoveDirectoryA(path.c_str());
			DWORD dw = GetLastError();
			if (dw == 145)
				cout << "The directory isn't empty!" << endl;
		}
		FindClose(hFind);
	}
	else {
		FindClose(hFind);
	}
}

void rmdir_p(string path)
{
	WIN32_FIND_DATAA FindFileData = { 0 };
	HANDLE hFind = INVALID_HANDLE_VALUE;
	BOOL IsEmpty = FALSE;
	string p;
	if ((hFind = FindFirstFileA(p.assign(path).append("\\*").c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0)
					rm_R(p.assign(path).append("\\").append(FindFileData.cFileName));
			}
		} while (FindNextFileA(hFind, &FindFileData) != 0);
			RemoveDirectoryA(path.c_str());
			DWORD dw = GetLastError();
			if (dw == 145)
				cout << "The directory isn't empty!" << endl;
			else
				cout << "The directory has deleted:" << path << endl;

		FindClose(hFind);
	}
	else {
		FindClose(hFind);
	}
}

/*string getDriveStrings()
{
	char szBuf[100];
	memset(szBuf, 0, 100);
	DWORD len = GetLogicalDriveStringsA(sizeof(szBuf) / sizeof(TCHAR), szBuf);
	string s = (string)szBuf;
	return s;
}*/

void cd(string path)
{
	WIN32_FIND_DATAA FindFileData = { 0 };
	if (path == "..")
		cwd = cwd.substr(0, cwd.rfind("\\", cwd.length()));
	else if (path == "..\..")
	{
		cwd = cwd.substr(0, cwd.rfind("\\", cwd.length()));
		cwd = cwd.substr(0, cwd.rfind("\\", cwd.length()));
	}
	else if (path == "~")
		cwd = cwd.substr(0, 2);
	else
	{
		if (FindFirstFileA(path.c_str(), &FindFileData) != INVALID_HANDLE_VALUE
			&& (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			if (path.size() <= 4 && path.size() > 2)
				cwd = path.substr(0, 2);
			else
				cwd = path;
		}
		else if (GetDriveTypeA(path.c_str()) != DRIVE_NO_ROOT_DIR)
		{
			if (path.size() <= 4 && path.size() > 2)
				cwd = path.substr(0, 2);
			else
				cwd = path;
		}
		else
			cout << "The path isn't a right directory,please check again!" << endl;
	}
}
void cat(string path,BOOL pFlag)
{
	HANDLE hFile = (HANDLE)CreateFileA(path.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		NULL,
		NULL);
	DWORD filesize = GetFileSize(hFile, NULL);//源文件的长度
	DWORD dwFileSize = 1024;//每次读取的文件长度
	char *pBuffer = new char[dwFileSize];//接收读取的字节
	DWORD dwReadSize;//实际读取或写入字节数的指针，
	BOOL Flag = FALSE;
	static COORD curser_position;
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	HANDLE hOut;
	int line = 1;
	do {
		if (Flag)
		{
			SetConsoleCursorPosition(hOut, curser_position);
		}
		ReadFile(hFile,
			pBuffer,
			dwFileSize,
			&dwReadSize,
			NULL);
		if (!pFlag)
		{
			if (dwReadSize != dwFileSize)
			{
				for (int i = 0; i < dwReadSize; i++)
					cout << pBuffer[i];
				break;
			}
			else
				cout << pBuffer;
		}
		else
		{
			for (int i = 0; i < dwReadSize; i++)
			{
				cout << pBuffer[i];
				if (pBuffer[i] == '\n')
				{
					cout << line;
					line++;
				}
			}
			if (dwReadSize != dwFileSize)
				break;
		}
		Flag = TRUE;
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hOut, &bInfo);
		curser_position.X = bInfo.dwCursorPosition.X;
		curser_position.Y = bInfo.dwCursorPosition.Y;
		curser_position.X = curser_position.X-2;
		curser_position.Y = curser_position.Y;

		cout << "More--";
	} while (cin.get() == '\n');
	cout << endl;
	delete[]pBuffer;
	CloseHandle(hFile);
}

void mv(string sourcepath, string goalpath)
{
     //判断goalpath是目录还是文件
    WIN32_FIND_DATAA FindFileData_source= { 0 };
	WIN32_FIND_DATAA FindFileData_goal = { 0 };
	HANDLE hFind_source = INVALID_HANDLE_VALUE;
	HANDLE hFind_goal = INVALID_HANDLE_VALUE;
	BOOL IsEmpty = FALSE;
	string p;
	string dir, file;
	hFind_source = FindFirstFileA(p.assign(sourcepath).append("\\*").c_str(), &FindFileData_source);
	hFind_goal = FindFirstFileA(p.assign(goalpath).append("\\*").c_str(), &FindFileData_goal);

	 
	if (!(FindFileData_source.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))// source为文件
	{
		if (!(FindFileData_goal.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))// goal 为文件
			
		{
			CopyFileA(sourcepath.c_str(), goalpath.c_str(), false);
			rm(sourcepath.c_str());
	
		}
	}
	if ((FindFileData_source.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) //source为目录

	{
		if (!(FindFileData_goal.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			cout << "ERROR:NOT SUPPORTED" << endl;
		}
		else
		{
		   
			cp_R(sourcepath, goalpath);
			/*rm_R(sourcepath);*/
           
		}
	}
}
void short_find(string path, string option, string parameter)
{

	if (strcmp(option.c_str(), "-name") == 0)
	{

		long hFile = 0;
		struct _finddata_t fileinfo;  //很少用的文件信息读取结构
		string p;
		if ((hFile = _findfirst(p.assign(path).append("\\").append("*").c_str(), &fileinfo)) != -1)
		{
			num++;
			do {
				if ((fileinfo.attrib & _A_SUBDIR) && !(fileinfo.attrib &_A_HIDDEN)) {  //比较文件类型是否是文件夹
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
							FOREGROUND_BLUE);
						if (num > 0)
							cout << right << setw(num * 2) << "|";
						cout << fileinfo.name << endl;
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
							FOREGROUND_BLUE);
						short_find(p.assign(path).append("\\").append("\\").append(fileinfo.name), option, parameter);
						num--;
					}
				}
				else if (!(fileinfo.attrib & _A_HIDDEN)) {
					string temp;
					temp.append(fileinfo.name);
					int i;
					int j = 0;
					char temp_1[10] = {};
					for (i = temp.length() - 1; i > 0; i--)
					{
						if (temp[i] != '.')
						{
							temp_1[j] = temp[i];
							j++;
						}
						else
							break;
					}
					strrev(temp_1);
					temp = temp_1;

					if (strcmp(temp.c_str(), parameter.c_str()) == 0)
					{
						if (num > 0)
							cout << right << setw(num * 2) << "|";
						cout << fileinfo.name << endl;
					}

				}

			} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
			_findclose(hFile);
		}

		
	}


	else if (strcmp(option.c_str(), "-amin") == 0)
	{
		long hFile = 0;
		struct _finddata_t fileinfo;  //很少用的文件信息读取结构
		string p;
		if ((hFile = _findfirst(p.assign(path).append("\\").append("*").c_str(), &fileinfo)) != -1)
		{
			num++;
			do {
				if ((fileinfo.attrib & _A_SUBDIR) && !(fileinfo.attrib &_A_HIDDEN)) {  //比较文件类型是否是文件夹
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
							FOREGROUND_BLUE);
						if (num > 0)
							cout << right << setw(num * 2) << "|";
						cout << fileinfo.name << endl;
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
							FOREGROUND_BLUE);
						short_find(p.assign(path).append("\\").append("\\").append(fileinfo.name), option, parameter);
						num--;
					}
				}
				else if (!(fileinfo.attrib & _A_HIDDEN)) {

					time_t current_time;
					string temp = parameter;
					current_time = time(0);
					int delta_time = current_time - fileinfo.time_access;
					char temp_char = temp.at(0);
					if (temp_char == '-')
					{
						temp.erase(0, 1);
						
                     	if (delta_time < 60 * atoi(temp.c_str()))
						{
							cout << right << setw(num * 2) << "|";
							cout << fileinfo.name << endl;
						}

					}
					else if (temp_char== '+')
					{
						temp.erase(0, 1);
						
						if (delta_time > 60 * atoi(temp.c_str()))
						{
							cout << right << setw(num * 2) << "|";
							cout << fileinfo.name << endl;
                        }

					}
					else
					{
     					if (delta_time==60 * atoi(temp.c_str()))
						{
							cout << right << setw(num * 2) << "|";
							cout << fileinfo.name << endl;

						}
					}

				}

			} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
			_findclose(hFile);
		}
	}
	else if (strcmp(option.c_str(), "-mmin") == 0)
	{
		long hFile = 0;
		struct _finddata_t fileinfo;  //很少用的文件信息读取结构
		string p;
		if ((hFile = _findfirst(p.assign(path).append("\\").append("*").c_str(), &fileinfo)) != -1)
		{
			num++;
			do {
				if ((fileinfo.attrib & _A_SUBDIR) && !(fileinfo.attrib &_A_HIDDEN)) {  //比较文件类型是否是文件夹
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
							FOREGROUND_BLUE);
						if (num > 0)
							cout << right << setw(num * 2) << "|";
						cout << fileinfo.name << endl;
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
							FOREGROUND_BLUE);
						short_find(p.assign(path).append("\\").append("\\").append(fileinfo.name), option, parameter);
						num--;
					}
				}
				else if (!(fileinfo.attrib & _A_HIDDEN)) {

					time_t current_time;
					string temp = parameter;
					current_time = time(0);
					int delta_time = current_time - fileinfo.time_write;
					char temp_char = temp.at(0);
					if (temp_char == '-')
					{
						temp.erase(0, 1);

						if (delta_time < 60 * atoi(temp.c_str()))
						{
							cout << right << setw(num * 2) << "|";
							cout << fileinfo.name << endl;
						}

					}
					else if (temp_char == '+')
					{
						temp.erase(0, 1);

						if (delta_time > 60 * atoi(temp.c_str()))
						{
							cout << right << setw(num * 2) << "|";
							cout << fileinfo.name << endl;
						}

					}
					else
					{
						if (delta_time == 60 * atoi(temp.c_str()))
						{
							cout << right << setw(num * 2) << "|";
							cout << fileinfo.name << endl;

						}
					}
				}

			} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
			_findclose(hFile);
		}

	}
	else if (strcmp(option.c_str(), "-atime") == 0)
	{
		long hFile = 0;
		struct _finddata_t fileinfo;  //很少用的文件信息读取结构
		string p;
		if ((hFile = _findfirst(p.assign(path).append("\\").append("*").c_str(), &fileinfo)) != -1)
		{
			num++;
			do {
				if ((fileinfo.attrib & _A_SUBDIR) && !(fileinfo.attrib &_A_HIDDEN)) {  //比较文件类型是否是文件夹
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
							FOREGROUND_BLUE);
						if (num > 0)
							cout << right << setw(num * 2) << "|";
						cout << fileinfo.name << endl;
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
							FOREGROUND_BLUE);
						short_find(p.assign(path).append("\\").append("\\").append(fileinfo.name), option, parameter);
						num--;
					}
				}
				else if (!(fileinfo.attrib & _A_HIDDEN)) {

					time_t current_time;
					string temp = parameter;
					current_time = time(0);
					int delta_time = current_time - fileinfo.time_access;
					char temp_char = temp.at(0);
					if (temp_char == '-')
					{
						temp.erase(0, 1);

						if (delta_time < 60*60*24 * atoi(temp.c_str()))
						{
							cout << right << setw(num * 2) << "|";
							cout << fileinfo.name << endl;
						}

					}
					else if (temp_char == '+')
					{
						temp.erase(0, 1);

						if (delta_time > 60 * 60 * 24 * atoi(temp.c_str()))
						{
							cout << right << setw(num * 2) << "|";
							cout << fileinfo.name << endl;
						}

					}
					else
					{
						if (delta_time == 60 * 60 * 24 * atoi(temp.c_str()))
						{
							cout << right << setw(num * 2) << "|";
							cout << fileinfo.name << endl;

						}
					}
				}

			} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
			_findclose(hFile);
		}
	}
	else if (strcmp(option.c_str(), "-mtime") == 0)
	{
		long hFile = 0;
		struct _finddata_t fileinfo;  //很少用的文件信息读取结构
		string p;
		if ((hFile = _findfirst(p.assign(path).append("\\").append("*").c_str(), &fileinfo)) != -1)
		{
			num++;
			do {
				if ((fileinfo.attrib & _A_SUBDIR) && !(fileinfo.attrib &_A_HIDDEN)) {  //比较文件类型是否是文件夹
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
							FOREGROUND_BLUE);
						if (num > 0)
							cout << right << setw(num * 2) << "|";
						cout << fileinfo.name << endl;
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
							FOREGROUND_BLUE);
						short_find(p.assign(path).append("\\").append("\\").append(fileinfo.name), option, parameter);
						num--;
					}
				}
				else if (!(fileinfo.attrib & _A_HIDDEN)) {

					time_t current_time;
					string temp = parameter;
					current_time = time(0);
					int delta_time = current_time - fileinfo.time_write;
					char temp_char = temp.at(0);
					if (temp_char == '-')
					{
						temp.erase(0, 1);

						if (delta_time < 60*60*24*atoi(temp.c_str()))
						{
							cout << right << setw(num * 2) << "|";
							cout << fileinfo.name << endl;
						}

					}
					else if (temp_char == '+')
					{
						temp.erase(0, 1);

						if (delta_time > 60 * 60 * 24 * atoi(temp.c_str()))
						{
							cout << right << setw(num * 2) << "|";
							cout << fileinfo.name << endl;
						}

					}
					else
					{
						if (delta_time == 60 * 60 * 24 * atoi(temp.c_str()))
						{
							cout << right << setw(num * 2) << "|";
							cout << fileinfo.name << endl;

						}
					}
				}

			} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
			_findclose(hFile);
		}
	}

	else if (strcmp(option.c_str(), "-size") == 0)
	{
		long hFile = 0;
		struct _finddata_t fileinfo;  //很少用的文件信息读取结构
		string p;
		if ((hFile = _findfirst(p.assign(path).append("\\").append("*").c_str(), &fileinfo)) != -1)
		{
			num++;
			do {
				if ((fileinfo.attrib & _A_SUBDIR) && !(fileinfo.attrib &_A_HIDDEN)) {  //比较文件类型是否是文件夹
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
							FOREGROUND_BLUE);
						if (num > 0)
						{
							cout << right << setw(num * 2) << "|";
							cout << fileinfo.name << endl;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
								FOREGROUND_BLUE);
							short_find(p.assign(path).append("\\").append("\\").append(fileinfo.name), option, parameter);
							num--;
						}
					}
				}
				else if (!(fileinfo.attrib & _A_HIDDEN)) {
					string temp = parameter;
					char unit = temp.at(temp.length() - 1);
					char sign = temp.at(0);
					int number = 0;
					int currency;

					if (unit == 'b')
					{
						currency = 512;
						temp.erase(temp.end() - 1);

					}
					else if (unit == 'c')
					{
						currency = 1;
						temp.erase(temp.end() - 1);

					}
					else if (unit == 'w')
					{
						currency = 2;
						temp.erase(temp.end() - 1);
					}
					else if (unit == 'k')
					{
						currency = 1024;
						temp.erase(temp.end() - 1);

					}
					else if (unit == 'm')
					{
						currency = 1048576;
						temp.erase(temp.end() - 1);
					}
					else if (unit == 'g')
					{
						currency = 1073741824;
						temp.erase(temp.end() - 1);
					}
					else
					{
						currency = 512;
					}


					if (sign == '-')
					{
						temp.erase(0, 1);
						number = atoi(temp.c_str())*currency;
						if (fileinfo.size < number)
						{
							cout << right << setw(num * 2) << "|";
							cout << fileinfo.name << endl;
						}
					}

					else if (sign == '+')
					{
						temp.erase(0, 1);
						number = atoi(temp.c_str())*currency;
						if (fileinfo.size > number)
						{
							cout << right << setw(num * 2) << "|";
							cout << fileinfo.name << endl;
						}
					}
					else
					{
						number = atoi(temp.c_str())*currency;
						if (fileinfo.size == number)
						{
							cout << right << setw(num * 2) << "|";
							cout << fileinfo.name << endl;

						}
					}
				}

			} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
			_findclose(hFile);
		}
	}
	else if (strcmp(option.c_str(), "-empty") == 0)
	{
		long hFile = 0;
		struct _finddata_t fileinfo;  //很少用的文件信息读取结构
		string p;
		if ((hFile = _findfirst(p.assign(path).append("\\").append("*").c_str(), &fileinfo)) != -1)
		{
			num++;
			do {
				if ((fileinfo.attrib & _A_SUBDIR) && !(fileinfo.attrib &_A_HIDDEN)) {  //比较文件类型是否是文件夹
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
							FOREGROUND_BLUE);
						if (num > 0)
						{

							cout << right << setw(num * 2) << "|";
							cout << fileinfo.name << endl;

							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
								FOREGROUND_BLUE);

						}
						short_find(p.assign(path).append("\\").append("\\").append(fileinfo.name), option, parameter);
						num--;
					}
				}
				else if (!(fileinfo.attrib & _A_HIDDEN)) {
					if (fileinfo.size == 0)
					{
						cout << right << setw(num * 2) << "|";
						cout << fileinfo.name << endl;

					}
				}

			} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
			_findclose(hFile);
		}
	}
	else if (strcmp(option.c_str(), "-iname") == 0)
	{
		long hFile = 0;
		struct _finddata_t fileinfo;  //很少用的文件信息读取结构
		string p;
		if ((hFile = _findfirst(p.assign(path).append("\\").append("*").c_str(), &fileinfo)) != -1)
		{
			num++;
			do {
				if ((fileinfo.attrib & _A_SUBDIR) && !(fileinfo.attrib &_A_HIDDEN)) {  //比较文件类型是否是文件夹
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
							FOREGROUND_BLUE);
						if (num > 0)
							cout << right << setw(num * 2) << "|";
						cout << fileinfo.name << endl;
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
							FOREGROUND_BLUE);
						short_find(p.assign(path).append("\\").append("\\").append(fileinfo.name), option, parameter);
						num--;
					}
				}
				else if (!(fileinfo.attrib & _A_HIDDEN)) {
					string temp;
					temp.append(fileinfo.name);
					int i;
					int j = 0;
					char temp_1[10] = {};
					for (i = temp.length() - 1; i > 0; i--)
					{
						if (temp[i] != '.')
						{
							temp_1[j] = temp[i];
							j++;
						}
						else
							break;
					}
					strrev(temp_1);
					temp = temp_1;
					if (strcmp(temp.c_str(), parameter.c_str()) == 0)
					{
						if (num > 0)
							cout << right << setw(num * 2) << "|";
						cout << fileinfo.name << endl;
					}
				}

			} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
			_findclose(hFile);
		}
	}
	
}

void direct_find(string path, string parameter)                          //可定义Recursive_find(string path,string parameter) 复用。
{   
	long hFile = 0;
	struct _finddata_t fileinfo;  //很少用的文件信息读取结构
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\").append("*").c_str(), &fileinfo)) != -1)
	{
		num++;
		do {
			if ((fileinfo.attrib & _A_SUBDIR) && !(fileinfo.attrib &_A_HIDDEN)) {  //比较文件类型是否是文件夹
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					if (num > 0)
						cout << right << setw(num * 2) << "|";
					    cout << fileinfo.name << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					direct_find(p.assign(path).append("\\").append("\\").append(fileinfo.name), parameter);
					num--;
				}
			}
			else if (!(fileinfo.attrib & _A_HIDDEN)) {
				string temp;
				temp.append(fileinfo.name);
				if (temp.find(parameter) != string::npos)
				{
					if (num > 0)
						cout << right << setw(num * 2) << "|";
					    cout << fileinfo.name << endl;
				}
			}
       } while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
		_findclose(hFile);
	}

}
 
bool Dir_IsEmpty(string path)   //   伪代码
{
	  string cp_path;
	  cp_path.assign(path).append("(1)");
	  CreateDirectoryA(cp_path.c_str(), NULL);
       cp_R(path, cp_path);
		if (RemoveDirectoryA(cp_path.c_str()))
			return true;
		else
			return false;
}
void find_newerfile(string path,string parameter)
{
	recursive_find_1(path, parameter);

	if (flag_num == 1)
		recursive_find_2(path, cmp_time);
	else
	{
		cout << "ERROR:Input file name is not unique" << endl;
	}
	    flag_num = 0;

}
void recursive_find_1(string path, string parameter) {
	long hFile = 0;
	struct _finddata_t fileinfo;  //很少用的文件信息读取结构
	string p;

	if ((hFile = _findfirst(p.assign(path).append("\\").append("*").c_str(), &fileinfo)) != -1)
	{
		num++;
		do {
			if ((fileinfo.attrib & _A_SUBDIR) && !(fileinfo.attrib &_A_HIDDEN)) {  //比较文件类型是否是文件夹
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {

					recursive_find_1(p.assign(path).append("\\").append("\\").append(fileinfo.name), parameter);
					num--;
				}
			}
			else if (!(fileinfo.attrib & _A_HIDDEN)) {
				if (strcmp(fileinfo.name, parameter.c_str()) == 0)
				{
					flag_num++;

					cmp_time = int(fileinfo.time_write);

				}

			}

		} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
		_findclose(hFile);
	}
}
void recursive_find_2(string path, int time)
{
	long hFile = 0;
	struct _finddata_t fileinfo;  //很少用的文件信息读取结构
	string q;

	if ((hFile = _findfirst(q.assign(path).append("\\").append("*").c_str(), &fileinfo)) != -1)
	{
		num++;
		do {
			if ((fileinfo.attrib & _A_SUBDIR) && !(fileinfo.attrib &_A_HIDDEN)) {  //比较文件类型是否是文件夹
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					if (num > 0)
						cout << right << setw(num * 2) << "|";
					cout << fileinfo.name << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					recursive_find_2(q.assign(path).append("\\").append("\\").append(fileinfo.name), time);
					num--;
				}
			}
			else if (!(fileinfo.attrib & _A_HIDDEN)) {


				if (fileinfo.time_write > time)
				{
					cout << right << setw(num * 2) << "|";
					cout << fileinfo.name << endl;
				}
			}

		} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
		_findclose(hFile);
	}
}
int depth;
void  find_maxdepth(string path, string parameter){

    long hFile = 0;
	struct _finddata_t fileinfo;  //很少用的文件信息读取结构
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
	    depth++;
		do {
			if ((fileinfo.attrib & _A_SUBDIR) && !(fileinfo.attrib &_A_HIDDEN)) {  //比较文件类型是否是文件夹
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					if (depth > 1)
						cout << right << setw(depth * 2) << "|";
					cout << fileinfo.name << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					if (depth < atoi(parameter.c_str())+1)
					{
						find_maxdepth(p.assign(path).append("\\").append("\\").append(fileinfo.name),parameter);
						depth--;
					}
				}
			}
			else if (!(fileinfo.attrib & _A_HIDDEN)) {
				if (depth > 1)
					cout << right << setw(depth * 2) << "|";
				cout << fileinfo.name << endl;
			}

		} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
		_findclose(hFile);
	}

}
void  find_mindepth(string path, string parameter)
{
	long hFile = 0;
	struct _finddata_t fileinfo;  //很少用的文件信息读取结构
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		depth++;
		do {
			if ((fileinfo.attrib & _A_SUBDIR) && !(fileinfo.attrib &_A_HIDDEN)) {  //比较文件类型是否是文件夹
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
					if (depth > 1)
						cout << right << setw(depth * 2) << "|";
					cout << fileinfo.name << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
						FOREGROUND_BLUE);
                       find_mindepth(p.assign(path).append("\\").append("\\").append(fileinfo.name), parameter);
					depth--;

				}
			}
			else if (!(fileinfo.attrib & _A_HIDDEN)) {
				if (depth > atoi(parameter.c_str()))
				{
					if (depth > 1)
					{
						cout << right << setw(depth * 2) << "|";
					}
					cout << fileinfo.name << endl;
				}
			}

		} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
		_findclose(hFile);

	}
}
void find_maxdepth_1(string path, string parameter)
{
	depth = 0;
	find_maxdepth( path,  parameter);

}
void find_mindepth_1(string path, string parameter)
{
	depth = 0;
	find_mindepth(path, parameter);
}
bool complex_find_name(struct _finddata_t file, string name)
{
	if (name == "")
		return true;
	else
	{
		string temp;
		temp.append(file.name);
		int i;
		int j = 0;
		char temp_1[10] = {};
		for (i = temp.length() - 1; i > 0; i--)
		{
			if (temp[i] != '.')
			{
				temp_1[j] = temp[i];
				j++;
			}
			else
				break;
		}
		strrev(temp_1);
		temp = temp_1;
		if (strcmp(temp.c_str(), name.c_str()) == 0)
			return true;
		else
			return false;
	}

}
bool complex_find_size(struct _finddata_t file, string size)
{
	if (size == "")
		return true;
	else
	{
		string temp = size;
		char unit = temp.at(temp.length() - 1);
		char sign = temp.at(0);
		int number = 0;
		int currency;

		if (unit == 'b')
		{
			currency = 512;
			temp.erase(temp.end() - 1);

		}
		else if (unit == 'c')
		{
			currency = 1;
			temp.erase(temp.end() - 1);

		}
		else if (unit == 'w')
		{
			currency = 2;
			temp.erase(temp.end() - 1);
		}
		else if (unit == 'k')
		{
			currency = 1024;
			temp.erase(temp.end() - 1);

		}
		else if (unit == 'm')
		{
			currency = 1048576;
			temp.erase(temp.end() - 1);
		}
		else if (unit == 'g')
		{
			currency = 1073741824;
			temp.erase(temp.end() - 1);
		}
		else
		{
			currency = 512;
		}
		if (sign == '-')
		{
			temp.erase(0, 1);
			number = atoi(temp.c_str())*currency;
			if (file.size < number)
				return true;		
		}

		else if (sign == '+')
		{
			temp.erase(0, 1);
			number = atoi(temp.c_str())*currency;
			if (file.size > number)
				return true;
		}
		else
		{
			number = atoi(temp.c_str())*currency;
			if (file.size == number)   
				return true;
		}
}















































































































































































































































	












































































































































































































































































































