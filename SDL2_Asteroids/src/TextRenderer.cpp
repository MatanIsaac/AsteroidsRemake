#include "TextRenderer.hpp"
#include "Game.h"

namespace venture
{
	TextRenderer::TextRenderer( const char* text, uint8_t textSize, SDL_Color textColor )
		: mText( text ), mTextSize( textSize ), mTextColor( textColor )
	{
		mPosition = glm::vec2();
		std::string defaultFont = std::string( SOLUTION_DIR ) + "Assets/fonts/pixeldue.ttf";

		mFont.reset( TTF_OpenFont( defaultFont.c_str(), mTextSize ) );
		if ( mFont == nullptr )
		{
			printf( "Failed to open font!" );
		}

		mTexture.reset( new Texture() );
	}

	TextRenderer::~TextRenderer()
	{
		Clean();
	}

	void TextRenderer::Clean()
	{}

	void TextRenderer::CreateText()
	{
		if ( !mTexture->CreateTextureFromText(
			Game::GetInstance()->GetRenderer(),
			mFont.get(),
			mText,
			mTextColor ) )
		{
			printf( "Failed to create a texture from text!\n" );
		}
	}

	void venture::TextRenderer::RenderText( SDL_Renderer* renderer, const glm::vec2& position )
	{
		SDL_SetRenderDrawColor( renderer, mTextColor.r, mTextColor.g, mTextColor.b, mTextColor.a );
		if(mTexture)
			mTexture->Render( renderer, static_cast< int >( position.x ), static_cast< int >( position.y ) );
	}

	void TextRenderer::UpdateText( const std::string& newText )
	{
		mText = newText;
		CreateText(); // Recreate the texture with new text
	}
}