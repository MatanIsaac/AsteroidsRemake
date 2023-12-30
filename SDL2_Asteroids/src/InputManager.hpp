/**
 * @class InputManager
 * @brief Singleton class for managing input in SDL2 applications.
 *
 * The InputManager class is designed to handle keyboard and mouse input in an SDL2 application.
 * It provides methods to check the state of individual keys and mouse buttons, including whether
 * they are currently down, just pressed, or just released. The class uses the Singleton design
 * pattern to ensure only one instance manages input across the application.
 *
 * Example usage:
 * @code
 * venture::InputManager* inputManager = venture::InputManager::get();
 * if (inputManager->isKeyPressed(SDL_SCANCODE_SPACE)) {
 *     // Handle space-bar pressed event
 * }
 * if (inputManager->isMouseButtonDown(venture::MouseButton::LEFT)) {
 *     // Handle left mouse button down event
 * }
 * // Update input state at the end of the frame
 * inputManager->UpdatePrevInput();
 * @endcode
 *
 * @note Make sure to call UpdatePrevInput() at the end of each frame to correctly update
 * the previous state of the inputs.
 */

#pragma once
#include <SDL2/SDL.h>
#include <cstdint>
#include <glm/glm.hpp>

namespace venture
{
	enum class MouseButton
	{
		LEFT = 1,
		RIGHT,
		MIDDLE,
		BACK,
		FORWARD,
	};


	class InputManager
	{
	public:

		static InputManager* get()
		{
			if ( s_Instance == nullptr )
			{
				s_Instance = new InputManager();
			}
			return s_Instance;
		}

		void ProcessInput( SDL_Event* event );
		void UpdatePrevInput();

		bool isKeyDown( SDL_Scancode scancode );
		const bool isKeyPressed( SDL_Scancode scancode ) const;
		const bool isKeyReleased( SDL_Scancode scancode ) const;
		const bool isMouseButtonDown( MouseButton button ) const;
		const bool isMouseButtonPressed( MouseButton button ) const;
		const bool isMouseButtonReleased( MouseButton button ) const;

		int GetMouseX() const { return mMouseXPos; }
		int GetMouseY() const { return mMouseYPos; }
		
		glm::ivec2 GetMousePosition();

		const bool IsMouseLocked() const { return mMouseLock; }
		const bool IsKeyboardLocked() const { return mKeyLock; }

		void LockMouse() { mMouseLock = true; }
		void LockKeyboard() { mKeyLock = true; }
		
		void UnlockMouse() { mMouseLock = false; }
		void UnlockKeyboard() { mKeyLock = false; }

	private:
		InputManager();
		~InputManager();

		static InputManager* s_Instance;

		uint8_t* mPrevKeyState;
		const uint8_t* mCurrKeyState;
		int mKeyLength;
		int mMouseLength;

		uint32_t mPrevMouseState;
		uint32_t mCurrMouseState;

		int mMouseXPos;
		int mMouseYPos;

		bool mMouseLock;
		bool mKeyLock;

	private:
		// Unwanted deleted constructors
		InputManager( InputManager&& ) = delete;
		InputManager( const InputManager& ) = delete;
		InputManager& operator=( InputManager&& ) = delete;
		InputManager& operator=( const InputManager& ) = delete;
	};
}