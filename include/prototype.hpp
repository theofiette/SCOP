# pragma once

class GLFWwindow;
class Camera;
class Mesh;
struct registre;
class Material;

int		clean_exit(bool should_glfwTerminate, int exit_code);

void 	init(int argc, GLFWwindow** window_ptr, registre *registrePtr);

void	_onWindowResize(GLFWwindow* window, int width, int height);
void	_onScroll(GLFWwindow* window, double x, double y);
void	_processInputs(GLFWwindow* window, Transform &transform);
void	_processRender(GLFWwindow* window, const Camera &camera, const Mesh &mesh, Material &material);
