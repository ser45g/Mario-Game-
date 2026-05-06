#include "State_Paused.h"
#include "StateManager.h"

State_Paused::State_Paused(StateManager* l_stateManager)
	: BaseState(l_stateManager){}

State_Paused::~State_Paused(){}

void State_Paused::OnCreate(){
	SetTransparent(true); // Set our transparency flag.
	m_font.loadFromFile(Utils::GetWorkingDirectory() + "Game\\Fonts\\arial.ttf");
	m_text.setFont(m_font);
	m_text.setString(sf::String("PAUSED"));
	m_text.setCharacterSize(14);
	m_text.setStyle(sf::Text::Bold);

	sf::Vector2u windowSize = m_stateMgr->
		GetContext()->m_wind->GetRenderWindow()->getSize();

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
	m_rect.setSize(m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getDefaultView().getSize());
	m_rect.setPosition(0, 0);
	m_rect.setFillColor(sf::Color(0,0,0,150));
}

void State_Paused::OnDestroy(){
	m_elapsed = 0;
}

void State_Paused::Draw(){
	sf::RenderWindow* wind = m_stateMgr->
		GetContext()->m_wind->GetRenderWindow();
	wind->draw(m_rect);
	wind->draw(m_text);
}

void State_Paused::Unpause(){
	if (ChangeTime >= ChangeTimeThreshold) {

		m_stateMgr->SwitchTo(StateType::Game);
		ChangeTime = 0;
	}
}

void State_Paused::Activate(){}
void State_Paused::Deactivate(){}
void State_Paused::Update(const float l_time){
	ChangeTime += l_time;
}