#include <Duck.h>
#include "imgui/imgui.h"

class ExampleLayer : public Duck::Layer
{
public:
	ExampleLayer() : Layer("Example") {

	}

	void OnUpdate() override {
		if (Duck::Input::IsKeyPressed(Duck::Key::Tab)) {
			DUCK_INFO("Tab key is pressed! (Poll)");
		}
	}
	void yomama() {

	}
	virtual void OnImGuiRender()
	{
		ImGui::Begin("test");
		ImGui::Text("Hello World");
		ImGui::End();

	}

	void OnEvent(Duck::Event& event) override {
		//DUCK_TRACE("{0}", event);

		if (event.GetEventType() == Duck::EventType::KeyPressed) {
			Duck::KeyPressedEvent& e = (Duck::KeyPressedEvent&)event;

			if (e.GetKeyCode() == Duck::Key::Tab) {
				DUCK_INFO("Tab key is pressed! (Event)");
			}

			DUCK_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Duck::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

Duck::Application* Duck::CreateApplication() {
	return new Sandbox();
}