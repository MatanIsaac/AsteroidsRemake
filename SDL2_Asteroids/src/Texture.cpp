#include "Texture.hpp"
#include <cstdio>

namespace venture
{
	Texture::Texture()
		: mTexture( nullptr )
		, mSize( glm::ivec2() )
	{

	}

	Texture::Texture( Texture&& other ) noexcept

		: mSize( other.mSize ), mTexture( std::move( other.mTexture ) )
	{
		other.SetTextureSize( glm::ivec2( 0, 0 ) );
	}

	Texture::~Texture() { Clean(); }

	bool Texture::CreateTexture( SDL_Renderer* renderer, std::string path )
	{

		SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
		if ( loadedSurface == nullptr )
		{
			printf( "Unable to load image %s! Error: %s\n", path.c_str(), IMG_GetError() );
			return false;
		}


		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0, 0 ) );

		SDL_Texture* newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if ( newTexture == nullptr )
		{
			printf( "Failed to create texture from %s! Error: %s", path.c_str(), SDL_GetError() );
			return false;
		}
		SDL_FreeSurface( loadedSurface );

		SDL_QueryTexture( newTexture, nullptr, nullptr, &mSize.x, &mSize.y );

		mTexture.reset( newTexture );
		return ( mTexture != nullptr );
	}

	bool Texture::CreateTextureFromText( SDL_Renderer* renderer, TTF_Font* font, std::string textureText, SDL_Color textColor )
	{

		SDL_Surface* loadedSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
		if ( loadedSurface == nullptr )
		{
			printf( "Unable to render text %s! Error: %s\n", textureText.c_str(), TTF_GetError() );
			return false;
		}

		mTexture.reset( SDL_CreateTextureFromSurface( renderer, loadedSurface ) );
		if ( mTexture == nullptr )
		{
			printf( "Failed to create texture from text %s! Error: %s", textureText.c_str(), SDL_GetError() );
			return false;
		}

		SDL_FreeSurface( loadedSurface );

		SDL_QueryTexture( mTexture.get(), nullptr, nullptr, &mSize.x, &mSize.y );

		return ( mTexture != nullptr );
	}

	void Texture::Render( SDL_Renderer* renderer, int xPos, int yPos )
	{
		SDL_Rect srcRect = { 0, 0, mSize.x, mSize.y };
		SDL_Rect renderQuad = { xPos, yPos, mSize.x, mSize.y };
		SDL_RenderCopyEx( renderer, mTexture.get(), &srcRect, &renderQuad, 0.0, nullptr, SDL_FLIP_NONE );
	}

	void Texture::RenderFrame( SDL_Renderer* renderer, int xPos, int yPos, SDL_Rect* clip, SDL_RendererFlip flip )
	{
		//Set rendering space and render to screen
		SDL_Rect renderQuad = { xPos, yPos, mSize.x, mSize.y };

		//Set clip rendering dimensions
		if ( clip != nullptr )
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}

		//Render to screen
		SDL_RenderCopyEx( renderer, mTexture.get(), clip, &renderQuad, 0.0, nullptr, flip );

	}

	void Texture::Clean()
	{

	}

	void Texture::SetBlendMode( SDL_BlendMode blending )
	{
		SDL_SetTextureBlendMode( mTexture.get(), blending );
	}

	void Texture::setAlpha( Uint8 alpha )
	{
		SDL_SetTextureAlphaMod( mTexture.get(), alpha );
	}
	void Texture::SetTextureColor( SDL_Color newColor )
	{
		SDL_SetTextureColorMod( mTexture.get(), newColor.r, newColor.g, newColor.b );
	}
}