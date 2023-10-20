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

namespace Duck {
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(std::shared_ptr<MapDataHandler> map);
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
		void CreateObjects();
		

		void BlockEvents(bool block) { m_BlockEvents = block; }


		void HandleDragAndDropTarget(); //drag and drop functionality

		void InitiateDragAndDropSource(); //drag and drop functionality



	private:
		bool m_BlockEvents = true;
		float m_time = 0.0f;
		std::shared_ptr<MapDataHandler> m_map;
		const char* filename;
	};
}