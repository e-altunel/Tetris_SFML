#ifndef INCLUDE_TETRIS_BOARD
#define INCLUDE_TETRIS_BOARD

#include <SFML/Graphics.hpp>
#include <array>
#include <optional>

#include "constants.hpp"
#include "tetris_block.hpp"
#include "tetromino.hpp"

namespace Tetris {

class TetrisBoard {
 public:
  TetrisBoard();
  ~TetrisBoard();

  void loop();
  void draw() const;
  bool isFilledSafe(sf::Vector2i gridPosition) const;

 private:
  bool isGame;
  int score;
  bool lazyUpdate;
  mutable sf::RenderWindow window;
  sf::RectangleShape background;
  std::optional<Tetromino> currentTetromino;
  std::optional<Tetromino> nextTetromino;
  std::array<std::array<TetrisBlock, BOARD_WIDTH>, BOARD_HEIGHT> visualBoard;
  std::array<std::array<bool, BOARD_WIDTH>, BOARD_HEIGHT> logicalBoard;

  void update();
  void placeTetromino();
  bool isCollided() const;
};

}  // namespace Tetris

#endif /* INCLUDE_TETRIS_BOARD */
