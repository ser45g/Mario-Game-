#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Utility.cpp"

Game::Game() : m_window("Mario", sf::Vector2u(25*32, 13*32)),
	m_stateManager(&m_context),
	m_levelManager(&m_musicManager,&m_textureManager) {
	m_clock.restart();
	m_context.m_wind = &m_window;
	m_context.m_levelManager = &m_levelManager;
	
	icon.loadFromFile(Utils::GetWorkingDirectory() + "Game\\Paint\\eye.png");
	m_window.GetRenderWindow()->setIcon(32,32,icon.getPixelsPtr());
	m_stateManager.SwitchTo(StateType::Loading);
	//m_stateManager.SwitchTo(StateType::LevelsOrContinue);
	srand(time(nullptr));
}
	
Game::~Game(){}

sf::Time Game::GetElapsed(){ return m_clock.getElapsedTime(); }
void Game::RestartClock(){ m_elapsed += m_clock.restart().asSeconds(); }
Window* Game::GetWindow(){ return &m_window; }

void Game::HandleInput(){
	sf::Event event;
	Window* window = m_stateManager.GetContext()->m_wind;
	sf::Vector2i window_pos=window->GetRenderWindow()->getPosition();
	while (window->GetRenderWindow()->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window->Close();
		}
		else if (event.type == sf::Event::LostFocus) {
			m_window.IsFocused() = false;
		}
		else if (event.type == sf::Event::GainedFocus) {

			m_window.IsFocused() = true;
		
		}else if (event.type == sf::Event::Resized ) {
			
			RestartClock();
			m_elapsed = 0;
		}
	}
	if (m_window.GetRenderWindow()->getPosition() != window_pos) {
		RestartClock();
		m_elapsed = 0;
	}
	m_stateManager.HandleInput(event);
}

void Game::Update(){

	if(m_elapsed > m_timestep ) {
		m_window.Update();
		m_stateManager.Update(m_elapsed);
		m_elapsed = 0;
	}
	
}

void Game::Render(){
	m_window.BeginDraw();
	m_stateManager.Draw();
	m_window.EndDraw();
}