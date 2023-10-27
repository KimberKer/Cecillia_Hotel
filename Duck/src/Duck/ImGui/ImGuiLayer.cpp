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
#include "Duck/Log.h"
#include "imgui_internal.h" //for drag and drop functionality


//temp
#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace Duck {

	ImGuiLayer::ImGuiLayer(std::vector<std::shared_ptr<MapDataHandler>> maplist, std::vector<std::shared_ptr<GameObject>> objectlist) : Layer("ImGuiLayer")
	{
		m_maplist = maplist;

		for (int i{}; i < objectlist.size(); i++) {
			if (objectlist[i]->getObj() == OBJ_PLAYER) {
				p_player = objectlist[i];
			}
		}
		m_objList = objectlist;

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
	void ImGuiLayer::TabDisplayGameObjects() {
		if (ImGui::CollapsingHeader("GameObjects Info", ImGuiTreeNodeFlags_None))
		{

			ImGui::SeparatorText("GameObjects:");

			ImGui::BulletText("Number of Player: %d", m_maplist[GetMapIndex()]->GetNumberOfObjects(OBJ_PLAYER));
			ImGui::BulletText("Number of Ghost: %d", m_maplist[GetMapIndex()]->GetNumberOfObjects(OBJ_GHOST));
			ImGui::BulletText("Number of Walls: %d", m_maplist[GetMapIndex()]->GetNumberOfObjects(OBJ_OBJ));
			ImGui::BulletText("Number of NPC: %d", m_maplist[GetMapIndex()]->GetNumberOfObjects(OBJ_NPC));

			//total
			int totalCount = m_maplist[GetMapIndex()]->GetNumberOfObjects(OBJ_OBJ) +
				m_maplist[GetMapIndex()]->GetNumberOfObjects(OBJ_GHOST) +
				m_maplist[GetMapIndex()]->GetNumberOfObjects(OBJ_PLAYER) +
				m_maplist[GetMapIndex()]->GetNumberOfObjects(OBJ_NPC);

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + additionalSpacing); //spacing
			ImGui::BulletText("Total Number of Objects: %d", totalCount);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + additionalSpacing); //spacing

		}
	}
	void ImGuiLayer::TabCreateGameObj() {

		if (ImGui::CollapsingHeader("Adding/Removing Objects", ImGuiTreeNodeFlags_None))
		{
			ImGui::SeparatorText("Objects");

			//------------Radio Button---------------------------
			static int selectedOption = 3; //1= false, 0 = true
			ImGui::RadioButton("Wall", &selectedOption, 0); ImGui::SameLine();
			ImGui::RadioButton("Ghost", &selectedOption, 1); ImGui::SameLine();
			ImGui::RadioButton("Empty", &selectedOption, 2);
			OBJ_TYPE obj = OBJ_EMPTY;
			if (selectedOption == 0) { //wall
				obj = OBJ_OBJ;
			}
			else if (selectedOption == 1) { //ghost 
				obj = OBJ_GHOST;
			}
			else if (selectedOption == 2) { //ghost 
				obj = OBJ_EMPTY;
			}


			//------------Input text values---------------------------
			int x_min_value = 0;  // Set your minimum value here
			int y_min_value = 0;  // Set your minimum value here
			int max_w_value = m_maplist[GetMapIndex()]->GetWidth();
			int max_h_value = m_maplist[GetMapIndex()]->GetHeight();


			ImGui::Text("X value");
			static int y_value{ 1 };
			static int x_value{ 1 };

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

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + additionalSpacing);
			//------------Button---------------------------

			ImGui::PushID(1);

			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(4 / 7.0f, 0.6f, 0.6f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(4 / 7.0f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(4 / 7.0f, 0.8f, 0.8f));

			ImVec2 tabContentRegion = ImGui::GetContentRegionAvail();
			float buttonWidth = tabContentRegion.x;
			float buttonX = (tabContentRegion.x - buttonWidth) * 0.5f;
			ImGui::SetCursorPosX(buttonX);

			if (ImGui::Button("Add Object", ImVec2(buttonWidth, 20))) {
				if (p_player->getX() == x_value - 1 && p_player->getY() == y_value - 1) {
					DUCK_CORE_ERROR("Error: Change the player position first!");
				}
				else {
					m_maplist[GetMapIndex()]->UpdateCellData( x_value - 1, y_value - 1, obj);
					std::cout << m_objList.size() << std::endl;
					//change the state
					m_objList[(x_value - 1) * m_maplist[GetMapIndex()]->GetWidth() + (y_value - 1)]->SetType(obj);


				}
				
				//ExampleLayer::InitializeGame();

			}

			if (ImGui::IsItemClicked()) {
				ImGui::SetKeyboardFocusHere(-1);
			}
			ImGui::PopStyleColor(3);
			ImGui::PopID();

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + additionalSpacing);



		}
	}
	void ImGuiLayer::TabUpdatePlayer() {
		if (ImGui::CollapsingHeader("Replace Player Current Position", ImGuiTreeNodeFlags_None))
		{
			int x_min_pvalue = 0;  // Set your minimum value here
			int y_min_pvalue = 0;  // Set your minimum value here
			int max_w_pvalue = m_maplist[GetMapIndex()]->GetWidth();
			int max_h_pvalue = m_maplist[GetMapIndex()]->GetHeight();


			ImGui::Text("X Player value");
			static int y_pvalue{ 1 };
			static int x_pvalue{ 1 };

			if (ImGui::InputInt("X position", &x_pvalue, 1))
			{
				// Check and enforce the minimum and maximum values
				if (x_pvalue < x_min_pvalue)
					x_pvalue = x_min_pvalue;
				else if (x_pvalue > max_w_pvalue)
					x_pvalue = max_w_pvalue;
			}
			ImGui::Text("Y Player value");

			if (ImGui::InputInt("Y position", &y_pvalue, 1))
			{
				// Check and enforce the minimum and maximum values
				if (y_pvalue < y_min_pvalue)
					y_pvalue = y_min_pvalue;
				else if (y_pvalue > max_h_pvalue)
					y_pvalue = max_h_pvalue;
			}

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + additionalSpacing);
			ImGui::PushID(1);

			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(4 / 7.0f, 0.6f, 0.6f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(4 / 7.0f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(4 / 7.0f, 0.8f, 0.8f));


			ImVec2 tabContentRegion = ImGui::GetContentRegionAvail();
			float buttonWidth = tabContentRegion.x;
			float buttonX = (tabContentRegion.x - buttonWidth) * 0.5f;
			ImGui::SetCursorPosX(buttonX);

			if (ImGui::Button("Update Player Position", ImVec2(buttonWidth, 20))) {
				//make original position of the player empty
				if (m_maplist[GetMapIndex()]->UpdateCellData( p_player->getX(), p_player->getY(), OBJ_EMPTY)) {

					//change to the new position
					m_objList[(x_pvalue - 1) * m_maplist[GetMapIndex()]->GetWidth() + (y_pvalue - 1)]->SetType(OBJ_EMPTY);
					m_maplist[GetMapIndex()]->UpdateCellData( x_pvalue - 1, y_pvalue - 1, OBJ_PLAYER);
					p_player->SetPositionX(x_pvalue - 1);
					p_player->SetPositionY(y_pvalue - 1);

				}



			}

			ImGui::PopStyleColor(3);
			ImGui::PopID();



			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + additionalSpacing);
		}

	}

	void ImGuiLayer::CreateObjects()
	{

		ImGui::Begin("Objects");
		TabDisplayGameObjects();
		TabUpdatePlayer();
		TabCreateGameObj();

		ImGui::End();
	}

	void ImGuiLayer::MapData()
	{

		ImGui::Begin("Map");
		
		ImGui::End();
	}
	void ImGuiLayer::Console()
	{

		ImGui::Begin("Console");
		ImGui::Text("Console Output:");
		ImGui::Separator();

		// Update the text area with console messages
	/*	for (const auto& message : consoleMessages) {
			ImGui::TextWrapped("%s", message.c_str());
		}*/

		ImGui::End();
	}


	void ImGuiLayer::DisplayFPS(double &fps)
	{
		ImGui::Begin("FPS");
		ImGui::Text("FPS: %.2f", fps);

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

	void ImGuiLayer::OnImGuiRender(double &fps)
	{

		// Start a new frame
		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("Game")) {
				if (isGamePlaying) {
					if (ImGui::MenuItem("Pause")) {
						isGamePlaying = false;
					}
				}
				else {
					if (ImGui::MenuItem("Resume")) {
						isGamePlaying = true;
					}
				}
				if (ImGui::MenuItem("Quit")) {
					// Handle "Save" action
					Application::Get().SetRunning(false);
				}
				ImGui::EndMenu();
			}

			// Add more menus and menu items as needed

			ImGui::EndMainMenuBar();
		}

		// Add your GUI content here
	

		CreateObjects();
		DisplayFPS(fps);
		//ImGui::ShowDemoWindow(&show);

	}
	//------------FOR DRAG AND DROP---------------------










	

}