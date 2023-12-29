#include "tetromino.hpp"

#include <random>

#include "constants.hpp"

namespace Tetris {

Tetromino::Tetromino(sf::Vector2i gridPosition) : gridPosition(gridPosition) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 6);

  type = static_cast<TetrominoType>(dis(gen));
  initBlocks();
}

Tetromino::Tetromino(sf::Vector2i gridPosition, TetrominoType type)
    : gridPosition(gridPosition), type(type) {
  initBlocks();
}

Tetromino::~Tetromino() {}

void Tetromino::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (const auto& row : blocks) {
    for (const auto& block : row) {
      if (!block.isEmpty()) target.draw(block, states);
    }
  }
}

void Tetromino::moveLeft() { move(sf::Vector2i(-1, 0)); }

void Tetromino::moveRight() { move(sf::Vector2i(1, 0)); }

void Tetromino::moveDown() { move(sf::Vector2i(0, 1)); }

void Tetromino::rotate() {
  size = sf::Vector2i(size.y, size.x);
  std::vector<std::vector<TetrisBlock>> rotatedBlocks;
  rotatedBlocks.resize(blocks[0].size());
  for (auto& row : rotatedBlocks) {
    row.resize(blocks.size());
  }

  for (size_t i = 0; i < blocks.size(); i++) {
    for (size_t j = 0; j < blocks[i].size(); j++) {
      rotatedBlocks[j][i] = blocks[i][j];
    }
  }

  blocks = rotatedBlocks;
}

const std::vector<std::vector<TetrisBlock>>& Tetromino::getBlocks() const {
  return blocks;
}

bool Tetromino::isFilled(sf::Vector2i gridRelPosition) const {
  if (gridRelPosition.x < 0 || gridRelPosition.x >= size.x ||
      gridRelPosition.y < 0 || gridRelPosition.y >= size.y)
    return false;
  return !blocks[gridRelPosition.y][gridRelPosition.x].isEmpty();
}

Tetromino::TetrominoType Tetromino::getType() const { return type; }

sf::Vector2i Tetromino::getGridPosition() const { return gridPosition; }

sf::Vector2i Tetromino::getSize() const { return size; }

void Tetromino::initBlocks() {
  if (type == Tetromino::TetrominoType::I) {
    size = sf::Vector2i(1, 4);
    blocks.resize(4);
    for (auto& row : blocks) {
      row.resize(1);
    }
    blocks[0][0] = TetrisBlock(I_COLOR);
    blocks[1][0] = TetrisBlock(I_COLOR);
    blocks[2][0] = TetrisBlock(I_COLOR);
    blocks[3][0] = TetrisBlock(I_COLOR);
  } else if (type == Tetromino::TetrominoType::J) {
    size = sf::Vector2i(2, 3);
    blocks.resize(3);
    for (auto& row : blocks) {
      row.resize(2);
    }
    blocks[0][1] = TetrisBlock(J_COLOR);
    blocks[1][1] = TetrisBlock(J_COLOR);
    blocks[2][1] = TetrisBlock(J_COLOR);
    blocks[2][0] = TetrisBlock(J_COLOR);
  } else if (type == Tetromino::TetrominoType::L) {
    size = sf::Vector2i(2, 3);
    blocks.resize(3);
    for (auto& row : blocks) {
      row.resize(2);
    }
    blocks[0][0] = TetrisBlock(L_COLOR);
    blocks[1][0] = TetrisBlock(L_COLOR);
    blocks[2][0] = TetrisBlock(L_COLOR);
    blocks[2][1] = TetrisBlock(L_COLOR);
  } else if (type == Tetromino::TetrominoType::O) {
    size = sf::Vector2i(2, 2);
    blocks.resize(2);
    for (auto& row : blocks) {
      row.resize(2);
    }
    blocks[0][0] = TetrisBlock(O_COLOR);
    blocks[0][1] = TetrisBlock(O_COLOR);
    blocks[1][0] = TetrisBlock(O_COLOR);
    blocks[1][1] = TetrisBlock(O_COLOR);
  } else if (type == Tetromino::TetrominoType::S) {
    size = sf::Vector2i(2, 3);
    blocks.resize(3);
    for (auto& row : blocks) {
      row.resize(2);
    }
    blocks[0][0] = TetrisBlock(S_COLOR);
    blocks[1][0] = TetrisBlock(S_COLOR);
    blocks[1][1] = TetrisBlock(S_COLOR);
    blocks[2][1] = TetrisBlock(S_COLOR);
  } else if (type == Tetromino::TetrominoType::T) {
    size = sf::Vector2i(3, 2);
    blocks.resize(2);
    for (auto& row : blocks) {
      row.resize(3);
    }
    blocks[0][0] = TetrisBlock(T_COLOR);
    blocks[0][1] = TetrisBlock(T_COLOR);
    blocks[0][2] = TetrisBlock(T_COLOR);
    blocks[1][1] = TetrisBlock(T_COLOR);
  } else if (type == Tetromino::TetrominoType::Z) {
    size = sf::Vector2i(3, 2);
    blocks.resize(3);
    for (auto& row : blocks) {
      row.resize(2);
    }
    blocks[0][1] = TetrisBlock(Z_COLOR);
    blocks[1][0] = TetrisBlock(Z_COLOR);
    blocks[1][1] = TetrisBlock(Z_COLOR);
    blocks[2][0] = TetrisBlock(Z_COLOR);
  }

  for (size_t i = 0; i < blocks.size(); i++) {
    for (size_t j = 0; j < blocks[i].size(); j++) {
      blocks[i][j].setGridPosition(gridPosition + sf::Vector2i(j, i));
    }
  }
}

void Tetromino::move(sf::Vector2i offset) {
  if (gridPosition.x + offset.x < 0 ||
      gridPosition.x + size.x + offset.x > BOARD_WIDTH)
    return;
  if (gridPosition.y + offset.y < 0 ||
      gridPosition.y + size.y + offset.y > BOARD_HEIGHT)
    return;
  gridPosition += offset;
  for (auto& row : blocks) {
    for (auto& block : row) {
      block.move(offset);
    }
  }
}

}  // namespace Tetris