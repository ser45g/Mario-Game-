#pragma once
#include <unordered_map>
#include <SFML/Audio.hpp>
#include "../Utility.cpp"

class Music {
private:
	std::string name;
	sf::SoundBuffer* sbff;
	sf::Sound* sound;
public:

	Music(const std::string& name, sf::SoundBuffer* sbff,sf::Sound* sound):name(name),
		sbff(sbff),sound(sound){}
	Music(const std::string& name, sf::SoundBuffer* sbff) :Music(name, sbff, new sf::Sound) {
		sound->setBuffer(*sbff);
	}
	Music():Music("",nullptr,nullptr) {}

	~Music(){
		delete sbff;
		delete sound;
	}
	sf::SoundBuffer* get_buffer()const { return sbff; }
	sf::Sound* get_sound()const{return sound;}
	const std::string& get_name()const{return name;}
	
	void set_buffer(sf::SoundBuffer* _sbff) { sbff = _sbff;}
	void set_sound(sf::Sound* _sound) { sound = _sound; }
	void set_name(const std::string& _name) { name = _name;}


};
class MusicManager {
private:
	std::unordered_map<std::string, Music*> music_buffers;
	

public:
	MusicManager() {}
	void Load();
	~MusicManager();
	Music* get_Music(const std::string& s);
	void add(const std::string& name, const std::string& path);

	void remove(const std::string& name);
	bool empty() const;

};