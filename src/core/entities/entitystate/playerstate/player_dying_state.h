#pragma once
#include "player_state.h"
#include "entity.h"
#include "entity_state_machine.h"
#include "entity_dying_delegate.h"

namespace albinjohansson::wanderer {

/**
 * The PlayerDyingState class is an implementation of the IPlayerState interface that represents
 * the state of the player when dying.
 *
 * @see IPlayerState
 * @since 0.1.0
 */
class PlayerDyingState final : public IPlayerState {
 private:
  EntityDyingDelegate dyingDelegate;

 public:
  /**
   * @param entity a pointer to the associated entity.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit PlayerDyingState(IEntity* entity);

  ~PlayerDyingState() override;

  void HandleInput(const Input& input, const IWandererCore& core) override;

  void Draw(Renderer& renderer, const Viewport& viewport) const override;

  void Tick(const IWandererCore& core, float delta) override;

  void Enter(const IWandererCore& core) override;

  // TODO game over stuff
  void Exit(const IWandererCore& core) override;
};

}
