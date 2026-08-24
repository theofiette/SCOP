#include "scop.hpp"

/*
*	The process function responsible for rendering.
*	Called every frame.
*/
void _processRender(GLFWwindow* window, Camera &camera, Mesh &mesh, Material &material)
{
	Shader		*currentShader;
	mat4x4		transformation, projection;
	registre	*windowContext;

	glClearColor(BACKGROUND_COLOR);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	transformation = mesh.constructTransformationMatrix();
	projection = camera.getProjectionMatrix();

	windowContext = static_cast<registre *>(glfwGetWindowUserPointer(window));
	currentShader = (windowContext->textureToggle ? &material.getTextureShader() : &material.getColorShader());
	currentShader->use();
	currentShader->setUniform<float[16]>("projection", projection.m);
	currentShader->setUniform<float[16]>("transformation", transformation.m);

	mesh.draw();

	glfwSwapBuffers(window);
}
