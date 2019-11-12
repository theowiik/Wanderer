#pragma once
#include "movable_object.h"
#include "vector_2.h"

namespace wanderer::core {

/**
 * The MovableObjectDelegate class is an implementation of the IGameObject interface that is meant
 * to be used as a delegate.
 *
 * @see IMovableObject
 * @since 0.1.0
 */
class MovableObjectDelegate final : public IMovableObject {
 private:
  Vector2 velocity;
  Vector2 currPosition;
  Vector2 prevPosition;
  Vector2 interpolatedPosition;
  float speed = 0;
  float width;
  float height;

 public:
  /**
   * @param width the width of the object.
   * @param height the height of the object.
   * @since 0.1.0
   */
  MovableObjectDelegate(float width, float height); // TODO should throw if bad dimensions?

  ~MovableObjectDelegate() override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) const noexcept override {
    /* do nothing */
  }

  void Tick(float delta) override { /* do nothing */ }

  void Move(Direction direction) noexcept override;

  void Stop(Direction direction) noexcept override;

  void Stop() noexcept override;

  void SavePosition() noexcept override;

  void Interpolate(float alpha) noexcept override;

  void AddX(float dx) noexcept override;

  void AddY(float dy) noexcept override;

  void SetX(float x) noexcept override;

  void SetY(float y) noexcept override;

  void SetSpeed(float speed) noexcept override;

  [[nodiscard]] float GetX() const noexcept override;

  [[nodiscard]] float GetY() const noexcept override;

  [[nodiscard]] inline float GetWidth() const noexcept override { return width; }

  [[nodiscard]] inline float GetHeight() const noexcept override { return height; }

  [[nodiscard]] Rectangle GetHitbox() const noexcept override;

  [[nodiscard]] inline Vector2 GetVelocity() const noexcept override { return velocity; }

  [[nodiscard]] inline Vector2 GetPosition() const noexcept override { return currPosition; }

  [[nodiscard]] inline Vector2 GetInterpolatedPosition() const noexcept override {
    return interpolatedPosition;
  }
};

}
