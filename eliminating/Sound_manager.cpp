#include "Sound_manager.h"

Sound_manager::Sound_manager() {
	swap_buffer.loadFromFile("Sounds/Drop.wav"); // ����������������
	remove_Buffer.loadFromFile("Sounds/LYNC_presence.wav"); // ����
	hammer_buffer.loadFromFile("Sounds/hammer1.mp3");

	remove_sound.setBuffer(remove_Buffer);
	swap_sound.setBuffer(swap_buffer);
	hammer_sound.setBuffer(hammer_buffer);
}