#include "SimpleTextureCoord.h"

using namespace calm3d;

#define B 0x00, 0x00, 0x00, 0x00
#define W 0xFF, 0xFF, 0xFF, 0xFF
static const GLubyte tex_data[] =
{
	B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
	W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
	B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
	W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
	B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
	W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
	B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
	W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
	B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
	W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
	B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
	W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
	B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
	W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
	B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
	W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
};
#undef B
#undef W

bool SimpleTextureCoord::init()
{
	if (!GLView::init()) {
		return false;
	}

	_glProgram.setVertShader("shaders/05/SimpleTextureCoord.vsh.glsl");
	_glProgram.setFragShader("shaders/05/SimpleTextureCoord.fsh.glsl");
	uniforms.mv_matrix = glGetUniformLocation(_glProgram.getProgram(), "mv_matrix");
	uniforms.proj_matrix = glGetUniformLocation(_glProgram.getProgram(), "proj_matrix");

	// Generate a name for the texture
	mTexIdx = 0;
	glGenTextures(1, &_textureIds[0]);
	// Now bind it to the context using the GL_TEXTURE_2D binding point
	glBindTexture(GL_TEXTURE_2D, _textureIds[0]);
	// Specify the amount of storage we want to use for the texture
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, 16, 16);
	// Assume the texture is already bound to the GL_TEXTUE_2D target
	glTexSubImage2D(GL_TEXTURE_2D, // 2D texture
		0,			// level 0
		0, 0,		// Offset 0, 0
		16, 16,	// 256 x 256 texels, replace entire image
		GL_RGBA,		// Four channel data
		GL_UNSIGNED_SHORT,	// Floating point data
		tex_data);		// Pointer to texture data
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	_object = make_shared<Object3D>();
	_object->load("objects/torus_nrms_tc.sbm");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void SimpleTextureCoord::render(double time)
{
	static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
	static const GLfloat ones[] = { 1.0f };
	glClearBufferfv(GL_COLOR, 0, green);
	glClearBufferfv(GL_DEPTH, 0, ones);

	glViewport(0, 0, _frameSize.width, _frameSize.height);

	glBindTexture(GL_TEXTURE_2D, _textureIds[mTexIdx]);

	glUseProgram(_glProgram.getProgram());

	zmath::mat4 proj_matrix = zmath::perspective(60.0f,
		(float)_frameSize.width / (float)_frameSize.height,
		0.1f, 1000.0f);
	zmath::mat4 mv_matrix = zmath::
}

void SimpleTextureCoord::generate_texture(float* data, int width, int height)
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

void SimpleTextureCoord::onExit()
{
	glDeleteVertexArrays(1, &_vao);
	glDeleteTextures(1, &_textureIds[0]);

	GLView::onExit();
}

CREATE_MAIN(SimpleTextureCoord);