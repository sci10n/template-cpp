#include "Locator.hpp"
#include <iostream>
#include <utility>

// Locator for naughty developers
const glm::vec2 DummyInputLocator::getMousePos(){
	return glm::vec2(0.0f,0.0f);
}

// Unused since we don't want a response
bool DummyInputLocator::isButtonPressed(int button){
	(void)button;
	return false;
}

// Unused since we don't want a response
bool DummyInputLocator::isKeyPressed(int key){
	(void)key;
	return false;
}

std::map<int,bool> GLFWInputLocator::_keys;
std::map<int,bool> GLFWInputLocator::_buttons;
glm::vec2 GLFWInputLocator::_mousePos = glm::vec2(0.0f,0.0f);
GLFWwindow* GLFWInputLocator::_window;

void GLFWInputLocator::cursor_callback(GLFWwindow* window, double x, double y)
{
		// Supress unised warning
		(void)window;
		_mousePos  = glm::vec2(x,y);
}

void GLFWInputLocator::mouse_callback(GLFWwindow* window, int button, int action, int mods){

	_window = window;
	(void)mods;
		if(action == GLFW_RELEASE){
			_buttons[button] = false;
		}else if(action == GLFW_PRESS){
			_buttons[button] = true;
		}

	// Supress unised warning
}

void GLFWInputLocator::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// Supress unised warning
	(void)scancode;
	(void)mode;
	if(action == GLFW_RELEASE){
		_keys[key] = false;
	}else if(action == GLFW_PRESS){
		_keys[key] = true;
	}

	if ((key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
         || (key == GLFW_KEY_Q && action == GLFW_PRESS))
		glfwSetWindowShouldClose(window, GL_TRUE);
}



const glm::vec2 GLFWInputLocator::getMousePos(){
	return _mousePos;
}

bool GLFWInputLocator::isButtonPressed(int button){
	try
	{
		return _buttons.at(button);
	}
	catch (std::out_of_range& e)
	{
		return false;
	}
	return false;
}

bool GLFWInputLocator::isKeyPressed(int key){
	try
	{
		return _keys.at(key);
	}
	catch (std::out_of_range& e)
	{
		return false;
	}
	return false;
}

GLFWwindow* GLFWInputLocator::getWindow(){
  return _window;
}

InputLocator* Locator::_inputLocator = nullptr;
DummyInputLocator Locator::_dummyInput;

InputLocator* Locator::input()
{
	if(_inputLocator != nullptr)
		return _inputLocator;
	else
		return &_dummyInput;
} 

void Locator::setInput(InputLocator* input){
	_inputLocator= input;
}
