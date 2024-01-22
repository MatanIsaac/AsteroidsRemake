#pragma once
#include <vector>
#include <utility>

#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "SpaceObject.h"
#include "Asteroid.h"

using std::vector, std::pair, std::make_pair;

class Ship
{
public:
	/**
	* @brief Constructor for Ship class.
	* @param position Initial position of the ship.
	* @param color Color of the ship.
	*/
	Ship( const glm::vec2& position, const SDL_Color& color );

	/**
	 * @brief Processes user input for the ship.
	 */
	void ProcessInput();

	/**
	 * @brief Updates the ship's state.
	 * @param deltaTime Time elapsed since the last update.
	 */
	void Update( float deltaTime );

	/**
	 * @brief Renders the ship on the given renderer.
	 * @param renderer SDL Renderer to draw the ship.
	 */
	void Render( SDL_Renderer* renderer );

	/**
	* @brief Performs cleanup of the ship's resources.
	*/
	void Clean();

	/**
	 * @brief Retrieves the ship's position.
	 * @return Current position of the ship.
	 */
	const glm::vec2& GetPosition() { return mShip.mPosition; }

	/**
	 * @brief Accessor for the ship's SpaceObject instance.
	 * @return Reference to the ship's SpaceObject.
	 */
	SpaceObject& GetSpaceObject() { return mShip; }

	/**
	 * @brief Moves the ship based on the elapsed time.
	 * @param deltaTime Time since last move.
	 */
	void MoveShip( float deltaTime );

	/**
	* @brief Moves a bullet, updating its position.
	* @param bullet The bullet to move.
	* @param deltaTime Time since last update.
	*/
	void MoveBullet( SpaceObject& bullet, float deltaTime );

	/**
	* @brief Checks collision of the ship with an asteroid.
	* @param asteroid Pointer to the asteroid to check collision with.
	* @return True if there is a collision, false otherwise.
	*/
	bool IsCollidingWithAsteroid( Asteroid* asteroid );

	/**
	 * @brief Halts all playing sounds related to the ship.
	 */
	void HaltAllSounds();

	/**
	 * @brief Checks if the ship is dead.
	 * @return True if the ship is dead, false otherwise.
	 */
	bool GetIsDead() const noexcept { return mIsDead; }

	/**
	 * @brief Sets the ship's dead status.
	 * @param isDead New dead status of the ship.
	 */
	void SetIsDead( bool isDead ) { mIsDead = isDead; }

	/**
	 * @brief Loads and sets sound effects for the ship.
	 */
	void LoadAndSetSFX();

	/**
	 * @brief Checks for collisions between the ship's bullets and asteroids.
	 */
	void CheckAsteroidsCollision();
	
	/**
	* @brief Updates the state of bullets fired by the ship.
	* @param deltaTime Time since the last update.
	*/
	void UpdateBullets( float deltaTime );

private:
	/**
	 * @brief Calculates the forward vector of the ship based on its rotation.
	 * @return The forward vector of the ship.
	 */
	glm::vec2 GetShipForwardVector() const
	{
		return { sinf( mShip.mRotation ), -cosf( mShip.mRotation ) };
	}

	/**
	 * @brief Spawns a bullet at the ship's position.
	 */
	void SpawnBullet();

private:
	// Model coordinates for the ship.
	std::vector<std::pair<float, float>> vecModelShip;
	// SpaceObject representing the ship.
	SpaceObject mShip;
	// Color of the ship.
	SDL_Color mColor;

	// Flag indicating if the ship is dead.
	bool mIsDead;

	// Factor for acceleration.
	float mAccelerationFactor;
	// Speed of rotation.
	static const float mRotationSpeed;

	// Vector of bullets fired by the ship.
	std::vector<SpaceObject> mBulletsVec;
	// Speed of bullets.
	float mBulletSpeed;

	// Sound chunk for the hover sound.
	Mix_Chunk* mHoverSound;
	// Channel for the hover sound.
	int mHoverChannel;

	// Sound chunk for the laser sound.
	Mix_Chunk* mLaserSound;
	// Channel for the laser sound.
	int mLaserChannel;

	// Sound chunk for the death sound.
	Mix_Chunk* mDeadSound;
	// Channel for the death sound.
	int mDeadChannel;

	// Sound chunk for the asteroid hit sound.
	Mix_Chunk* mAsteroidHitSound;
	// Channel for the asteroid hit sound.
	int mAsteroidHitChannel;

	// Offset from the center of the ship to its top point.
	static const float topPointOffset;

};
