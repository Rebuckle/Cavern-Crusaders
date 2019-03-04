#include "InputHandler.h"

//--- Static Variables ---//
InputHandler* InputHandler::inst = 0;



//--- Constructor and Destructor ---//
InputHandler::InputHandler()
{

}

InputHandler::~InputHandler()
{
	//Delete the singleton instance
	delete inst;
	inst = nullptr;
}



//--- Setters and Getters ---//
//Keyboard
bool InputHandler::getKeyPress(KeyCode key) const
{
	//If the key requested is set to pressed, it was pressed this exact frame
	return (keyboardStates[(int)key] == InputState::Pressed);
}

bool InputHandler::getKeyRelease(KeyCode key) const
{
	//If the key requested is set to released, it was released this exact frame
	return (keyboardStates[(int)key] == InputState::Released);
}

bool InputHandler::getKey(KeyCode key) const
{
	//If the key requested is set to pressed OR set to held, it is currently down and so should return true
	return (keyboardStates[(int)key] == InputState::Pressed || keyboardStates[(int)key] == InputState::Held);
}

//--- Methods ---//
void InputHandler::updateInputs()
{
	//Loop through the keyboard buttons and update their states. If they were pressed last frame, they are now held. If they were released last frame, they are now idle.
	for (int i = 0; i < NUM_KEY_CODES; i++)
	{
		if (keyboardStates[i] == InputState::Idle)
			continue;

		if (keyboardStates[i] == InputState::Pressed)
			keyboardStates[i] = InputState::Held;
		else if (keyboardStates[i] == InputState::Released)
			keyboardStates[i] = InputState::Idle;
	}
}

//--- Singleton Instance ---//
InputHandler* InputHandler::getInstance()
{
	//Generate the singleton if it hasn't been created yet
	if (!inst)
		inst = new InputHandler();

	//Return the singleton
	return inst;
}
