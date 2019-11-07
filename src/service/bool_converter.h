#pragma once
#include <SDL.h>

namespace wanderer::service {

/**
 * The BoolConverter class is a service for converting C++ boolean values to the
 * corresponding SDL_bool enum values.
 *
 * @since 0.0.1
 */
class BoolConverter final {
 public:
  BoolConverter() = delete;

  ~BoolConverter() = default;

  /**
   * Returns the corresponding SDL_bool value for the supplied boolean value.
   *
   * @param b the boolean value that will be converted.
   * @return the corresponding SDL_bool value for the supplied boolean value.
   * @since 0.0.1
   */
  [[nodiscard]] inline static SDL_bool Convert(bool b) noexcept {
    return (b) ? SDL_TRUE : SDL_FALSE;
  }
};

}  // namespace wanderer::service