#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "../Utility.cpp"
#include "MusicManager.h"
#include "../Map.h"
#include "TextureManager.h"

class Level {
private:
	sf::Sprite m_background;
	sf::Texture* m_texture;
	Music* m_music;
	Map* m_map;
	bool m_done = false;
	bool MusicOn = true;
public:
	
	Level(Music* m_music, Map* m_map, sf::Texture* txt,bool done) :m_music(m_music),
		m_map(m_map),m_texture(txt),m_done(done) {
		if(txt!=nullptr)
			m_background.setTexture(*txt);
	}
	Level(Music* m_music, Map* m_map, sf::Texture* txt) :Level(m_music,m_map,txt,false){}
	Level() :Level(nullptr, nullptr,nullptr) {}

	~Level() {
		delete m_map;
	}
	Map* get_map() { return m_map; }
	sf::Sprite* get_sprite() { return &m_background; }
	sf::Texture* get_texture() { return m_texture; }
	Music* get_music() { return m_music; }
	bool& IsDone() { return m_done; }
	bool IsMusicOn()const { return MusicOn; }

	void set_map(Map* map) { m_map = map; }
	void set_background(sf::Sprite* background) { m_background= *background; }
	void set_music(Music* music) { m_music= music; }
	void setMusicOn(bool a) {
		MusicOn = a; }
};
class LevelManager {
private:
	std::vector< Level*> level_storage;
	MusicManager* m_musicManager;
	TextureManager* m_textureManager;
	int current_level = 0;
	
public:
	LevelManager(MusicManager* m_musicManager,
	TextureManager* m_textureManager):m_musicManager(m_musicManager), m_textureManager(m_textureManager) {}
	void Load();
	~LevelManager();
	int amountLevels()const;

	void Reset();
	void Continue();
	Level* get_Level(int index);
	bool nextLevel();
	bool IsLastLevel() const;
	Level* get_currentLevel();
	int get_current_level()const;

	void set_current_level(int a);

	MusicManager* get_musicManager();

	TextureManager* get_textureManager();

	void add(const std::string& map_path, Music* music, sf::Texture* texture, bool done = false) {
		Map* temp_map = new Map(map_path);
		level_storage.push_back(new Level(music, temp_map, texture, done));
	}

	bool empty() const;

};