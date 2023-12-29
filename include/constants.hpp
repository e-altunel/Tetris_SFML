#ifndef INCLUDE_CONSTANTS
#define INCLUDE_CONSTANTS

#include <SFML/Graphics.hpp>
#include <iostream>

namespace Tetris {
	constexpr int BLOCK_SIZE = 40;
	constexpr int BOARD_WIDTH = 10;
	constexpr int BOARD_HEIGHT = 20;

	const sf::Color EMPTY_COLOR = sf::Color::Black;
	const sf::Color O_COLOR = sf::Color::Yellow;
	const sf::Color I_COLOR = sf::Color::Cyan;
	const sf::Color J_COLOR = sf::Color::Blue;
	const sf::Color L_COLOR = sf::Color(255, 165, 0);
	const sf::Color S_COLOR = sf::Color::Green;
	const sf::Color Z_COLOR = sf::Color::Red;
	const sf::Color T_COLOR = sf::Color::Magenta;

}

#endif /* INCLUDE_CONSTANTS */
