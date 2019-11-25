#pragma once
#include "image_generator.h"
#include "drawable.h"
#include "tile.h"
#include <vector>
#include <memory>
#include "rectangle.h"
#include "image.h"
#include "tile_set.h"
#include "render_bounds.h"

namespace albinjohansson::wanderer {

// TODO Tiled map loading
//  - Layers
//  - Animated tiles

using TileMatrix = std::vector<std::vector<int>>;

class TileMap;

using TileMap_uptr = std::unique_ptr<TileMap>;
using TileMap_sptr = std::shared_ptr<TileMap>;
using TileMap_wptr = std::weak_ptr<TileMap>;

/**
 * The TileMap class represents a map of tiles, used to build the game world.
 *
 * @since 0.1.0
 */
class TileMap final : public IDrawable {
 private:
  std::unique_ptr<TileMatrix> tiles = nullptr;
  TileSet tileSet;
  int nRows;
  int nCols;

  [[nodiscard]] RenderBounds CalculateRenderBounds(const Rectangle& bounds) const noexcept;

 public:
  /**
   * @param nRows the number of rows in the tile map.
   * @param nCols the number of columns in the tile map.
   * @since 0.1.0
   */
  TileMap(ImageGenerator& imageGenerator, int nRows, int nCols);

  ~TileMap() override;

  static TileMap_uptr Create(ImageGenerator& imageGenerator,
                             int nRows,
                             int nCols);

  void Draw(Renderer& renderer, const Viewport& viewport) const noexcept override;

  /**
   * Sets the tile at the specified position.
   *
   * @param row the row index of the position that will be set.
   * @param col the column index of the position that will be set.
   * @param id the tile ID that will be set..
   * @throws std::out_of_range if the specified position is out-of-bounds.
   * @since 0.1.0
   */
  void SetTile(int row, int col, int id);

  /**
   * Returns the number of rows in the tile map.
   *
   * @return the number of rows in the tile map.
   * @since 0.1.0
   */
  [[nodiscard]] inline int GetRows() const noexcept { return nRows; }

  /**
   * Returns the number of columns in the tile map.
   *
   * @return the number of columns in the tile map.
   * @since 0.1.0
   */
  [[nodiscard]] inline int GetCols() const noexcept { return nCols; }

  [[nodiscard]] inline int GetWidth() const noexcept {
    return nCols * static_cast<int>(ITile::SIZE);
  }

  [[nodiscard]] inline int GetHeight() const noexcept {
    return nRows * static_cast<int>(ITile::SIZE);
  }

};

}