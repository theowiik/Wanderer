#pragma once
#include "tile.h"
#include "renderer.h"
#include "render_bounds.h"
#include "tile_set.h"
#include "viewport.h"
#include <vector>
#include <memory>

namespace albinjohansson::wanderer {

class TileMapLayer final {
 private:
  const int nRows;
  const int nCols;
  std::vector<TileID> tiles;

 public:
  TileMapLayer(int nRows, int nCols, std::vector<TileID> tiles);

  ~TileMapLayer();

  void Update(const TileMapBounds& bounds, TileSet& tileSet);

  void Draw(Renderer& renderer,
            const TileMapBounds& bounds,
            const Viewport& viewport,
            const TileSet& tileSet) const;

  [[nodiscard]] TileID GetTileId(int row, int col) const;

  [[nodiscard]] const std::vector<TileID>& GetTiles() const noexcept {
    return tiles;
  }

  [[nodiscard]] int GetIndex(int row, int col) const noexcept {
    return row * nCols + col;
  }

};

using TileMapLayer_uptr = std::unique_ptr<TileMapLayer>;
using TileMapLayer_sptr = std::shared_ptr<TileMapLayer>;
using TileMapLayer_wptr = std::weak_ptr<TileMapLayer>;

}
