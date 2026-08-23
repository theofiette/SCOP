#include "scop.hpp"

void _onWindowResize(GLFWwindow* window, int width, int height) {

	(void)window;
	glViewport(0, 0, width, height);

}

/*
*	The function responsible to catch a user scroll input.
*	Due to the functionnement of GLFW, this function isn't called every frame, but in 
*	reaction to the scroll input
*/
void _onScroll(GLFWwindow* window, double x, double y) {
	
	int	*zMarker;
	
	zMarker = static_cast<int *>(glfwGetWindowUserPointer(window));
	(y > 0 ? *zMarker += 1 : *zMarker -= 1);
	
	(void)x;
}

void _processSensibilityInputs(
	GLFWwindow* window, float &sensi, bool &sensiOnRotation)
{
	static bool		sensiRotationKeyHold = false;
	static bool		sensiVariationKeyHold = false;
	int 			inputAxis = 0;

	if (glfwGetKey(window, GLFW_KEY_KP_MULTIPLY) == GLFW_PRESS)
	{
		if (sensiRotationKeyHold) 	return;
		sensiOnRotation = !sensiOnRotation;
		sensiRotationKeyHold = true;
	}
	else if (sensiRotationKeyHold)
		sensiRotationKeyHold = false;

	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
	{
		if (sensiVariationKeyHold) return;
		if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
			inputAxis += 1;
		if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
			inputAxis -= 1;	
		sensi = std::clamp(sensi + (inputAxis * SENSIBILITY_STEP), SENSIBILITY_MIN, SENSIBILITY_MAX);
	}
	else if (sensiVariationKeyHold) sensiVariationKeyHold = false;
}

void _processTransformationInputs(GLFWwindow *window, Transform &transform, float sensi, bool sensiOnRotation)
{
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		transform.translation.y += SENSI_BASE * sensi;	
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		transform.translation.y -= SENSI_BASE * sensi;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		transform.translation.x -= SENSI_BASE * sensi;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		transform.translation.x += SENSI_BASE * sensi;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		transform.rotation.x += sensiOnRotation ? SENSI_BASE * sensi / 4.0f : 0.1f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		transform.rotation.x -= sensiOnRotation ? SENSI_BASE * sensi / 4.0f : 0.1f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		transform.rotation.z -= sensiOnRotation ? SENSI_BASE * sensi / 4.0f : 0.1f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		transform.rotation.z += sensiOnRotation ? SENSI_BASE * sensi / 4.0f : 0.1f;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		transform.rotation.y -= sensiOnRotation ? SENSI_BASE * sensi / 4.0f : 0.1f;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		transform.rotation.y += sensiOnRotation ? SENSI_BASE * sensi / 4.0f : 0.1f;
	
	registre *reg = static_cast<registre *>(glfwGetWindowUserPointer(window));
	if (reg->zMarker)
	{
		transform.translation.z += SENSI_BASE * sensi * reg->zMarker;
		reg->zMarker = 0;
	}
}

void _processRenderInputs(GLFWwindow *window)
{
	static bool	shaderSwitchKeyHold = false;

	if (glfwGetKey(window, GLFW_KEY_APOSTROPHE))
	{
		if (shaderSwitchKeyHold)
			return;
		shaderSwitchKeyHold = true;

		registre *reg = static_cast<registre *>(glfwGetWindowUserPointer(window));
		reg->shaderSwitch = true;
	}
	else if (shaderSwitchKeyHold)
		shaderSwitchKeyHold = false;
}

/*
*	The process function responsible of reacting to user inputs.
*
*	Process function means it is called every frame.
*/
void _processInputs(
	GLFWwindow* window, Transform &transform) {

	static float	sensi = 0.5;
	static bool		sensiOnRotation = false;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		return ;
	}

	_processRenderInputs(window);
	_processSensibilityInputs(window, sensi, sensiOnRotation);
	_processTransformationInputs(window, transform, sensi, sensiOnRotation);
}

