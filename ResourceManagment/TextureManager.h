#pragma once
#include <unordered_map>
#include "../Utility.cpp"
#include <SFML/Graphics.hpp>

class TextureManager {
private:
	std::unordered_map<std::string, sf::Texture*> textrues;

public:
	TextureManager() {}
	void Load() {
		add("State_GameEnemy", Utils::GetWorkingDirectory() + "Game\\Paint\\enemy.png");
		add("State_GamePlayer", Utils::GetWorkingDirectory() + "Game\\Paint\\mario.png");
		add("BackgroundStarsSky", Utils::GetWorkingDirectory() + "Game\\Paint\\stars_sky.jpg");
		add("BackgroundForest", Utils::GetWorkingDirectory() + "Game\\Paint\\forest.png");
		add("EndCredits", Utils::GetWorkingDirectory() + "Game\\Paint\\end credits.jpeg");
		add("MainMenu", Utils::GetWorkingDirectory() + "Game\\Menu\\screen.png");
		add("Intro", Utils::GetWorkingDirectory() + "Game\\Paint\\bg1.png");
		add("IntroLogo", Utils::GetWorkingDirectory() + "Game\\Paint\\intro.png");
		add("MaincraftSunset", Utils::GetWorkingDirectory() + "Game\\Paint\\maincraft_sunset.png");
		add("MrBeastLogo", Utils::GetWorkingDirectory() + "Game\\Paint\\mrbeast.png");

	}
	 ~TextureManager() {
		for (auto& p : textrues) {
			delete p.second;
		}
	}
	sf::Texture* get_texture(const std::string& s) {
		auto it = textrues.find(s);
		return (it != textrues.end() ? (*it).second : nullptr);
	}
	void add(const std::string& name, const std::string& path) {
		sf::Texture* txtr = new sf::Texture;
		if (!(*txtr).loadFromFile(path))
			return;
		textrues[name] = txtr;
	}

	void remove(const std::string& name) {
		textrues.erase(name);
	}
	bool empty() const {
		return textrues.empty();
	}

};



