#pragma once
#include "Window.h"
#include "ResourceManagment/LevelManager.h"

class Map;
struct SharedContext {
	SharedContext() :
		m_wind(nullptr),
		m_levelManager(nullptr){}

	Window* m_wind;
	LevelManager* m_levelManager;
};