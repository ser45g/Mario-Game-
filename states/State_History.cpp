#include "State_History.h"
#include "StateManager.h"
#include <fstream>

State_History::State_History(StateManager* l_stateManager):
	m_notActiveRects(m_amountButtons), m_notActiveLabels(m_amountButtons),
	BaseState(l_stateManager) {}

State_History::~State_History() {}

void State_History::OnCreate() {
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
	m_headline.setString(sf::String("GAME HISTORY:"));
	m_headline.setCharacterSize(30);
	m_headline.setFillColor(sf::Color::Cyan);

	sf::FloatRect headtextRect = m_headline.getLocalBounds();
	m_headline.setOrigin(headtextRect.left + headtextRect.width / 2.0f,
		headtextRect.top + headtextRect.height / 2.0f);

	m_headline.setPosition(windowSize.x / 2.0f, 25);


	m_buttonSize = sf::Vector2f(750.0f, 32.0f);
	m_buttonPos = sf::Vector2f(windowSize.x / 2.0f, 70);
	m_buttonPadding = 10; // 4px.
	std::string str[1];
	//str[0] = "GO BACK TO MAIN MENU";

	
	std::ifstream f(Utils::GetWorkingDirectory() + "Game\\Log\\history.txt");
	if (!f.good()) {
		std::cout << "Can't open history.txt";
	}
	std::string s;
	
	while (!f.eof()) {
		getline(f, s);
		auto i = s.find_first_not_of(' ');
		if (i==s.npos)
			continue;
		history_info.push_back(std::move(s));
	}
	for (int i = 0; i < std::min<const size_t>(m_amountButtons,history_info.size()); ++i) {
		sf::Vector2f buttonPosition(
			m_buttonPos.x, m_buttonPos.y +
			(i * (m_buttonSize.y + m_buttonPadding)));
		m_notActiveRects[i].setSize(m_buttonSize);
		m_notActiveRects[i].setFillColor(sf::Color::Transparent);
		m_notActiveRects[i].setOutlineColor(sf::Color::White);
		m_notActiveRects[i].setOutlineThickness(3);

		m_notActiveRects[i].setOrigin(
			m_buttonSize.x / 2.0f, m_buttonSize.y / 2.0f);
		m_notActiveRects[i].setPosition(buttonPosition);

		m_notActiveLabels[i].setFont(m_font);
		m_notActiveLabels[i].setFillColor(sf::Color::White);
		m_notActiveLabels[i].setString(sf::String(history_info[i]));
		m_notActiveLabels[i].setCharacterSize(20);
		m_notActiveLabels[i].setOutlineColor(sf::Color::Black);
		m_notActiveLabels[i].setOutlineThickness(1);

		sf::FloatRect rect = m_notActiveLabels[i].getLocalBounds();
		m_notActiveLabels[i].setOrigin(
			rect.left + rect.width / 2.0f,
			rect.top + rect.height / 2.0f);

		m_notActiveLabels[i].setPosition(buttonPosition);
	}
	
	sf::Vector2f buttonPosition(windowSize.x/2.0f,windowSize.y-m_buttonSize.y-10);
	sf::Vector2f GoBackButtonSize{ m_buttonSize.x / 2.0f, 32.0f };
	GoBackButtonRect.setSize(GoBackButtonSize);
	GoBackButtonRect.setFillColor(sf::Color::Transparent);
	GoBackButtonRect.setOutlineColor(sf::Color::White);
	GoBackButtonRect.setOutlineThickness(3);

	GoBackButtonRect.setOrigin(
		GoBackButtonSize.x / 2.0f, GoBackButtonSize.y / 2.0f);
	GoBackButtonRect.setPosition(buttonPosition);
	
	GoBackButtonText.setFont(m_font);
	GoBackButtonText.setFillColor(sf::Color::White);
	GoBackButtonText.setString(sf::String("GO BACK TO MENU"));
	GoBackButtonText.setCharacterSize(20);
	GoBackButtonText.setOutlineColor(sf::Color::Red);
	GoBackButtonText.setOutlineThickness(1);

	sf::FloatRect rect = GoBackButtonText.getLocalBounds();
	GoBackButtonText.setOrigin(
		rect.left + rect.width / 2.0f,
		rect.top + rect.height / 2.0f);

	GoBackButtonText.setPosition(buttonPosition);
	//m_text.setPosition(windowSize.x/2,windowSize.y/2+200);
	//EventManager_* evMgr = m_stateMgr->
		//GetContext()->m_eventManager;
	//evMgr->AddCallback(StateType::Intro, "Intro_Continue", &State_Intro::Continue, this);
	f.close();
}
void State_History::Scroll(float delta) {

	if (delta < 0)
		if (scroll_pos + 1 < history_info.size()) {

			scroll_pos += 1;
		}
		else return;
	else if ((scroll_pos - 1) >= 0) {
		scroll_pos -= 1;
	}

	int a = scroll_pos + std::min<const size_t>(m_amountButtons,
		std::abs(int(scroll_pos - history_info.size())));
	int ii = 0;

	for (int i = 0; i < m_amountButtons; ++i) {
		sf::FloatRect rect = m_notActiveLabels[i].getLocalBounds();
		//m_notActiveLabels[i].setOrigin(
		//	rect.left + rect.width / 2.0f,
		//	rect.top + rect.height / 2.0f);
		m_notActiveLabels[i].setString(sf::String(""));
		m_notActiveRects[i].setOutlineColor(sf::Color::Transparent);
	}
	for (int i = scroll_pos; i < a; ++i, ++ii) {
		m_notActiveLabels[ii].setString(sf::String(history_info[i]));
		m_notActiveRects[ii].setOutlineColor(sf::Color::White);
	}

}

