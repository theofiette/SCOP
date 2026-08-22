#include <scop.hpp>

/*
*	The process function responsible for rendering.
*
*	Process function means it is called every frame.
*/
void _processRender(GLFWwindow* window, const vec3<float> &translation,
	const vec3<float>rotation, mat4x4 &transformation)
{
	
	(void)window;
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	transformation = _createTransformationMat(translation, rotation);

}

int main(int argc, char *argv[]) {

	if (argc != 2 && argc != 3)
	{
		std::cerr << "usage : [programme] [.obj file path] (.tga file path)" << std::endl;
		clean_exit(false, 1);
	}

	GLFWwindow* window = NULL;

	init(&window);

	Shader	texture_shader("src/SHADERS/shader_texture.vert",
								"src/SHADERS/shader_texture.frag");
	Shader	color_shader("src/SHADERS/shader_color.vert",
								"src/SHADERS/shader_color.frag");
	
	Mesh mesh(argv[1]);

	//TODO: Could get the texture directly via parsing the .mtl
	Texture texture(argc == 3 ? argv[2] : BASIC_TEXTURE_PATH, true);

	// PROJECTION MATRIX

	mat4x4 projection = _createProjectionMat();

	// TRANSFORMATION MATRIX
	
	mat4x4		transformation;
	vec3<float> translation;
	vec3<float>	rotation;

	struct registre registre = {};
	glfwSetWindowUserPointer(window, static_cast<void *>(&registre));

	bool textureToggle = false;

	texture.bind(0);
	texture_shader.setUniform<int>("tex", 0);

	while (!glfwWindowShouldClose(window)) {
		
		_processInputs(window, translation, rotation);
		_processRender(window, translation, rotation, transformation);
		
		texture_shader.setUniform<float[16]>("projection", projection.m);
		texture_shader.setUniform<float[16]>("transformation", transformation.m);
		color_shader.setUniform<float[16]>("projection", projection.m);
		color_shader.setUniform<float[16]>("transformation", transformation.m);
		// color_shader.use();

		mesh.draw();

		if (registre.shaderSwitch)
		{
			textureToggle = !textureToggle;
			registre.shaderSwitch = false;
		}
		if (textureToggle)
			texture_shader.use();
		else
			color_shader.use();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

