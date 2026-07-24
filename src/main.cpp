#include <scop.hpp>

#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <string.h>

#include "stb_image.h"


// const char *vertexShaderSource = "#version 440 core\n"
// "layout (location = 0) in vec3 aPos;\n"
// "layout (location = 1) in vec3 aColor;\n"
// "out vec3 vertexColor;\n"
// "void main()\n"
// "{\n"
// "	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
// "	vertexColor = aColor;"
// "}\n";


// const char *fragmentShaderSource = "#version 440 core\n"
// "in vec3 vertexColor;\n"
// "out vec4 FragColor;\n"
// "void main()\n"
// "{\n"
// "	FragColor = vec4(vertexColor, 1.0);\n"
// "}\n";


void _on_window_resize(GLFWwindow* window, int width, int height) {

	(void)window;
	glViewport(0, 0, width, height);
	std::cout << "Resizing window" << std::endl;
}

/*
*	The process function responsible of reacting to user inputs.
*
*	Process function means it is called every frame.
*/
void _process_inputs(GLFWwindow* window) {

	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

/*
*	The process function responsible of rendering.
*
*	Process function means it is called every frame.
*/
void _process_render(GLFWwindow* window) {

	(void)window;
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

}

GLFWwindow* instanciate_window()
{
	GLFWwindow* window = NULL;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 600, "./SCOP", NULL, NULL);
	if (window == NULL)
		clean_exit(true, 1);

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		clean_exit(true, 1); 

	return (window);
}

void init(GLFWwindow** window_ptr) {

	if (!glfwInit())
		clean_exit(false, 1); 
	*window_ptr = instanciate_window();

	glfwSetFramebufferSizeCallback(*window_ptr, _on_window_resize);
}

