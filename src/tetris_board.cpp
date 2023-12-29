#include "tetris_board.hpp"

#include "constants.hpp"

namespace Tetris {

TetrisBoard::TetrisBoard()
    : isGame(true),
      score(0),
      lazyUpdate(true),
      window(sf::VideoMode((BOARD_WIDTH + MAX_TETROMINO_SIZE) * BLOCK_SIZE +
                               2 * TABLE_BORDER,
                           BOARD_HEIGHT * BLOCK_SIZE),
             "Tetris"),
      background(static_cast<sf::Vector2f>(window.getSize())) {
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      visualBoard[i][j].setGridPosition(sf::Vector2i(j, i));
      logicalBoard[i][j] = false;
    }
  }

  currentTetromino = Tetromino(sf::Vector2i(BOARD_WIDTH / 2, 0));
  nextTetromino = Tetromino(sf::Vector2i(BOARD_WIDTH / 2, 0));
  background.setFillColor(BACKGROUND_COLOR);
}

TetrisBoard::~TetrisBoard() {}

void TetrisBoard::loop() {
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) window.close();
        else if (currentTetromino.has_value()) {
          if (event.key.code == sf::Keyboard::A)
            lazyUpdate = currentTetromino->moveLeft(*this);
          else if (event.key.code == sf::Keyboard::D)
            lazyUpdate = currentTetromino->moveRight(*this);
          else if (event.key.code == sf::Keyboard::S)
            lazyUpdate = currentTetromino->moveDown(*this);
          else if (event.key.code == sf::Keyboard::Q)
            lazyUpdate = currentTetromino->rotateLeft(*this);
          else if (event.key.code == sf::Keyboard::E)
            lazyUpdate = currentTetromino->rotateRight(*this);
        }
        if (event.key.code == sf::Keyboard::Space) update();
      }
    }

    if (lazyUpdate) {
      lazyUpdate = false;
      window.clear();
      window.draw(background);
      if (nextTetromino.has_value())
        nextTetromino->drawRelative(
            window, sf::RenderStates::Default,
            sf::Vector2i(BOARD_WIDTH * BLOCK_SIZE + TABLE_BORDER +
                             (MAX_TETROMINO_SIZE - nextTetromino->getSize().x) /
                                 2.0 * BLOCK_SIZE,
                         10));
      draw();
      if (currentTetromino.has_value()) window.draw(*currentTetromino);
      window.display();
      std::cout << "Score: " << score << std::endl;
    }
  }
}

void TetrisBoard::draw() const {
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      window.draw(visualBoard[i][j]);
    }
  }
}

bool TetrisBoard::isFilledSafe(sf::Vector2i gridPosition) const {
  if (gridPosition.x < 0 || gridPosition.x >= BOARD_WIDTH) return true;
  if (gridPosition.y < 0 || gridPosition.y >= BOARD_HEIGHT) return true;
  return logicalBoard[gridPosition.y][gridPosition.x];
}

void TetrisBoard::update() {
  if (!isGame) return;
  if (currentTetromino.has_value()) {
    if (!(lazyUpdate = currentTetromino->moveDown(*this))) {
      placeTetromino();
      currentTetromino.reset();
    }
  } else {
    if (nextTetromino->isCollided(*this)) {
      std::cout << "Game Over!" << std::endl;
      std::cout << "Score " << score << std::endl;
      isGame = false;
    } else {
      lazyUpdate = true;
      currentTetromino = nextTetromino;
      nextTetromino = Tetromino(sf::Vector2i(BOARD_WIDTH / 2, 0));
    }
  }
}

void TetrisBoard::placeTetromino() {
  if (!currentTetromino.has_value()) return;
  score += currentTetromino->getScore();
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