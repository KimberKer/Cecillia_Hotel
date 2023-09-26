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
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray , const std::shared_ptr<Shader>& shader, const glm::mat4& transform);

	};
}