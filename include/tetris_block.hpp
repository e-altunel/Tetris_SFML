#ifndef INCLUDE_TETRIS_BLOCK
#define INCLUDE_TETRIS_BLOCK

#include <SFML/Graphics.hpp>

namespace Tetris {

class TetrisBlock : public sf::Drawable {
 public:
  TetrisBlock();
  TetrisBlock(sf::Color color);
  TetrisBlock(sf::Color color, sf::Vector2f size);
  ~TetrisBlock();

  void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  const sf::Vector2i getPosition() const;
  const sf::Vector2i getGridPosition() const;
  void setGridPosition(sf::Vector2i gridPosition);
  void move(sf::Vector2i offset);

  bool isEmpty() const;

 private:
  sf::RectangleShape block;
  bool empty = true;
};
}  // namespace Tetris

#endif /* INCLUDE_TETRIS_BLOCK */
