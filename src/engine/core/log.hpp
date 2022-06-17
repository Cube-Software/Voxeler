#pragma once

#include "../fr.hpp"
#include "../vendor/termcolor.hpp"

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

namespace fr {
	namespace Log {
		inline void ErrorLog(std::string log) { std::cout << termcolor::red << "[ERROR] " << log << termcolor::white << std::endl; }
		inline void WarnLog(std::string log) { std::cout << termcolor::bright_magenta << "[WARN] " << log << termcolor::white << std::endl; }
		inline void InfoLog(std::string log) {
		#ifndef FR_BULID
			std::cout << "[" << termcolor::bright_green << " OK " << "] " << termcolor::white << log.CString() << std::endl; 
		#endif
		}
	}
}

#define INFO(...) fr::Log::InfoLog(__VA_ARGS__)
#define FR_ERROR(...) fr::Log::ErrorLog(__VA_ARGS__)
#define WARNING(...) fr::Log::WarnLog(__VA_ARGS__)