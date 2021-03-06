#pragma once
#include "tiled_animation.h"
#include "tiled_object.h"
#include "tiled_tile.h"
#include "tiled_object.h"
#include <stdexcept>
#include <pugixml.hpp>
#include <string>
#include <unordered_map>

namespace albinjohansson::tiled {

class TiledTileSet final {
 private:
  pugi::xml_node tileSetNode;
  std::unordered_map<int, TiledTile> tiles;
  const int firstId;
  const int lastId;

  void init();

 public:
  /**
   * @param tileSetNode the root tile set node.
   * @param firstId the first valid tile id.
   * @param lastId the last valid tile id.
   * @since 0.1.0
   */
  TiledTileSet(pugi::xml_node tileSetNode, int firstId, int lastId);

  /**
   * @param tileSetNode the root tile set node.
   * @param firstId the first valid tile id.
   * @param lastId the last valid tile id.
   * @since 0.1.0
   */
  TiledTileSet(pugi::xml_node&& tileSetNode, int firstId, int lastId);

  ~TiledTileSet();

  /**
   * Returns the name of the tile set.
   *
   * @return the name of the tile set.
   * @since 0.1.0
   */
  [[nodiscard]]
  std::string get_name() const;

  /**
   * Returns the width of all tiles in the tile set.
   *
   * @return the width of all tiles in the tile set.
   * @since 0.1.0
   */
  [[nodiscard]]
  int get_tile_width() const;

  /**
   * Returns the height of all tiles in the tile set.
   *
   * @return the height of all tiles in the tile set.
   * @since 0.1.0
   */
  [[nodiscard]]
  int get_tile_height() const;

  /**
   * Returns the total amount of tiles in the tile set.
   *
   * @return the total amount of tiles in the tile set.
   * @since 0.1.0
   */
  [[nodiscard]]
  int get_tile_count() const;

  /**
   * Returns the amount of columns in the tile set.
   *
   * @return the amount of columns in the tile set.
   * @since 0.1.0
   */
  [[nodiscard]]
  int get_cols() const;

  /**
   * Returns the image source path for the image associated with the tile set.
   *
   * @return the image source path for the image associated with the tile set.
   * @since 0.1.0
   */
  [[nodiscard]]
  std::string get_image_source() const;

  [[nodiscard]]
  std::string get_image_name() const;

  /**
   * Returns the width of the image associated with the tile set.
   *
   * @return the width of the image associated with the tile set.
   * @since 0.1.0
   */
  [[nodiscard]]
  int get_image_width() const;

  /**
   * Returns the height of the image associated with the tile set.
   *
   * @return the height of the image associated with the tile set.
   * @since 0.1.0
   */
  [[nodiscard]]
  int get_image_height() const;

  /**
   * Returns the first valid tile ID in the tile set.
   *
   * @return the first valid tile ID in the tile set.
   * @since 0.1.0
   */
  [[nodiscard]]
  int get_first_tile_id() const noexcept { return firstId; }

  /**
   * Returns the last valid tile ID in the tile set.
   *
   * @return the last valid tile ID in the tile set.
   * @since 0.1.0
   */
  [[nodiscard]]
  int get_last_tile_id() const noexcept { return lastId; }

  [[nodiscard]]
  bool has_tile(int id) const noexcept;

  [[nodiscard]]
  const TiledTile& get_tile(int id) const;
};

}
