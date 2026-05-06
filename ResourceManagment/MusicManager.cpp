#include "MusicManager.h"
void MusicManager::Load() {
	add("WhatRemainsOfEdithFinch_Milton",
		Utils::GetWorkingDirectory() + "Game\\Sound\\WhatRemainsOfEdithFinch_Milton.ogg");
	add("SilentDeepCosmo", Utils::GetWorkingDirectory() + "Game\\Sound\\SilentDeepCosmo.ogg");
	add("NHK", Utils::GetWorkingDirectory() + "Game\\Sound\\nhk.ogg");
	add("Ladder", Utils::GetWorkingDirectory() + "Game\\Sound\\ladder.ogg");

}
MusicManager::~MusicManager() {
	for (auto& p : music_buffers) {
		delete p.second;
	}
}
Music* MusicManager::get_Music(const std::string& s) {
	auto it = music_buffers.find(s);
	return (it != music_buffers.end() ? (*it).second : nullptr);
}
void MusicManager::add(const std::string& name, const std::string& path) {
	sf::SoundBuffer* sbff = new sf::SoundBuffer;
	if (!(*sbff).loadFromFile(path))
		return;
	music_buffers[name] = new Music(name, sbff);
}

void MusicManager::remove(const std::string& name) {
	music_buffers.erase(name);
}
bool MusicManager::empty() const {
	return music_buffers.empty();
}