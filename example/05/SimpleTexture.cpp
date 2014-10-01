#include "SimpleTexture.h"

using namespace calm3d;

bool SimpleTexture::init()
{
	if (!GLView::init()) {
		return false;
	}

	_glProgram.setVertShader("shaders/05/SimpleTexture.vsh.glsl");
	_glProgram.setFragShader("shaders/05/SimpleTexture.fsh.glsl");

	// Generate a name for the texture
	glGenTextures(1, &_textureId);
	// Now bind it to the context using the GL_TEXTURE_2D binding point
	glBindTexture(GL_TEXTURE_2D, _textureId);
	// Specify the amount of storage we want to use for the texture
	glTexStorage2D(GL_TEXTURE_2D,	// 2D texture
				  8,				// 1 mipmap level 
				  GL_RGBA32F,		// 32-bit floating-point RGBA data
				  256, 256);		// 256 x 256 texels
	
	// Define some data to upload into the texture
	float* data = new float[256 * 256 * 4];
	// Generate custom defined texture
	this->generate_texture(data, 256, 256);
	// Assume the texture is already bound to the GL_TEXTUE_2D target
	glTexSubImage2D(GL_TEXTURE_2D, // 2D texture
		0,			// level 0
		0, 0,		// Offset 0, 0
		256, 256,	// 256 x 256 texels, replace entire image
		GL_RGBA,		// Four channel data
		GL_FLOAT,	// Floating point data
		data);		// Pointer to texture data
	// Free the memory we allocated before
	delete[] data;

}

void SimpleTexture::render(double time)
{
	static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, green);

	glUseProgram(_glProgram.getProgram());

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void SimpleTexture::generate_texture(float* data, int width, int height)
{
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			data[(y * width + x) * 4 + 0] = (float)((x & y) & 0xFF) / 255.0f;
			data[(y * width + x) * 4 + 1] = (float)((x | y) & 0xFF) / 255.0f;
			data[(y * width + x) * 4 + 2] = (float)((x ^ y) & 0xFF) / 255.0f;
			data[(y * width + x) * 4 + 3] = 1.0f;
		}
	}
}

void SimpleTexture::onExit()
{
	glDeleteVertexArrays(1, &_vao);
	glDeleteTextures(1, &_textureId);

	GLView::onExit();
}

//CREATE_MAIN(SimpleTexture);