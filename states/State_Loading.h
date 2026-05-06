#pragma once
#include "BaseState.h"
#include <SFML/Audio.hpp>
#include <thread>

class State_Loading : public BaseState {
public:
	State_Loading(StateManager* l_stateManager);
	~State_Loading();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();
	void HandleInput(const sf::Event& event) override { }
	void Update(const float l_time);
	void Draw();

	void Continue();
private:
	sf::Sprite m_introSprite;
	sf::Texture m_introTexture;

	std::thread* music_manager_thread;
	std::thread* texture_manager_thread;

	sf::Sprite m_backgroundSprite;
	sf::Texture m_backgroundTexture;
	sf::Font m_font;
	sf::Text m_text;
	float m_elapsed = 0;
	float threshold_sec = 2;
};