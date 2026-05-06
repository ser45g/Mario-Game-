#pragma once
#include "Window.h"
//#include "World.h"
//#include "Player.h"
//#include "Textbox.h"
//#include "Map.h"
//#include "enemy.h"
#include "states/StateManager.h"
#include "ResourceManagment/LevelManager.h"
//#include "Snake.h"
//#include "Textbox.h"
//#include "enemy.cpp"

class Game{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();

	sf::Time GetElapsed();
	void LateUpdate() {
		m_stateManager.ProcessRequests();
		RestartClock();
	}
	void RestartClock();

	Window* GetWindow();
private:
	Window m_window;
	sf::Clock m_clock;
	sf::Image icon;
	float m_timestep = 1 / 24;
	float m_elapsed=0;
	SharedContext m_context;
	StateManager m_stateManager;
	LevelManager m_levelManager;
	MusicManager m_musicManager;
	TextureManager m_textureManager;

};