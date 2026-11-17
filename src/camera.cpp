//
// The Rogue 20 Project
// (C) 2026 Alessio Saltarin
//
//  This software is licensed unser ISC
//  (see LICENSE)
//


#include "camera.h"

#include <algorithm>

#include "config.h"

namespace rogue20 {

void Camera::update(float targetX, float targetY, float targetSize) {
    if (targetX - x_ < kCameraMargin) {
        x_ = targetX - kCameraMargin;
    } else if ((targetX + targetSize) - x_ > kWindowWidth - kCameraMargin) {
        x_ = (targetX + targetSize) - (kWindowWidth - kCameraMargin);
    }

    if (targetY - y_ < kCameraMargin) {
        y_ = targetY - kCameraMargin;
    } else if ((targetY + targetSize) - y_ > kWindowHeight - kCameraMargin) {
        y_ = (targetY + targetSize) - (kWindowHeight - kCameraMargin);
    }

    x_ = std::clamp(x_, 0.0f, static_cast<float>(kWorldWidth - kWindowWidth));
    y_ = std::clamp(y_, 0.0f, static_cast<float>(kWorldHeight - kWindowHeight));
}

}  // namespace rogue20
