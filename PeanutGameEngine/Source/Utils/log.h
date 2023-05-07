#pragma once
#include <fstream>
#include <string>
#include <map>

namespace peanut {
	enum LogLevel {
		Info,
		Debug,
		Warning,
		Severe,
		Fatal
	};

	class Log {
	public:

	private:
		std::ofstream log;
		std::map<LogLevel, std::string> logLevelDictionary;
		LogLevel logLevel;
		 
	public:
		Log(std::string path);
		~Log();
		void Write(std::string message, LogLevel level);
		void SetLogLevel(LogLevel level);

	private:

	};
}


