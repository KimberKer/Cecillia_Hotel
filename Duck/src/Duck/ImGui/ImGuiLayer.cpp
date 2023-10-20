//---------------------------------------------------------
// File:		ImGuiLayer.cpp
// 
// authors:		Rina Firdianna binte Raihan
// email:		rinafirdiana.b\@digipen.edu
//
// Brief:      Integration of ImGui for GUI rendering.
//
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "duckpch.h"
#include "imgui.h"
#include "ImGuiLayer.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Duck/Application.h"
#include "imgui_internal.h" //for drag and drop functionality


//temp
#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace Duck {
	ImGuiLayer::ImGuiLayer(std::shared_ptr<MapDataHandler> map) : Layer("ImGuiLayer")
	{
		m_map = map;
	}
	ImGuiLayer::~ImGuiLayer()
	{
	}

	/******************************************************************************/
	/*!
		This function Initializes ImGui, sets up style, and binds platform/renderer.
	 */
	 /******************************************************************************/
	void ImGuiLayer::OnAttach()
	{

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	/******************************************************************************/
	/*!
		This function shuts down ImGui and its context.
	 */
	 /******************************************************************************/
	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	/******************************************************************************/
	/*!
		This function starts a new ImGui frame, prepares for rendering.
	 */
	 /******************************************************************************/
	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_PassthruCentralNode);
		
	}

	void ImGuiLayer::CreateObjects()
	{

		ImGui::Begin("Create Objects");
		ImGui::SeparatorText("Objects");
		//radio
		static int selectedOption = 3; //1= false, 0 = true
		ImGui::RadioButton("Wall", &selectedOption, 0); ImGui::SameLine();
		ImGui::RadioButton("Ghost", &selectedOption, 1); ImGui::SameLine();
		ImGui::RadioButton("Player", &selectedOption, 2);
		OBJ_TYPE obj;
		if (selectedOption == 0) {
			obj = OBJ_OBJ;
		}
		else if (selectedOption == 1) {
			obj = OBJ_GHOST;
		}
		else if (selectedOption == 2) {
			obj = OBJ_PLAYER;
		}
		int x_min_value = 0;  // Set your minimum value here
		int y_min_value = 0;  // Set your minimum value here
		int max_w_value = m_map->GetWidth();
		int max_h_value = m_map->GetHeight();


		ImGui::Text("X value");
		static int y_value{1};
		static int x_value{1};

		if (ImGui::InputInt("X", &x_value, 1))
		{
			// Check and enforce the minimum and maximum values
			if (x_value < x_min_value)
				x_value = x_min_value;
			else if (x_value > max_w_value)
				x_value = max_w_value;
		}
		ImGui::Text("Y value");

		if (ImGui::InputInt("Y", &y_value, 1))
		{
			// Check and enforce the minimum and maximum values
			if (y_value < y_min_value)
				y_value = y_min_value;
			else if (y_value > max_h_value)
				y_value = max_h_value;
		}
		//ImGui::SameLine();
		//button
		//ImGui::SameLine();
		ImGui::PushID(1);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(4 / 7.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(4 / 7.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(4 / 7.0f, 0.8f, 0.8f));
		if (ImGui::Button("Add Object")) {
			m_map->UpdateCellData(m_map->GetFile(), x_value, y_value, obj);
		}
		ImGui::PopStyleColor(3);
		ImGui::PopID();



		ImGui::End();
	}

	/******************************************************************************/
	/*!
		This function handles events, prevents ImGui from capturing input when necessary.
	 */
	 /******************************************************************************/
	void ImGuiLayer::OnEvent(Event& e)
	{
		if (m_BlockEvents)
		{
			ImGuiIO& io = ImGui::GetIO();
			e.Handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
			e.Handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
		}
	}

	/******************************************************************************/
	/*!
		This function ends the ImGui frame, renders ImGui and platform windows.
	 */
	 /******************************************************************************/
	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}


	/******************************************************************************/
	/*!
		This function renders ImGui demo window if needed.
	 */
	 /******************************************************************************/

	void ImGuiLayer::OnImGuiRender()
	{
		static bool show = true;
		CreateObjects();
		//ImGui::ShowDemoWindow(&show);

	}







	//------------FOR DRAG AND DROP---------------------
	// Implement the functions in your ImGuiLayer.cpp file
	void ImGuiLayer::HandleDragAndDropTarget()
	{
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("YOUR_PAYLOAD_TYPE"))
			{
				// Handle the dropped data here.
				// You can access the payload data using payload->Data and payload->DataSize.
			}
			ImGui::EndDragDropTarget();
		}
	}

	void ImGuiLayer::InitiateDragAndDropSource()
	{
		if (ImGui::BeginDragDropSource())
		{
			// Set the payload data (e.g., a pointer to the object being dragged).
			// UNCOMMENT THE LINE BELOW VVVVV
			//ImGui::SetDragDropPayload("YOUR_PAYLOAD_TYPE", &yourData, sizeof(yourData));

			// Display the text or image that represents the draggable item.
			ImGui::Text("Drag me");

			ImGui::EndDragDropSource();
		}
	}
	//------------FOR DRAG AND DROP---------------------





}