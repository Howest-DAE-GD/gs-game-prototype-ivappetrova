#pragma once
#include "BaseGame.h"
#include "utils.h"
#include "Timer.h"
#include "Texture.h"

class Game : public BaseGame
{
public:
	explicit Game(const Window& window);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update(float elapsedSec);
	void Draw() const override;

	// Event handling
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e) override;
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e) override;
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e) override;
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e) override;
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e) override;

	// MOITE FUNKCII


private:

	// FUNCTIONS
	void Initialize();
	void Cleanup();
	void ClearBackground() const;

	//my stuff
	Rectf katinar{ int(200.f), int(200.f), int(200.f), int(200.f) };
	Rectf kluch{ int(400.f), int(100.f), int(199.f), int(199.f) };

	float angle{ 20.f };
	float elapsedTime = 30.0f; // total time in seconds
	bool m_timeFinished = false;

	Timer* m_pTimer;

	bool m_Start = false;
	bool IsIntersecting(const Rectf& r1, const Rectf& r2) const;



};