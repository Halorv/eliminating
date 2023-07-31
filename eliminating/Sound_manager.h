#include <SFML\Audio.hpp>

using namespace std;
using namespace sf;

class Sound_manager {
public:
	Sound_manager();
	SoundBuffer swap_buffer;
	Sound swap_sound;

	SoundBuffer remove_Buffer;
	Sound remove_sound;

	SoundBuffer hammer_buffer;
	Sound hammer_sound;
};