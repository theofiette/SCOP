#include "scop.hpp"

void _applyTexture(GLFWwindow* window, Shader &shader)
{
	registre	*windowContext;

	windowContext = static_cast<registre *>(glfwGetWindowUserPointer(window));

	if (windowContext->normalToggle)
	{
		if (windowContext->colDisplay == GREY)
		{
			shader.setUniform<float>("normalDisplay", 1.0f);
			windowContext->colDisplay = NORMAL;
		}
		else if (windowContext->colDisplay == NORMAL)
		{
			shader.setUniform<float>("normalDisplay", 0.0f);
			windowContext->colDisplay = GREY;
		}
		windowContext->normalToggle = false;
	}

	if (windowContext->textureToggle)
	{
		if (windowContext->texDisplay == COLOR)
			windowContext->textureCoef += TEXTURE_STEP;
		else
			windowContext->textureCoef -= TEXTURE_STEP;
		windowContext->textureCoef = std::clamp(windowContext->textureCoef, 0.0f, 1.0f);
		if (windowContext->textureCoef == 0.0f || windowContext->textureCoef == 1.0f)
			windowContext->textureToggle = false;
	}
	shader.setUniform<float>("texCoef", windowContext->textureCoef);
	// shader.setUniform<float>("normalDisplay", windowContext->);
}

/*
*	The process function responsible for rendering.
*	Called every frame.
*/
void _processRender(GLFWwindow* window, Camera &camera, Mesh &mesh, Material &material)
{
	Shader		*shader;
	mat4x4		transformation, projection;

	glClearColor(BACKGROUND_COLOR);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	transformation = mesh.constructTransformationMatrix();
	projection = camera.getProjectionMatrix();
	shader = &material.getShader();

	_applyTexture(window, *shader);

	shader->use();
	shader->setUniform<float[16]>("projection", projection.m);
	shader->setUniform<float[16]>("transformation", transformation.m);

	mesh.draw();

	glfwSwapBuffers(window);
}
