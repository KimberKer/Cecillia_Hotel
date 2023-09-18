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