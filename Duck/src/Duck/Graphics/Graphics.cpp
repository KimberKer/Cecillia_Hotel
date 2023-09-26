#include "duckpch.h"
#include "Graphics.h"
#include <glad/glad.h>
#include "Duck/Window.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Duck {

	void DrawBackground(const int cols, const int rows, const std::shared_ptr<VertexArray>& BGVA, const std::shared_ptr<Shader>& BGshader, uint32_t texture) {


		glm::vec3 Pos{ 0.0f, 0.0f, 0.0f };
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), Pos);
		transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 1.0f));
		Renderer::BackgroundSubmit(BGVA, BGshader, transform, texture, cols, rows);
		



	}

	void DrawGrid(const int cols, const int rows, const std::shared_ptr<VertexArray>& LineVA, const std::shared_ptr<Shader>& LineShader) {



		float xOffset = 2.f / (float)cols;
		float yOffset = 2.f / (float)rows;

		float xMax = (float)2.f / 2.f;
		float xMin = -xMax;

		float yMax = (float)2.f / 2.f;
		float yMin = -yMax;

		for (float x = xMin; x <= (xMax + xOffset); x += xOffset) {

			glm::vec3 LinePos{ x,0.0f,0.0f };
			float LineAngle{ 90.0f };
			glm::mat4 transform = glm::translate(glm::mat4(1.0), LinePos);
			transform = glm::scale(transform, glm::vec3(0.5f, 1.0f, 1.0f));
			transform = glm::rotate(transform, glm::radians(LineAngle), glm::vec3(0, 0, 1));

			Renderer::Submit(LineVA, LineShader, transform);
		}

		for (float y = yMin; y <= (yMax + yOffset); y += yOffset) {

			glm::vec3 LinePos{ 0.0f, y, 0.0f };
			float LineAngle{ 0.0f };
			glm::mat4 transform = glm::translate(glm::mat4(1.0), LinePos);
			transform = glm::scale(transform, glm::vec3(1.0f, 0.5f, 1.0f));
			transform = glm::rotate(transform, glm::radians(LineAngle), glm::vec3(0, 0, 1));

			Renderer::Submit(LineVA, LineShader, transform);
		}
	}



	void DrawSquareObject(float PosX, float PosY, std::shared_ptr<VertexArray> VA, std::shared_ptr<Shader> shader, uint32_t texture) {

		float x = (PosX * 0.2f) - 0.9;
		float y = -(PosY * 0.2f) + 0.9;


		glm::vec3 Pos{ x,y ,0.0f };
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), Pos);
		transform = glm::scale(transform, glm::vec3(0.1f,0.1f,1.0f));
		Renderer::Submit(VA, shader, transform, texture);

	}



	void DrawSquareAnimation(float PosX, float PosY, std::shared_ptr<VertexArray> VA, std::shared_ptr<Shader> shader, uint32_t texture) {

		float x = (PosX * 0.2f) - 0.9;
		float y = -(PosX * 0.2f) + 0.9;


		glm::vec3 Pos{ x,y ,0.0f };
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), Pos);
		transform = glm::scale(transform, glm::vec3(0.1f, 0.1f, 1.0f));
		Renderer::Submit(VA, shader, transform, texture);

	}




	//void renderAnimation(GLuint texture, int numRows, int numCols, float dt) {
	//	static float frameTime = 0.1f; // Time in seconds per frame
	//	static int currentFrame = 0;

	//	// Update current frame based on elapsed time
	//	frameTime -= dt;
	//	if (frameTime <= 0.0f) {
	//		currentFrame = (currentFrame + 1) % (numRows * numCols);
	//		frameTime = 0.1f; // Reset frame time
	//	}

	//	// Calculate texture coordinates for the current frame
	//	int row = currentFrame / numCols;
	//	int col = currentFrame % numCols;
	//	float frameWidth = 1.0f / numCols;
	//	float frameHeight = 1.0f / numRows;
	//	float texCoordX = col * frameWidth;
	//	float texCoordY = 1.0f - (row + 1) * frameHeight; // Invert Y-axis

	//	// Bind the sprite sheet texture
	//	glBindTexture(GL_TEXTURE_2D, texture);

	//	// Set the texture coordinates for the current frame
	//	glBegin(GL_QUADS);
	//	glTexCoord2f(texCoordX, texCoordY + frameHeight);
	//	glVertex2f(-0.5f, -0.5f);

	//	glTexCoord2f(texCoordX + frameWidth, texCoordY + frameHeight);
	//	glVertex2f(0.5f, -0.5f);

	//	glTexCoord2f(texCoordX + frameWidth, texCoordY);
	//	glVertex2f(0.5f, 0.5f);

	//	glTexCoord2f(texCoordX, texCoordY);
	//	glVertex2f(-0.5f, 0.5f);
	//	glEnd();
	//}


		
		
	

}

