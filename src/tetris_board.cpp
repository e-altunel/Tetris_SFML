#include "tetris_board.hpp"

#include "constants.hpp"

namespace Tetris {

TetrisBoard::TetrisBoard()
    : window(sf::VideoMode(BOARD_WIDTH * BLOCK_SIZE, BOARD_HEIGHT * BLOCK_SIZE),
             "Tetris") {
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      visualBoard[i][j].setGridPosition(sf::Vector2i(j, i));
      logicalBoard[i][j] = false;
    }
  }

  currentTetromino = Tetromino(sf::Vector2i(0, 0), Tetromino::TetrominoType::L);
}

TetrisBoard::~TetrisBoard() {}

void TetrisBoard::loop() {
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) window.close();
        if (currentTetromino.has_value()) {
          if (event.key.code == sf::Keyboard::A) currentTetromino->moveLeft();
          if (event.key.code == sf::Keyboard::D) currentTetromino->moveRight();
          if (event.key.code == sf::Keyboard::S) currentTetromino->moveDown();
        }
        if (event.key.code == sf::Keyboard::Space) update();
      }
    }

    window.clear();
    draw();
    if (currentTetromino.has_value()) window.draw(*currentTetromino);
    window.display();
  }
}

void TetrisBoard::draw() const {
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      window.draw(visualBoard[i][j]);
    }
  }
}

void TetrisBoard::update() {
  if (currentTetromino.has_value()) {
    if (isCollided()) {
      placeTetromino();
      currentTetromino = Tetromino(sf::Vector2i(0, 0));
    } else {
      currentTetromino->moveDown();
    }
  } else
    currentTetromino = Tetromino(sf::Vector2i(0, 0));
}

void TetrisBoard::placeTetromino() {
  if (!currentTetromino.has_value()) return;
  for (auto& row : currentTetromino->getBlocks()) {
    for (auto& block : row) {
      if (block.isEmpty()) continue;
      auto position = block.getGridPosition();
      logicalBoard[position.y][position.x] = true;
      visualBoard[position.y][position.x] = block;
    }
  }
  currentTetromino.reset();
}

bool TetrisBoard::isCollided() const {
  if (!currentTetromino.has_value()) return false;
  sf::Vector2i gridPosition = currentTetromino->getGridPosition();
  sf::Vector2i size = currentTetromino->getSize();
  for (int i = 0; i < size.y; i++) {
    for (int j = 0; j < size.x; j++) {
      if (currentTetromino->isFilled(sf::Vector2i(j, i))) {
        if (gridPosition.y + i + 1 >= BOARD_HEIGHT) return true;
        if (logicalBoard[gridPosition.y + i + 1][gridPosition.x + j])
          return true;
      }
    }
  }
  return false;
}

}  // namespace Tetris