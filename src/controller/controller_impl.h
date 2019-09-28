#pragma once
#include "controller.h"
#include "model.h"
#include "view.h"
#include <memory>
#include <ctn_window_interface.h>
#include <ctn_input_dispatcher.h>

namespace wanderer::controller {

/**
 * The ControllerImpl class is an implementation of the IController interface.
 *
 * @since 0.1.0
 */
class ControllerImpl final : public IController {
 private:
  model::IModel_sptr model;
  view::IView_uptr view;
  centurion::visuals::IWindow_uptr window;
  centurion::input::InputDispatcher_uptr inputDispatcher;
  bool running = false;

  /**
   * @param model a shared pointer to the associated model instance.
   * @param view a unique pointer to the associated view instance.
   * @param window a unique pointer to the associated parent window instance.
   * @throws invalid_argument if any of the supplied arguments are nullptr.
   * @since 0.1.0
   */
  ControllerImpl(model::IModel_sptr model,
                 view::IView_uptr view,
                 centurion::visuals::IWindow_uptr window);

  void InitFonts();

 public:
  ~ControllerImpl() override;

  ControllerImpl(const ControllerImpl& model) = delete;

  ControllerImpl& operator=(const ControllerImpl& model) = delete;

  /**
   * Creates and returns a unique pointer to an IController instance.
   *
   * @param model a shared pointer to the associated IModel instance, may not be nullptr.
   * @param view a unique pointer to the associated IView instance, may not be nullptr.
   * @param window a unique pointer to the associated parent window instance.
   * @return a unique pointer to an IController instance.
   * @throws invalid_argument if any of the supplied arguments are nullptr.
   * @since 0.1.0
   */
  friend IController_uptr CreateController(model::IModel_sptr model,
                                           view::IView_uptr view,
                                           centurion::visuals::IWindow_uptr window);

  void Run() override;

  void Exit() override;

  void MovePlayer(model::Direction direction) override;

  void StopPlayer(model::Direction direction) override;

};

} // namespace wanderer::controller