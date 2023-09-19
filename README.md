# OpenGL Mathematics

Code Sample:
```cpp
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

glm::mat4 camera(float Translate, glm::vec2 const & Rotate) {
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
    glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
    View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
    View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));

    return Projection * View * Model;
}
```

# Logging
5 types of logging you can use.
```cpp
DUCK_TRACE
DUCK_INFO
DUCK_WARN
DUCK_ERROR
DUCK_FATAL
```
To log into console,
```cpp
void OnUpdate() override {
	if (Duck::Input::IsKeyPressed(Duck::Key::Tab)) {
		DUCK_INFO("Tab key is pressed! (Poll)");
	}
}
```
```cpp
void OnEvent(Duck::Event& event) override {
	if (event.GetEventType() == Duck::EventType::KeyPressed) {
		Duck::KeyPressedEvent& e = (Duck::KeyPressedEvent&)event;

		if (e.GetKeyCode() == Duck::Key::Tab) {
			DUCK_INFO("Tab key is pressed! (Event)");
		}

		DUCK_TRACE("{0}", (char)e.GetKeyCode());
	}
}
```
