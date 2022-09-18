#include <string>
#include <memory>
#include "SDL_mixer.h"
#include "Component.h"
#include "GameObject.h"

#ifndef SOUND_H
#define SOUND_H

// Classe "Sound"
// COMPONENT
class Sound : public Component {
	private:
		std::shared_ptr<Mix_Chunk> chunk;
		int channel;

	public:
		Sound(GameObject& associated);
		Sound(GameObject& associated, std::string file);
		~Sound();
		void Play(int times = 1);
		void Stop();
		void Open(std::string file);
		bool IsPlaying();
		bool IsOpen();
		void Update(float dt);
		void Render();
		bool Is(std::string type);
		void Volume(int volume);
};

#endif // SOUND_H