void State_History::OnDestroy() {}

void State_History::MouseClick(const sf::Vector2i& l_details) {
	SharedContext* context = m_stateMgr->GetContext();
	sf::Vector2i mousePos = l_details;

	float halfX = m_buttonSize.x / 2.0f;
	float halfY = m_buttonSize.y / 2.0f;
	for (int i = 0; i < 1; ++i) {
		if (mousePos.x >= GoBackButtonRect.getPosition().x - halfX &&
			mousePos.x <= GoBackButtonRect.getPosition().x + halfX &&
			mousePos.y >= GoBackButtonRect.getPosition().y - halfY &&
			mousePos.y <= GoBackButtonRect.getPosition().y + halfY) {
			switch (i) {
			case 0:
				Continue();
				break;
			}
		}
	}
}
void State_History::Draw() {
	sf::RenderWindow* window = m_stateMgr->
		GetContext()->m_wind->GetRenderWindow();
	
	window->draw(m_backgroundSprite);
	for (int i = 0; i < m_amountButtons; ++i) {
		window->draw(m_notActiveRects[i]);
		window->draw(m_notActiveLabels[i]);
	}
	window->draw(GoBackButtonRect);
	window->draw(GoBackButtonText);
	window->draw(m_headline);
}

void State_History::Continue() {
	m_stateMgr->SwitchTo(StateType::MainMenu);
	m_stateMgr->Remove(StateType::History);
}

void State_History::Update(const float l_time) {

	sf::Vector2u windowSize = m_stateMgr->GetContext()
		->m_wind->GetRenderWindow()->getSize();

	float a = windowSize.x / m_backgroundSprite.getLocalBounds().width;
	float b = windowSize.y / m_backgroundSprite.getLocalBounds().height;
	m_backgroundSprite.setScale(a, b);
	m_backgroundSprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);


	sf::Vector2f GoBackButtonSize = sf::Vector2f(350.0f, 32.0f);
	GoBackButtonRect.setSize(GoBackButtonSize);
	m_backgroundSprite.setScale(a, b);
	GoBackButtonRect.setSize(GoBackButtonSize);
	GoBackButtonRect.setFillColor(sf::Color::Transparent);
	GoBackButtonRect.setOutlineColor(sf::Color::White);
	GoBackButtonRect.setOutlineThickness(3);
	sf::Vector2f buttonPosition(windowSize.x / 2.0f, windowSize.y - m_buttonSize.y - 10);
	GoBackButtonRect.setOrigin(
		GoBackButtonSize.x / 2.0f, GoBackButtonSize.y / 2.0f);
	GoBackButtonRect.setPosition(buttonPosition);
}
void State_History::Activate() {}
void State_History::Deactivate() {}