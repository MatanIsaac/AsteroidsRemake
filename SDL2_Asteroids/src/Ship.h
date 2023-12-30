#pragma once
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <utility>
#include "SpaceObject.h"
#include "Asteroid.h"

using std::vector, std::pair, std::make_pair;

class Ship 
{
public:
    Ship(const glm::vec2& position, const SDL_Color& color);

    void ProcessInput();
    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer);
    
    void Clean();

   const glm::vec2& GetPosition() { return mShip.mPosition; }
    SpaceObject& GetSpaceObject() { return mShip; }

    void MoveShip(float deltaTime);
    void MoveBullet(SpaceObject& bullet, float deltaTime);

	bool IsCollidingWithAsteroid( Asteroid* asteroid );

    void HaltAllSounds();

private:

    glm::vec2 GetShipForwardVector() const
	{
		return { sinf( mShip.mRotation ), -cosf( mShip.mRotation ) };
	}

    void SpawnBullet();
private:
    std::vector<std::pair<float, float>> vecModelShip;
    SpaceObject mShip;    
    SDL_Color mColor;

    float mAccelerationFactor;

    std::vector<SpaceObject> mBulletsVec;
    float mBulletSpeed;

    Mix_Chunk* mHoverSound;
    int mHoverChannel;
    
    Mix_Chunk* mLaserSound;
    int mLaserChannel;
    
    Mix_Chunk* mDeadSound;
    int mDeadChannel;
    
    Mix_Chunk* mAsteroidHitSound;
    int mAsteroidHitChannel;
};
