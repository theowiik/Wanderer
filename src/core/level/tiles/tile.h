#pragma once
#include "game_object.h"
#include "tile_id.h"
#include "render_depth.h"
#include "tile_animation.h"
#include <memory>

namespace albinjohansson::wanderer {

class Image;
class Vector2;
class TileSet;
class Frame;

/**
 * The Tile class represents a type of tile. Note! The Tile class is designed to represent a type
 * of tile, and as such, only one instance is meant to be created for each type. For storage of a
 * tile map, all that is needed is a matrix of tile identifiers.
 *
 * @since 0.1.0
 */
class Tile final {
 private:
  std::shared_ptr<Image> sheet = nullptr;
  Rectangle hitbox; // TODO create Hitbox class which holds multiple rectangles

  TileAnimation animation;

  TileID id = Tile::EMPTY;
  int depth = RenderDepth::MIN;

  bool isBlocked = false;
  bool isAnimated = false;
  bool isObject = false;

 public:
  /**
   * The logical size (width and height) of all tiles.
   *
   * @since 0.1.0
   */
  static constexpr float SIZE = 64;

  /**
   * The tile ID of all empty tiles.
   *
   * @since 0.1.0
   */
  static constexpr TileID EMPTY = 0;

  Tile() noexcept;

  ~Tile() noexcept;

  /**
   * Renders the tile at a specific position.
   *
   * @param pos the position of the rendered tile.
   * @param renderer the renderer that will be used.
   * @param viewport the viewport that will be used.
   * @param tileSet the associated tile set.
   * @since 0.1.0
   */
  void Draw(const Vector2& pos,
            Renderer& renderer,
            const Viewport& viewport,
            const TileSet& tileSet) const;

  /**
   * Updates the state of the tile.
   *
   * @since 0.1.0
   */
  void Tick();

  /**
   * Sets the associated tile sheet image.
   *
   * @param sheet the associated tile sheet image.
   * @since 0.1.0
   */
  void SetSheet(std::shared_ptr<Image> sheet);

  /**
   * Sets whether or not the tile is blocked. By default, this property is set to false.
   *
   * @param isBlocked true if the tile is blocked; false otherwise.
   * @since 0.1.0
   */
  void SetBlocked(bool isBlocked) noexcept;

  /**
   * Sets whether or not the tile is animated. By default, this property is set to false.
   *
   * @param isAnimated true if the tile is animated; false otherwise.
   * @since 0.1.0
   */
  void SetAnimated(bool isAnimated) noexcept;

  /**
   * Sets whether or not the tile is an object tile. By default, this property is set to false.
   *
   * @param isObject true if the tile should be regarded as an object tile; false otherwise.
   * @since 0.1.0
   */
  void SetObject(bool isObject) noexcept;

  /**
   * Sets the render depth of the tile.
   *
   * @param depth the render depth value that will be used.
   * @since 0.1.0
   */
  void SetDepth(int depth) noexcept;

  /**
   * Sets the ID that should be associated with the tile. Note, this value should be unique
   * for the tile!
   *
   * @param id the ID that will be associated with the tile.
   * @since 0.1.0
   */
  void SetId(TileID id) noexcept;

  /**
   * Sets the animation that will be used by the tile.
   *
   * @param animation the animation that will be used.
   * @since 0.1.0
   */
  void SetAnimation(const TileAnimation& animation) noexcept;

  /**
   * Sets the hitbox of the tile.
   *
   * @param hitbox the hitbox that will be used.
   * @since 0.1.0
   */
  void SetHitbox(const Rectangle& hitbox) noexcept;

  /**
   * Indicates whether or not the tile is blocked.
   *
   * @return true if the tile is blocked; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool IsBlocked() const noexcept;

  /**
   * Indicates whether or not the tile is animated.
   *
   * @return true if the tile is animated; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool IsAnimated() const noexcept;

  /**
   * Indicates whether or not the tile is an "object".
   *
   * @return true if the tile represents an object; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool IsObject() const noexcept;

  /**
   * Returns the render depth of the tile.
   *
   * @return the render depth of the tile.
   * @since 0.1.0
   */
  [[nodiscard]] int GetDepth() const noexcept;

  /**
   * Returns the tile ID that will be used for rendering the tile. If the tile isn't animated,
   * the returned will always the same as Tile::GetId().
   *
   * @return the tile ID that will be used for rendering the tile.
   * @since 0.1.0
   */
  [[nodiscard]] TileID GetFrameId() const;

  /**
   * Returns the type ID the tile.
   *
   * @return the type ID the tile.
   * @since 0.1.0
   */
  [[nodiscard]] TileID GetId() const noexcept;

  /**
   * Returns a reference to the associated image.
   *
   * @return a reference to the associated image.
   * @since 0.1.0
   */
  [[nodiscard]] Image& GetImage() const noexcept;

};

}
