#pragma once
#include "Duck/Application.h"

namespace Duck {

	void DrawBackground(const int cols, const int rows, const std::shared_ptr<VertexArray>& BGVA, const std::shared_ptr<Shader>& BGshader, uint32_t texture);

	void DrawGrid(const int x, const int y , const std::shared_ptr<VertexArray>& LineVA, const std::shared_ptr<Shader>& LineShader);

	void DrawSquareObject(float PosX, float PosY, std::shared_ptr<VertexArray> VA, std::shared_ptr<Shader> shader, uint32_t texture);

}