#include "Game.h"


#include <random>


Game::~Game()
{
	//If window isn't equal to nullptr
	if (m_window != nullptr)
	{
		//Delete window
		delete m_window;
		//set window to nullptr
		m_window = nullptr;
	}

	//Goes through the scenes and deletes them
	for (unsigned i = 0; i < m_scenes.size(); i++)
	{
		if (m_scenes[i] != nullptr)
		{
			delete m_scenes[i];
			m_scenes[i] = nullptr;
		}
	}
}

void Game::InitGame()
{
	//Scene names and clear colors
	m_name = "Hello World";
	m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);

	//Initializes the backend
	BackEnd::InitBackEnd(m_name);

	//Grabs the initialized window
	m_window = BackEnd::GetWindow();

	//Grabs the initialized window, whenever making a new scene
	m_scenes.push_back(new HelloWorld("Hello World"));
	m_scenes.push_back(new Scene("First Loaded Scene"));

	//Sets active scene reference to our HelloWorld scene
	//m_activeScene = m_scenes[0]; //Load the HelloWorld basic scene
	m_activeScene = m_scenes[0]; //Load the first scene
	
	//Inititalizes the scene, //Save, uncomment to save and comment the load
	m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	
	//Load uncomment to load and comment the save
	//*m_activeScene = File::LoadJSON("Hello World.json"); //Hello World Sprite
	//*m_activeScene = File::LoadJSON("Hello Anime World.json"); //Load the saved scene

	
	//Sets m_register to point to the register in the active scene
	m_register = m_activeScene->GetScene();
}

bool Game::Run()
{
	//While window is still open
	while (m_window->isOpen())
	{
		//Clear window with clearColor
		m_window->Clear(m_clearColor);
		//Updates the game
		Update();
		//Draws the game
		BackEnd::Draw(m_register);

		//Draws ImGUI
		if (m_guiActive)
			GUI();
		
		//Flips the windows
		m_window->Flip();
		
		//Polls events and then checks them
		BackEnd::PollEvents(m_register, &m_close, &m_motion, &m_click, &m_wheel);
		CheckEvents();

		//does the window have keyboard focus?
		if (Input::m_windowFocus)
		{
			//Accept all input
			AcceptInput();
		}
	}

	return true;
}

void Game::Update()
{
	//Update timer
	Timer::Update();
	//Update the backend
	BackEnd::Update(m_register);
}

void Game::GUI()
{
	UI::Start(BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());

	ImGui::Text("Place your different tabs below.");

	if (ImGui::BeginTabBar(""))
	{
		BackEnd::GUI(m_register, m_activeScene);

		ImGui::EndTabBar();
	}

	UI::End();
}

void Game::CheckEvents()
{
	if (m_close)
		m_window->Close();

	if (m_motion)
		MouseMotion(BackEnd::GetMotionEvent());

	if (m_click)
		MouseClick(BackEnd::GetClickEvent());

	if (m_wheel)
		MouseWheel(BackEnd::GetWheelEvent());
}

void Game::AcceptInput()
{
	//Just calls all the other input functions 
	KeyboardHold();
	KeyboardDown();
	KeyboardUp();

	//Resets the key flags
	//Must be done once per frame for input to work
	Input::ResetKeys();
}

//Keys being press continuely
void Game::KeyboardHold()
{
	//Keyboard button held
	if (Input::GetKey(Key::F3))
	{
		
	}
	if (Input::GetKey(Key::F4)){
		printf("F4 Key Held\n");
	}


	vec3 position = m_register->get<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

	float speed = 30.f;
	//Keyboard button held
	if (Input::GetKey(Key::W)) {
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionY(++position.y + (speed * Timer::deltaTime));

	}
	if (Input::GetKey(Key::S)) {
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionY(--position.y - (speed * Timer::deltaTime));
	
	}
	if (Input::GetKey(Key::A)) {
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionX(--position.x - (speed * Timer::deltaTime));
	
	}
	if (Input::GetKey(Key::D)) {
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionX(++position.x + (speed * Timer::deltaTime));

	}

	m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionX(position.x);
	

	

}

//Keys being pressed once
void Game::KeyboardDown()
{
	//Keyboard button down
	if (Input::GetKeyDown(Key::F2))
	{
		
	}

	if (Input::GetKeyDown(Key::F4))
	{
		printf("F4 Key Down\n");
	}


	
	auto& animControllerr = ECS::GetComponent<AnimationController>(2);

	if (Input::GetKeyDown(Key::A))
	{
		
		printf("A Key Down\n");
		animControllerr.SetActiveAnim(2);
		
	}
	
	if (Input::GetKeyDown(Key::W))
	{
		printf("W Key Down\n");
		animControllerr.SetActiveAnim(1);

	}if (Input::GetKeyDown(Key::S))
	{
		printf("S Key Down\n");
		animControllerr.SetActiveAnim(0);
	}
	if (Input::GetKeyDown(Key::D))
	{
		printf("D Key Down\n");
		animControllerr.SetActiveAnim(3);
	}


	
}
//Keys after being press once
void Game::KeyboardUp()
{
	//Keyboard button up
	if (Input::GetKeyUp(Key::F1))
	{
		if (!UI::m_isInit)
		{
			UI::InitImGUI();
		}
		m_guiActive = !m_guiActive;
	}

	if (Input::GetKeyUp(Key::F4))
	{
		printf("F4 Key Released\n");
	}
}

void Game::MouseMotion(SDL_MouseMotionEvent evnt)
{
	printf("Mouse Moved (%f, %f)\n", float(evnt.x), float(evnt.y));

	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));

		if (!ImGui::GetIO().WantCaptureMouse)
		{

		}
	}

	//Resets the enabled flag
	m_motion = false;

	
}

void Game::MouseClick(SDL_MouseButtonEvent evnt)
{
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) 
	{
		printf("Left Mouse Button Clicked at (% f, % f)\n", float(evnt.x), float(evnt.y));
	}

	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		printf("Right Mouse Button Clicked at (% f, % f)\n", float(evnt.x), float(evnt.y));
	}

	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE))
	{
		printf("Middle Mouse Button Clicked at (% f, % f)\n", float(evnt.x), float(evnt.y));
	}

	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));
		ImGui::GetIO().MouseDown[0] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
		ImGui::GetIO().MouseDown[1] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT));
		ImGui::GetIO().MouseDown[2] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE));
	}

	//Resets the enabled flag
	m_click = false;
}

void Game::MouseWheel(SDL_MouseWheelEvent evnt)
{
	printf("Mouse Scroll %f\n", float(evnt.y));

	if (m_guiActive)
	{
		ImGui::GetIO().MouseWheel = float(evnt.y);
	}
	//Resets the enabled flag
	m_wheel = false;
}
