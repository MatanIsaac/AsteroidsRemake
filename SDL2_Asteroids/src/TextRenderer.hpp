#pragma once
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include <SDL2/SDL_ttf.h>

#include "Texture.hpp"
#include "Timer.h"

namespace venture
{
	// To render the text after instantiating a TextRenderer Object, Call CreateText(),
	// Can only be called once, no need to call it every frame. (for creating a text at run time too)
	// NOTE: if you want to use the setters such as "SetFont"/"SetTextColor"/"SetTextSize" 
	// You MUST call them before you call "CreateText" as the text attributes cannot be changed at runtime.
	// I.E Setting the font to a custom one / changing the color, must happen before we create the text.

	/**
	 * @brief A custom deleter for the Texture class.
	 *
	 * Facilitates custom cleanup logic for TTF_Font instances, ensuring that any
	 * associated resources are properly released.
	 */
	struct SDLFontDeleter
	{
		void operator()( TTF_Font* font ) const
		{
			TTF_CloseFont( font );
		}
	};

	class TextRenderer
	{
	public:
		
		/// Constructors & Destructors
		///--------------------------------------------------------

		/**
		* @brief Constructor for TextRenderer class.
		* @param text The text to render
		* @param textSize The size of the text.
		* @param color textColor of the text.
		*/
		TextRenderer( const char* text, uint8_t textSize, SDL_Color textColor );
		
		/**
		 * @brief Destructor for the TextRenderer class
		 */
		~TextRenderer();

		/// Utility
		///--------------------------------------------------------

		/**
		 * @brief Cleans resources (also used for the custom TextRenderer deleter)
		 */
		void Clean();

		/**
		 * @brief Creates the text to render 
		 */
		void CreateText();
		
		/**
		 * @brief Renders the text at a certain position
		 * @param position The position of the text to render
		 */
		void RenderText( SDL_Renderer* renderer, const glm::vec2& position );

		/**
		 * @brief Recreates the text texture
		 * @param newText The new text to render 
		 */
		void UpdateText( const std::string& newText );


		/// Setters 
		///--------------------------------------------------------
		
		/**
		 * @brief Set a custom font
		 * @param newFont The new font to set for the text
		 */
		void SetFont( std::unique_ptr<TTF_Font, SDLFontDeleter> newFont ) { mFont = std::move( newFont ); }
		
		/**
		 * @brief Set the text color
		 * @param newColor The new color for the text
		 */
		void SetTextColor( SDL_Color newColor ) { mTextColor = newColor; }
		
		/**
		 * @brief Set the text size
		 * @param newSize The new size for the text
		 */
		void SetTextSize( int newSize ) { mTextSize = newSize; }

		/// Getters 
		///--------------------------------------------------------
		
		/**
		 * @brief Get the text font
		 */
		std::unique_ptr<TTF_Font, SDLFontDeleter>& GetFont() { return mFont; }
		
		/**
		 * @brief Get the text texture
		 */
		std::unique_ptr<Texture, TextureDeleter>& GetTextTexture() { return mTexture; }
		
		/**
		 * @brief Get the text size
		 */
		const glm::ivec2 GetTextSize() const { return mTexture->GetTextureSize(); }
		
		/**
		 * @brief Get the text position
		 */
		glm::vec2& GetTextPosition() { return mPosition; }

		/**
		 * @brief Get the text color
		 */
		const SDL_Color& GetTextColor() { return mTextColor; }

		
	private:
		// The font of the text
		std::unique_ptr<TTF_Font, SDLFontDeleter> mFont;
		// The texture of the text
		std::unique_ptr<Texture, TextureDeleter> mTexture;
		// The text to render
		std::string mText;
		// The text color
		SDL_Color mTextColor;
		// The text size
		int mTextSize;
		// The text position
		glm::vec2 mPosition;
	};

	/**
	 * @brief A custom deleter for the Texture class.
	 *
	 * Facilitates custom cleanup logic for TextRenderer instances, ensuring that any
	 * associated resources are properly released.
	 */
	struct TextRendererDeleter
	{
		void operator()( TextRenderer* t ) const
		{
			t->Clean();
			delete t;
		}
	};
}