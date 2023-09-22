#include "duckpch.h"
#include "LayerStack.h"

namespace Duck {
	// Constructor initializes the LayerStack
	LayerStack::LayerStack() {
		m_LayerInsert = m_Layers.begin();
	}

	// Destructor cleans up all the layers in the stack
	LayerStack::~LayerStack() {
		for (Layer* layer : m_Layers) {
			delete layer;
		}
	}

	// Push a layer onto the top of the stack
	void LayerStack::PushLayer(Layer* layer) {
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
	}

	// Push an overlay onto the top of the stack
	void LayerStack::PushOverlay(Layer* overlay) {
		m_Layers.emplace_back(overlay);
	}

	// Pop a layer from the stack
	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
			m_LayerInsert--;
		}
	}

	// Pop an overlay from the stack
	void LayerStack::PopOverlay(Layer* overlay) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
		}
	}
}
