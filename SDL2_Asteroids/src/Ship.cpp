#include "Ship.h"
#include <iostream>
#include <algorithm>
#include "Game.h"
#include "InputManager.hpp"

Ship::Ship( const glm::vec2& position, const SDL_Color& color )
	: mColor( color ), mIsDead(false)
{
	// A simple Isoceles Triangle
	vecModelShip =
	{
		{  0.0f, -25.0f },
		{ -12.5f, +12.5f },
		{ +12.5f, +12.5f }
	};

	mAccelerationFactor = 100.f;

	mShip.mPosition = position;
	mShip.mVelocity = { 0.f,0.f };
	mShip.mRotation = 0.0f;

	mBulletSpeed = 200.f;

	std::string hoverSoundSrc = std::string( SOLUTION_DIR ) + "Assets/spaceshipHover.wav";
	mHoverSound = Mix_LoadWAV( hoverSoundSrc.c_str() );
	if ( !mHoverSound )
	{
		printf("Failed to load the spaceship hover sound! , Error: %s", Mix_GetError());
	}
	Mix_VolumeChunk( mHoverSound, MIX_MAX_VOLUME * 10);
	mHoverChannel = -1;
	
	std::string laserSoundSrc = std::string( SOLUTION_DIR ) + "Assets/LaserShoot.wav";
	mLaserSound = Mix_LoadWAV( laserSoundSrc.c_str() );
	if ( !mLaserSound )
	{
		printf("Failed to load the spaceship laser sound! , Error: %s", Mix_GetError());
	}

	Mix_VolumeChunk( mLaserSound, MIX_MAX_VOLUME / 7 );
	mLaserChannel = -1;
	
	std::string deadSoundSrc = std::string( SOLUTION_DIR ) + "Assets/ShipDead.wav";
	mDeadSound = Mix_LoadWAV( deadSoundSrc.c_str() );
	if ( !mDeadSound )
	{
		printf("Failed to load the spaceship hit sound! , Error: %s", Mix_GetError());
	}

	Mix_VolumeChunk( mDeadSound, MIX_MAX_VOLUME / 5 );
	mDeadChannel = -1;
	
	std::string asteroidHitSoundSrc = std::string( SOLUTION_DIR ) + "Assets/AsteroidExplosion.wav";
	mAsteroidHitSound = Mix_LoadWAV( asteroidHitSoundSrc.c_str() );
	if ( !mAsteroidHitSound )
	{
		printf("Failed to load the asteroid hit sound! , Error: %s", Mix_GetError());
	}

	Mix_VolumeChunk( mAsteroidHitSound, MIX_MAX_VOLUME / 8 );
	mAsteroidHitChannel = -1;

}

void Ship::ProcessInput()
{
	auto game = Game::Getinstance();
	auto input = venture::InputManager::get();
	if ( !mIsDead )
	{
		// Rotation
		if ( input->isKeyDown( SDL_SCANCODE_LEFT ) )

			mShip.mRotation -= 5.f * game->GetDeltaTime();

		if ( input->isKeyDown( SDL_SCANCODE_RIGHT ) )
			mShip.mRotation += 5.f * game->GetDeltaTime();


		// Acceleration
		if ( input->isKeyDown( SDL_SCANCODE_UP ) )
		{
			mShip.mVelocity.x += sin( mShip.mRotation ) * mAccelerationFactor * game->GetDeltaTime();
			mShip.mVelocity.y += -cos( mShip.mRotation ) * mAccelerationFactor * game->GetDeltaTime();

			mHoverChannel = Mix_PlayChannel( 1, mHoverSound, 0 );
		}

		if ( input->isKeyReleased( SDL_SCANCODE_UP ) )
		{
			Mix_HaltChannel( mHoverChannel );
		}

		// Spawn Bullets with space key
		if ( input->isKeyPressed( SDL_SCANCODE_SPACE ) )
		{
			mLaserChannel = Mix_PlayChannel( 2, mLaserSound, 0 );
			SpawnBullet();
		}
	}

}

