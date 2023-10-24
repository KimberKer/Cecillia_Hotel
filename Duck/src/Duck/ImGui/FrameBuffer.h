#pragma once
#include "duckpch.h"
#include <glad/glad.h>

namespace Duck {
	struct FrameBufferSpecification {
		uint32_t width;
		uint32_t height;
		uint32_t sameples = 1;

	};

	class FrameBuffer {
	private:
		GLuint framebuffer;
		GLuint texture;
		uint32_t width;
		uint32_t height;


	public:
		FrameBuffer(const FrameBufferSpecification& spec) {

		}

		~FrameBuffer();

	};
}