//---------------------------------------------------------
// File:		ImGuiLayer.cpp
// 
// authors:		Rina Firdianna binte Raihan
// email:		rinafirdiana.b\@digipen.edu
//
// Brief:      Integration of ImGui for GUI rendering.
//
// Copyright   2023 DigiPen, All rights reserved.
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

	ImGuiLayer::ImGuiLayer(std::vector<std::shared_ptr<MapDataHandler>>& maplist, std::vector<std::shared_ptr<GameObject>>& objectlist) : Layer("ImGuiLayer")
	{
		m_maplist = maplist;

		for (int i{}; i < objectlist.size(); i++) {
			if (objectlist[i]->getObj() == OBJ_PLAYER) {
				p_player = objectlist[i];
			}
		}
		m_objList = objectlist;

	}
	void ImGuiLayer::PicVecPush(uint32_t pics) {
		picVec.push_back(pics);
	}
	/*uint32_t ImGuiLayer::ReturnPicVecPush(std::string pics) {
		for (int i{}; i < picVec.size(); i++) {
			if(picVec[i] == )
		}
	}*/
	void ImGuiLayer::UpdateObjects(std::vector<std::shared_ptr<MapDataHandler>> maplist, std::vector<std::shared_ptr<GameObject>> objectlist) {
		maplist = maplist;

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

	void ImGuiLayer::SetUpdated() {
		isUpdated = !isUpdated;
	}

	bool ImGuiLayer::GetUpdated() {
		return isUpdated;
	}


	void ImGuiLayer::SetGhostChanged() { GhostChanged = !GhostChanged;  }

	bool ImGuiLayer::GetGhostChanged() { return GhostChanged; }

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
			ImGui::BulletText("Number of Walls: %d", m_maplist[GetMapIndex()]->GetNumberOfObjects(OBJ_WALL));
			ImGui::BulletText("Number of NPC: %d", m_maplist[GetMapIndex()]->GetNumberOfObjects(OBJ_NPC));

			//total
			int totalCount = m_maplist[GetMapIndex()]->GetNumberOfObjects(OBJ_WALL) +
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
			bool Ghostselected = false;
			ImGui::RadioButton("Wall", &selectedOption, 0); ImGui::SameLine();
			
			ImGui::RadioButton("Empty", &selectedOption, 2); 
			if (m_maplist[GetMapIndex()]->GetNumberOfObjects(OBJ_GHOST) < 1) {
				ImGui::SameLine();
				ImGui::RadioButton("Ghost", &selectedOption, 1); 
				Ghostselected = true;

			}
			OBJ_TYPE obj = OBJ_EMPTY;
			if (selectedOption == 0) { //EMPTY
				obj = OBJ_WALL;
			}
			else if (selectedOption == 1) { //ghost 
				obj = OBJ_GHOST;
			}
			else if (selectedOption == 2) { //EMPTY 
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

			if (ImGui::Button("Add/Remove Object", ImVec2(buttonWidth, 20))) {
				if (p_player->getX() == x_value - 1 && p_player->getY() == y_value - 1) {
					DUCK_CORE_ERROR("Error: Change the player position first!");
				}
				else {
					m_maplist[GetMapIndex()]->UpdateCellData(x_value - 1, y_value - 1, obj);
					isUpdated = true;
			
					GhostChanged = (Ghostselected)? false: true;

			


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

				//set new player spot
				m_maplist[GetMapIndex()]->UpdateCellData(x_pvalue - 1, y_pvalue - 1, OBJ_PLAYER);

				//make original position of the player empty
				m_maplist[GetMapIndex()]->UpdateCellData(p_player->getX(), p_player->getY(), OBJ_EMPTY);


				//change to the new position
				//if(!mapChanged){
				p_player->SetPositionX(x_pvalue - 1);
				p_player->SetPositionY(y_pvalue - 1);
				//}

				isUpdated = true;

				std::cout << "--------------" << GetMapIndex() << ": " << p_player->getX() << " " << p_player->getY() << "--------------" << std::endl;
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

	void ImGuiLayer::ShowAssetBrowser() {
		static std::vector<std::filesystem::directory_entry> assetEntries;
		static std::filesystem::path currentAssetDirectory("../assets/images/");
		static std::map<int, std::string> assetNames; // Map to associate image IDs with their names
		static int selectedAsset = -1;

		assetEntries.clear();
		for (const auto& entry : std::filesystem::directory_iterator(currentAssetDirectory)) {
			assetEntries.push_back(entry);
		}

		if (ImGui::Begin("Asset Browser")) {
			float itemWidth = 100.0f;
			float itemHeight = 100.0f;
			int itemsPerRow = static_cast<int>(ImGui::GetContentRegionAvail().x / itemWidth);

			ImGui::BeginChild("AssetBrowserScroll", ImVec2(0, 0), true);
			// Separator
			ImGui::Separator();
			int itemCount = 0;
			std::string name;
		
			// Display the selected asset name
			if (selectedAsset != -1) {
				auto found = assetNames.find(selectedAsset);
				if (found != assetNames.end()) {
					ImGui::Text("Selected: %s", found->second.c_str());
					name = "../assets/images/" + found->second;
				}
			}
			int x_min_pvalue = 0;  // Set your minimum value here
			int y_min_pvalue = 0;  // Set your minimum value here
			int max_w_pvalue = m_maplist[GetMapIndex()]->GetWidth();
			int max_h_pvalue = m_maplist[GetMapIndex()]->GetHeight();


			ImGui::Text("X Player value:");
			ImGui::SameLine();
			static int x_pvalue{ 1 };
			ImGui::PushItemWidth(100);
			ImGui::SameLine();
			if (ImGui::InputInt("##XPosition", &x_pvalue, 1)) {
				// Check and enforce the minimum and maximum values
				if (x_pvalue < x_min_pvalue)
					x_pvalue = x_min_pvalue;
				else if (x_pvalue > max_w_pvalue)
					x_pvalue = max_w_pvalue;
			}
			ImGui::SameLine();
			ImGui::Text("    ");
			ImGui::SameLine();
			ImGui::Text("Y Player value:");
			static int y_pvalue{ 1 };
			ImGui::PushItemWidth(100);
			ImGui::SameLine();
			if (ImGui::InputInt("##YPosition", &y_pvalue, 1)) {
				// Check and enforce the minimum and maximum values
				if (y_pvalue < y_min_pvalue)
					y_pvalue = y_min_pvalue;
				else if (y_pvalue > max_h_pvalue)
					y_pvalue = max_h_pvalue;
			}

			if (ImGui::Button("Add texture", ImVec2(120, 20))) {
				if (p_player->getX() == x_pvalue - 1 && p_player->getY() == y_pvalue - 1) {
					DUCK_CORE_ERROR("Error: Can't change Player Texture");
				}
				else {
					std::cout << name.c_str() << std::endl;
					m_objList[(y_pvalue-1) * m_maplist[GetMapIndex()]->GetWidth() + (x_pvalue-1)]->SetImage(Shader::LoadTexture(name.c_str()));
					//m_objList[0]->SetImage(Shader::LoadTexture(name.c_str()));
				}

				//ExampleLayer::InitializeGame();

			}
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + additionalSpacing);
			ImGui::Separator();
			for (int i = 0; i < assetEntries.size(); ++i) {
				std::filesystem::path entryPath = assetEntries[i].path();
				if (entryPath.extension() == ".png" || entryPath.extension() == ".jpg" || entryPath.extension() == ".jpeg") {
					std::string assetName = entryPath.filename().string();

					if (itemCount > 0 && itemCount % itemsPerRow != 0) {
						ImGui::SameLine();
					}

					ImTextureID textureID = (ImTextureID)(intptr_t)i;
					if (ImGui::ImageButton(textureID, ImVec2(itemWidth, itemHeight), { 0, 1 }, { 1, 0 })) {
						selectedAsset = i;
					}

					// Store the asset name in the map
					assetNames[i+1] = assetName;


					itemCount++;
				}
			}
			ImGui::EndChild();

		}
		ImGui::End();
	}


	void ImGuiLayer::ShowFileBrowser() {
		// Ensure that the directory_entries are loaded once
		static std::vector<std::filesystem::directory_entry> directory_entries;
		static std::filesystem::path current_directory_path("../txtfiles/Map/");
		static int selected_item = -1;
		// Load directory entries
		directory_entries.clear();
		for (const auto& entry : std::filesystem::directory_iterator(current_directory_path)) {
			directory_entries.push_back(entry);
		}

		// Display the file browser window
		if (ImGui::Begin("File Browser")) {
			// List directories and files in the current directory

			ImGui::Text("Current File: %s", directory_entries[GetMapIndex()].path().filename().string().c_str());


			if (ImGui::BeginCombo("Files", selected_item >= 0 ? directory_entries[selected_item].path().filename().string().c_str() : NULL)) {
				for (int i = 0; i < directory_entries.size(); i++) {
					bool is_selected = (selected_item == i);
					if (ImGui::Selectable(directory_entries[i].path().filename().string().c_str(), is_selected)) {
						SetMapIndex(i);
						isUpdated = true;
						mapChanged = true;
					
					}

					// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
					if (is_selected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::SeparatorText("Files in Dir");

			// Loop through directories and files and display them
			for (const auto& entry : directory_entries) {
				if (entry.is_directory()) {
					ImGui::TextColored(ImVec4(0.4f, 0.7f, 1.0f, 1.0f), "[Dir] %s", entry.path().filename().string().c_str());
					// Handle directory selection
				}
				else {
					ImGui::Text("[File] %s", entry.path().filename().string().c_str());
					// Handle file selection
				}
			}
		}
		ImGui::End();
	}




	void ImGuiLayer::DisplayFPS(double& fps)
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

	void ImGuiLayer::OnImGuiRender(double& fps)
	{
		// Start a new frame
		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("Game")) {
				if (isGamePlaying) {
					if (ImGui::MenuItem("Stop")) {
						isGamePlaying = false;
					}
				}
				else {
					if (ImGui::MenuItem("Play")) {
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
		ShowFileBrowser();
		ShowAssetBrowser();
		//ImGui::ShowDemoWindow(&show);

	}
	//------------FOR DRAG AND DROP---------------------

	bool ImGuiLayer::GetChanged()
	{
		return mapChanged;
	}










}