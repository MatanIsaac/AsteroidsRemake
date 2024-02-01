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
	// Enumeration to differentiate between mouse buttons
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
		/**
		 * @brief Retrieves the static instance of the class, creating one if it doesn't exist.
		 */
		static InputManager* get()
		{
			if ( s_Instance == nullptr )
			{
				s_Instance = new InputManager();
			}
			return s_Instance;
		}

		/// Input
		///--------------------------------------------------------
		
		/**
		 * @brief Processes input events.
		 */
		void ProcessInput( SDL_Event* event );
		
		/**
		 * @brief Updates the state of inputs from the previous frame.
		 */
		void UpdatePrevInput();

		/// State Checks
		///--------------------------------------------------------
		
		/**
		 * @brief Checks if a key is held down
		 */
		bool isKeyDown( SDL_Scancode scancode );
		
		/**
		 * @brief Checks if a key is pressed
		 */
		const bool isKeyPressed( SDL_Scancode scancode ) const;
		
		/**
		 * @brief Checks if a key is released
		 */
		const bool isKeyReleased( SDL_Scancode scancode ) const;
		
		/**
		 * @brief Checks if a mouse button is held down
		 */
		const bool isMouseButtonDown( MouseButton button ) const;
		
		/**
		 * @brief Checks if a mouse button is pressed
		 */
		const bool isMouseButtonPressed( MouseButton button ) const;
		
		/**
		 * @brief Checks if a mouse button is released
		 */
		const bool isMouseButtonReleased( MouseButton button ) const;
		
		/**
		 * @brief Checks if a mouse button is locked (held down)
		 */
		const bool IsMouseLocked() const { return mMouseLock; }
		
		/**
		 * @brief Checks if a key is locked(held down)
		 */
		const bool IsKeyboardLocked() const { return mKeyLock; }

		/// Getters
		///--------------------------------------------------------

		/**
		 * @brief Get the mouse's x position
		 */
		int GetMouseX() const { return mMouseXPos; }
		
		/**
		 * @brief Get the mouse's y position
		 */
		int GetMouseY() const { return mMouseYPos; }
		
		/**
		 * @brief Get the mouse's position
		 */
		glm::ivec2 GetMousePosition();


		/// Utility
		///--------------------------------------------------------
		
		/**
		 * @brief Locks the mouse (I.E cannot "trigger" a button if the mouse is locked)
		 */
		void LockMouse() { mMouseLock = true; }
		
		/**
		 * @brief Locks the keyboard
		 */
		void LockKeyboard() { mKeyLock = true; }
		
		/**
		 * @brief Unlocks the mouse
		 */
		void UnlockMouse() { mMouseLock = false; }
		
		/**
		 * @brief Unlocks the keyboard 
		 */
		void UnlockKeyboard() { mKeyLock = false; }

	private:

		// Private constructor and destructor to follow the singleton design pattern.
		
		/**
		 * @brief The InputManager constructor 
		 */
		InputManager();
		
		/**
		 * @brief The InputManager destructor
		 */
		~InputManager();

		// The static instance of the class (to follow the singleton design pattern)
		static InputManager* s_Instance;

		// Previous keyboard state.
		uint8_t* mPrevKeyState;

		// Current keyboard state.
		const uint8_t* mCurrKeyState;

		// Number of keys tracked.
		int mKeyLength;

		// Previous mouse state.
		uint32_t mPrevMouseState;
		// Current mouse state.
		uint32_t mCurrMouseState;

		// Mouse positions.
		int mMouseXPos, mMouseYPos; 
		// Lock states for mouse and keyboard.
		bool mMouseLock, mKeyLock; 

		// Deleted constructors and assignment operators for Singleton enforcement.
		InputManager( InputManager&& ) = delete;
		InputManager( const InputManager& ) = delete;
		InputManager& operator=( InputManager&& ) = delete;
		InputManager& operator=( const InputManager& ) = delete;
	};
}