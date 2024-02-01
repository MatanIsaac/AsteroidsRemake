#pragma once
#include <vector>
#include <utility>

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

#include "SpaceObject.h"

using std::vector, std::pair, std::make_pair;

class Asteroid
{
public:

	/// Constructors & Destructors
	///--------------------------------------------------------

	/**
	* @brief Constructor for Asteroid class.
	* @param obj SpaceObject representing the asteroid.
	* @param color Color of the asteroid.
	*/
	Asteroid( const SpaceObject& obj, const SDL_Color& color );

	/**
	 * @brief Copy constructor for the Asteroid class.
	 * @param other Another Asteroid instance to copy from.
	 */
	Asteroid( const Asteroid& other);

	/**
	 * @brief Copy assignment operator for the Asteroid class.
	 * @param other Another Asteroid instance to assign from.
	 * @return Reference to the updated Asteroid instance.
	 */
	Asteroid operator=( const Asteroid& other);

	/**
	 * @brief Destructor for the Asteroid class.
	 */
	~Asteroid();

	/// Utility
	///--------------------------------------------------------
	
	/**
	 * @brief Updates the asteroid's state.
	 * @param deltaTime Time elapsed since the last update.
	 */
	void Update( float deltaTime );

	/**
	 * @brief Renders the asteroid on the given renderer.
	 * @param renderer SDL Renderer to draw the asteroid.
	 */
	void Render( SDL_Renderer* renderer );

	/**
	 * @brief Performs cleanup of the asteroid's resources.
	 */
	void Clean();	

	/// Getters 
	///--------------------------------------------------------

	/**
	 * @brief Retrieves the asteroid's position.
	 * @return Current position of the asteroid.
	 */
	glm::vec2& GetPosition() { return mAsteroid.mPosition; };

	/**
	 * @brief Retrieves the asteroid's velocity.
	 * @return Current velocity of the asteroid.
	 */
	glm::vec2& GetVelocity() { return mAsteroid.mVelocity; };
	
	/**
	 * @brief Sets the X position of the asteroid.
	 * @param newXPos New X coordinate of the asteroid.
	 */
	void SetPositionX(float newXPos) { mAsteroid.mPosition.x = newXPos; };

	/**
	 * @brief Gets the size of the asteroid.
	 * @return The size of the asteroid.
	 */
	int GetSize() const { return mAsteroid.mSize; };

	/**
	 * @brief Accessor for the asteroid's SpaceObject instance.
	 * @return Reference to the asteroid's SpaceObject.
	 */
	SpaceObject& GetSpaceObject() { return mAsteroid; }

	/**
	 * @brief Retrieves the color of the asteroid.
	 * @return The SDL_Color representing the asteroid's color.
	 */
	const SDL_Color& GetColor() const noexcept { return mColor; }

private:

	// Model coordinates for the asteroid.
	vector<pair<float, float>> vecModelAsteroid;
	// SpaceObject representing the asteroid.
	SpaceObject mAsteroid;
	
	// Color of the asteroid.
	SDL_Color mColor;

	// Minimum size of the asteroid.
	static const int MIN_SIZE = 48;
	// Maximum size of the asteroid.
	static const int MAX_SIZE = 96;

};


