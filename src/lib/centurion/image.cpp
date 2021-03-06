#include "image.h"
#include "require.h"
#include "centurion_exception.h"
#include <SDL_image.h>
#include <sstream>

using namespace albinjohansson::wanderer;

namespace centurion {

Image::Image(SDL_Renderer* renderer, const std::string& path) {
  Require::not_null(renderer);
  texture = IMG_LoadTexture(renderer, path.c_str());
  if (!texture) {
    throw CenturionException("Failed to load image from " + path);
  }
}

Image::Image(SDL_Texture* texture) {
  this->texture = Require::not_null(texture);
}

Image::Image(SDL_Renderer* renderer, SDL_Surface* surface) {
  Require::not_null(renderer);
  Require::not_null(surface);

  this->texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (!texture) {
    throw CenturionException("Failed to create image from surface!");
  }
}

Image::~Image() {
  SDL_DestroyTexture(texture);
}

void Image::set_alpha(uint8_t alpha) noexcept {
  SDL_SetTextureAlphaMod(texture, alpha);
}

uint32_t Image::get_format() const noexcept {
  uint32_t format = 0;
  SDL_QueryTexture(texture, &format, nullptr, nullptr, nullptr);
  return format;
}

int Image::get_access() const noexcept {
  int access = 0;
  SDL_QueryTexture(texture, nullptr, &access, nullptr, nullptr);
  return access;
}

int Image::get_width() const noexcept {
  int width = 0;
  SDL_QueryTexture(texture, nullptr, nullptr, &width, nullptr);
  return width;
}

int Image::get_height() const noexcept {
  int height = 0;
  SDL_QueryTexture(texture, nullptr, nullptr, nullptr, &height);
  return height;
}

SDL_Texture* Image::get_texture() noexcept {
  return texture;
}

std::string Image::to_string() const {
  std::ostringstream address;
  address << static_cast<void const*>(this);

  auto w = std::to_string(get_width());
  auto h = std::to_string(get_height());

  return "(Image@" + address.str() + " | Width: " + w + ", Height: " + h + ")";
}

Image::operator SDL_Texture*() const noexcept {
  return texture;
}

Image::operator std::string() {
  return to_string();
}

}