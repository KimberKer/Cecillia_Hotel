//---------------------------------------------------------
// File:    Shader.h
//authors:	Ahmad Mahdi Bin Jamal
// email:	ahmadmahdi.b@digipen.edu
// 
//
// Brief:	This header file defines the Shader class, 
//			which is responsible for loading, compiling,
//			and managing OpenGL shaders. It also provides 
//			functions to bind and unbind shaders,load textures, 
//			and upload uniform values to shaders.
// 
// 
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Duck {

	class Shader {
	public:

        // Constructor: Create a shader from vertex and fragment shader source code.
        Shader(const std::string& VtxSrc, const std::string& FragSrc);

        // Destructor: Clean up the shader program.
        ~Shader();

        // Bind the shader for rendering.
        void Bind() const;

        // Unbind any active shader.
        void Unbind() const;

        // Load shader source code from a file and return it as a string.
        static std::string LoadShaderSource(const char* filePath);

        // Load a texture from an image file and return its OpenGL texture ID.
        static uint32_t LoadTexture(const char* filePath, int& Width, int& Height);

        // Load a texture from an image file and return its OpenGL texture ID.
        static uint32_t LoadTexture(const char* filePath);

        // Upload a 4x4 matrix uniform to the shader by its name.
        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

        // Upload an integer uniform to the shader by its name.
        void UploadUniformInt(const std::string& name, int value);

        // Upload a float uniform to the shader by its name.
        void UploadUniformFloat(const std::string& name, float value);
		
	private:
		uint32_t m_rendererID;
	};
}