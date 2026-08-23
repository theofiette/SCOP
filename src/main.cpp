#include "scop.hpp"
#include "classes.hpp"

/*
*	The process function responsible for rendering.
*
*	Process function means it is called every frame.
*/
void _processRender(GLFWwindow* window, mat4x4 &projection, Mesh &mesh, registre &registre,
	Material &material)
{
	Shader		*currentShader;
	static bool	textureToggle = false;
	mat4x4	transformation;

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	transformation = _createTransformationMat(mesh.getTransform());

	if (registre.shaderSwitch)
	{
		textureToggle = !textureToggle;
		registre.shaderSwitch = false;
	}

	currentShader = (textureToggle ? &material.getTextureShader() : &material.getColorShader());
	currentShader->use();
	currentShader->setUniform<float[16]>("projection", projection.m);
	currentShader->setUniform<float[16]>("transformation", transformation.m);
	mesh.draw();

	glfwSwapBuffers(window);
}

int main(int argc, char *argv[]) {

	if (argc != 2 && argc != 3)
	{
		std::cerr << "usage : [programme] [.obj file path] (.tga file path)" << std::endl;
		clean_exit(false, 1);
	}

	GLFWwindow*		window = NULL;
	struct registre registre = {};

	init(&window, &registre);

	Mesh 		mesh(argv[1]);
	Material	material(argc == 3 ? argv[2] : BASIC_TEXTURE_PATH);
	// TODO : camera classe
	mat4x4 		projection = _createProjectionMat();

	while (!glfwWindowShouldClose(window)) {
		
		_processInputs(window, mesh.getTransform());
		_processRender(window, projection, mesh, registre, material);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

