#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <Windows.h>

// TODO
//class ConsoleLogHandler
//{
//public:
//
//	void Log();
//};

class Logger
{
	enum class Level : unsigned char
	{
		Fatal,
		Error,
		Warn,
		Info,
		Debug,
		Trace		
	};

public:
	template<typename... Args>
	void LogFatal(const char* msg, Args const&... args) 
	{ 
		Log(Level::Fatal, msg, args...); 
	};

	void LogError(const char* msg, ...) { Log(Level::Error, msg); };
	void LogWarn(const char* msg, ...) { Log(Level::Warn, msg); };
	void LogInfo(const char* msg, ...) { Log(Level::Info, msg); };
	void LogDebug(const char* msg, ...) { Log(Level::Debug, msg); };
	void LogTrace(const char* msg, ...) { Log(Level::Trace, msg); };

	template<typename... Args>
	void Log(Level level, const char* msg, Args const&... args)
	{
		char buffer[100];
		
		int result = snprintf(buffer, 100, msg, args...);
		OutputDebugStringA(buffer);
	}

	static Logger& Get();

private:
	Logger();

	Level m_level;
};

#endif