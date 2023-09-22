#pragma once

#ifdef DUCK_PLATFORM_WINDOWS

extern Duck::Application* Duck::CreateApplication();

int main(int argc, char** argv) {
	auto app = Duck::CreateApplication();
	app->Run();
	delete app;
}

#endif