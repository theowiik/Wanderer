#include "player_state_machine_impl.h"
#include "player_moving_state.h"
#include "player_idle_state.h"
#include "player_attack_state.h"
#include "player_dying_state.h"

using namespace wanderer::visuals;

namespace wanderer::core {

PlayerStateMachineImpl::PlayerStateMachineImpl(IEntity* entity)
    : AbstractEntityStateMachine(entity) {
  Put(EntityStateID::IDLE, std::make_unique<PlayerIdleState>(this));
  Put(EntityStateID::DIE, std::make_unique<PlayerDyingState>(entity));
  Put(EntityStateID::WALK, std::make_unique<PlayerMovingState>(this));
  Put(EntityStateID::ATTACK, std::make_unique<PlayerAttackState>(this));
}

PlayerStateMachineImpl::~PlayerStateMachineImpl() = default;

IPlayerStateMachine_uptr PlayerStateMachineImpl::Create(IEntity* entity) {
  return std::make_unique<PlayerStateMachineImpl>(entity);
}

void PlayerStateMachineImpl::HandleInput(const Input& input, const IGame& game) {
  GetActiveState().HandleInput(input, game);
}

}