#include "LevelManager.h"
void LevelManager::Load() {

	add(Utils::GetWorkingDirectory() + "Game\\Maps\\map1.txt",
		m_musicManager->get_Music("NHK"),
		m_textureManager->get_texture("BackgroundForest"));

	add(Utils::GetWorkingDirectory() + "Game\\Maps\\map2.txt",
		m_musicManager->get_Music("SilentDeepCosmo"),
		m_textureManager->get_texture("BackgroundStarsSky"));
	level_storage[1]->get_music()->get_sound()->setVolume(40);

	add(Utils::GetWorkingDirectory() + "Game\\Maps\\map3.txt",
		m_musicManager->get_Music("NHK"),
		m_textureManager->get_texture("EndCredits"));


	std::ifstream f(Utils::GetWorkingDirectory() + "Game\\Log\\levels_done.txt");
	if (!f.good()) {
		std::cout << "cant open " << Utils::GetWorkingDirectory() + "Game\\Log\\levels_done.txt\n";
	}
	std::vector<bool> IsDone;
	bool temp;
	while (!f.eof()) {
		f >> temp;
		IsDone.push_back(temp);
	}
	if (IsDone.size() < level_storage.size()) {
		IsDone.resize(level_storage.size(), false);
	}
	for (int i = 0; i < level_storage.size(); ++i) {
		level_storage[i]->IsDone() = IsDone[i];
	}
	f.close();
}
LevelManager::~LevelManager() {
	std::ofstream f(Utils::GetWorkingDirectory() + "Game\\Log\\levels_done.txt");
	if (!f.good()) {
		std::cout << "cant open " << Utils::GetWorkingDirectory() + "Game\\Log\\levels_done.txt\n";
	}

	for (auto p : level_storage) {
		f << p->IsDone() << '\n';
		delete p;
	}
	f.close();
}
int LevelManager::amountLevels() const { return level_storage.size(); }

void LevelManager::Reset() {
	for (auto p : level_storage) {
		p->IsDone() = false;
	}
}
void LevelManager::Continue() {
	bool found = false;
	int i = 0;
	for (; i < level_storage.size(); ++i) {
		if (level_storage[i]->IsDone() == false) {
			found = true;
			current_level = i;
			break;
		}
	}
	if (!found) {
		current_level = i - 1;
	}
}
Level* LevelManager::get_Level(int index) {
	return level_storage.at(index);
}
bool LevelManager::nextLevel() {
	//returns true if it went to the next level and false if it's the last available level
	if (IsLastLevel())
		return false;
	bool a = level_storage[current_level]->IsMusicOn();
	++current_level;
	level_storage[current_level]->setMusicOn(a);
	return true;
}
bool LevelManager::IsLastLevel() const {
	return current_level + 1 > level_storage.size() - 1;
}
Level* LevelManager::get_currentLevel() {
	return get_Level(current_level);
}
int LevelManager::get_current_level()const { return current_level; }

void LevelManager::set_current_level(int index) {
	if (index >(level_storage.size()))
		return ;
	
	bool a = level_storage[current_level]->IsMusicOn();
	current_level = index;
	level_storage[index]->setMusicOn(a);
}

MusicManager* LevelManager::get_musicManager() { return m_musicManager; }

TextureManager* LevelManager::get_textureManager() { return m_textureManager; }

bool LevelManager::empty() const {
	return level_storage.empty();
}