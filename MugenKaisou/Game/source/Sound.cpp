#include "AppFrame.h"
#include "Sound.h"

// サウンド（BGM・SE）
Sound::Sound() {
	_handle = -1;
}

Sound::~Sound() {

}

void Sound::Load(int num) {
	_handle = LoadSoundMem(("res/sound/BGM/" + std::to_string(num) + ".mp3").c_str());
}

void Sound::Play(int type) {
	PlaySoundMem(_handle, type);
}

void Sound::Stop() {
	StopSoundMem(_handle);
}

void Sound::Delete() {
	DeleteSoundMem(_handle);
}