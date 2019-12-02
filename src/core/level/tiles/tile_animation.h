#pragma once
#include "tile_id.h"
#include "rectangle.h"
#include <unordered_map>

namespace albinjohansson::wanderer {

struct Frame {
  TileID frameId = 0;
  uint32_t duration = 100;
};

class TileAnimation final {
 private:
  std::unordered_map<int, Frame> frames;
  int nFrames = 1;
  int index = 0;
  uint32_t previous = 0;

 public:
  explicit TileAnimation(int nFrames);

  ~TileAnimation();

  void Update();

  void SetFrame(int index, Frame frame);

  [[nodiscard]] Frame GetFrame() const {
    return frames.at(index);
  }

};

}