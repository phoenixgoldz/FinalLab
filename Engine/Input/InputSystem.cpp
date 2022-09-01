#include "InputSystem.h"
#include <iostream>
#include <SDL.h>

using namespace std;

namespace phoenix
{
	//keyboard layout
	const uint32_t key_enter = SDL_SCANCODE_RETURN;
	const uint32_t key_space = SDL_SCANCODE_SPACE;
	const uint32_t key_up = SDL_SCANCODE_W;
	const uint32_t key_down = SDL_SCANCODE_S;
	const uint32_t key_left = SDL_SCANCODE_A;
	const uint32_t key_right = SDL_SCANCODE_D;
	const uint32_t key_escape = SDL_SCANCODE_ESCAPE;

	//mouse keys
	const uint32_t button_left = 0;
	const uint32_t button_middle = 1;
	const uint32_t button_right = 2;

	void InputSystem::Initialize()
	{
		const uint8_t* keyboardState = SDL_GetKeyboardState(&m_numKeys);

		m_keyboardState.resize(m_numKeys);
		copy(keyboardState, keyboardState + m_numKeys, m_keyboardState.begin());

		m_PrevKeyboardState = m_keyboardState;
	}

	void InputSystem::Shutdown()
	{
		//
	}

	void InputSystem::Update()
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		//save prev keyboard state
		m_PrevKeyboardState = m_keyboardState;

		//get current state
		const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
		copy(keyboardState, keyboardState + m_numKeys, m_keyboardState.begin());

		cout << m_keyboardState[SDL_SCANCODE_A] << endl;

		//MOUSE STATE
		m_prevMouseButtonState = m_mouseButtonState;
		int x, y;
		uint32_t buttons = SDL_GetMouseState(&x, &y);
		m_mousePosition = phoenix::Vector2{ x , y };
		m_mouseButtonState[0] = buttons & SDL_BUTTON_LMASK; // buttons [0001] & [0RML] 
		m_mouseButtonState[1] = buttons & SDL_BUTTON_MMASK; // buttons [0010] & [0RML] 
		m_mouseButtonState[2] = buttons & SDL_BUTTON_RMASK; // buttons [0100] & [0RML]

	}

	//keyboard input
	InputSystem::KeyState InputSystem::GetKeyState(uint32_t key)
	{
		KeyState keystate = Idle;

		bool buttonDown = GetKeyDown(key);
		bool prevButtonDown = GetPreviousKeyDown(key);

		if (buttonDown && prevButtonDown)
		{
			 keystate = Held;

		}
		else if (buttonDown && (!prevButtonDown))
		{
			 keystate = Pressed;
		}
		else if (!buttonDown && prevButtonDown)
		{
			 keystate = Released;
		}
		return keystate;
	}
	// mouse input
	InputSystem::KeyState InputSystem::GetButtonState(uint32_t button)
	{
		KeyState keystate = Idle;

		bool buttonDown = GetButtonDown(button);
		bool prevButtonDown = GetPreviousButtonDown(button);

		if (buttonDown && prevButtonDown)
		{
			keystate = Held;

		}
		else if (buttonDown && (!prevButtonDown))
		{
			keystate = Pressed;
		}
		
		else if (!buttonDown && prevButtonDown)
		{
			keystate = Released;
		}
		return keystate;
	}
}
