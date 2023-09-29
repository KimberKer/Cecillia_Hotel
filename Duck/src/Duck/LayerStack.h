//---------------------------------------------------------
// File:    LayerStack.h
//authors:	Kimber Ker Soon Kiat
// email:	s.ker\@digipen.edu
// 
//
// Brief:     Contains the declarations to manage layers
//
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include "Duck/Core.h"
#include "Layer.h"
#include <vector>

namespace Duck {
	// A class for managing layers and overlays in an application
	class LayerStack {
	public:
		// Constructor to initialize the layer stack
		LayerStack();

		// Destructor to clean up memory allocated for layers
		~LayerStack();

		// Push a layer onto the top of the stack
		void PushLayer(Layer* layer);

		// Push an overlay onto the top of the stack
		void PushOverlay(Layer* overlay);

		// Pop a layer from the stack
		void PopLayer(Layer* layer);

		// Pop an overlay from the stack
		void PopOverlay(Layer* overlay);

		// Get an iterator to the beginning of the layer stack
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }

		// Get an iterator to the end of the layer stack
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers; // Container to hold layers
		unsigned int m_LayerInsertIndex = 0; // Iterator to insert layers at a specific position
	};
}
