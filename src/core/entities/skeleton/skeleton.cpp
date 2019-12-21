#include "skeleton.h"
#include "skeleton_state_machine.h"
#include "tile.h"
#include "image.h"
#include "renderer.h"
#include "viewport.h"
#include "wanderer_core.h"
#include "objects.h"

namespace albinjohansson::wanderer {

Skeleton::Skeleton(const std::shared_ptr<Image>& sheet) : AbstractEntity(sheet) {
  stateMachine = std::make_unique<SkeletonStateMachine>(this);
}

Skeleton::~Skeleton() = default;

void Skeleton::Draw(Renderer& renderer, const Viewport& viewport) const {
  stateMachine->Draw(renderer, viewport);
}

void Skeleton::Tick(IWandererCore& core, float delta) {
  AbstractEntity::Tick(core, delta);
  stateMachine->Tick(core, delta);
}

}