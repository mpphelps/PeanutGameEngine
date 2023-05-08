#include "log.h"

namespace peanut {
	Log::Log(std::string path)
	{
		log.open(path);
		logLevel = Info;
		logLevelDictionary[Info] = "Info";
		logLevelDictionary[Debug] = "Debug";
		logLevelDictionary[Warning] = "Warning";
		logLevelDictionary[Severe] = "Severe";
		logLevelDictionary[Fatal] = "Fatal";
	}
	Log::~Log()
	{
		log.close();
	}
	void Log::Write(std::string message, LogLevel level)
	{
		if (level >= logLevel)
			log << logLevelDictionary[level] << ": " << message << "\n";
	}

	void Log::SetLogLevel(LogLevel level) {
		logLevel = level;
	}
}