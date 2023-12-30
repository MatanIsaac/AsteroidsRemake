#pragma once
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <vector>
#include <utility>
#include "SpaceObject.h"

using std::vector, std::pair, std::make_pair;

class Asteroid
{
public:
	Asteroid( const SpaceObject& obj, const SDL_Color& color );
	Asteroid( const Asteroid& other);
	Asteroid operator=( const Asteroid& other);
	~Asteroid();

	void Update( float deltaTime );
	void Render( SDL_Renderer* renderer );

	void Clean();	

	glm::vec2& GetPosition() { return mAsteroid.mPosition; };
	glm::vec2& GetVelocity() { return mAsteroid.mVelocity; };
	
	void SetPositionX(float newXPos) { mAsteroid.mPosition.x = newXPos; };

	int GetSize() const { return mAsteroid.mSize; };
	SpaceObject& GetSpaceObject() { return mAsteroid; }

	const SDL_Color& GetColor() const noexcept { return mColor; }

private:
	vector<pair<float, float>> vecModelAsteroid;
	SpaceObject mAsteroid;
	
	SDL_Color mColor;

	static const int MIN_SIZE = 48;
	static const int MAX_SIZE = 96;
	static const float MIN_X_VELOCITY;
	static const float MAX_X_VELOCITY;
	static const float MIN_Y_VELOCITY;
	static const float MAX_Y_VELOCITY;
};


