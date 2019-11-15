#pragma once
#include "menu_state_machine.h"
#include <map>

namespace wanderer::core {

/**
 * The MenuStateMachineImpl class is an implementation of the IMenuStateMachine interface.
 *
 * @see IMenuStateMachine
 * @since 0.1.0
 */
class MenuStateMachineImpl final : public IMenuStateMachine {
 private:
  std::map<MenuID, IMenu_sptr> menus;
  IMenu_sptr activeMenu = nullptr;

 public:
  MenuStateMachineImpl();

  ~MenuStateMachineImpl() override;

  static IMenuStateMachine_uptr Create();

  void Draw(visuals::Renderer& renderer, const core::Viewport& viewport) const noexcept override;

  void HandleInput(const Input& input) noexcept override;

  bool IsBlocking() const noexcept override;

  void SetMenu(MenuID id) noexcept override;
};

}