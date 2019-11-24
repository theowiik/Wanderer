#include "player_idle_state.h"
#include "entity_state_machine.h"

namespace albinjohansson::wanderer {

PlayerIdleState::PlayerIdleState(IEntityStateMachine* parent)
    : idleDelegate(EntityIdleDelegate(parent)) {}

PlayerIdleState::~PlayerIdleState() = default;

void PlayerIdleState::HandleInput(const Input& input, const ILevel& level) {
  if (input.IsPressed(SDL_SCANCODE_D)
      || input.IsPressed(SDL_SCANCODE_A)
      || input.IsPressed(SDL_SCANCODE_W)
      || input.IsPressed(SDL_SCANCODE_S)) {
    idleDelegate.GetParent().SetState(EntityStateID::WALK, level);
  } else if (input.IsPressed(SDL_SCANCODE_SPACE)) {
    idleDelegate.GetParent().SetState(EntityStateID::ATTACK, level);
  } else if (input.IsPressed(SDL_SCANCODE_U)) {
    idleDelegate.GetParent().SetState(EntityStateID::DIE, level);
  }

  // TODO attack...
}

}
