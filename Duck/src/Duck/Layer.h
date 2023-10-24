//---------------------------------------------------------
// File:    Layer.h
//authors:	Kimber Ker Soon Kiat
// email:	s.ker\@digipen.edu
// 
//
// Brief:     Contains the declarations related to layer
//
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include "Duck/Core.h"
#include "Duck/Events/Event.h"

namespace Duck {
	// Base class for application layers
	class Layer {
	public:
		// Constructor that takes a layer name
		Layer(const std::string& name = "Layer");

		// Destructor
		virtual ~Layer();

		// Called when the layer is attached to the application
		virtual void OnAttach() {}

		// Called when the layer is detached from the application
		virtual void OnDetach() {}

		// Called on every update cycle of the layer
		virtual void OnUpdate() {}

		// Called when an event is dispatched to the layer
		virtual void OnEvent(Event& event) {}

		virtual void OnImGuiRender(double &fps) {}

		// Get the name of the layer
		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName; // Debug name of the layer
	};
}