void Ship::Update( float deltaTime )
{
	MoveShip(deltaTime);

	auto game = Game::Getinstance();
	auto& asteroidsMap = game->GetAsteroidsMap();

	vector<Asteroid> newAsteroids;
	std::vector<Asteroid*> asteroidsToRemove;

	for ( auto asteroidIt = asteroidsMap.begin(); asteroidIt != asteroidsMap.end();)
	{
		Asteroid* asteroid = &asteroidIt->second;
		if ( IsCollidingWithAsteroid( asteroid ) )
		{
			Mix_PlayChannel(3,mDeadSound,0);
			Mix_HaltChannel(mHoverChannel);
			SetIsDead( true );
			break; 
		}
		else
		{
			++asteroidIt;
		}

	}

	for ( auto bulletIt = mBulletsVec.begin(); bulletIt != mBulletsVec.end();)
	{
		bool bulletHit = false;
		SpaceObject& bullet = *bulletIt;
		MoveBullet( bullet, deltaTime );

		for ( auto asteroidIt = asteroidsMap.begin(); asteroidIt != asteroidsMap.end();)
		{
			Asteroid& asteroid = asteroidIt->second;
			
			if ( game->IsPointInCircle( asteroid.GetPosition().x, asteroid.GetPosition().y, static_cast< float >( asteroid.GetSize() ), bullet.mPosition.x, bullet.mPosition.y ) )
			{
				game->AddScore(1);
				Mix_PlayChannel(4, mAsteroidHitSound,0);
				auto& pos = asteroid.GetPosition();
				if ( asteroid.GetSize() > 12 )
				{
					double angle1 = static_cast< float >( rand() ) / RAND_MAX * 2.0f * M_PI;
					double angle2 = static_cast< float >( rand() ) / RAND_MAX * 2.0f * M_PI;

					SpaceObject child1( pos, glm::vec2{ 35.0f * sin( angle1 ), 35.0f * cos( angle1 ) }, 0.5f, asteroid.GetSize() / 2 );
					SpaceObject child2( pos, glm::vec2{ 35.0f * sin( angle2 ), 35.0f * cos( angle2 ) }, 0.5f, asteroid.GetSize() / 2 );

					game->AddAsteroid( child1 );
					game->AddAsteroid( child2 );
					asteroid.SetPositionX( -300.f );
				}
				asteroidsMap.erase( asteroidIt );
				bulletHit = true;
				break;
			}
			++asteroidIt;

		} // end of asteroids loop

		if ( bulletHit )
		{

			bulletIt = mBulletsVec.erase( bulletIt );
		}
		else
		{
			++bulletIt;
		}

	} // end of bullets loop

}

void Ship::Render( SDL_Renderer* renderer )
{
	auto game = Game::Getinstance();
	SDL_SetRenderDrawColor( renderer, mColor.r, mColor.g, mColor.b, mColor.a );
	game->DrawWireFrameModel( renderer, vecModelShip,
							  mShip.mPosition.x, mShip.mPosition.y, mShip.mRotation );

	for ( auto& bullet : mBulletsVec )
	{
		game->DrawCircleFill( renderer, bullet.mPosition.x, bullet.mPosition.y, static_cast< float >( bullet.mSize ), SDL_Color( 255, 0, 0 ) );
	}

}

void Ship::Clean()
{
	vecModelShip.clear();
	mBulletsVec.clear();

	Mix_FreeChunk( mHoverSound );
	mHoverSound = nullptr;
	Mix_FreeChunk( mLaserSound );
	mLaserSound = nullptr;
	Mix_FreeChunk( mDeadSound );
	mDeadSound = nullptr;
	Mix_FreeChunk( mAsteroidHitSound );
	mAsteroidHitSound = nullptr;
}

void Ship::MoveShip( float deltaTime )
{
	mShip.mPosition.x += mShip.mVelocity.x * deltaTime;
	mShip.mPosition.y += mShip.mVelocity.y * deltaTime;
}

void Ship::MoveBullet( SpaceObject& bullet, float deltaTime )
{
	bullet.mPosition.x += bullet.mVelocity.x * deltaTime;
	bullet.mPosition.y += bullet.mVelocity.y * deltaTime;

}

void Ship::HaltAllSounds()
{
	Mix_HaltChannel(mHoverChannel);
	Mix_HaltChannel(mLaserChannel);
	Mix_HaltChannel(mDeadChannel);
	Mix_HaltChannel(mAsteroidHitChannel);
}

void Ship::SpawnBullet()
{
	glm::vec2 shipPosition = mShip.mPosition;
	float shipRotation = mShip.mRotation;
	float topPointOffset = 25.0f; // Distance from the center of the ship to the top point

	// Calculate the bullet's initial position based on
	// the ship's position, rotation, and offset from the ship's center to its top point
	float bulletX = shipPosition.x + topPointOffset * sinf( shipRotation );
	float bulletY = shipPosition.y + topPointOffset * -cosf( shipRotation );

	auto pos = glm::vec2{ bulletX, bulletY };
	auto vel = glm::vec2{ mBulletSpeed * GetShipForwardVector() };
	mBulletsVec.emplace_back( pos, vel, 0.f, 2 );
}

bool Ship::IsCollidingWithAsteroid( Asteroid* asteroid )
{
	if ( !asteroid ) return false;  // Null check

	for ( const auto& vertex : vecModelShip )
	{
		// Transform the vertex according to the ship's current position and rotation
		float transformedX = vertex.first * cosf( mShip.mRotation ) - vertex.second * sinf( mShip.mRotation );
		float transformedY = vertex.first * sinf( mShip.mRotation ) + vertex.second * cosf( mShip.mRotation );

		// Apply scale factor if needed
		// transformedX *= mShip.mScale;
		// transformedY *= mShip.mScale;

		// Translate the vertex
		transformedX += mShip.mPosition.x;
		transformedY += mShip.mPosition.y;

		// Check if the transformed vertex is inside the asteroid
		float dx = transformedX - asteroid->GetPosition().x;
		float dy = transformedY - asteroid->GetPosition().y;
		if ( sqrt( dx * dx + dy * dy ) < asteroid->GetSize() )
		{
			return true;  // Collision detected
		}
	}
	return false;  // No collision
}
