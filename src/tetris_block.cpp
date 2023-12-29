#include "tetris_block.hpp"

#include "constants.hpp"

namespace Tetris {

TetrisBlock::TetrisBlock() : empty(true) {
  block.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
  block.setFillColor(EMPTY_COLOR);
}

TetrisBlock::TetrisBlock(sf::Color color) : empty(false) {
  block.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
  block.setFillColor(color);
}

TetrisBlock::TetrisBlock(sf::Color color, sf::Vector2f size) : empty(false) {
  block.setSize(sf::Vector2f(size.x * BLOCK_SIZE, size.y * BLOCK_SIZE));
  block.setFillColor(color);
}

TetrisBlock::~TetrisBlock() {}

void TetrisBlock::draw(sf::RenderTarget& target,
                       sf::RenderStates states) const {
  target.draw(block, states);
}

const sf::Vector2i TetrisBlock::getPosition() const {
  return sf::Vector2i(block.getPosition().x, block.getPosition().y);
}

const sf::Vector2i TetrisBlock::getGridPosition() const {
  return sf::Vector2i(block.getPosition().x / BLOCK_SIZE,
					  block.getPosition().y / BLOCK_SIZE);
}

void TetrisBlock::setGridPosition(sf::Vector2i gridPosition) {
  block.setPosition(
      sf::Vector2f(gridPosition.x * BLOCK_SIZE, gridPosition.y * BLOCK_SIZE));
}

void TetrisBlock::move(sf::Vector2i offset) {
  block.move(sf::Vector2f(offset.x * BLOCK_SIZE, offset.y * BLOCK_SIZE));
}

bool TetrisBlock::isEmpty() const { return empty; }

}  // namespace Tetris