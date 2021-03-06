#pragma once
#include "movable_object.h"
#include "animated.h"
#include "game_constants.h"

namespace albinjohansson::wanderer {

// TODO merchant, citizen, wizard, orc

/**
 * The IEntity interface is a subinterface of IMovableObject that specifies objects that are
 * "alive" in the game world.
 *
 * @see IMovableObject
 * @see IAnimated
 * @since 0.1.0
 */
class IEntity : public virtual IMovableObject, public virtual IAnimated {
 public:
  static constexpr float SIZE = tileSize * (7.0f / 3.0f); // FIXME maybe use distinct w & h?

  ~IEntity() override = default;

  /**
   * Hurts the entity by the supplied damage amount.
   *
   * @param dmg the amount of damage that will be inflicted upon the entity.
   * @since 0.1.0
   */
  virtual void hurt(int dmg) noexcept = 0;

  /**
   * Returns the health of the entity.
   *
   * @return the health of the entity.
   * @since 0.1.0
   */
  [[nodiscard]]
  virtual int get_health() const noexcept = 0;

  /**
   * Indicates whether or not the entity is dead.
   *
   * @return true if the entity is dead; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]]
  virtual bool is_dead() const noexcept = 0;

};

}
