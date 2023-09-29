//---------------------------------------------------------
// File:    Renderer.h
//authors:	Ahmad Mahdi Bin Jamal
// email:	ahmadmahdi.b@digipen.edu
// 
//
// Brief:	This file declares classes and functions related 
//			to rendering in the Duck game. It includes rendering
//			commands to set clear color, clear the screen,
//			and draw indexed elements. The Renderer class 
//			provides functions for beginning and ending 
//			rendering scenes, submitting objects for rendering, 
//			rendering backgrounds, handling sprite animations, 
//			and getting the current texture for animations.
// 
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once

#include <glm/glm.hpp>
#include "Vertex.h"
#include "Shader.h"

namespace Duck {

	// A class containing static rendering commands.
	class RenderCommand {

	public:
		// Set the clear color for the screen.
		static void SetClearColor(const glm::vec4& color);
		// Clear the screen.
		static void Clear();
		// Draw indexed elements using the provided vertex array.
		static void DrawIndex(const std::shared_ptr<VertexArray>& vertexArray);

	};

	// A class for managing rendering operations.
	class Renderer {

	public:

		// Begin the rendering scene.
		static void BeginScene();
		// End the rendering scene.
		static void EndScene();
		// Submit an object for rendering with a given transform.
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform);
		// Submit an object for rendering with a given transform and texture.
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform, const uint32_t texture);
		// Submit a background for rendering with a given transform, texture, and grid size.
		static void BackgroundSubmit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform, const uint32_t texture, const int cols, const int rows);
		// Submit an animation for rendering with a given transform, texture, and grid size.
		static void AnimationSubmit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform, const uint32_t texture, const int cols, const int rows);
		// Get the current texture for sprite animations based on the current frame and timing.
		static uint32_t GetCurrentTexture(const uint32_t SpriteSheet, const int Width, const int Height, const int Rows, const int Columns, float currentTime);

	};
}