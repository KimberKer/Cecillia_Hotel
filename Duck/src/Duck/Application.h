#pragma once
#include "Core.h"
#include <iostream>
//#include <GLFW/glfw3.h>
#include "De-serialize/GameObject.h"
#include "Logging/Logging.h"
#include "Events/Event.h"
#include "Window.h"
#include "Duck/LayerStack.h"
#include "Duck/Events/ApplicationEvent.h"
#include "Duck/Graphics/Shader.h"
#include "Duck/Graphics/Buffer.h"
#include "Duck/Graphics/Vertex.h"
#include "Duck/Graphics/Renderer.h"


namespace Duck {
	class DUCK_API Application {
	public:
		Application();
		virtual ~Application();
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;


		std::shared_ptr<Shader> m_Shader; 
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

		std::shared_ptr<VertexArray> m_SquareVA;
		std::shared_ptr<Shader> m_SquareShader;

		std::shared_ptr<VertexArray> m_PointVA;
		std::shared_ptr<Shader> m_PointShader;

		std::shared_ptr<VertexArray> m_LineVA;
		std::shared_ptr<Shader> m_LineShader;

		glm::mat4 m_SquareTransform;
		glm::mat4 m_TriangleTransform;
		glm::mat4 m_PointTransform;
		glm::mat4 m_LineTransform;



	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


 GLFWwindow* window;
 