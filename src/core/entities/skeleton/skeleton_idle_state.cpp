#include "skeleton_idle_state.h"
#include "entity_state_machine.h"
#include "player.h"
#include "skeleton.h"
#include "wanderer_core.h"
#include "time_utils.h"

using namespace centurion;

namespace albinjohansson::wanderer {

SkeletonIdleState::SkeletonIdleState(IEntityStateMachine* parent)
    : idleDelegate{parent} {}

SkeletonIdleState::~SkeletonIdleState() = default;

void SkeletonIdleState::tick(const IWandererCore& core, float /*delta*/) {

  auto& entity = idleDelegate.GetParent().get_entity();
  float distance = entity.get_position().distance_to(core.get_player().get_position());

  if (distance <= Skeleton::HOMING_RANGE || (TimeUtils::get_millis() - enterTime) >= 2000) {
    idleDelegate.GetParent().set_state(EntityStateID::Walk, core);
  }
}

void SkeletonIdleState::draw(const Renderer& renderer, const Viewport& viewport) const {
  idleDelegate.draw(renderer, viewport);
}

void SkeletonIdleState::enter(const IWandererCore& core) {
  idleDelegate.enter(core);
  enterTime = TimeUtils::get_millis();
}

void SkeletonIdleState::exit(const IWandererCore& core) {
  idleDelegate.exit(core);
}

}
