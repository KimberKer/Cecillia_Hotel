#include "duckpch.h"
#include "Shader.h"

#include "glad/glad.h"
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "Duck/stb_image.h"

namespace Duck {

	Shader::Shader(const std::string& VtxSrc, const std::string& FragSrc) {

		m_rendererID = {};


		// START OF VERTEX SHADER /////////////////////////////////////////////////////////

		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = VtxSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{

			// THIS ARE FOR IF COMPILATION FAILS!
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			return;
		}

		// START OF FRAGMENT SHADER ////////////////////////////////////////////////////////

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = FragSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			return;
		}


// Attach Shaders ////////////////////////////////////////////////////////////////////


		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_rendererID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_rendererID, vertexShader);
		glAttachShader(m_rendererID, fragmentShader);



// Link Shaders ////////////////////////////////////////////////////////////////////////

		// Link our program
		glLinkProgram(m_rendererID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_rendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_rendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_rendererID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_rendererID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.
			// In this simple program, we'll just leave

			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_rendererID, vertexShader);
		glDetachShader(m_rendererID, fragmentShader);




	}


	Shader::~Shader() {

		glDeleteProgram(m_rendererID);


	}

	
	void Shader::Bind() const {

		glUseProgram(m_rendererID);


	}


	void Shader::Unbind() const {

		glUseProgram(0);

	}


	// Function to load shader source code from a file
	std::string Shader::LoadShaderSource(const char* filePath) {

		std::string shaderCode;
		std::ifstream shaderFile;

		// Ensure ifstream objects can throw exceptions
		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			// Open the shader file
			shaderFile.open(filePath);

			std::stringstream shaderStream;

			// Read file's buffer contents into streams
			shaderStream << shaderFile.rdbuf();

			// Close the file handler
			shaderFile.close();

			// Convert stream into a string
			shaderCode = shaderStream.str();
		}
		catch (...) {
			std::cerr << "Error at " << filePath << std::endl;
		}

		return shaderCode;
	}


	// Would return the height and width. Is needed for Sprite images.
	uint32_t Shader::LoadTexture(const char* filePath, int& Width, int& Height ) {

		uint32_t textureID;
		glGenTextures(1, &textureID);

		int width, height, channels;
		stbi_set_flip_vertically_on_load(true); // Flip the image vertically (OpenGL expects the top-left corner as the origin)

		unsigned char* data = stbi_load(filePath, &width, &height, &channels, 0);

		if (!data) {
			std::cerr << "Failed to load texture from " << filePath << std::endl;
			return 0; // Return 0 to indicate failure
		}

		Width = width;
		Height = height;

		GLenum format = GL_RGB;
		if (channels == 1)
			format = GL_RED;
		else if (channels == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		// Set texture parameters (optional)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);\
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		stbi_image_free(data); // Free the loaded image data, as it's already been uploaded to the GPU

		return textureID;


	}

	uint32_t Shader::LoadTexture(const char* filePath) {

		uint32_t textureID;
		glGenTextures(1, &textureID);

		int width, height, channels;
		stbi_set_flip_vertically_on_load(true); // Flip the image vertically (OpenGL expects the top-left corner as the origin)

		unsigned char* data = stbi_load(filePath, &width, &height, &channels, 0);

		if (!data) {
			std::cerr << "Failed to load texture from " << filePath << std::endl;
			return 0; // Return 0 to indicate failure
		}

		GLenum format = GL_RGB;
		if (channels == 1)
			format = GL_RED;
		else if (channels == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		// Set texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		stbi_image_free(data); // Free the loaded image data, as it's already been uploaded to the GPU

		return textureID;


	}


	void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) {

		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));

	}

	void Shader::UploadUniformInt(const std::string& name, int value) {

		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform1i(location, value);

	}

	void Shader::UploadUniformFloat(const std::string& name, float value) {

		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform1f(location, value);

	}


}