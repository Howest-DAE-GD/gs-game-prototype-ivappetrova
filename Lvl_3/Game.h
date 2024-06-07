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
	const std::vector< Point2f > katinar{ Point2f {int(300.f), int(150.f)}, Point2f {int(250.f), int(300.f)}, Point2f {int(270.f), int(320.f)},
										  Point2f {int(250.f), int(360.f)}, Point2f {int(300.f), int(420.f)}, Point2f {int(400.f), int(380.f)},
										  Point2f {int(420.f), int(350.f)}, Point2f {int(320.f), int(270.f)}, Point2f {int(370.f), int(150.f)},
										  Point2f {int(300.f), int(150.f)}
	};

	std::vector< Point2f > kluch{ Point2f {int(130.f), int(50.f) }, Point2f {int(80.f), int(200.f)}, Point2f {int(100.f), int(220.f)},
								  Point2f {int(80.f), int(260.f)}, Point2f {int(130.f), int(320.f)}, Point2f {int(230.f), int(280.f)},
								  Point2f {int(250.f), int(250.f)}, Point2f {int(150.f), int(170.f)}, Point2f {int(200.f), int(50.f)},
								  Point2f {int(130.f), int(50.f)}
	};

	/*std::vector< Point2f > kluch{ Point2f {300.f, 150.f}, Point2f {250.f, 300.f}, Point2f {270.f, 320.f},
									Point2f {250.f, 360.f}, Point2f {300.f, 420.f}, Point2f {400.f, 380.f},
									Point2f	{420.f, 350.f}, Point2f {320.f, 270.f}, Point2f {370.f, 150.f},
									Point2f {300.f, 150.f}
								};*/

	float angle{ 15.f };


	float elapsedTime = 30.0f; // total time in seconds
	bool m_timeFinished = false;

	Timer* m_pTimer;
	Timer* m_pStoryTimer;

	bool m_Start = false;
	bool m_HasWon = false; // Add this flag
	bool IsIntersecting(std::vector<Point2f> vector1, const std::vector<Point2f>& constVECTOR) const;



	/*Texture* m_pStringTexture;*/
};