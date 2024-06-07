#include "pch.h"
#include "Game.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>


Game::Game( const Window& window ) 
	:BaseGame{ window }, m_pTimer{}
{
	Initialize();
	//hi
	if (m_Start == false)
	{
			std::cout << "You are an archaeologist" << std::endl;
			std::cout << " " << std::endl;
			std::cout << "Your dream has always been to go on a expedition in Egypt." << std::endl;
			std::cout << "Lucky you! You were chosen from your boss and your dream is about to become true." << std::endl;
			std::cout << "Unfortuantely, you were trapped in the pyramid that you were investigating." << std::endl;
			std::cout << "The first known locks in history were created over 6000 years ago in Ancient Egypt and Mesopotamia and you know that. ";
			std::cout << " " << std::endl;
			std::cout << "Can you break the locks in the pyramid on time and escape?" << std::endl;
			std::cout << " " << std::endl;
			std::cout << "Controls: " << std::endl;
			std::cout << "- Move   : Arrows " << std::endl;
			std::cout << "- Rotate : R" << std::endl;
			std::cout << " " << std::endl;
			std::cout << "You have 20 seconds to fit the key (green) in the lock (red). Are you gonna make it out? ;)" << std::endl;
			std::cout << " " << std::endl;
			std::cout << "Click S to start the game" << std::endl;
	}
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize()
{
	m_pTimer = new Timer();
}

void Game::Cleanup( )
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
					kluch.left += moveDistance;
					/*std::cout << "Left KLUCH: " << int(kluch.left) << std::endl;*/
				}
				if (pStates[SDL_SCANCODE_LEFT])
				{
					kluch.left -= moveDistance;
					/*std::cout << "Left KLUCH: " << int(kluch.left) << std::endl;*/
				}
				if (pStates[SDL_SCANCODE_UP])
				{
					kluch.bottom += moveDistance;
					/*std::cout << "Bottom KLUCH: " << int(kluch.bottom) << std::endl;*/
				}
				if (pStates[SDL_SCANCODE_DOWN])
				{
					kluch.bottom -= moveDistance;
					/*std::cout << "Bottom KLUCH: " << int(kluch.bottom) << std::endl;*/
				}

				// Rotation
				if (pStates[SDL_SCANCODE_R]) 
				{
					if (!rKeyPressed) 
					{
						angle +=10;
						rKeyPressed = true;  
					}
				}
				else {
					rKeyPressed = false; 
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
		std::cout << "YOU WIN" << std::endl;
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

	utils::SetColor(Color4f{ 1.f, 0.f, 0.f, 1.f });
	utils::DrawRect(katinar);

	glPushMatrix();
	{

		glTranslatef(kluch.left, kluch.bottom, 0);
		glRotatef(angle, 0.f, 0.f, 1.f);
		glTranslatef(-kluch.left, -kluch.bottom, 0);
		utils::SetColor(Color4f{ 0.f, 1.f, 0.f, 0.5f });
		utils::FillRect(kluch);

		/*std::cout << "Angle:" << angle << std::endl;*/

		utils::SetColor(Color4f{ 1.f,0.f,1.f,1.f });
		utils::DrawEllipse(Point2f{ kluch.left,kluch.bottom }, 5.f, 5.f);
	}

	glPopMatrix();

	if (m_pTimer->TimeOut(elapsedTime) && !IsIntersecting(kluch, katinar))
	{
		std::cout << "TIME FINISHED. YOU LOSE! MUHAHAHAHA" << std::endl;
		utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
		utils::FillRect(0.f, 0.f, 800.f, 500.f);
	}
}


bool Game::IsIntersecting(const Rectf& r1, const Rectf& r2) const
{
	if (	(int(r1.left) == int(r2.left) && int(r1.bottom) == int(r2.bottom) && (int(angle) % 360) == 0)
		||  (int(r1.left + 1) == int(r2.left) && int(r1.bottom) == int(r2.bottom) && (int(angle) % 360) == 0) )
	{
		return true;
	}
	

	//
	return false;
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

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
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

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
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

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
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




void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
