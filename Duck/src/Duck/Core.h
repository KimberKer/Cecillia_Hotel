//---------------------------------------------------------
// File:    Core.h
//authors:	Kimber Ker Soon Kiat
// email:	s.ker\@digipen.edu
// 
//
// Brief:	Contains the fundamental macros and platform-specific 
//			definitions for the Duck Engine project
//
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once

#ifdef DUCK_PLATFORM_WINDOWS
#if DUCK_DYNAMIC_LINK
	#ifdef DUCK_BUILD_DLL
		#define DUCK_API __declspec(dllexport)
	#else
		#define DUCK_API __declspec(dllimport)
	#endif
#else
	#define DUCK_API
#endif
#else
	#error Duck Engine only supports Windows!
#endif

#ifdef DUCK_DEBUG
	#define DUCK_ENABLE_ASSERTS
#endif

#ifdef DUCK_ENABLE_ASSERTS
	#define DUCK_ASSERT(x, ...)			{ if(!(x)) { DUCK_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define DUCK_CORE_ASSERT(x, ...)	{ if(!(x)) { DUCK_CORE_ERROR("Assertion Fialed: {0}", __VA_ARGS__); __debugbreak();} }
#else
	#define DUCK_ASSERT(x, ...)
	#define DUCK_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define DUCK_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)