#include "State_Levels.h"
#include "StateManager.h"

State_Levels::State_Levels(StateManager* l_stateManager) :
	m_rects(m_amountButtons), m_labels(m_amountButtons),
	m_levelRects(m_stateMgr->GetContext()->m_levelManager->amountLevels()),
	m_levelLabels(m_stateMgr->GetContext()->m_levelManager->amountLevels()),
	BaseState(l_stateManager) {}

State_Levels::~State_Levels() {}

void State_Levels::OnCreate() {
	sf::Vector2u windowSize = m_stateMgr->GetContext()
		->m_wind->GetRenderWindow()->getSize();

	sf::Texture* backgroundTexture = m_stateMgr->GetContext()->m_levelManager->get_textureManager()->
		get_texture("BackgroundStarsSky");
	m_backgroundSprite.setTexture(*(backgroundTexture));
	m_backgroundSprite.setScale(0.7,
		0.5);


	m_backgroundSprite.setOrigin(backgroundTexture->getSize().x / 2.0f, backgroundTexture->getSize().y / 2.0f);
	m_backgroundSprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	m_font.loadFromFile(Utils::GetWorkingDirectory() + "Game\\Fonts\\arial.ttf");

	m_headline.setFont(m_font);
	m_headline.setString(sf::String("LEVELS:"));
	m_headline.setCharacterSize(30);
	m_headline.setFillColor(sf::Color::Cyan);

	sf::FloatRect headtextRect = m_headline.getLocalBounds();
	m_headline.setOrigin(headtextRect.left + headtextRect.width / 2.0f,
		headtextRect.top + headtextRect.height / 2.0f);

	m_headline.setPosition(windowSize.x / 2.0f, 50);

	m_text.setFont(m_font);
	m_text.setString(
		sf::String("\n")

	);
	m_text.setCharacterSize(25);
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	m_text.setFillColor(sf::Color::White);
	m_text.setOutlineColor(sf::Color::Red);
	m_text.setOutlineThickness(1.5);
	//m_text.setPosition(10, 0);

	m_text.setPosition(windowSize.x / 2.0F, windowSize.y / 2.0f);


	m_buttonSize = sf::Vector2f(400.0f, 32.0f);
	m_buttonPos = sf::Vector2f(windowSize.x / 2.0f, windowSize.y - m_buttonSize.y * 2.0f);

	m_buttonPadding = 10; // 4px.
	std::string str[1];
	
	str[0] = "GO BACK TO MENU";

	for (int i = 0; i < m_amountButtons; ++i) {
		sf::Vector2f buttonPosition(
			m_buttonPos.x, m_buttonPos.y +
			(i * (m_buttonSize.y + m_buttonPadding)));
		m_rects[i].setSize(m_buttonSize);
		m_rects[i].setFillColor(sf::Color::Transparent);
		m_rects[i].setOutlineColor( sf::Color::White);
		m_rects[i].setOutlineThickness(3);

		m_rects[i].setOrigin(
			m_buttonSize.x / 2.0f, m_buttonSize.y / 2.0f);
		m_rects[i].setPosition(buttonPosition);

		m_labels[i].setFont(m_font);
		m_labels[i].setFillColor(sf::Color::White);
		m_labels[i].setString(sf::String(str[i]));
		m_labels[i].setCharacterSize(20);
		m_labels[i].setOutlineColor(sf::Color::Blue);
		m_labels[i].setOutlineThickness(1);

		sf::FloatRect rect = m_labels[i].getLocalBounds();
		m_labels[i].setOrigin(
			rect.left + rect.width / 2.0f,
			rect.top + rect.height / 2.0f);

		m_labels[i].setPosition(buttonPosition);
	}

	m_levelButtonSize = sf::Vector2f(64.0f, 64.0f);
	m_levelButtonPos = sf::Vector2f(m_levelButtonSize.x, windowSize.y/2.0f - m_headline.getPosition().y);

	m_levelButtonPadding = m_levelButtonSize.x/2.0f; // 4px.

	int row = 0;
	int column = 0;
	sf::Vector2f buttonPosition;
	for (int i = 0; i < m_levelLabels.size(); ++i) {
		
		if (buttonPosition.x + (m_levelButtonSize.x + m_levelButtonPadding) > windowSize.x) {
			++row;
			column += i;
			
		}
		buttonPosition= sf::Vector2f(
			m_levelButtonPos.x+
			((i-column) * (m_levelButtonSize.y + m_levelButtonPadding)),
			m_levelButtonPos.y+ (row * (m_levelButtonSize.y + m_levelButtonPadding)));
			
		m_levelRects[i].setSize(m_levelButtonSize);
		m_levelRects[i].setFillColor(sf::Color::Transparent);
		m_levelRects[i].setOutlineColor(
			m_stateMgr->GetContext()->m_levelManager->get_Level(i)->IsDone()?sf::Color::Green:
		sf::Color::White);
		m_levelRects[i].setOutlineThickness(3);

		m_levelRects[i].setOrigin(
			m_levelButtonSize.x / 2.0f, m_levelButtonSize.y / 2.0f);
		m_levelRects[i].setPosition(buttonPosition);

		m_levelLabels[i].setFont(m_font);
		m_levelLabels[i].setFillColor(sf::Color::White);
		m_levelLabels[i].setString(std::to_string(i+1));
		m_levelLabels[i].setCharacterSize(30);
		m_levelLabels[i].setOutlineColor(sf::Color::White);
		m_levelLabels[i].setOutlineThickness(1);

		sf::FloatRect rect = m_levelLabels[i].getLocalBounds();
		m_levelLabels[i].setOrigin(
			rect.left + rect.width / 2.0f,
			rect.top + rect.height / 2.0f);

		m_levelLabels[i].setPosition(buttonPosition);
	}
}

