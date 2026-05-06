#pragma once
#include "BaseState.h"
#include <vector>
#include "../Utility.cpp"
#include <fstream>
class State_Settings : public BaseState {
public:
	State_Settings(StateManager* l_stateManager);
	~State_Settings();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();
	void HandleInput(const sf::Event& event) override {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
			Continue();
		}
		else if(sf::Event::MouseButtonPressed==event.type) 
		{
			MouseClick(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
		}
	}
	void MouseClick(const sf::Vector2i& l_details);

	void Update(const float l_time);
	void Draw();

	void DeleteHistory(){
		std::ofstream ofs(Utils::GetWorkingDirectory() + "Game\\Log\\history.txt",
			std::ios::out | std::ios::trunc);
		ofs.close();
	}
	void Reset();
	void ToggleMusic(bool play);

	void Continue();
private:
	sf::Text m_headline;
	sf::Sprite m_backgroundSprite;
	sf::Font m_font;
	sf::Text m_text;

	sf::Vector2f m_buttonSize;
	sf::Vector2f m_buttonPos;
	unsigned int m_buttonPadding;
	const int m_amountButtons = 4;
	std::vector<sf::RectangleShape >m_rects;
	std::vector<sf::Text> m_labels;
	std::vector<bool> m_state;
};

