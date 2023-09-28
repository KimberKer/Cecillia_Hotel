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

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform, const uint32_t texture) {

		shader->Bind();
		shader->UploadUniformMat4("u_Transform", transform);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		shader->UploadUniformInt("u_Tex", 0);

		vertexArray->Bind();


		RenderCommand::DrawIndex(vertexArray);


	}


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

	void Renderer::AnimationSubmit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform, const uint32_t texture, const int cols, const int rows) {


		float SpriteWidth = 1.f / cols;
		float SpriteHeight = 1.f / rows;


		// Calculate the row and column of the current frame
		//int row = currentFrame / cols;
		//int col = currentFrame % cols;

		// Calculate the u (horizontal) and v (vertical) texture coordinates for the current frame
		//float u = col * SpriteWidth;
		//float v = 1.0f - (row + 1) * SpriteWidth; // Invert v for OpenGL's coordinate system

		// Bind the shader and set uniform values
		shader->Bind();
		shader->UploadUniformMat4("u_Transform", transform);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);


		shader->Bind();
		shader->UploadUniformMat4("u_Transform", transform);



		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		shader->UploadUniformInt("u_Tex", 0);


		vertexArray->Bind();


		RenderCommand::DrawIndex(vertexArray);


	}


	//void Renderer::SubmitSprite(const std::shared_ptr<VertexArray>& vertexArray,
	//							const std::shared_ptr<Shader>& shader, 
	//							const glm::mat4& transform, 
	//							const uint32_t texture,
	//							const int Width, const int height, const int Xnum, const int Ynum, // Sprite dimensions and num of frames
	//							const float Duration) // Time in seconds spent per frame 
	//{

	//	shader->Bind();
	//	shader->UploadUniformMat4("u_Transform", transform);

	//	glActiveTexture(GL_TEXTURE0);
	//	glBindTexture(GL_TEXTURE_2D, texture);

	//	shader->UploadUniformInt("u_Tex", 0);


	//	UpdateTextureCoordinates(left, right, top, bottom);

	//	vertexArray->Bind();


	//	RenderCommand::DrawIndex(vertexArray);


	//}


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

		//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(glm::vec4(1.0f))); // Set border color to white
		//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(glm::vec4(0.0f))); // Set border color to black

		return SpriteSheet;
	}


}

