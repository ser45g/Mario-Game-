#pragma once
#include "BaseState.h"
#include <SFML/Audio.hpp>
#include <thread>

class State_Intro : public BaseState{
public:
	State_Intro(StateManager* l_stateManager);
	~State_Intro();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();
	void HandleInput(const sf::Event& event) override;
	
	void Update(const float l_time);
	void Draw();

	void Continue();
private:
	sf::Sprite m_introSprite;
	sf::Sprite m_backgroundSprite;
	sf::Texture* backgroundTexture;
	sf::Font m_font;
	sf::Text m_text;
};