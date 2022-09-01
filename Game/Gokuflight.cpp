#include "Gokuflight.h"
#include "Engine.h"
#include "GameComponents/EnemyComponent.h"

void Gokuflight::Initialize()
{
	REGISTER_CLASS(EnemyComponent);

	phoenix::g_audioSystem.AddAudio("Pickup", "Sound/coin.wav");

	m_scene = std::make_unique<phoenix::Scene>();

	rapidjson::Document document;
	std::vector<std::string> sceneNames = { "Scene/level.txt","Scene/prefabs.txt", "Scene/Menu.txt" };

	for (auto& sceneName : sceneNames)
	{

		bool successs = phoenix::json::Load(sceneName, document);
		if (!successs)
		{
			LOG("could not load scene %s", sceneName.c_str());
			continue;
		}
		std::cout << sceneName << std::endl;
		m_scene->Read(document);

	}
	m_scene->Initialize();

	phoenix::g_eventManager.Subscribe("EVENT_ADD_POINTS", std::bind(&Gokuflight::OnNotify, this, std::placeholders::_1));
	phoenix::g_eventManager.Subscribe("EVENT_PLAYER_DEAD", std::bind(&Gokuflight::OnNotify, this, std::placeholders::_1));

}

void Gokuflight::Shutdown()
{
	phoenix::g_audioSystem.Shutdown(); //STOPS AUDIO when ending game
	m_scene->RemoveAll();
}

void Gokuflight::Update()
{
	switch (m_gameState)
	{
	case Gokuflight::gameState::Menu:
		// add title screen menu options before play begins
		m_scene->GetActorFromName("LevelMusic")->GetComponent<phoenix::AudioComponent>()->Stop();
		m_scene->GetActorFromName("Menu")->SetActive(true);
		if (phoenix::g_inputSystem.GetKeyState(phoenix::key_enter) == phoenix::InputSystem::KeyState::Pressed)
		{
			m_scene->GetActorFromName("Music")->GetComponent<phoenix::AudioComponent>()->Stop();
			m_gameState = gameState::titleScreen;
		}



		break;

	case Gokuflight::gameState::titleScreen:
	{

		m_scene->GetActorFromName("Title")->SetActive(true);
		m_gameState = gameState::startLevel;

		m_scene->GetActorFromName("LevelMusic")->GetComponent<phoenix::AudioComponent>()->Play();
	}
	break;

	case Gokuflight::gameState::startLevel:
		// change in game music to different sound than menu screen
		m_scene->GetActorFromName("Menu")->SetActive(false);
		for (int i = 0; i < 3; i++)
		{
			auto actor = phoenix::Factory::Instance().Create<phoenix::Actor>("Coin");
			if (actor)
			{
				actor->m_transform.position = { phoenix::randomf(0,540), phoenix::randomf(100,300) };
			
			}

			// change coins to only do 1 coin in random spots fly by to collect 
			actor->Initialize();

			m_scene->Add(std::move(actor));
		}
		for (int i = 0; i < 1; i++)
		{
			auto actor = phoenix::Factory::Instance().Create<phoenix::Actor>("Ghost");
			if (actor)
			{
				actor->m_transform.position = { phoenix::randomf(0,540), 100.0f };

			}
			actor->Initialize();

			m_scene->Add(std::move(actor));
		}
		//add clouds as transparent texture so player can pass through it and collect coins and damage enemies

		m_gameState = gameState::game;

		break;
	case Gokuflight::gameState::game:
	{
		auto actor = m_scene->GetActorFromName("Lives");
		if (actor)
		{
			auto component = actor->GetComponent<phoenix::TextComponent>();
			component->SetText(std::to_string(m_lives));

		}

	}

	//enemies fly from right side and attack player


	break;
	case Gokuflight::gameState::playerDead:
		m_stateTimer = phoenix::g_time.deltaTime;
		if (m_stateTimer <= 0)
		{

			m_gameState = (m_lives < 0) ? gameState::startLevel : gameState::gameOver;
		}
		break;

	case Gokuflight::gameState::gameOver:
		// add game over title screen

		break;
	default:
		break;
	}

	m_scene->Update();

}

void Gokuflight::Draw(phoenix::Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void Gokuflight::OnAddPoints(const phoenix::Event& event)
{
	std::cout << event.name << std::endl;
	std::cout << std::get<int>(event.data) << std::endl;
}

void Gokuflight::OnPlayerDead(const phoenix::Event& event)
{
	m_gameState = gameState::playerDead;
	m_stateTimer = 3;
}

void Gokuflight::OnNotify(const phoenix::Event& event)
{
	if (event.name == "EVENT_ADD_POINTS")
	{

	}
	if (event.name == "EVENT_PLAYER_DEAD")
	{
		m_gameState = gameState::playerDead;
		m_lives;;
		m_stateTimer = 3;
	}

}
