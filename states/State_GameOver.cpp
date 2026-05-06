#include "State_GameOver.h"
#include "StateManager.h"


State_GameOver::State_GameOver(StateManager* l_stateManager)
	: BaseState(l_stateManager),m_rects(m_amountButtons),m_labels(m_amountButtons) {}

State_GameOver::~State_GameOver(){}

void State_GameOver::OnCreate(){
	sf::Vector2u windowSize = m_stateMgr->GetContext()
		->m_wind->GetRenderWindow()->getSize(); 

	sf::Texture* backgroundTexture = m_stateMgr->GetContext()->m_levelManager->get_textureManager()->
		get_texture("MaincraftSunset");
	m_backgroundSprite.setTexture(*(backgroundTexture));
	m_backgroundSprite.setScale(static_cast<float>(windowSize.x) / backgroundTexture->getSize().x+0.25f,
		static_cast<float>(windowSize.y) / backgroundTexture->getSize().y);
	

	m_backgroundSprite.setOrigin(backgroundTexture->getSize().x / 2.0f, backgroundTexture->getSize().y / 2.0f);
	m_backgroundSprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	m_font.loadFromFile(Utils::GetWorkingDirectory() + "Game\\Fonts\\arial.ttf");

	m_headline.setFont(m_font);
	m_headline.setString(sf::String("GAME OVER!"));
	m_headline.setCharacterSize(30);
	m_headline.setFillColor(sf::Color::Cyan);

	sf::FloatRect headtextRect = m_headline.getLocalBounds();
	m_headline.setOrigin(headtextRect.left + headtextRect.width / 2.0f,
		headtextRect.top + headtextRect.height / 2.0f);

	m_headline.setPosition(windowSize.x / 2.0f, 50);

	std::ifstream f(Utils::GetWorkingDirectory() + "Game\\Log\\history.txt");

	std::string s;
	getline(f,  s);
	std::stringstream strstr(s);
	std::string result,temp;
	while (!strstr.eof()) {
		strstr >> temp;
		if (temp=="Time"||temp == "Coins:" || temp == "Date:")
			result += "\n";
		result += temp+" ";
		
	}
	m_text.setFont(m_font);
	m_text.setString(
		sf::String("YOU PASSED THIS LEVEL WITH THESE RESULTS:\n") +result 
	);
	m_text.setCharacterSize(25);
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	m_text.setFillColor(sf::Color::White);
	m_text.setOutlineColor(sf::Color::Red);
	m_text.setOutlineThickness(1.5);

	m_text.setPosition(windowSize.x / 2.0F, windowSize.y / 2.0f);

	m_buttonSize = sf::Vector2f(300.0f, 32.0f);
	m_buttonPos = sf::Vector2f(windowSize.x / 2.0f, windowSize.y - m_buttonSize.y * 2.0f);
	m_buttonPadding = 10; // 4px.
	std::string str[2];
	str[0] = "GO BACK TO MAIN MENU";
	str[1] = "GO TO THE NEXT LEVEL";

	for (int i = 0; i < m_amountButtons; ++i) {
		sf::Vector2f buttonPosition(
			m_buttonPos.x, m_buttonPos.y +
			(i * (m_buttonSize.y + m_buttonPadding)));
		m_rects[i].setSize(m_buttonSize);
		m_rects[i].setFillColor(sf::Color::Transparent);
		m_rects[i].setOutlineColor(sf::Color::White);
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
	m_stateMgr->Remove(StateType::Game);
}

void State_GameOver::OnDestroy(){}

void State_GameOver::Activate(){}
void State_GameOver::Deactivate(){}

void State_GameOver::Update(const float l_time){

	sf::Vector2u windowSize = m_stateMgr->GetContext()
		->m_wind->GetRenderWindow()->getSize();

	float a = windowSize.x / m_backgroundSprite.getLocalBounds().width;
	float b = windowSize.y / m_backgroundSprite.getLocalBounds().height;
	m_backgroundSprite.setScale(a, b);
	m_backgroundSprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
	m_elapsed += l_time;
	if(m_elapsed >= 15.0f){
		m_stateMgr->SwitchTo(StateType::MainMenu);
		m_stateMgr->Remove(StateType::GameOver);
		m_elapsed = 0;
	}
}

void State_GameOver::MouseClick(const sf::Vector2i& l_details) {
	SharedContext* context = m_stateMgr->GetContext();
	sf::Vector2i mousePos = l_details;

	float halfX = m_buttonSize.x / 2.0f;
	float halfY = m_buttonSize.y / 2.0f;
	for (int i = 0; i < m_amountButtons; ++i) {
		if (mousePos.x >= m_rects[i].getPosition().x - halfX &&
			mousePos.x <= m_rects[i].getPosition().x + halfX &&
			mousePos.y >= m_rects[i].getPosition().y - halfY &&
			mousePos.y <= m_rects[i].getPosition().y + halfY)
		{
			switch (i) {
			case 0:
				Continue();
				break;
			case 1:
				m_stateMgr->GetContext()->m_levelManager->nextLevel();
				m_stateMgr->SwitchTo(StateType::Game);
				m_stateMgr->Remove(StateType::GameOver);
				break;
			}
		}
	}
}

void State_GameOver::Continue() {
	m_stateMgr->SwitchTo(StateType::MainMenu);
	m_stateMgr->Remove(StateType::GameOver);
}

void State_GameOver::Draw(){
	sf::RenderWindow* window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
	//window->clear(sf::Color::Black);
	window->draw(m_backgroundSprite);
	for (int i = 0; i < m_amountButtons; ++i) {
		window->draw(m_rects[i]);
		window->draw(m_labels[i]);
	}
	window->draw(m_headline);
	window->draw(m_text);
}