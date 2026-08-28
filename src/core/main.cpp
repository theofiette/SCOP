#include "core/scop.hpp"
#include "core/classes.hpp"

int main(int argc, char *argv[]) {

	GLFWwindow*		window = NULL;
	registre 		data = {};

	try {

		init(argc, &window, &data);

		Mesh 		mesh(argv[1]);
		Material	material(argc == 3 ? argv[2] : BASIC_TEXTURE_PATH);
		Camera		camera;

		while (!glfwWindowShouldClose(window)) {

			_processInputs(window, mesh.getTransform());
			_processRender(window, camera, mesh, material);
			glfwPollEvents();
		}

		glfwTerminate(); }
	
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
