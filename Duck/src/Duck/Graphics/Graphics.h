#pragma once
#include <memory>
#include "Duck/Application.h"


namespace Duck {

	class DUCK_API Graphics {
		
	public:

		Graphics();
		virtual ~Graphics();


		static Graphics* Create();


		virtual void SetGridSize(int GridSize);
		virtual void SetTileWidth(int TileWidth);

		virtual void DrawBackground(const uint32_t texture);
		virtual void ShowGrid();
		virtual void DrawSquareObject(const float PosX, const float PosY, const float scale, const float angle, const uint32_t texture, const bool ShowBoundingBox);



	private:

		int cols;
		int rows;
		int tileWidth;

		uint32_t m_RendererID{};


		std::shared_ptr<VertexArray> m_TriangleVA;
		std::shared_ptr<Shader> m_TriangleShader;

		std::shared_ptr<VertexArray> m_SquareVA;
		std::shared_ptr<Shader> m_SquareShader;

		std::shared_ptr<VertexArray> m_PointVA;
		std::shared_ptr<Shader> m_PointShader;

		std::shared_ptr<VertexArray> m_LineVA;
		std::shared_ptr<Shader> m_LineShader;
		std::shared_ptr<Shader> m_BoundingLineShader;

		std::shared_ptr<VertexArray> m_SquareImgVA;
		std::shared_ptr<Shader> m_SquareImgShader;
		std::shared_ptr<Shader> m_BackgroundImgShader;

		std::shared_ptr<VertexArray> m_SquareSprVA;
		std::shared_ptr<Shader> m_SquareSprShader;



	};


	

}