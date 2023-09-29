//---------------------------------------------------------
// File:    EntryPoint.h
//authors:	Kimber Ker Soon Kiat
// email:	s.ker\@digipen.edu
// 
//
// Brief:     Contains the main entry point
//
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once

#ifdef DUCK_PLATFORM_WINDOWS

extern Duck::Application* Duck::CreateApplication();

int main(int argc, char** argv) {
	Duck::Log::Init();
	DUCK_CORE_WARN("Initialized Log!");

	auto app = Duck::CreateApplication();
	app->Run();
	delete app;
}

#endif