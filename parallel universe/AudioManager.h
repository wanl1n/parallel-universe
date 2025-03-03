#pragma once
#include <unordered_map>
#include <mutex>

#include "Screen.h"
#include "SFML/Audio.hpp"

class AudioManager
{
public:
	typedef std::string String;
	typedef std::vector<sf::Sound*> AudioPack;
	typedef std::unordered_map<String, AudioPack> AudioPackList;
	enum MeowNotes { asharp0 = 0, asharp1, asharp2, a0, a1, a2,
					b0, b1, b2,
					csharp1, csharp2, c1, c2, c3,
					dsharp1, dsharp2, d1, d2,
					e1, e2,
					fsharp1, fsharp2, f1, f2,
					gsharp1, gsharp2, g1, g2 };

	static AudioManager* getInstance();
	void loadAudioList(std::string objName, std::string audioName, bool isSFX); // audioName is the name of the folder in which all the audio files are located.
	void instantiateAsSound(String path, String assetName, bool isSFX);
	sf::Sound* getFromAudioPack(const String assetName, int clipIndex);

	void playBGM(Screen::ScreenName screenName);
	void playSFX(String assetName, int clipIndex);

	bool isPlayingSFX();
	bool isPlayingBGM();

private:
	AudioManager();
	AudioManager(AudioManager const&) {};             // copy constructor is private
	AudioManager& operator=(AudioManager const&) {};  // assignment operator is private
	static AudioManager* sharedInstance;

	AudioPackList audioPackList;
	AudioPack bgmList;
	AudioPack sfxList;

	const std::string AUDIO_PATH = "Media/Audio/";
	sf::Sound* sfxToPlay;
	sf::Music* bgmToPlay;
};
