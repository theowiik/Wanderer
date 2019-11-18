#pragma once
#include "player_state.h"
#include "entity_state_machine.h"
#include "entity_move_delegate.h"
#include "entity.h"

namespace wanderer::core {

class PlayerMovingState final : public IPlayerState {
 private:
  IEntity* entity = nullptr;
  IEntityStateMachine* parent = nullptr;
  EntityMoveDelegate moveDelegate;
  bool areMoveKeysDown = false;

  void CheckPressed(const Input& input);

  void CheckReleased(const Input& input);

 public:
  /**
   * @param entity a pointer to the associated entity instance.
   * @param parent a pointer to the parent entity state machine.
   * @throws NullPointerException if any pointers are pointer null.
   * @since 0.1.0
   */
  PlayerMovingState(IEntity* entity, IEntityStateMachine* parent);

  ~PlayerMovingState() override;

  void HandleInput(const Input& input) override;

  inline void Draw(visuals::Renderer& renderer, const Viewport& viewport) noexcept override {
    moveDelegate.Draw(renderer, viewport);
  }

  inline void Tick(float delta) override { moveDelegate.Tick(delta); }

  inline void Enter() override { moveDelegate.Enter(); }

  inline void Exit() override { moveDelegate.Exit(); }
};

}
