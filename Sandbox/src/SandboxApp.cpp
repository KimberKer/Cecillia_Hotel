#include <Duck.h>
#include "imgui/imgui.h"
#include "Duck/Time.h"

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

	void OnImGuiRender() override
	{
		Duck::Time time;

		time.start_frame();
		time.end_frame();
		double dt = time.get_delta_time();
		ImGui::Begin("FrameRate");
		ImGui::Text("FPS: %d", 1.0f/dt);
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