void State_Levels::OnDestroy() {
}
void State_Levels::MouseClick(const sf::Vector2i& l_details) {
	//SharedContext* context = m_stateMgr->GetContext();
	sf::Vector2i mousePos = l_details;

	float halfX = m_levelButtonSize.x / 2.0f;
	float halfY = m_levelButtonSize.y / 2.0f;
	for (int i = 0; i < m_levelRects.size(); ++i) {
		if (mousePos.x >= m_levelRects[i].getPosition().x - halfX &&
			mousePos.x <= m_levelRects[i].getPosition().x + halfX &&
			mousePos.y >= m_levelRects[i].getPosition().y - halfY &&
			mousePos.y <= m_levelRects[i].getPosition().y + halfY){
			if (!m_stateMgr->HasState(StateType::Game)) {

				m_stateMgr->GetContext()->m_levelManager->set_current_level(i);
				m_stateMgr->SwitchTo(StateType::Game);
				m_stateMgr->Remove(StateType::Levels);
			}
		}
	}

	halfX = m_buttonSize.x / 2.0f;
	halfY = m_buttonSize.y / 2.0f;
	for (int i = 0; i < m_amountButtons; ++i) {
		if (mousePos.x >= m_rects[i].getPosition().x - halfX &&
			mousePos.x <= m_rects[i].getPosition().x + halfX &&
			mousePos.y >= m_rects[i].getPosition().y - halfY &&
			mousePos.y <= m_rects[i].getPosition().y + halfY) {
			switch (i) {
			case 0:
				Continue();
				break;
			}
		}
	}
}


void State_Levels::Draw() {
	sf::RenderWindow* window = m_stateMgr->
		GetContext()->m_wind->GetRenderWindow();
	window->draw(m_backgroundSprite);
	for (int i = 0; i < m_amountButtons; ++i) {
		window->draw(m_rects[i]);
		window->draw(m_labels[i]);
	}
	for (int i = 0; i < m_levelRects.size(); ++i) {
		window->draw(m_levelRects[i]);
		window->draw(m_levelLabels[i]);
	}
	window->draw(m_headline);
	window->draw(m_text);
}

void State_Levels::Continue() {
	if (ChangeTime >= ChangeTimeThreshold) {
		m_stateMgr->SwitchTo(StateType::MainMenu);
		m_stateMgr->Remove(StateType::Levels);
		ChangeTime = 0;
	}
}

void State_Levels::Update(const float l_time) {
	sf::Vector2u windowSize = m_stateMgr->GetContext()
		->m_wind->GetRenderWindow()->getSize();
	m_backgroundSprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
	float a = m_stateMgr->GetContext()->m_wind->GetViewSpace().width / m_backgroundSprite.getLocalBounds().width;
	float b = m_stateMgr->GetContext()->m_wind->GetViewSpace().height / m_backgroundSprite.getLocalBounds().height;
	m_backgroundSprite.setScale(a, b);
	ChangeTime += l_time; 
}
void State_Levels::Activate() {	}
void State_Levels::Deactivate() {}