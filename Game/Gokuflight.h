#pragma once
#include "Framework/Game.h"
#include "Framework/Event.h"

class Gokuflight : public phoenix::Game, public phoenix::INotify
{
public:

	enum class gameState
	{
		titleScreen,
		Menu,
		startLevel,
		game,
		playerDead,
		gameOver

	};


	// Inherited via Game
	virtual void Initialize() override;
	virtual void Shutdown() override;

	virtual void Update() override;
	virtual void Draw(phoenix::Renderer& renderer) override;

	void OnAddPoints(const phoenix::Event& event);
	void OnPlayerDead(const phoenix::Event& event);

private:
	gameState m_gameState = gameState::Menu;
	float m_stateTimer = 0;
	int m_lives = 3;

	// Inherited via INotify
	virtual void OnNotify(const phoenix::Event& event) override;

};