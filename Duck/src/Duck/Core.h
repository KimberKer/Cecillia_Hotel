#pragma once

#ifdef DUCK_PLATFORM_WINDOWS
	#ifdef DUCK_BUILD_DLL
		#define DUCK_API __declspec(dllexport)
	#else
		#define DUCK_API __declspec(dllimport)
	#endif
#else
	#error Duck Engine only supports Windows!
#endif

#define BIT(x) (1 << x)