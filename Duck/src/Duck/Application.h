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
#include "Duck/ImGui/ImGuiLayer.h"

#include "Duck/Graphics/Shader.h"
#include "Duck/Graphics/Buffer.h"
#include "Duck/Graphics/Vertex.h"
#include "Duck/Graphics/Renderer.h"



namespace Duck {
	class  Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline Window& GetWindow() { return *m_Window; }
		
		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;


/////////////////////////// MAHDI ////////////////////////////////////
///																   ///


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


		std::shared_ptr<VertexArray> m_SquareImgVA;
		std::shared_ptr<Shader> m_SquareImgShader;
		std::shared_ptr<Shader> m_BackgroundImgShader;

		std::shared_ptr<VertexArray> m_SquareSprVA;
		std::shared_ptr<Shader> m_SquareSprShader;

		uint32_t m_CharacterTexture;
		uint32_t m_BackgroundTexture;
		//glm::vec2<*int> m_TextureDim;
		uint32_t m_Sprite;
		int m_SpriteWidth, m_SpriteHeight;



		glm::mat4 m_SquareTransform;
		glm::mat4 m_TriangleTransform;
		glm::mat4 m_PointTransform;
		glm::mat4 m_LineTransform;
		glm::mat4 m_SquareImgTransform;
		glm::mat4 m_SquareSprTransform;


///																   ///
/////////////////////////// MAHDI ////////////////////////////////////



	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

 //GLFWwindow* window;