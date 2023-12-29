#include "tetromino.hpp"

#include <random>

#include "constants.hpp"
#include "tetris_board.hpp"

namespace Tetris {

Tetromino::Tetromino(sf::Vector2i gridPosition) : gridPosition(gridPosition) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 6);

  type = static_cast<TetrominoType>(dis(gen));
  initBlocks();
  gridPosition.x -= size.x / 2;
  gridPosition.y -= size.y / 2;
  resetBlocksGridPosition();
}

Tetromino::Tetromino(sf::Vector2i gridPosition, TetrominoType type)
    : gridPosition(gridPosition), type(type) {
  initBlocks();
  gridPosition.x -= size.x / 2;
  gridPosition.y -= size.y / 2;
  resetBlocksGridPosition();
}

Tetromino::~Tetromino() {}

void Tetromino::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (const auto& row : blocks) {
    for (const auto& block : row) {
      if (!block.isEmpty()) target.draw(block, states);
    }
  }
}

void Tetromino::drawRelative(sf::RenderTarget& target, sf::RenderStates states,
                             sf::Vector2i position) const {
  Tetromino relativeTetromino(*this);
  relativeTetromino.resetBlocksPosition(position);
  target.draw(relativeTetromino, states);
}

bool Tetromino::moveLeft(const TetrisBoard& board) {
  return move(board, sf::Vector2i(-1, 0));
}

bool Tetromino::moveRight(const TetrisBoard& board) {
  return move(board, sf::Vector2i(1, 0));
}

bool Tetromino::moveDown(const TetrisBoard& board) {
  return move(board, sf::Vector2i(0, 1));
}

bool Tetromino::rotateLeft(const TetrisBoard& board) {
  sf::Vector2i rotatedSize = sf::Vector2i(size.y, size.x);
  sf::Vector2i rotatedGridPosition = gridPosition;
  rotatedGridPosition.x += (rotatedSize.y - rotatedSize.x) / 2;
  rotatedGridPosition.y += (rotatedSize.x - rotatedSize.y) / 2;
  Tetromino rotatedTetromino(rotatedGridPosition, type);
  rotatedTetromino.size = rotatedSize;
  rotatedTetromino.resetVectorSize();
  for (int i = 0; i < size.y; i++) {
    for (int j = 0; j < size.x; j++) {
      rotatedTetromino.blocks[j][i] = blocks[i][size.x - j - 1];
    }
  }
  rotatedTetromino.resetBlocksGridPosition();
  if (!rotatedTetromino.isCollided(board)) {
    *this = rotatedTetromino;
    return true;
  }
  return false;
}

bool Tetromino::rotateRight(const TetrisBoard& board) {
  sf::Vector2i rotatedSize = sf::Vector2i(size.y, size.x);
  sf::Vector2i rotatedGridPosition = gridPosition;
  rotatedGridPosition.x += (rotatedSize.y - rotatedSize.x) / 2;
  rotatedGridPosition.y += (rotatedSize.x - rotatedSize.y) / 2;
  Tetromino rotatedTetromino(rotatedGridPosition, type);
  rotatedTetromino.size = rotatedSize;
  rotatedTetromino.resetVectorSize();
  for (int i = 0; i < size.y; i++) {
    for (int j = 0; j < size.x; j++) {
      rotatedTetromino.blocks[j][i] = blocks[size.y - i - 1][j];
    }
  }
  rotatedTetromino.resetBlocksGridPosition();
  if (!rotatedTetromino.isCollided(board)) {
    *this = rotatedTetromino;
    return true;
  }
  return false;
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

bool Tetromino::isCollided(const TetrisBoard& board) const {
  return isCollided(board, sf::Vector2i(0, 0));
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
    size = sf::Vector2i(2, 3);
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

bool Tetromino::move(const TetrisBoard& board, sf::Vector2i gridOffset) {
  if (isCollided(board, gridOffset)) return false;
  if (gridPosition.x + gridOffset.x < 0 ||
      gridPosition.x + size.x + gridOffset.x > BOARD_WIDTH)
    return false;
  if (gridPosition.y + gridOffset.y < 0 ||
      gridPosition.y + size.y + gridOffset.y > BOARD_HEIGHT)
    return false;
  gridPosition += gridOffset;
  for (auto& row : blocks) {
    for (auto& block : row) {
      block.move(gridOffset);
    }
  }
  return true;
}

bool Tetromino::isCollided(const TetrisBoard& board,
                           sf::Vector2i gridOffset) const {
  for (int i = 0; i < size.y; i++) {
    for (int j = 0; j < size.x; j++) {
      if (isFilled(sf::Vector2i(j, i))) {
        if (board.isFilledSafe(sf::Vector2i(gridPosition.x + j + gridOffset.x,
                                            gridPosition.y + i + gridOffset.y)))
          return true;
      }
    }
  }
  return false;
}

void Tetromino::resetBlocksGridPosition() {
  for (size_t i = 0; i < blocks.size(); i++) {
    for (size_t j = 0; j < blocks[i].size(); j++) {
      blocks[i][j].setGridPosition(gridPosition + sf::Vector2i(j, i));
    }
  }
}

void Tetromino::resetBlocksPosition(sf::Vector2i position) {
  for (size_t i = 0; i < blocks.size(); i++) {
    for (size_t j = 0; j < blocks[i].size(); j++) {
      blocks[i][j].setPosition(position +
                               sf::Vector2i(j * BLOCK_SIZE, i * BLOCK_SIZE));
    }
  }
}

void Tetromino::resetVectorSize() {
  blocks.resize(size.y);
  for (auto& row : blocks) {
    row.resize(size.x);
  }
}

int Tetromino::getScore() const {
  if (type == Tetromino::TetrominoType::I) {
    return 40;
  } else if (type == Tetromino::TetrominoType::J) {
    return 30;
  } else if (type == Tetromino::TetrominoType::L) {
    return 30;
  } else if (type == Tetromino::TetrominoType::O) {
    return 20;
  } else if (type == Tetromino::TetrominoType::S) {
    return 30;
  } else if (type == Tetromino::TetrominoType::T) {
    return 30;
  } else if (type == Tetromino::TetrominoType::Z) {
    return 30;
  }
  return 0;
}

}  // namespace Tetris