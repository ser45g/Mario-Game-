#pragma once
#include "BaseState.h"
#include "../Map.h"
#include "../enemy.h"
#include "../Textbox.h"
#include "../Player.h"
#include "StateManager.h"
#include<SFML/Audio.hpp>
#include "../ResourceManagment/LevelManager.h"
#include<thread>
#include "../Flag.h"

class State_Game : public BaseState{
public:
	State_Game(StateManager* l_stateManager);
	~State_Game();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();
	void HandleInput(const sf::Event& event);
	void Update(const float l_time);
	void Draw();

	void SaveResults();
	void MainMenu();
	void Pause();
	void GameOver();
	void EndCredits();
private:
	sf::Clock m_clockshow;
	float m_elapsed;
	float m_timePassedSinceLastPausePushed = 0;
	Player m_player;
	sf::Sprite heart;
	sf::Texture heartTexture;
	
	sf::Sprite* m_backgroundSprite;

	std::thread* music_thread;
	Music* music;

	Textbox m_textbox;
	Map* map;
	Level* level;
	Flag flag;
	std::vector<Enemy*> enemy;

};