#include "Engine.h"
#include "Gokuflight.h"

#include <iostream>

int main()
{

	phoenix::InitializeMemory();
	phoenix::SetFilePath("../Assets");

	phoenix::g_physicsSystem.Initialize();
	phoenix::g_renderer.Initialize();
	phoenix::g_inputSystem.Initialize();
	phoenix::g_audioSystem.Initialize();
	phoenix::g_resources.Initialize();
	phoenix::g_eventManager.Initialize();

	phoenix::Engine::Instance().Register();

	//create window
	phoenix::g_renderer.CreateWindow("GAT150 Game", 800, 600);
	phoenix::g_renderer.SetClearColor(phoenix::Color{ 0, 0, 0, 255 });

	//create game
	std::unique_ptr<Gokuflight> game = std::make_unique<Gokuflight>();
	game->Initialize();
	
	// ^^ initialized Engine Above ^^ 

	bool quit = false;
	while (!quit)
	{
		phoenix::g_time.Tick();
		phoenix::g_inputSystem.Update();
		phoenix::g_audioSystem.Update();
		phoenix::g_physicsSystem.Update();
		phoenix::g_eventManager.Update();

		if (phoenix::g_inputSystem.GetKeyState(phoenix::key_escape)) quit = true;

		game->Update();

		//update game objects
		phoenix::g_renderer.BeginFrame();

		game->Draw(phoenix::g_renderer);

		//end window
		phoenix::g_renderer.EndFrame();
	}
	game->Shutdown();
	game.reset();

	phoenix::Factory::Instance().Shutdown();

	phoenix::g_physicsSystem.Shutdown();
	phoenix::g_resources.Shutdown();
	phoenix::g_inputSystem.Shutdown();
	phoenix::g_audioSystem.Shutdown();
	phoenix::g_renderer.Shutdown();
	phoenix::g_eventManager.Shutdown();



}


