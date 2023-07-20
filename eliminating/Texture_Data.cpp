#include <SFML\Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "Texture_Data.h"

  
Texture_Data::Texture_Data() {
	effectt.loadFromFile("images/Effects/effect.png"); // 选中某块
	effec.setTexture(effectt);

	rectangle.setSize(Vector2f(960, 437)); // 设置背景
	background.loadFromFile("images/Background/Untitled-1.png");
	rectangle.setTexture(&background);

	font.loadFromFile("Fonts/MAGNETOB.TTF"); // 分数字体设置
	text_score.setFont(font);
	text_score.setCharacterSize(30);
	text_score.setColor(sf::Color::Black);
	text_score.setPosition(545, 70);
}