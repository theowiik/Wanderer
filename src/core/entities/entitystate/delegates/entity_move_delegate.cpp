#include "entity_move_delegate.h"
#include "entity_state_machine.h"
#include "entity_draw_delegate.h"
#include "entity_sheet.h"
#include "entity.h"
#include "wanderer_core.h"
#include "require.h"
#include "tile_map.h"

using namespace centurion;

namespace albinjohansson::wanderer {

EntityMoveDelegate::EntityMoveDelegate(IEntityStateMachine* parent) {
  this->parent = Require::NotNull(parent);
}

EntityMoveDelegate::~EntityMoveDelegate() = default;

void EntityMoveDelegate::Draw(const Renderer& renderer, const Viewport&) const {
  IEntity& entity = parent->GetEntity();

  auto srcX = entity.get_velocity().IsZero() ? 0 : entity.GetAnimationFrame() * 64;
  auto srcY = EntitySheet::GetSourceY(512, entity.get_dominant_direction());
  EntityDrawDelegate::Draw(renderer, entity, srcX, srcY);
}

void EntityMoveDelegate::Tick(const IWandererCore&, float delta) {
  UpdateAnimation();
  UpdatePosition(delta);
}

void EntityMoveDelegate::Enter(const IWandererCore&) {
  IEntity& entity = parent->GetEntity();

  entity.SetAnimationFrame(0);
  entity.SetAnimationFrameAmount(9);
  entity.SetAnimationDelay(60);
}

void EntityMoveDelegate::Exit(const IWandererCore&) {}

void EntityMoveDelegate::UpdateAnimation() {
  parent->GetEntity().UpdateAnimation();
}

void EntityMoveDelegate::UpdatePosition(float delta) {
  auto& entity = parent->GetEntity();
  auto[velocityX, velocityY] = entity.get_velocity();
  entity.add_x(velocityX * delta);
  entity.add_y(velocityY * delta);
}

IEntityStateMachine& EntityMoveDelegate::GetParent() noexcept { return *parent; }

}
