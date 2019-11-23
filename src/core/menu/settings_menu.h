#pragma once
#include "abstract_menu.h"
#include "menu_state_machine.h"
#include <memory>

namespace albinjohansson::wanderer {

class SettingsMenu final : public AbstractMenu {
 public:
  explicit SettingsMenu(IMenuStateMachine* parent);

  ~SettingsMenu() noexcept override;

  static IMenu_uptr Create(IMenuStateMachine* parent);

  void Draw(Renderer& renderer, const Viewport& viewport) const override;

  void HandleInput(const Input& input) noexcept override;

  [[nodiscard]] inline bool IsBlocking() const noexcept override { return true; }
};

}
