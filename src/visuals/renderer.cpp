#include "renderer.h"
#include "objects.h"
#include "bool_converter.h"
#include <SDL_log.h>

using namespace wanderer::core;
using namespace wanderer::service;

namespace wanderer::visuals {

Renderer::Renderer(SDL_Renderer* renderer) {
  this->renderer = Objects::RequireNonNull(renderer);
}

Renderer::Renderer(SDL_Window* window) {
  Objects::RequireNonNull(window);
  Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  renderer = SDL_CreateRenderer(window, -1, flags);
}

Renderer::~Renderer() {
  if (renderer != nullptr) {
    SDL_DestroyRenderer(renderer);
  }
}

void Renderer::Clear() noexcept { SDL_RenderClear(renderer); }

void Renderer::Present() noexcept { SDL_RenderPresent(renderer); }

void Renderer::RenderTexture(SDL_Texture* texture, int x, int y) noexcept {
  if (texture != nullptr) {
    int width = 0;
    int height = 0;

    // TODO check if OK
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    SDL_Rect dst = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
  }
}

void Renderer::RenderTexture(SDL_Texture* texture, int x, int y, int width,
                             int height) noexcept {
  if ((texture != nullptr) && (width > 0) && (height > 0)) {
    SDL_Rect dst = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
  }
}

void Renderer::RenderTexture(SDL_Texture* texture,
                             float x,
                             float y,
                             float width,
                             float height) noexcept {
  if ((texture != nullptr) && (width > 0) && (height > 0)) {
    SDL_FRect dst = {x, y, width, height};
    SDL_RenderCopyF(renderer, texture, nullptr, &dst);
  }
}

void Renderer::RenderTexture(SDL_Texture* texture,
                             const core::Rectangle& s,
                             const core::Rectangle& d) noexcept {
  if (texture != nullptr) {
    SDL_Rect src = s.ToSdlRect();
    SDL_FRect dst = {d.GetX(), d.GetY(), d.GetWidth(), d.GetHeight()};
    SDL_RenderCopyF(renderer, texture, &src, &dst);
  }
}

void Renderer::RenderFillRect(float x, float y, float width, float height) noexcept {
  if ((width > 0) && (height > 0)) {
    SDL_FRect rect = {x, y, width, height};
    SDL_RenderFillRectF(renderer, &rect);
  }
}

void Renderer::RenderFillRect(int x, int y, int width, int height) noexcept {
  if ((width > 0) && (height > 0)) {
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderFillRect(renderer, &rect);
  }
}

void Renderer::RenderRect(float x, float y, float width, float height) noexcept {
  if ((width > 0) && (height > 0)) {
    SDL_FRect rect = {x, y, width, height};
    SDL_RenderDrawRectF(renderer, &rect);
  }
}

void Renderer::RenderRect(int x, int y, int width, int height) noexcept {
  if ((width > 0) && (height > 0)) {
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderDrawRect(renderer, &rect);
  }
}

void Renderer::SetColor(Uint8 red, Uint8 green, Uint8 blue,
                        Uint8 alpha) noexcept {
  SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
}

void Renderer::SetColor(Uint8 red, Uint8 green, Uint8 blue) noexcept {
  SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
}

void Renderer::SetViewport(const core::Rectangle& viewport) noexcept {
  SDL_Rect rect = viewport.ToSdlRect();
  SDL_RenderSetViewport(renderer, &rect);
}

void Renderer::SetScale(float xScale, float yScale) noexcept {
  SDL_RenderSetScale(renderer, xScale, yScale);
}

void Renderer::SetLogicalSize(float width, float height) noexcept {
  int result = SDL_RenderSetLogicalSize(renderer,
                                        static_cast<int>(width),
                                        static_cast<int>(height));
  if (result != 0) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                   SDL_LOG_PRIORITY_WARN,
                   "Failed to set logical size! %s",
                   SDL_GetError());
  }
}

void Renderer::SetLogicalIntegerScale(bool useLogicalIntegerScale) noexcept {
  SDL_RenderSetIntegerScale(renderer, BoolConverter::Convert(useLogicalIntegerScale));
}

int Renderer::GetLogicalWidth() const noexcept {
  int w = 0;
  SDL_RenderGetLogicalSize(renderer, &w, nullptr);
  return w;
}

int Renderer::GetLogicalHeight() const noexcept {
  int h = 0;
  SDL_RenderGetLogicalSize(renderer, nullptr, &h);
  return h;
}

}  // namespace wanderer::visuals