#include "tile.h"

namespace wanderer::core {

Tile::Tile(int row, int col, int id) : row(row), col(col), id(id) {}

void Tile::Tick(float delta) {
  /* do nothing */
}

void Tile::Draw(visuals::Renderer& renderer, const Viewport& viewport) const noexcept {
  auto x = viewport.GetTranslatedX(static_cast<float>(GetCol() * SIZE));
  auto y = viewport.GetTranslatedY(static_cast<float>(GetRow() * SIZE));

  renderer.SetColor(0x72, 0x9E, 0x74);
  renderer.RenderFillRect(x, y, SIZE, SIZE);
  renderer.SetColor(0, 0, 0);
  renderer.RenderRect(x, y, SIZE, SIZE);
}

Rectangle Tile::GetHitbox() const noexcept {
  return Rectangle(GetX(), GetY(), SIZE, SIZE);
}

}