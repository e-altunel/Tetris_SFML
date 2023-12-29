#ifndef INCLUDE_TETROMINO
#define INCLUDE_TETROMINO

#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>

#include "tetris_block.hpp"

namespace Tetris {
class TetrisBoard;

class Tetromino : public sf::Drawable {
 public:
  enum class TetrominoType { I, J, L, O, S, T, Z };

  Tetromino(sf::Vector2i position);
  Tetromino(sf::Vector2i position, TetrominoType type);
  ~Tetromino();

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  void drawRelative(sf::RenderTarget& target, sf::RenderStates states,
                    sf::Vector2i position) const;

  bool moveLeft(const TetrisBoard& board);
  bool moveRight(const TetrisBoard& board);
  bool moveDown(const TetrisBoard& board);

  bool rotateLeft(const TetrisBoard& board);
  bool rotateRight(const TetrisBoard& board);

  const std::vector<std::vector<TetrisBlock>>& getBlocks() const;

  TetrominoType getType() const;
  sf::Vector2i getGridPosition() const;
  sf::Vector2i getSize() const;

  bool isFilled(sf::Vector2i pos) const;
  bool isCollided(const TetrisBoard& board) const;
  int getScore() const;

 private:
  sf::Vector2i gridPosition;
  sf::Vector2i size;
  TetrominoType type;
  std::vector<std::vector<TetrisBlock>> blocks;

  void initBlocks();
  bool move(const TetrisBoard& board, sf::Vector2i gridOffset);
  bool isCollided(const TetrisBoard& board, sf::Vector2i gridOffset) const;
  void resetBlocksGridPosition();
  void resetBlocksPosition(sf::Vector2i position);
  void resetVectorSize();
};

}  // namespace Tetris

#endif /* INCLUDE_TETROMINO */
