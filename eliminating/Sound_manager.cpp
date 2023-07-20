#include "Sound_manager.h"

Sound_manager::Sound_manager() {
	swap_buffer.loadFromFile("Sounds/Drop.wav"); // 交换（不能消除）
	remove_Buffer.loadFromFile("Sounds/LYNC_presence.wav"); // 消除
	remove_sound.setBuffer(remove_Buffer);
	swap_sound.setBuffer(swap_buffer);
}