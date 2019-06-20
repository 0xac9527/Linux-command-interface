#include "pch.h"
#include "Logger.h"
#include <cstdlib>
#include<string>
#include <ctime>
using namespace std;
std::ofstream Logger::m_error_log_file;
std::ofstream Logger::m_info_log_file;
std::ofstream Logger::m_warn_log_file;

void initLogger(const std::string&info_log_filename,
	const std::string&warn_log_filename,
	const std::string&error_log_filename) {
	Logger::m_info_log_file.open(info_log_filename.c_str());
	Logger::m_warn_log_file.open(warn_log_filename.c_str());
	Logger::m_error_log_file.open(error_log_filename.c_str());
}

std::ostream & Logger::getStream(log_rank_t log_rank) {
	return (INFO == log_rank) ?
		(m_info_log_file.is_open() ? m_info_log_file : std::cout) :
		(WARNING == log_rank ?
		(m_warn_log_file.is_open() ? m_warn_log_file : std::cerr) :
			(m_error_log_file.is_open() ? m_error_log_file : std::cerr));
}

std::ostream & Logger::start(log_rank_t log_rank,
	const int line,
	const std::string&function) {
	string t;
	time_t rawtime;
	struct tm * timeinfo;
	char s[100];
	time(&rawtime);

	timeinfo = localtime(&rawtime);
	time_t tick = mktime(timeinfo);

	int Year = timeinfo->tm_year + 1900;
	int Mon = timeinfo->tm_mon + 1;
	int Day = timeinfo->tm_mday;
	int Hour = timeinfo->tm_hour;
	int Min = timeinfo->tm_min;
	int Second = timeinfo->tm_sec;

	t.append(to_string(Year)).append("-").append(to_string(Mon)).append("-").append(to_string(Day))
		.append(" ").append(to_string(Hour)).append(":").append(to_string(Min)).append(":").append(to_string(Second));

	return getStream(log_rank) << t
		<< "function (" << function << ")"
		<< "line " << line
		<< std::flush;
}

Logger::~Logger() {
	getStream(m_log_rank) << std::endl << std::flush;

	if (FATAL == m_log_rank) {
		m_info_log_file.close();
		m_info_log_file.close();
		m_info_log_file.close();
		abort();
	}
}
