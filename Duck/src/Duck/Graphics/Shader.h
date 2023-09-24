#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Duck {

	class Shader {
	public:

		Shader(const std::string& VtxSrc, const std::string& FragSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;
		static std::string LoadShaderSource(const char* filePath);

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		
	private:
		uint32_t m_rendererID;
	};
}