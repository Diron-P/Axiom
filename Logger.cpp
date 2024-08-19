#include "Logger.h"

Logger& Logger::Get()
{
	static Logger logger;
	return logger;
}

Logger::Logger()
	: m_level(Level::Debug)
{
}
