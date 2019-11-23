#pragma once
#include "abstract_tile.h"

namespace albinjohansson::wanderer {

/**
 * The GrassTile class is a subclass of AbstractTile that represents a tile of grass.
 *
 * @see AbstractTile
 * @since 0.1.0
 */
class GrassTile final : public AbstractTile {
 public:
  GrassTile(int row, int col, int id);

  ~GrassTile() override;

  void Draw(Renderer& renderer, const Viewport& viewport) const noexcept override;

  [[nodiscard]] inline bool IsBlocked() const noexcept override { return false; }
};

}
