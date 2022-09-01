#include "Gokuflight.h"
#include "Engine.h"
#include "GameComponents/EnemyComponent.h"

void Gokuflight::Initialize()
{
	REGISTER_CLASS(EnemyComponent);

	m_scene = std::make_unique<phoenix::Scene>();

	rapidjson::Document document;
	std::vector<std::string> sceneNames = { "Scene/Menu.txt", "Scene/prefabs.txt","Scene/level.txt" };

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
	{
			m_scene->GetActorFromName("Menu")->SetActive(false);

	}
			m_gameState = gameState::titleScreen;

		break;

	case Gokuflight::gameState::titleScreen:
	{

	//	m_scene->GetActorFromName("Title")->SetActive(false);
		m_gameState = gameState::startLevel;
		
	}
		break;

	case Gokuflight::gameState::startLevel:
		// change in game music to different sound than menu screen

		//for (int i = 0; i < 1; i++)
		//{
		//	auto actor = phoenix::Factory::Instance().Create<phoenix::Actor>("Coin");
		//	actor->m_transform.position = { phoenix::randomf(0,400), 100.0f };

		//	// change coins to only do 1 coin in random spots fly by to collect 


		//	actor->Initialize();

		//	m_scene->Add(std::move(actor));
		//}
		for (int i = 0; i < 1; i++)
		{
			auto actor = phoenix::Factory::Instance().Create<phoenix::Actor>("Ghost");
			actor->m_transform.position = { phoenix::randomf(0,500 ), 100.0f };
			actor->Initialize();

			m_scene->Add(std::move(actor));
		}
		//add clouds as transparent texture so player can pass through it and collect coins and damage enemies
		m_gameState = gameState::game;

		break;
	case Gokuflight::gameState::game:
	{
		auto actor = m_scene->GetActorFromName("Lives");
		auto component = actor->GetComponent<phoenix::TextComponent>();
		component->SetText(std::to_string(m_lives));

		/*auto player = m_scene->GetActorFromName("Player");
		auto playerComponent = player->GetComponent<phoenix::TextComponent>();
		component->SetText(std::to_string((int)playerComponent->health));*/


		
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
