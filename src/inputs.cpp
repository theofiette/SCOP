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
	GLFWwindow* window, float &sensi, bool &sensiAffectsRotation)
{
	static bool		sensiRotationKeyHold = false;
	static bool		sensiVariationKeyHold = false;

	if (glfwGetKey(window, GLFW_KEY_KP_MULTIPLY) == GLFW_PRESS)
	{
		if (sensiRotationKeyHold)
			return;
		sensiAffectsRotation = !sensiAffectsRotation;
		sensiRotationKeyHold = true;
	}
	else if (sensiRotationKeyHold)
		sensiRotationKeyHold = false;

	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
	{
		if (sensiVariationKeyHold)
			return;
		int input = 0;
		if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
			input += 1;
		if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
			input -= 1;
		
		sensi = std::clamp(sensi + (input * SENSIBILITY_STEP), SENSIBILITY_MIN, SENSIBILITY_MAX);
	}
	else if (sensiVariationKeyHold)
		sensiVariationKeyHold = false;
}

void _processTransformationInputs(GLFWwindow *window, vec3<float> &translation, 
		vec3<float> &rotation, float sensi, bool sensiAffectsRotation)
{
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		translation.y += SENSIBILITY_BASE * sensi;	
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		translation.y -= SENSIBILITY_BASE * sensi;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		translation.x -= SENSIBILITY_BASE * sensi;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		translation.x += SENSIBILITY_BASE * sensi;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		rotation.x += sensiAffectsRotation ? SENSIBILITY_BASE * sensi / 4.0f : 0.1f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		rotation.x -= sensiAffectsRotation ? SENSIBILITY_BASE * sensi / 4.0f : 0.1f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		rotation.z -= sensiAffectsRotation ? SENSIBILITY_BASE * sensi / 4.0f : 0.1f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		rotation.z += sensiAffectsRotation ? SENSIBILITY_BASE * sensi / 4.0f : 0.1f;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		rotation.y -= sensiAffectsRotation ? SENSIBILITY_BASE * sensi / 4.0f : 0.1f;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		rotation.y += sensiAffectsRotation ? SENSIBILITY_BASE * sensi / 4.0f : 0.1f;
	
	registre *reg = static_cast<registre *>(glfwGetWindowUserPointer(window));
	if (reg->zMarker)
	{
		translation.z += SENSIBILITY_BASE * sensi * reg->zMarker;
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
	GLFWwindow* window, vec3<float> &translation, vec3<float> &rotation) {

	static float	sensi = 0.5;
	static bool		sensiAffectsRotation = false;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		return ;
	}

	_processRenderInputs(window);
	_processSensibilityInputs(window, sensi, sensiAffectsRotation);
	_processTransformationInputs(window, translation, rotation, sensi, sensiAffectsRotation);
}

