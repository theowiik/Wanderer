#include "wanderer_core_impl.h"
#include "menu_state_machine_impl.h"
#include "world_level.h"
#include "player_impl.h"
#include "tiled_map_parser.h"
#include <fstream>
#include <memory>

namespace albinjohansson::wanderer {

WandererCoreImpl::WandererCoreImpl(ImageGenerator& imageGenerator) {
  menuStateMachine = MenuStateMachineImpl::Create(this); // TODO fix "this" parameter

  player = std::make_unique<PlayerImpl>(imageGenerator.Load("resources/img/player2.png"));
  player->SetSpeed(230);
  player->SetX(750);
  player->SetY(1900);

  soundEngine = std::make_unique<SoundEngine>();
  LoadSounds();

  TiledMapParser parser(imageGenerator, "resources/map/world/world_demo.tmx");
  level = std::make_unique<WorldLevel>(parser.GetMap(), player, soundEngine, imageGenerator);

  // TODO listener for viewport dimensions
  viewport.SetLevelWidth(static_cast<float>(level->GetWidth()));
  viewport.SetLevelHeight(static_cast<float>(level->GetHeight()));
  viewport.SetWidth(1280); // FIXME hardcoded
  viewport.SetHeight(720); // FIXME hardcoded

  viewport.Center(player->GetX(),
                  player->GetY(),
                  {player->GetWidth(), player->GetHeight()});
}

WandererCoreImpl::~WandererCoreImpl() = default;

void WandererCoreImpl::LoadSounds() {
  try {
    std::ifstream infile("resources/audio/sfx.txt");
    std::string line;
    while (std::getline(infile, line)) {
      auto i = line.find(';');
      std::string id = line.substr(0, i);
      std::string path = line.substr(i + 1);
      soundEngine->Register(id, SoundEffect::Create(path));
    }
  } catch (std::exception& e) {
    SDL_Log("Failed to load sound effects! Error: %s", e.what());
  }
}

void WandererCoreImpl::HandleInput(const Input& input) {
  menuStateMachine->HandleInput(input);
  if (!menuStateMachine->GetMenu().IsBlocking()) {
    player->HandleInput(input, *level);
  }
}

void WandererCoreImpl::Update(float delta) {
  if (!menuStateMachine->GetMenu().IsBlocking()) {
    level->Update(viewport, delta);

    auto[ix, iy] = player->GetInterpolatedPosition();
    viewport.Track(ix, iy, {player->GetWidth(), player->GetHeight()}, delta);
  }
}

void WandererCoreImpl::Render(Renderer& renderer, float alpha) {
  level->Render(renderer, viewport, alpha);
  menuStateMachine->Draw(renderer, viewport);
}

void WandererCoreImpl::SetViewportWidth(float width) {
  viewport.SetWidth(width);
}

void WandererCoreImpl::SetViewportHeight(float height) {
  viewport.SetHeight(height);
}

void WandererCoreImpl::Quit() noexcept {
  shouldQuit = true;
}

}