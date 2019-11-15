#include "in_game_menu.h"
#include "objects.h"

using namespace wanderer::core;

namespace wanderer::visuals {

InGameMenu::InGameMenu(IMenuStateMachine* parent) {
  this->parent = Objects::RequireNonNull(parent);

}

InGameMenu::~InGameMenu() {

}

void InGameMenu::Draw(Renderer& renderer,
                      const wanderer::core::Viewport& viewport) const noexcept {

}

void InGameMenu::HandleInput(const wanderer::core::Input& input) noexcept {
  if (input.WasReleased(SDL_SCANCODE_ESCAPE)) {
    parent->SetMenu(MenuID::HOME); // TODO need to stop any player movement here
  }
}

}