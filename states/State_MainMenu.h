#pragma once
#include "BaseState.h"
class State_MainMenu : public BaseState{
public:
	State_MainMenu(StateManager* l_stateManager);
	~State_MainMenu();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void HandleInput(const sf::Event& event) override;

	void Update(const float l_time);
	void Draw();

	void MouseClick(const sf::Vector2i& l_details);
private:
	sf::Font m_font;
	sf::Text m_text;

	sf::Vector2f m_buttonSize;
	sf::Vector2f m_buttonPos;
	unsigned int m_buttonPadding;
	sf::Sprite m_backgroundSprite;

	sf::Texture* backgroundTexture;
	const int m_amountButtons = 6;
	std::vector<sf::RectangleShape >m_rects;
	std::vector<sf::Text> m_labels;
};