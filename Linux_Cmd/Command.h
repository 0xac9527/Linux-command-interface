#pragma once
#include "pch.h"
#include<istream>
#include<iostream>
#include <string>
#include <io.h>
#include <time.h>
#include<iomanip>
#include <windows.h>




using namespace std;

extern int num;
extern string cwd;
extern void ls(string path);
extern void ls_l(string path);
extern void ls_a(string path);
extern void ls_d(string path);
extern void ls_A(string path);
extern void ls_R(string path);
extern void ls_m(string path);
extern void Mkdir(string folderpath);
extern void Mkdir_p(string path);
extern void Mkdir_m(string folderpath, string num);
extern void touch(string filename);
extern void touch_a(string folderpath);
extern void touch_m(string folderpath);
extern void touch_r(string folderpath);
extern void touch_d(string filepath, const char* ptime);
extern void cp(string filepath1, string filepath2);
extern void cp_R(string filepath1, string filepath2);
extern void rm_R(string path);
extern void rm(string path);
extern void rm_i(string path);
extern void rmdir(string path);
extern void rmdir_p(string path);
extern void cd(string path);
extern void cat(string path,BOOL pFlag);
extern void mv(string sourcepath, string goalpath);
extern void short_find(string path, string option, string parameter);
extern void direct_find(string path, string parameter);
extern bool Dir_IsEmpty(string path);
extern  void recursive_find_1(string path, string parameter);
extern void find_newerfile(string path, string parameter);
extern void recursive_find_2(string path, int time);
extern void  find_maxdepth(string path,string parameter);
extern void  find_mindepth(string path,string parameter);
extern void find_maxdepth_1(string path, string parameter);
extern void  find_mindepth_1(string path, string parameter);
extern void complex_find(string path, string name, string size, string iname, string maxdepth, string mindepth, string atime, string amin,string mtime, string mmin, string newer, string empty);
extern void complex_find_depth(string path, string name, string size, string iname, string maxdepth, string mindepth, string atime, string amin, string mtime, string mmin, string newer, string empty);
extern bool complex_find_size(struct _finddata_t file, string size);
extern bool complex_find_empty(struct _finddata_t file, string empty);
extern bool complex_find_iname(struct _finddata_t file, string iname);
extern bool complex_find_name(struct _finddata_t file, string name);
extern bool complex_find_newer(struct _finddata_t file, string path, string newer);
extern bool complex_find_maxdepth(string maxdepth);
extern bool complex_find_mindepth(string mindepth);
extern bool complex_find_atime(struct _finddata_t file, string atime);
extern bool complex_find_mtime(struct _finddata_t file, string mtime);
extern bool complex_find_amin(struct _finddata_t file, string amin);
extern bool complex_find_mmin(struct _finddata_t file, string mmin);
extern bool find_time(struct _finddata_t file, string time_option, string time_str);
extern void find_time_print(struct _finddata_t file, string time_option, string time_str);
