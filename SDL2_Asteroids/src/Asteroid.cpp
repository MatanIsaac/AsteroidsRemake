#include "Asteroid.h"
#include "Game.h"

#include <random>

Asteroid::Asteroid( const SpaceObject& obj, const SDL_Color& color )
	: mAsteroid(obj), mColor(color)
{
	static std::mt19937 rng( std::random_device{}( ) );
	static std::uniform_real_distribution<float> asteroidVertsDist( 0.8f, 1.2f );

	mAsteroid.mSize = obj.mSize;
	mAsteroid.mPosition.x = obj.mPosition.x;
	mAsteroid.mPosition.y = obj.mPosition.y;
	mAsteroid.mVelocity.x = obj.mVelocity.x;
	mAsteroid.mVelocity.y = obj.mVelocity.y;

	int verts = 20;
	for ( int i = 0; i < verts; i++ )
	{
		float noise = asteroidVertsDist( rng );
		vecModelAsteroid.emplace_back( noise * sinf( ( ( float ) i / ( float ) verts ) * 6.28318f ),
									   noise * cosf( ( ( float ) i / ( float ) verts ) * 6.28318f ) );
	}
	
}

Asteroid::Asteroid( const Asteroid& other )
	: vecModelAsteroid(other.vecModelAsteroid) ,mColor(other.mColor)
{	
	mAsteroid.mPosition = other.mAsteroid.mPosition;
	mAsteroid.mVelocity = other.mAsteroid.mVelocity;
	mAsteroid.mRotation = other.mAsteroid.mRotation;
	mAsteroid.mSize = other.mAsteroid.mSize;
	
}

Asteroid Asteroid::operator=( const Asteroid& other )
{
	if ( &other != this )
	{
		vecModelAsteroid = other.vecModelAsteroid;
		mColor = other.mColor;
		mAsteroid.mPosition = other.mAsteroid.mPosition;
		mAsteroid.mVelocity = other.mAsteroid.mVelocity;
		mAsteroid.mRotation = other.mAsteroid.mRotation;
		mAsteroid.mSize = other.mAsteroid.mSize;
	}
	
	return *this;
}

Asteroid::~Asteroid()
{
	Clean();
}

void Asteroid::Update( float deltaTime )
{
	
	mAsteroid.mPosition.x += mAsteroid.mVelocity.x * deltaTime;
	mAsteroid.mPosition.y += mAsteroid.mVelocity.y * deltaTime;
	mAsteroid.mRotation += 0.7f * deltaTime;
	
	auto fSize = static_cast< float >( GetSize() );

	// Adjusting the position for screen wrapping
	if ( mAsteroid.mPosition.x > SCREEN_WIDTH + fSize )
	{
		mAsteroid.mPosition.x = -fSize;
	}
	else if ( mAsteroid.mPosition.x < -fSize )
	{
		mAsteroid.mPosition.x = SCREEN_WIDTH + fSize;
	}

	if ( mAsteroid.mPosition.y > SCREEN_HEIGHT + fSize )
	{
		mAsteroid.mPosition.y = -fSize;
	}
	else if ( mAsteroid.mPosition.y < -fSize )
	{
		mAsteroid.mPosition.y = SCREEN_HEIGHT + fSize;
	}

}

void Asteroid::Render( SDL_Renderer* renderer )
{
	auto game = Game::Getinstance();

	SDL_SetRenderDrawColor( renderer, mColor.r, mColor.g, mColor.b, mColor.a );

 	game->DrawWireFrameModel( renderer, vecModelAsteroid,
 												 mAsteroid.mPosition.x, mAsteroid.mPosition.y, 
 												 mAsteroid.mRotation, static_cast<float>( mAsteroid.mSize ) );
}

void Asteroid::Clean()
{
	vecModelAsteroid.clear();
}
