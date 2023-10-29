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
#pragma once

#include "Duck/Layer.h"

#include "Duck/Events/ApplicationEvent.h"
#include "Duck/Events/KeyEvent.h"
#include "Duck/Events/MouseEvent.h"
#include "Duck/De-serialize/GameObject.h"
#include "Duck/Map/Map.h"
#include "Duck/time.h"
#include <filesystem>

extern DUCK_API bool isGamePlaying;

namespace Duck {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(std::vector<std::shared_ptr<MapDataHandler>>& maplist, std::vector<std::shared_ptr<GameObject>>& objectlist);
		~ImGuiLayer();
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;
		virtual void OnImGuiRender(double& fps) override;

		void Begin();
		void End();
		void CreateObjects();
		void TabCreateGameObj();
		void TabUpdatePlayer();
		void TabDisplayGameObjects();
		void ShowAssetBrowser();
		void UpdateObjects(std::vector<std::shared_ptr<MapDataHandler>> maplist, std::vector<std::shared_ptr<GameObject>> objectlist);

		void Console();
		void DisplayFPS(double& fps);

		void BlockEvents(bool block) { m_BlockEvents = block; }


		void SetGhostChanged();

		bool GetGhostChanged();

		void SetUpdated();

		bool GetUpdated();
		bool GetChanged();

		void ShowFileBrowser();

		void PicVecPush(uint32_t pics);
		uint32_t ReturnPicVecPush(std::string pics);

	private:
		float  const additionalSpacing = 20.0f; // Set desired additional spacing
		double lastFrameTime = 0.0;
		double fps = 0.0;
		bool m_BlockEvents = true;
		std::vector<uint32_t> picVec;
		std::vector<std::shared_ptr<GameObject>> m_objList;
		std::vector<std::shared_ptr<MapDataHandler>> m_maplist;
		std::shared_ptr<GameObject> gameobj;
		double m_fps;
		const char* filename;
		std::shared_ptr<GameObject> p_player;
		bool isUpdated;
		std::vector<std::filesystem::directory_entry> directory_entries;
		bool mapChanged = false;
		bool GhostChanged = true;
	};

}