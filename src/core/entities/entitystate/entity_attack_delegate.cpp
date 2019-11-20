#include "entity_attack_delegate.h"
#include "objects.h"
#include "entity_sheet.h"
#include "entity_draw_delegate.h"

namespace wanderer::core {

EntityAttackDelegate::EntityAttackDelegate(IEntity* entity, IEntityStateMachine* parent) {
  this->entity = Objects::RequireNonNull(entity);
  this->parent = Objects::RequireNonNull(parent);
}

EntityAttackDelegate::~EntityAttackDelegate() = default;

void EntityAttackDelegate::Draw(visuals::Renderer& renderer, const Viewport& viewport) const {
  auto srcX = entity->GetAnimationFrame() * 64;
  auto srcY = EntitySheet::GetSourceY(0, entity->GetDominantDirection());
  EntityDrawDelegate::Draw(renderer, viewport, *entity, srcX, srcY);
}

void EntityAttackDelegate::Enter(const IGame& game) {
  entity->Stop();

  // TODO determine what kind of animation to use from the entity's weapon
  entity->SetAnimationFrameAmount(7);
  entity->SetAnimationFrame(0);
  entity->SetAnimationDelay(65);

  game.PlaySound("swing");
}

void EntityAttackDelegate::Exit(const IGame& game) {}

void EntityAttackDelegate::Tick(const IGame& game, float delta) {
  entity->UpdateAnimation();
  if (entity->IsAnimationDone()) {

    // TODO damage and stuff...

    parent->SetState(EntityStateID::IDLE, game);
  }
}

}