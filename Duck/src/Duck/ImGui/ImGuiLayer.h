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
#pragma once

#include "Duck/Layer.h"

#include "Duck/Events/ApplicationEvent.h"
#include "Duck/Events/KeyEvent.h"
#include "Duck/Events/MouseEvent.h"
#include "Duck/De-serialize/GameObject.h"
#include "Duck/Map/Map.h"
#include "Duck/time.h"

namespace Duck {
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(std::shared_ptr<MapDataHandler> map, std::vector<std::shared_ptr<GameObject>> objectlist);
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
		void DisplayFPS(double &fps);

		void BlockEvents(bool block) { m_BlockEvents = block; }


		void HandleDragAndDropTarget(); //drag and drop functionality

		void InitiateDragAndDropSource(); //drag and drop functionality



	private:
		float  const additionalSpacing = 20.0f; // Set desired additional spacing
		double lastFrameTime = 0.0;
		double fps = 0.0;
		bool m_BlockEvents = true;
		std::vector<std::shared_ptr<GameObject>> m_objList;
		std::shared_ptr<MapDataHandler> m_map;
		double m_fps;
		const char* filename;
		std::shared_ptr<GameObject> p_player;
	};
}