#pragma once

#include <glm/glm.hpp>
#include "Vertex.h"
#include "Shader.h"

namespace Duck {


	class RenderCommand {

	public:

		static void SetClearColor(const glm::vec4& color) ;
		static void Clear();
		static void DrawIndex(const std::shared_ptr<VertexArray>& vertexArray);

	};




	class Renderer {

	public:

		static void BeginScene();
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform);
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform, const uint32_t texture);
		static void BackgroundSubmit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform, const uint32_t texture, const int cols, const int rows);
		static void AnimationSubmit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform, const uint32_t texture, const int cols, const int rows);
		//static void SubmitSprite(const std::shared_ptr<VertexArray>& vertexArray,
		//	const std::shared_ptr<Shader>& shader,
		//	const glm::mat4& transform,
		//	const uint32_t texture,
		//	const int Width, const int height, const int Xnum, const int Ynum, // Sprite dimensions and num of frames
		//	const float Duration);// Time in seconds spent per frame 

		static uint32_t GetCurrentTexture(const uint32_t SpriteSheet, const int Width, const int Height, const int Rows, const int Columns, float currentTime);

	};
}