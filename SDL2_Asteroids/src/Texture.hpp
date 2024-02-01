#pragma once
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <glm/glm.hpp>
#include <string>

namespace venture
{

	struct SDLTextureDeleter
	{
		void operator()( SDL_Texture* sdl_t ) const
		{
			SDL_DestroyTexture( sdl_t );
		}
	};

	class Texture
	{

	public:

		/// Constructors & Destructors
		///--------------------------------------------------------

		/**
		* @brief Constructor for Texture class.
		*/
		Texture();
		
		/**
		* @brief Copy-Constructor for Texture class.
		*/
		Texture( Texture&& other ) noexcept;
		
		/**
		* @brief Destructor for Texture class.
		*/
		~Texture();

		/**
		 * @brief Creates a texture from an image file.
		 * @param renderer The SDL renderer.
		 * @param path The path to the image file.
		 * @return true on success, false on failure.
		 */
		bool CreateTexture( SDL_Renderer* renderer, std::string path );
		
		/**
		 * @brief Creates a texture from a text string.
		 * @param renderer The SDL renderer.
		 * @param font The font to use for the text.
		 * @param textureText The text string.
		 * @param textColor The color of the text.
		 * @return true on success, false on failure.
		 */
		bool CreateTextureFromText( SDL_Renderer* renderer, TTF_Font* font, std::string textureText, SDL_Color textColor );

		/**
		 * @brief Renders the texture at specified position.
		 * @param renderer The SDL renderer.
		 * @param xPos The x position to render the texture.
		 * @param yPos The y position to render the texture.
		 */
		void Render( SDL_Renderer* renderer, int xPos, int yPos );
		
		/**
		 * @brief Renders a frame of the texture with optional clipping and flipping.
		 * @param renderer The SDL renderer.
		 * @param xPos The x position to render the texture.
		 * @param yPos The y position to render the texture.
		 * @param clip Optional clipping rectangle to render a part of the texture.
		 * @param flip SDL_RendererFlip value to flip the texture horizontally or vertically.
		 */
		void RenderFrame( SDL_Renderer* renderer, int xPos, int yPos, SDL_Rect* clip, SDL_RendererFlip flip );
		
		/**
		 * @brief Cleans up the texture, preparing it for deletion or reuse.
		 */
		void Clean();
		
		/**
		 * @brief Gets the size of the texture.
		 */
		const glm::ivec2& GetTextureSize() const { return mSize; }
		
		/**
		 * @brief Sets the size of the texture.
		 * @param newSize The new size (width and height) to set.
		 */
		void SetTextureSize( const glm::ivec2& newSize ) { mSize = newSize; }

		/**
		 * @brief Sets the blending mode of the texture.
		 * @param blending The SDL_BlendMode to use for the texture.
		 */
		void SetBlendMode( SDL_BlendMode blending );

		/**
		 * @brief Sets the alpha value (transparency) of the texture.
		 * @param alpha The alpha value to set (0-255).
		 */
		void setAlpha( Uint8 alpha );

		/**
		 * @brief Sets the color modulation of the texture.
		 * @param newColor The SDL_Color to apply to the texture.
		 */
		void SetTextureColor( SDL_Color newColor );

	private:
		// Managed pointer to the SDL_Texture.
		std::unique_ptr<SDL_Texture, SDLTextureDeleter> mTexture;
		// Size (width and height) of the texture.
		glm::ivec2 mSize;
	};

	/**
	 * @brief A custom deleter for the Texture class.
	 *
	 * Facilitates custom cleanup logic for Texture instances, ensuring that any
	 * associated resources are properly released.
	 */
	struct TextureDeleter
	{
		void operator()( Texture* t ) const
		{
			t->Clean();
			delete t;
		}
	};


}