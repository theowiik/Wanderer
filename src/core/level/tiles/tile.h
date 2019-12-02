#pragma once
#include "game_object.h"
#include "drawable.h"
#include "image.h"
#include "animation.h"
#include "tile_animation.h"
#include "tile_id.h"
#include <memory>

namespace albinjohansson::wanderer {

struct TilePos {
  int row = 0;
  int col = 0;
};

struct TileProperties { // TODO reorder fields
  Image_sptr sheet = nullptr;
  TileID id = 0;
  TileAnimation animation = TileAnimation(1);
  Rectangle hitbox = {0, 0, 1, 1};
  bool blocked = false;
  bool animated = false;
};

class Tile {
 private:
  TileProperties properties;

 public:
  static constexpr float SIZE = 64;
  static constexpr TileID EMPTY = 0;

  explicit Tile(TileProperties properties);

  ~Tile();

  void Draw(TilePos pos, Renderer& renderer, const Viewport& viewport, const Rectangle& src) const;

  void Tick();

  [[nodiscard]] Image& GetImage() const noexcept { return *properties.sheet; }

  /**
   * Returns the type ID the tile.
   *
   * @return the type ID the tile.
   * @since 0.1.0
   */
  [[nodiscard]] TileID GetId() const noexcept { return properties.id; }

  /**
   * Indicates whether or not the tile is blocked.
   *
   * @return true if the tile is blocked; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool IsBlocked() const noexcept { return properties.blocked; }

  [[nodiscard]] bool IsAnimated() const noexcept { return properties.animated; }

  [[nodiscard]] TileID GetFrameId() const {
    return properties.animated ? properties.animation.GetFrame().frameId : properties.id;
  }
};

using ITile_uptr = std::unique_ptr<Tile>;
using ITile_sptr = std::shared_ptr<Tile>;
using ITile_wptr = std::weak_ptr<Tile>;

}
