#include "entity_idle_state.h"
#include "entity_state_machine.h"
#include "objects.h"
#include "vector_2.h"
#include "entity_sheet.h"

namespace wanderer::core {

EntityIdleState::EntityIdleState(IEntity* entity, IEntityStateMachine* parent) {
  this->entity = Objects::RequireNonNull(entity);
  this->parent = Objects::RequireNonNull(parent);
}

EntityIdleState::~EntityIdleState() = default;

void EntityIdleState::Tick(float delta) {
}

void EntityIdleState::HandleInput(const Input& input) {
  if (input.IsPressed(SDL_SCANCODE_D)
      || input.IsPressed(SDL_SCANCODE_A)
      || input.IsPressed(SDL_SCANCODE_W)
      || input.IsPressed(SDL_SCANCODE_S)) {
    parent->Change(EntityStateID::WALK);
    return;
  }

  // TODO attack...
}

void EntityIdleState::EnterState() {
}

void EntityIdleState::ExitState() {
}

void EntityIdleState::Draw(visuals::Renderer& renderer, const Viewport& viewport) const noexcept {
  float srcY = EntitySheet::GetSourceY(512, entity->GetDominantDirection());
  drawDelegate.Draw(renderer, viewport, *entity, 0, srcY);
}

}
