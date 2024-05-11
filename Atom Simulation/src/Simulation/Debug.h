#pragma once

#include "iostream"

// General macros
#define AS_ASSERT(x) if (!(x)) __debugbreak();

// Only debug macros
#ifdef AS_DEBUG

#define AS_LOG(message) std::cout << message << std::endl;

#else

#define AS_LOG 

#endif
