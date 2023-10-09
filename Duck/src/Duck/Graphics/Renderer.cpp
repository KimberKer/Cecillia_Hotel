//---------------------------------------------------------
// File:    Renderer.cpp
//authors:	Ahmad Mahdi Bin Jamal
// email:	ahmadmahdi.b@digipen.edu
// 
//
// Brief:    This file implements rendering-related functions 
//			and classes, including setting the clear color, 
//			clearing the screen, drawing indexed elements, 
//			and submitting objects for rendering. It also 
//			contains functions for rendering backgrounds and
//			handling sprite animations in the Duck game.
// 
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------


#include "duckpch.h"
#include "Renderer.h"
#include <glad/glad.h>


namespace Duck{


	// Set the clear color for the screen.
	void RenderCommand::SetClearColor(const glm::vec4& color) {

		glClearColor(color.r, color.g, color.b, color.a);

	}

	// Clear the screen.
	void RenderCommand::Clear() {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}

	// Draw indexed elements using the provided vertex array.
	void RenderCommand::DrawIndex(const std::shared_ptr<VertexArray>& vertexArray) {

		glDrawElements(vertexArray->GetPrimitiveType(), vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

	}


	// Begin the rendering scene.
	void Renderer::BeginScene() {

		// Not Implemented Yet

	}

	// End the rendering scene.
	void Renderer::EndScene() {

		// Not Implemented Yet

	}

	// Submit an object for rendering with a given transform.
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader,
		const glm::mat4& transform) {

		shader->Bind();
		shader->UploadUniformMat4("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndex(vertexArray);

	}

	// Submit an object for rendering with a given transform and texture.
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform, const uint32_t texture) {

		shader->Bind();
		shader->UploadUniformMat4("u_Transform", transform);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		shader->UploadUniformInt("u_Tex", 0);

		vertexArray->Bind();


		RenderCommand::DrawIndex(vertexArray);


	}

	// Submit a background for rendering with a given transform and texture.
	void Renderer::BackgroundSubmit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform, const uint32_t texture, const int cols, const int rows) {

		shader->Bind();
		shader->UploadUniformMat4("u_Transform", transform);



		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		shader->UploadUniformInt("u_Tex", 0);
		shader->UploadUniformFloat("u_Cols", (float)cols);
		shader->UploadUniformFloat("u_Rows", (float)rows);

		vertexArray->Bind();


		RenderCommand::DrawIndex(vertexArray);


	}

	// Submit a background for rendering with a given transform and texture.
	void Renderer::AnimationSubmit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform, const uint32_t texture, const int cols, const int rows) {


	// Not implemented yet.


	}

	// CURRENTLY NOT WORKING.
	// Get the current texture for sprite animations based on the current frameand timing.
	uint32_t Renderer::GetCurrentTexture(const uint32_t SpriteSheet, const int Width, const int Height, const int Rows, const int Columns, float currentTime) {

		// Calculate the total number of frames in the sprite sheet
		int totalFrames = Rows * Columns;

		// Calculate the index of the current frame based on time
		float frameDuration = 0.1f; // Adjust this value to control the animation speed
		int currentFrame = static_cast<int>(currentTime / frameDuration) % totalFrames;

		// Calculate UV coordinates for the current frame
		float frameWidth = 1.0f / Columns;
		float frameHeight = 1.0f / Rows;
		float xOffset = (currentFrame % Columns) * frameWidth;
		float yOffset = (currentFrame / Columns) * frameHeight;

		// Bind the sprite sheet texture
		glBindTexture(GL_TEXTURE_2D, SpriteSheet);

		// Set texture coordinates for the current frame
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		return SpriteSheet;
	}


}

