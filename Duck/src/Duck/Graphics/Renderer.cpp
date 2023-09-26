#include "duckpch.h"
#include "Renderer.h"
#include <glad/glad.h>


namespace Duck{


	void RenderCommand::SetClearColor(const glm::vec4& color) {

		glClearColor(color.r, color.g, color.b, color.a);

	}

	void RenderCommand::Clear() {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}

	void RenderCommand::DrawIndex(const std::shared_ptr<VertexArray>& vertexArray) {

		glDrawElements(vertexArray->GetPrimitiveType(), vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

	}



	void Renderer::BeginScene() {


	}


	void Renderer::EndScene() {



	}


	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader,
		const glm::mat4& transform) {

		shader->Bind();
		shader->UploadUniformMat4("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndex(vertexArray);

	}


}

