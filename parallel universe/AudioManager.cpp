#include <filesystem>
#include "AudioManager.h"

#include <iostream>

#include "StringUtils.h"

//a singleton class
AudioManager* AudioManager::sharedInstance = NULL;

AudioManager* AudioManager::getInstance() {
	if (sharedInstance == NULL) {
		//initialize
		sharedInstance = new AudioManager();
	}

	return sharedInstance;
}

void AudioManager::loadAudioList(std::string objName, std::string audioName, bool isSFX)
{
	for (const auto& entry : std::filesystem::directory_iterator(AUDIO_PATH + audioName)) {
		String path = entry.path().generic_string();
		String packName = objName + " " + audioName;
		this->instantiateAsSound(path, packName, isSFX);
	}
}

void AudioManager::instantiateAsSound(String path, String assetName, bool isSFX)
{
	sf::SoundBuffer* buffer = new sf::SoundBuffer(path);
	sf::Sound* sound = new sf::Sound(*buffer);
	this->audioPackList[assetName].push_back(sound);

	if (isSFX)
		sfxList.push_back(sound);
	else
		bgmList.push_back(sound);
}

sf::Sound* AudioManager::getFromAudioPack(const String assetName, int clipIndex)
{
	if (!this->audioPackList[assetName].empty()) {
		return this->audioPackList[assetName][clipIndex];
	}
	else {
		//std::cout << "[AudioManager] No sound found for " << assetName << std::endl;
		return NULL;
	}
}

void AudioManager::playBGM(Screen::ScreenName screenName)
{
	if (screenName == Screen::game)
		bgmToPlay = new sf::Music(AUDIO_PATH + "A Cruel Neko's Nyasis.mp3"); // Throws sf::Exception if an error occurs
	else
		bgmToPlay = new sf::Music(AUDIO_PATH + "Rhythm.mp3"); // Throws sf::Exception if an error occurs

	bgmToPlay->setVolume(0.5f);
	bgmToPlay->setLooping(true);
	bgmToPlay->play();
}

void AudioManager::playSFX(String assetName, int clipIndex)
{
	sfxToPlay = this->audioPackList[assetName][clipIndex];
	sfxToPlay->play();
}

bool AudioManager::isPlayingSFX()
{
	if (sfxToPlay == nullptr)
		return false;
	else
		return sfxToPlay->getStatus() == sf::SoundSource::Status::Playing;
}

bool AudioManager::isPlayingBGM()
{
	if (bgmToPlay == nullptr)
		return false;
	else
		return bgmToPlay->getStatus() == sf::SoundSource::Status::Playing;
}

AudioManager::AudioManager()
{
}
