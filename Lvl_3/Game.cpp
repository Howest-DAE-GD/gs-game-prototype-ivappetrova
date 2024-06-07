#include "pch.h"
#include "Game.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>


Game::Game(const Window& window)
	:BaseGame{ window }, m_pTimer{}
{
	Initialize();

	if (m_Start == false)
	{
		std::cout << "Here you are! The last floor!" << std::endl;
		std::cout << " " << std::endl;
		std::cout << "Controls: " << std::endl;
		std::cout << "- Move   : Arrows " << std::endl;
		std::cout << "- Rotation : R" << std::endl;
		std::cout << " " << std::endl;
		std::cout << "You have 10 seconds to fit the key (green) in the lock (red). Are you gonna make it out? ;)" << std::endl;
		std::cout << " " << std::endl;
		std::cout << "Click S to start the game" << std::endl;
	}

}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	m_pTimer = new Timer();
}

void Game::Cleanup()
{
	delete m_pTimer;
}

void Game::Update(float elapsedSec)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	static bool rKeyPressed = false;

	if (pStates[SDL_SCANCODE_S])
	{
		m_Start = true;
	}
	else
	{

	}

	if (m_Start == true)
	{
		float moveSpeed = 100.0f;
		float moveDistance = moveSpeed * elapsedSec;
		float moveDirection = 0.0f;

		m_pTimer->Update(elapsedSec);

		static std::chrono::time_point<std::chrono::system_clock> last_print_time = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_time = std::chrono::system_clock::now() - last_print_time;

		if (elapsed_time.count() >= 1.0)
		{
			last_print_time = std::chrono::system_clock::now();
			m_pTimer->Print();
		}

		if (m_pTimer->TimeOut(elapsedSec) == false)
		{
			if (!IsIntersecting(kluch, katinar))
			{
				// MOVEMENT
				if (pStates[SDL_SCANCODE_RIGHT])
				{
					moveDirection = 1.0f; // Move right
					for (auto& point : kluch)
					{
						point.x += moveDirection * moveDistance;
					}
				}
				if (pStates[SDL_SCANCODE_LEFT])
				{
					moveDirection = -1.0f; // Move left
					for (auto& point : kluch)
					{
						point.x += moveDirection * moveDistance;
					}
				}
				if (pStates[SDL_SCANCODE_UP])
				{
					moveDirection = 1.0f; // Move up
					for (auto& point : kluch)
					{
						point.y += moveDirection * moveDistance;
					}
				}
				if (pStates[SDL_SCANCODE_DOWN])
				{
					moveDirection = -1.0f; // Move down
					for (auto& point : kluch)
					{
						point.y += moveDirection * moveDistance;
					}
				}

				if (pStates[SDL_SCANCODE_R]) {
					if (!rKeyPressed) {
						angle += 20;  // Increase angle by 5
						rKeyPressed = true;  // Set the flag to true
					}
				}
				else {
					rKeyPressed = false;  // Reset the flag when the key is released
				}
			}
		}

	}
}

void Game::Draw() const
{
	ClearBackground();

	if (IsIntersecting(kluch, katinar) == true)
	{
		std::cout << "YOU HAVE ESCAPED THE PYRAMID! Congrats ;)" << std::endl;
		utils::SetColor(Color4f(1.f, 1.f, 1.f, 1.f));
		utils::FillRect(0.f, 0.f, 800.f, 500.f);
	}



	if (m_Start == false)
	{
		utils::SetColor(Color4f(1.f, 1.f, 0.f, 1.f));
		utils::FillRect(0.f, 0.f, 800.f, 500.f);
	}
	else
	{
	}


	////////////////////////////////////////
	// KATINAR
	////////////////////////////////////////


	glPushMatrix();
	{

		glTranslatef(katinar[7].x, katinar[7].y, 0);
		glRotatef(215.f, 0.f, 0.f, 1.f);
		glTranslatef(-katinar[7].x, -katinar[7].y, 0);
		utils::SetColor(Color4f{ 1.f, 0.f, 0.f, 1.0f });
		utils::DrawPolygon(katinar);
		utils::SetColor(Color4f{ 1.f, 0.f, 0.f, 1.f });
		utils::DrawEllipse(katinar[1], 5.0f, 5.0f);

	}
	glPopMatrix();




	////////////////////////////////////////
	// KLUCH
	////////////////////////////////////////


	glPushMatrix();
	{

		glTranslatef(kluch[7].x, kluch[7].y, 0);
		glRotatef(angle, 0.f, 0.f, 1.f);
		glTranslatef(-kluch[7].x, -kluch[7].y, 0);
		utils::SetColor(Color4f{ 0.f, 1.f, 0.f, 1.0f });
		utils::DrawPolygon(kluch);

		utils::SetColor(Color4f{ 1.f, 0.f, 0.f, 1.f });
		utils::DrawEllipse(kluch[1], 5.0f, 5.0f);

		if (IsIntersecting(kluch, katinar) == true)
		{
			utils::SetColor(Color4f{ 1.f, 0.f, 0.f, 1.f });
			utils::DrawEllipse(kluch[2], 5.0f, 5.0f);
			utils::DrawEllipse(kluch[3], 5.0f, 5.0f);
			utils::DrawEllipse(kluch[4], 5.0f, 5.0f);
			utils::DrawEllipse(kluch[5], 5.0f, 5.0f);
			utils::DrawEllipse(kluch[6], 5.0f, 5.0f);
			utils::DrawEllipse(kluch[7], 5.0f, 5.0f);
			utils::DrawEllipse(kluch[8], 5.0f, 5.0f);
			utils::DrawEllipse(kluch[9], 5.0f, 5.0f);
		}

	}
	glPopMatrix();

	if (m_pTimer->TimeOut(elapsedTime) && !IsIntersecting(kluch, katinar))
	{
		std::cout << "TIME FINISHED. YOU LOSE! MUHAHAHAHA" << std::endl;
		utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f)); // Green color
		utils::FillRect(0.f, 0.f, 800.f, 500.f);
	}
}


bool Game::IsIntersecting(std::vector<Point2f> vector1, const std::vector<Point2f>& constVECTOR) const
{
	if ((int(vector1[0].x + 1) == int(constVECTOR[0].x) && (int(vector1[0].y) == int(constVECTOR[0].y)) && (int(angle) % 360) == 215)
		|| (int(vector1[0].x) == int(constVECTOR[0].x) && (int(vector1[0].y) == int(constVECTOR[0].y)) && (int(angle) % 360) == 215))
	{
		return true;

	}
	else
	{
		return false;
	}

}


void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{

	//Check keyboard state
   /*const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
   if ( pStates[SDL_SCANCODE_RIGHT] )
   {
	   std::cout << "Right arrow key is down\n";
   }
   if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
   {
	   std::cout << "Left and up arrow keys are down\n";
   }*/

}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_w:
	//	kluch.
	//	break;
	//case SDLK_s:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_a:
	//case SDLK_d:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}


}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}

}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}




void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
