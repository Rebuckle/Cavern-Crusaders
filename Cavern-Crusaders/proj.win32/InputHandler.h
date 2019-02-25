#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "cocos2d.h"
using namespace cocos2d;

enum InputState
{
	Idle,
	Pressed,
	Released,
	Held
};

#define NUM_KEY_CODES (int)cocos2d::EventKeyboard::KeyCode::KEY_PLAY + 1
typedef cocos2d::EventKeyboard::KeyCode KeyCode;

class InputHandler
{
protected:
	//--- Constructor ---//
	InputHandler(); //Singleton pattern

public:
	//--- Destructor ---/
	~InputHandler();

	//--- Getters ---//
	//Keyboard
	bool getKeyPress(KeyCode key) const;
	bool getKeyRelease(KeyCode key) const;
	bool getKey(KeyCode key) const;

	//--- Methods ---//
	void initInputs(); //This HAS to be called ONCE. If not, no inputs will ever be read
	void updateInputs(); //This HAS to be called EVERY FRAME. If not, the inputs won't be synced to the current frame

	//--- Singleton Instance ---//
	static InputHandler* getInstance(); //Singleton 

private:
	//--- Private Data ---//
	//Keyboard
	InputState keyboardStates[NUM_KEY_CODES]; //States for all of the keycodes in cocos2D

	//--- Singleton Instance ---//
	static InputHandler* inst; //Singleton pattern
};

#define INPUTS InputHandler::getInstance()

#endif
