#pragma once
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <unordered_map>
#include <memory>

#include "TextRenderer.hpp"
#include "SpaceObject.h"
#include "Asteroid.h"
#include "Ship.h"
#include "Timer.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


using namespace venture;

class Game
{
public:

	static inline Game* Getinstance()
	{
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Game();
	}

	bool Init(const char* title, bool fullscreen);
	void Quit() { m_IsRunning = false; }

	void Update();
	void Render();
	void Clean();

	void ProcessInput();
	void RunEngine();

	inline bool IsRunning() { return m_IsRunning; }
	inline SDL_Renderer* GetRenderer() { return m_Renderer; }
	
	inline SDL_Window* GetWindow()
	{
		return m_Window;
	}
    
    float GetDeltaTime() { return mDeltaTime; }
    void DrawLine(SDL_Renderer* renderer, const glm::vec2& point1, const glm::vec2& point2);
    
	std::unordered_map<int, Asteroid>& GetAsteroidsMap() { return mAsteroidsMap; }

	void DrawWireFrameModel(SDL_Renderer* renderer, const std::vector<std::pair<float, float>>& vecModelCoordinates,
        float x, float y, float r = 0.0f, float s = 1.0f);

    /**
     * @brief Wraps coordinates to ensure continuous movement within game space.
	  * @param in_position The current position of the object in the game space.
	  * This is a 2D vector representing the X and Y coordinates.
    */
    void WrapCoordinates( SpaceObject& obj );

	void DrawCircleFill( SDL_Renderer* renderer, float centerX, float centerY, float mRadius, SDL_Color color );

	bool IsPointInCircle( float cx, float cy, float mRadius, float x, float y );

	void AddAsteroid( const SpaceObject& obj);

	void RestartGame();

	void AddScore(int score) { mScoreCount += score; }

private:
    Game()
        : m_Window(nullptr)
        , m_Renderer(nullptr)
        , m_IsRunning(false)
        , mShip(nullptr)
        , mTimer(nullptr)
        , mDeltaTime(0.0f)
        , mFPS(0.0)
        , mTicksCount(0)
		, mAsteroidsIndex(0)
		, mStartGameSound(nullptr)
		, mScoreCount(0)
		, mPlayerWon(false)
	{ }

	static Game* s_Instance;

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

	bool m_IsRunning;
	bool mPlayerWon;

	std::unordered_map<int,Asteroid> mAsteroidsMap;

    Ship* mShip;

    Timer* mTimer;
    uint64_t mTicksCount;
    float mDeltaTime;

	std::string mScoreStr;
	std::string mFPSText;
	long double mFPS;
	//std::unique_ptr<TextRenderer, TextRendererDeleter> mFpsText;
	std::unique_ptr<TextRenderer, TextRendererDeleter> mWinText;
	std::unique_ptr<TextRenderer, TextRendererDeleter> mDeadText;
	std::unique_ptr<TextRenderer, TextRendererDeleter> mRestartText;
	std::unique_ptr<TextRenderer, TextRendererDeleter> mScoreText;	

	int mScoreCount;
	int mAsteroidsIndex;
	int mStartGameChannel = 0;

	Mix_Chunk* mStartGameSound;

};