int main() {

	GLFWwindow* window = NULL;

	init(&window);


	// float vertices[] = {
	// 	-0.5f,	-0.5f,	0.0f,	/*color*/	1.0f,	0.0f,	0.0f,
	// 	0.5f,	-0.5f,	0.0f,				0.0f,	1.0f,	0.0f,
	// 	0.0f,	0.5f,	0.0f,				0.0f,	0.0f,	1.0f
	// };

	float rect_vertices[] = {
		0.5f,	0.5f,	0.0f,	/*color*/	1.0f,	0.0f,	0.0f,	/*textcoord*/	1.0f, 1.0f,
		0.5f,	-0.5f,	0.0f,				0.0f,	1.0f,	0.0f,					1.0f, 0.0f, 
		-0.5f,	-0.5f,	0.0f,				0.0f,	0.0f,	1.0f,					0.0f, 0.0f,
		-0.5f,	0.5f,	0.0f,				1.0f,	1.0f,	0.0f,					0.0f, 1.0f
	};

	unsigned int rect_indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	// float text_coord[] = {
	// 	0.0f,	0.0f,
	// 	1.0f,	0.0f,
	// 	0.5f,	1.0f
	// };
	
	// Creating the vertex shader

	Shader	shader("src/SHADERS/shader.vert",
					 "src/SHADERS/shader.frag");
	
	// shader.setUniform<float>("vertexColor", 0.5f);
	shader.use();

	// unsigned int vertexShader;
	// vertexShader = glCreateShader(GL_VERTEX_SHADER); // creating shader object of type VERTEX SHADER
	// glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // attach the code to the shader object
	// glCompileShader(vertexShader); // compiling

	// // checkShaderCompil(vertexShader, "VERTEX_SHADER");

	// // Creating the fragment shader
	// unsigned int fragmentShader;
	// fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// glCompileShader(fragmentShader);

	// // checkShaderCompil(fragmentShader, "FRAGMENT_SHADER");

	// // Linking the vertex shader and the fragment shader into a shader program
	// unsigned int shaderProgram;
	// shaderProgram = glCreateProgram();
	// glAttachShader(shaderProgram, vertexShader);
	// glAttachShader(shaderProgram, fragmentShader);
	// glLinkProgram(shaderProgram);

	// // checkProgramLink(shaderProgram, "SHADER_PROGRAM");

	// // Deleting shader Objects we don't need anymore

	// glDeleteShader(vertexShader);
	// glDeleteShader(fragmentShader);

	// // Render is done through this pipeline
	// glUseProgram(shaderProgram);

	///////

	// // Creating a VAO (Vertex Array Object) to create a rendering profile
	// unsigned int VAO_triangle;
	// glGenVertexArrays(1, &VAO_triangle);

	// // Bind Vertex Array Object
	// glBindVertexArray(VAO_triangle);

	// // Creating a vertex buffer object to store the vertices in the GPU memory
	// unsigned int VBO_triangle;
	// glGenBuffers(1, &VBO_triangle); // creating buffer ID
	// glBindBuffer(GL_ARRAY_BUFFER, VBO_triangle);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // copy vertices data in the buffer

	// // Tell OpenGL how to interpret the vertex data (for the vertex shader)
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// glEnableVertexAttribArray(0);
	// glEnableVertexAttribArray(1);
	
	// ---

	// Creating another VAO for this mesh

	unsigned int VAO_rectangle;
	glGenVertexArrays(1, &VAO_rectangle);
	
	glBindVertexArray(VAO_rectangle);

	// Creating another VBO to use with an EBO
	unsigned int VBO_rectangle;
	glGenBuffers(1, &VBO_rectangle);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_rectangle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect_vertices), rect_vertices, GL_STATIC_DRAW); // copy vertices data in the buffer

	// Creating an Element Buffer Object to use indices
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rect_indices), rect_indices, GL_STATIC_DRAW);

	// Tell OpenGL how to interpret the vertex data (for the vertex shader)
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// --- Texturing the triangle

		// Global texture settings

	// texture repeat
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	// // Generating the texture n1

	// int width, height, nrChannels;
	// stbi_set_flip_vertically_on_load(true);
	// unsigned char *data = NULL;
	
	// data = stbi_load("textures/mire.tga", &width, &height, &nrChannels, 0);
	// if (!data)
	// 	clean_exit(true, 2);

	// printf((const char*)data);
	// printf("%s\n", (const char*)data);


	// unsigned int size = strlen((const char *)data);
	// unsigned int sizeo = sizeof(data);

	
	// printf("size : %u\n", size);


	// printf("Sizeo : %d\n", sizeo);
	// printf("WIDTH : %d\n", width);
	// printf("Size of unsigned char : %ld\n", sizeof(unsigned char));
	// printf("Size of char : %ld\n", sizeof(char));
	// printf("Size of short : %ld\n", sizeof(short));
	// printf("Size of short int : %ld\n", sizeof(short int));

	// printf("Number of channels : %d\n", nrChannels);


	// std::cout << std::endl;
	// for (unsigned int i = 0; i < (unsigned int)(nrChannels * width * height); i++)
	// {
		
	// 	std::cout << (int)data[i];

	// 	if ((i + 1) % 4 == 0)
	// 	{
	// 		data[i] = 0;
	// 		std::cout << std::endl;
	// 	}
	// 	else
	// 		std::cout << " | ";

	// }

	// printf("----\n");

	// std::string content = FileLoader::toString("textures/mire.tga");

	// typedef struct {
   	// 	char  idlength;
   	// 	char  colourmaptype;
   	// 	char  datatypecode;
   	// 	short int colourmaporigin;
   	// 	short int colourmaplength;
   	// 	char  colourmapdepth;
   	// 	short int x_origin;
   	// 	short int y_origin;
   	// 	short width;
   	// 	short height;
   	// 	char  bitsperpixel;
   	// 	char  imagedescriptor;
	// } HEADER;

	// std::cout << "HEADER size is : " << sizeof(HEADER) << std::endl;

	// std::string	header[18] = {
	// 	"id length ", // char
	// 	"colour map type ",
	// 	"data type code ",
	// 	"colour map origin ", // short
	// 	"",
	// 	"colour map length ",
	// 	"",
	// 	"colour map depth ",
	// 	"x origin ",
	// 	"",
	// 	"y origin ",
	// 	"",
	// 	"width ",
	// 	"",
	// 	"height ",
	// 	"",
	// 	"bits per pixel ",
	// 	"image descriptor ",

	// };

	// std::cout << "\n\n TGA HEADER" << std::endl;
	// for (unsigned int i = 0; i < content.size(); i++)
	// {
	// 	if (i < 18 && header[i].size())
	// 	{
	// 		printf("\n");
	// 		std::cout << header[i];
	// 	}
	// 	std::cout << (int)content[i];

	// 	// if ((i + 1) % 4 == 0)
	// 	// 	std::cout << std::endl;
	// 	// else
	// 	// 	std::cout << " | ";

	// }
	// std::cout << std::endl;

	// return (0);

	// unsigned int texture1;
	// glGenTextures(1, &texture1);
	// glBindTexture(GL_TEXTURE_2D, texture1);

	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	
	// // texture mipmaps
	// glGenerateMipmap(GL_TEXTURE_2D);
	// stbi_image_free(data);

	// //Generating the texture n2

	// data = stbi_load("textures/test_picture.tga", &width, &height, &nrChannels, 0);
	// if (!data)
	// 	clean_exit(true, 2);
	
	
	// unsigned int texture2;
	// glGenTextures(1, &texture2);
	// glBindTexture(GL_TEXTURE_2D, texture2);

	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	// glGenerateMipmap(GL_TEXTURE_2D);
	// stbi_image_free(data);
	
	Texture mire("textures/mire.tga", true);
	Texture friends("textures/test_picture.tga", true);

	while (!glfwWindowShouldClose(window)) {
		
		_process_inputs(window);
		_process_render(window);

		// // Updating the color uniform

		// glUseProgram(shaderProgram);
		// float timeValue = glfwGetTime() * 4.0f;
		// float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		// int vertexColorLocation = glGetUniformLocation(shaderProgram, "vertexColor");
		// glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		//// should be in render loop


		// test
		float timeValue = glfwGetTime();
		float turnValue = (sin(timeValue) / 2.0f);
		shader.setUniform<float>("turnValue", turnValue);

		// // To draw the triangle
		// glBindVertexArray(VAO_triangle);
		// glDrawArrays(GL_TRIANGLES, 0, 3);

		// To draw the rectangle
		mire.bind(0);
		shader.setUniform<int>("tex2", 0);
		friends.bind(1);
		shader.setUniform<int>("tex2", 1);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

