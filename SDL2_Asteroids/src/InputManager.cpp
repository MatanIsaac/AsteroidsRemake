#include "InputManager.hpp"
#include "Game.h"

namespace venture
{
	InputManager* InputManager::s_Instance = nullptr;

	InputManager::InputManager()
		: mMouseLock( false ), mKeyLock( false )
	{
		mCurrKeyState = SDL_GetKeyboardState( &mKeyLength );
		mPrevKeyState = new uint8_t[ mKeyLength ];
		memcpy( mPrevKeyState, mCurrKeyState, mKeyLength );
	}

	InputManager::~InputManager()
	{
		delete[] mPrevKeyState;
		mPrevKeyState = nullptr;
	}

	void InputManager::ProcessInput( SDL_Event* event )
	{
		auto game =Game::Getinstance();
		while ( SDL_PollEvent( event ) )
		{
			if ( event->type == SDL_QUIT )
			{
				game->Quit();
			}
		}
		
		mCurrMouseState = SDL_GetMouseState( &mMouseXPos, &mMouseYPos );

	}

	void InputManager::UpdatePrevInput()
	{
		memcpy( mPrevKeyState, mCurrKeyState, mKeyLength );
		mPrevMouseState = mCurrMouseState;
	}

	bool InputManager::isKeyDown( SDL_Scancode scancode )
	{
		if (mKeyLock)
			return false; 
		return mCurrKeyState[ scancode ];
	}

	const bool InputManager::isKeyPressed( SDL_Scancode scancode ) const
	{
		if ( mKeyLock )
			return false; 

		return !mPrevKeyState[ scancode ] && mCurrKeyState[ scancode ];
	}

	const bool InputManager::isKeyReleased( SDL_Scancode scancode ) const
	{
		return mPrevKeyState[ scancode ] && !mCurrKeyState[ scancode ];
	}

	const bool InputManager::isMouseButtonDown( MouseButton button ) const
	{
		if ( mMouseLock )
			return false; 

		uint32_t mask = 0;
		switch ( button )
		{
		case MouseButton::LEFT:
			mask = SDL_BUTTON_LMASK;
			break;
		case MouseButton::RIGHT:
			mask = SDL_BUTTON_RMASK;
			break;
		case MouseButton::MIDDLE:
			mask = SDL_BUTTON_MMASK;
			break;
		case MouseButton::BACK:
			mask = SDL_BUTTON_X1MASK;
			break;
		case MouseButton::FORWARD:
			mask = SDL_BUTTON_X2MASK;
			break;
		}
		return ( mCurrMouseState & mask );
	}

	const bool InputManager::isMouseButtonPressed( MouseButton button ) const
	{
		if ( mMouseLock )
			return false;

		uint32_t mask = 0;
		switch ( button )
		{
		case MouseButton::LEFT:
			mask = SDL_BUTTON_LMASK;
			break;
		case MouseButton::RIGHT:
			mask = SDL_BUTTON_RMASK;
			break;
		case MouseButton::MIDDLE:
			mask = SDL_BUTTON_MMASK;
			break;
		case MouseButton::BACK:
			mask = SDL_BUTTON_X1MASK;
			break;
		case MouseButton::FORWARD:
			mask = SDL_BUTTON_X2MASK;
			break;
		}
		return !( mPrevMouseState & mask ) && ( mCurrMouseState & mask );
	}

	const bool InputManager::isMouseButtonReleased( MouseButton button ) const
	{
		uint32_t mask = 0;
		switch ( button )
		{
		case MouseButton::LEFT:
			mask = SDL_BUTTON_LMASK;
			break;
		case MouseButton::RIGHT:
			mask = SDL_BUTTON_RMASK;
			break;
		case MouseButton::MIDDLE:
			mask = SDL_BUTTON_MMASK;
			break;
		case MouseButton::BACK:
			mask = SDL_BUTTON_X1MASK;
			break;
		case MouseButton::FORWARD:
			mask = SDL_BUTTON_X2MASK;
			break;
		}
		return ( mPrevMouseState & mask ) && !( mCurrMouseState & mask );
	}

	glm::ivec2 InputManager::GetMousePosition()
	{
		auto mousePos = glm::ivec2(mMouseXPos,mMouseYPos);
		return mousePos;
	}


}