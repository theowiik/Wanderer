#pragma once
#include "wanderer_controller.h"
#include "wanderer_core.h"
#include "renderer.h"
#include "window.h"
#include "key_state_manager.h"
#include "mouse_state_manager.h"
#include "game_loop.h"

namespace albinjohansson::wanderer {

/**
 * The WandererControllerImpl class is an implementation of the IWandererController interface.
 *
 * @since 0.1.0
 */
class WandererControllerImpl final : public IWandererController {
 private:
  // 1280x720, 1366x768, 1600x900
  static constexpr float LOGICAL_WIDTH = 1280;
  static constexpr float LOGICAL_HEIGHT = 720;

  IWandererCore_uptr core = nullptr;
  Window_uptr window = nullptr;
  Renderer_sptr renderer = nullptr;

  KeyStateManager_sptr keyStateManager = nullptr;
  MouseStateManager_sptr mouseStateManager = nullptr;

  IGameLoop_uptr gameLoop = nullptr;

  /**
   * @throws BadStateException if the desktop dimensions cannot be deduced.
   * @since 0.1.0
   */
  WandererControllerImpl();

 public:
  /**
   * Creates and returns a unique pointer to an IWandererController instance.
   *
   * @throws BadStateException if the desktop dimensions cannot be deduced.
   * @since 0.1.0
   */
  friend IWandererController_uptr CreateController();

  ~WandererControllerImpl() override;

  void Run() override;
};

}
