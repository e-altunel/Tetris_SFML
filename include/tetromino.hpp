#ifndef INCLUDE_TETROMINO
#define INCLUDE_TETROMINO

#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>

#include "tetris_block.hpp"

namespace Tetris {

class Tetromino : public sf::Drawable {
 public:
  enum class TetrominoType { I, J, L, O, S, T, Z };

  Tetromino(sf::Vector2i position);
  Tetromino(sf::Vector2i position, TetrominoType type);
  ~Tetromino();

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  void moveLeft();
  void moveRight();
  void moveDown();
  void rotate();

  const std::vector<std::vector<TetrisBlock>>& getBlocks() const;

  TetrominoType getType() const;
  sf::Vector2i getGridPosition() const;
  sf::Vector2i getSize() const;

  bool isFilled(sf::Vector2i pos) const;

 private:
  sf::Vector2i gridPosition;
  sf::Vector2i size;
  TetrominoType type;
  std::vector<std::vector<TetrisBlock>> blocks;

  void initBlocks();
  void move(sf::Vector2i offset);
};

}  // namespace Tetris

#endif /* INCLUDE_TETROMINO */
